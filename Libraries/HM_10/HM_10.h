#ifndef _HM_10_H
#define _HM_10_H

#include "Arduino.h"
#include <SoftwareSerial.h>

#define REPLY_SIZE 30

class HM_10 : public SoftwareSerial
{
	public:
		HM_10(byte rxpin, byte txpin, byte keypin, byte statepin);
		void atKey(bool mode);
		bool connected();
		void readLine();
		
		void atTEST();					// Test Command
		void atADDR();					// Query module address
		void atADVI(char P1 = '?');		// Query/Set Advertising interval P1:[0,F] *Hex Char*
		void atADTY(char P1 = '?');		// Query/Set Advertising Type P1:[0,3]
		void atBATC(char P1 = '?');		// Set battery monitor switch P1:[0,1]
		void atBATT();					// Query battery information
		void atBAUD(char P1 = '?');		// Query/Set baud rate P1:[0,8]
		void atCLEAR();					// Clear Last Connected device address
		void atCONNL();					// Try connect to last succeeded device
		void atCO(char P0, char * P1);	// Try connect an address P0:{N, 0, 1, 2}, P1:[MAC Address]
		void atDISC();					// Start a device discovery scan
		void atCONN(byte P1);			// Connect to an Discovery device P1:[0,5]
		void atERASE();					// Remove bond information
		void atHELP();					// System Help Information
		void atIMME(char P1 = '?');		// Query/Set Module work type P1:[0,1]
		void atMODE(char P1 = '?');		// Query/Set Module Work Mode P1:[0,2]
		void atNOTI(char P1 = '?');		// Query/Set Notify information
		void atNOTP(char P1 = '?');		// Query/Set notify mode
		void atNAME();					//
		void atNAME(char * P1);			//
		void atPIO1(char P1 = '?');		//
		void atPASS();					//
		void atPOWE(char P1 = '?');		//
		void atPWRM(char P1 = '?');		//
		void atRENEW();					//
		void atRESET();					// Restart module
		void atROLE(char P1 = '?');		// Query/Set Master and Slaver Role
		void atRADD();					//
		void atRAT(char P1 = '?');		//
		void atSTART();					//
		void atSLEEP();					//
		void atSAVE(char P1 = '?');		//
		void atSHOW(char P1 = '?');		//
		void atTCON(char P1 = '?');		//
		void atTYPE(char P1 = '?');		//
		void atVERS();					// Query Software Version
		
		// ? = 0x3F = 63 = 0011 1111b
	private:
		byte _keyPin;
		byte _statePin;
		// char reply[REPLY_SIZE];
		
		// void clearReply();
};

#endif /* not defined _HM_10_H */