// Include required libraries
#include <Arduino.h>
#include <esp_camera.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <I2S.h>

// Define camera model & pinout
#define CAMERA_MODEL_XIAO_ESP32S3  // Has PSRAM
#include "camera_pins.h"

// Audio record time setting (in seconds, max value 240)
#define RECORD_TIME 10

// Audio settings
#define SAMPLE_RATE 16000U
#define SAMPLE_BITS 16
#define WAV_HEADER_SIZE 44
#define VOLUME_GAIN 3

// Camera status variable
bool camera_status = false;

// MicroSD status variable
bool sd_status = false;

// File Counter
int fileCount = 1;

// Touch Switch variables
int threshold = 1500;  // Adjust if not responding properly
bool touch1detected = false;


unsigned long startTime;
bool firstRecordingDone = false;
bool secondRecordingDone = false;

// Save pictures to SD card
void photo_save(const char *fileName) {
  // Take a photo
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Failed to get camera frame buffer");
    return;
  }
  // Save photo to file
  writeFile(SD, fileName, fb->buf, fb->len);

  // Release image buffer
  esp_camera_fb_return(fb);

  Serial.println("Photo saved to file");
}

// SD card write file
void writeFile(fs::FS &fs, const char *path, uint8_t *data, size_t len) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.write(data, len) == len) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void record_wav(String audiofile) {
  uint32_t sample_size = 0;
  uint32_t record_size = (SAMPLE_RATE * SAMPLE_BITS / 8) * RECORD_TIME;
  uint8_t *rec_buffer = NULL;
  Serial.printf("Recording Sound...\n");

  File file = SD.open(audiofile, FILE_WRITE);
  // Write the header to the WAV file
  uint8_t wav_header[WAV_HEADER_SIZE];
  generate_wav_header(wav_header, record_size, SAMPLE_RATE);
  file.write(wav_header, WAV_HEADER_SIZE);

  // PSRAM malloc for recording
  rec_buffer = (uint8_t *)ps_malloc(record_size);
  if (rec_buffer == NULL) {
    Serial.printf("Malloc failed!\n");
    while (1)
      ;
  }
  Serial.printf("Buffer: %d bytes\n", ESP.getPsramSize() - ESP.getFreePsram());


  // Start recording
  esp_i2s::i2s_read(esp_i2s::I2S_NUM_0, rec_buffer, record_size, &sample_size, portMAX_DELAY);
  if (sample_size == 0) {
    Serial.printf("Record Failed!\n");
  } else {
    Serial.printf("Record %d bytes\n", sample_size);
  }

  // Increase volume
  for (uint32_t i = 0; i < sample_size; i += SAMPLE_BITS / 8) {
    (*(uint16_t *)(rec_buffer + i)) <<= VOLUME_GAIN;
  }

  // Write data to the WAV file
  Serial.printf("Writing to the file ...\n");
  if (file.write(rec_buffer, record_size) != record_size)
    Serial.printf("Write file Failed!\n");

  free(rec_buffer);
  file.close();
  Serial.printf("The sound recording has finished.\n");
}

void generate_wav_header(uint8_t *wav_header, uint32_t wav_size, uint32_t sample_rate) {
  // See this for reference: http://soundfile.sapp.org/doc/WaveFormat/
  uint32_t file_size = wav_size + WAV_HEADER_SIZE - 8;
  uint32_t byte_rate = SAMPLE_RATE * SAMPLE_BITS / 8;
  const uint8_t set_wav_header[] = {
    'R', 'I', 'F', 'F',                                                   // ChunkID
    file_size, file_size >> 8, file_size >> 16, file_size >> 24,          // ChunkSize
    'W', 'A', 'V', 'E',                                                   // Format
    'f', 'm', 't', ' ',                                                   // Subchunk1ID
    0x10, 0x00, 0x00, 0x00,                                               // Subchunk1Size (16 for PCM)
    0x01, 0x00,                                                           // AudioFormat (1 for PCM)
    0x01, 0x00,                                                           // NumChannels (1 channel)
    sample_rate, sample_rate >> 8, sample_rate >> 16, sample_rate >> 24,  // SampleRate
    byte_rate, byte_rate >> 8, byte_rate >> 16, byte_rate >> 24,          // ByteRate
    0x02, 0x00,                                                           // BlockAlign
    0x10, 0x00,                                                           // BitsPerSample (16 bits)
    'd', 'a', 't', 'a',                                                   // Subchunk2ID
    wav_size, wav_size >> 8, wav_size >> 16, wav_size >> 24,              // Subchunk2Size
  };
  memcpy(wav_header, set_wav_header, sizeof(set_wav_header));
}

// Callback function for touch switch
void gotTouch1() {
  touch1detected = true;
}

// Camera Parameters for setup
void CameraParameters() {
  // Define camera parameters
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG;
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if (config.pixel_format == PIXFORMAT_JPEG) {
    if (psramFound()) {
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

void setup() {
  // Start Serial Monitor, wait until port is ready
  Serial.begin(115200);
  while (!Serial)
    ;

  // I2S Setup and start
  I2S.setAllPins(-1, 42, 41, -1, -1);
  if (!I2S.begin(PDM_MONO_MODE, SAMPLE_RATE, SAMPLE_BITS)) {
    Serial.println("Failed to initialize I2S!");
    while (1)
      ;
  }

  // Attach touch switch to interrupt handler
  touchAttachInterrupt(T1, gotTouch1, threshold);

  // Define Camera Parameters and Initialize
  CameraParameters();

  // Camera is good, set status
  camera_status = true;
  Serial.println("Camera OK!");

  // Initialize the MicroSD card
  if (!SD.begin(21)) {
    Serial.println("Failed to mount MicroSD Card!");
    while (1)
      ;
  }

  // Determine what type of MicroSD card is mounted
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No MicroSD card inserted!");
    return;
  }

  // Print card type
  Serial.print("MicroSD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  // MicroSD is good, set status
  sd_status = true;
  startTime = millis();
}


void loop() {
  if (camera_status && sd_status) {
    unsigned long currentTime = millis();
    unsigned long elapsed = currentTime - startTime;

    // First recording after 5 seconds (5000ms)
    if (elapsed >= 5000 && !firstRecordingDone) {
      Serial.println("Starting first audio recording (10 seconds)...");
      char audioFileName[32];
      sprintf(audioFileName, "/record1.wav");
      record_wav(audioFileName);
      Serial.printf("Saved audio: %s\n", audioFileName);
      firstRecordingDone = true;
    }

    // Second recording + picture after 20 seconds
    if (elapsed >= 20000 && !secondRecordingDone) {
      Serial.println("Starting second audio recording (10 seconds)...");
      char audioFileName[32];
      sprintf(audioFileName, "/record2.wav");
      record_wav(audioFileName);
      Serial.printf("Saved audio: %s\n", audioFileName);

      Serial.println("Capturing picture...");
      char imageFileName[32];
      sprintf(imageFileName, "/image1.jpg");
      photo_save(imageFileName);
      Serial.printf("Saved picture: %s\n", imageFileName);

      secondRecordingDone = true;
    }
  }

  delay(50); // Small delay to avoid tight looping
}