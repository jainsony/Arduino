#include <ESP8266WiFi.h>
#include <espnow.h>

// MAC Address of your reciever board 
uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0xDD, 0xE3, 0xA2};
uint8_t debug_mode = 0;

#define datalen 4
#define threshold 5

int i = 0;

int a_speed = 0;
int b_speed = 0;

float Speed;
float Direction;

String dataString = ""; // variable to hold input data
int dataArray[datalen]; // array to hold parsed integers
int dataIndex = 0; // index for dataArray

const int buttonPin = D5;
int buttonState = 0;
int counter = 1;
// Define variables to store incoming readings
float FeedBackSpeed;
float FeedBackDirection;


const long interval = 100; 
unsigned long previousMillis = 0;    // 

// Variable to store if sending data was successful
String success;



/*
Below this I have created this simple data structure to carry data 
*/
typedef struct struct_message {
    float speed;
    float dir;
} struct_message;
/////

struct_message Data_structure;
struct_message incomingData;


void parseData();
void printData();