#ifndef _HUB_LIB_H
#define _HUB_LIB_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <LinkedList.h>
#include <SerialGSM.h>
#include <HM_10.h>

//=====[ PINS ]=================================================================
// HM-10 Pins
#define RX  2
#define TX  3
#define KEY  4
#define STATE  5

// Hub-B Pins
#define RX_B 6
#define TX_B 7
#define FLAG 11

// Switch Pin
#define MODE_SWITCH 8

// GSM Pins
#define RX_GSM 9
#define TX_GSM 10

// LED Pins
#define MODE_LED 12
#define BUSY_LED 13


//=====[ CONSTANTS ]============================================================
#define MAX_ADDRESSES 6
#define BUFF_SIZE 20
#define CMD_SIZE 3
#define DATA_SIZE 16

#define HUB_ID_SIZE 4
#define PHONE_SIZE 15
#define MAX_SENSORS 5
#define NAME_SIZE 12
#define ADDR_SIZE 12

#define MIN_CMD 0
#define MAX_CMD 26


//=====[ VARIABLES ]============================================================
char Buffer[BUFF_SIZE];  			// Serial buffer
char Command[CMD_SIZE];  			// Arbitrary Value for command size
char Data[DATA_SIZE];    			// Arbitrary Value for data size

char HubID[HUB_ID_SIZE];
char AlertPhone[PHONE_SIZE];  		// Notification phone number
char PortalPhone[PHONE_SIZE]; 		// Portal phone number

byte PortalFreq = 0;    			// Portal notification frequency (default = 0)
byte LoggingFreq = 0;   			// Sensor logging frequency (default = 0)

bool HubMode = false;
bool flagCheck = false;

int critTemp = 30;
int critHum = 50;

//=====[ CLASSES ]==============================================================
class Sensor
{
  public:
    char address[ADDR_SIZE + 1];
};


//=====[ OBJECTS ]==============================================================
SoftwareSerial SerialB(RX_B, TX_B);
HM_10 BTSerial(RX, TX, KEY, STATE);
SerialGSM cell(RX_GSM, TX_GSM);
LinkedList<Sensor*> SensorList =  LinkedList<Sensor*>();


//=====[ SUBROUTINES ]==========================================================
void BluetoothParser(void);
void clearAllBuffers();
void clearBuffer();

void sendSetupCommand(char * cmd, char * dest);
void sendCommand(char * cmd, char * dest);
void sendCommand(char * cmd);


void getHubID();
void setHubID();
void getSensorList();
void addSensor();
void removeSensor();
void removeAllSensors();
void getAlertPhone();
void setAlertPhone();
void getPortalPhone();
void setPortalPhone();
void getPortalFreq();
void setPortalFreq();





























#endif
