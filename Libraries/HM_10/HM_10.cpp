// HM_10 version 1.0
// by Luis Ramirez
#include <HM_10.h>




HM_10::HM_10(byte rxpin, byte txpin, byte keypin, byte statepin):
SoftwareSerial(rxpin,txpin)
{
	pinMode(statepin, INPUT_PULLUP);
	pinMode(keypin, INPUT);
	
	_keyPin = keypin;
	_statePin = statepin;
}

void HM_10::atKey(bool mode)
{
	digitalWrite(_keyPin, mode);
	delay(500);
}

bool HM_10::connected()
{
	delay(500);
	return digitalRead((int)_statePin);
}

void HM_10::readLine()
{
	delay(1000);
	#ifdef DEBUG
	while(this->available())
		Serial.write(this->read());
	Serial.println();
	#endif
	#ifndef DEBUG
	while(this->available())
		this->read();
	#endif
}

/* Test Command */
void HM_10::atTEST()
{
	this->write("AT");	
	this->flush();
	#ifdef DEBUG
	Serial.println(F("AT"));
	Serial.flush();
	#endif
	readLine();
}

/* Query module address */
void HM_10::atADDR()
{
	this->print(F("AT+ADDR?"));
	this->flush();
	
	Serial.println(F("AT+ADDR?"));
	Serial.flush();
	
	readLine();
}

/* Query/Set Advertising interval */
void HM_10::atADVI(char P1)
{
	this->print(F("AT+ADVI"));
	this->print(P1);
	this->flush();
	
	Serial.print(F("AT+ADVI"));
	Serial.println(P1);
	Serial.flush();
	
	readLine();
}

/* Query/Set Advertising Type */
void HM_10::atADTY(char P1)
{
	this->print(F("AT+ADTY"));
	this->print(P1);
	this->flush();
	Serial.print(F("AT+ADTY"));
	Serial.println(P1);
	
	readLine();
}

/* Query/Set battery monitor switch */
void HM_10::atBATC(char P1)
{
	this->print(F("AT+BATC"));
	this->print(P1);
	this->flush();
	Serial.print(F("AT+BATC"));
	Serial.println(P1);
	
	readLine();
}

/* Query battery information */
void HM_10::atBATT()
{
	this->print(F("AT+BATT?"));
	this->flush();
	Serial.println(F("AT+BATT?"));
	
	readLine();
}

/* Query/Set baud rate */
void HM_10::atBAUD(char P1)
{
	this->print(F("AT+BAUD"));
	this->print(P1);
	this->flush();
	
	Serial.print(F("AT+BAUD"));
	Serial.println(P1);
	
	readLine();
}

/* Clear Last Connected device address */
void HM_10::atCLEAR()
{
	this->print(F("AT+CLEAR"));
	this->flush();
	Serial.println(F("AT+CLEAR"));
	
	readLine();
}

/* Try connect to last succeeded device */
void HM_10::atCONNL()
{
	this->print(F("AT+CONNL"));
	Serial.println(F("AT+CONNL"));
	
	readLine();
}

/* Try connect an address */
void HM_10::atCO(char P0, char * P1)
{
	this->print(F("AT+CO"));
	this->print(P0);
	this->print(P1);
	this->flush();
	
	#ifdef DEBUG
	Serial.print(F("AT+CO"));
	Serial.print(P0);
	Serial.println(P1);
	#endif
	
	readLine();
	// Start Waiting 10 Seconds for Connection
	int i = 0, count = 0;
	while(i < 10 && count < 3)
	{
		if(this->connected())
		{
			count++;
			continue;
		}
		delay(500);
		i++;
	}
	readLine();
}

/* Start a device discovery scan */
void HM_10::atDISC() // May need to fix
{
	this->print(F("AT+DISC?"));
	Serial.print(F("AT+DISC?"));
	
	while(Serial.read() != '\n')
	{
		while(this->available())
			Serial.print(this->read());
	}
	
}

/* Connect to an Discovery device */
void HM_10::atCONN(byte P1)
{
	this->print(F("AT+CONN"));
	this->print(P1);
	this->flush();
	Serial.print(F("AT+CONN"));
	Serial.println(P1);
	
	readLine();
}

/* Remove bond information */
void HM_10::atERASE()
{
	this->print(F("AT+ERASE"));
	this->flush();
	Serial.println(F("AT+ERASE"));
	
	readLine();
}

/* System Help Information */
void HM_10::atHELP()
{
	this->print(F("AT+HELP?"));
	this->flush();
	Serial.println(F("AT+HELP?"));
	
	readLine();
}

/* Query/Set Module work type */
void HM_10::atIMME(char P1)
{
	this->print(F("AT+IMME"));
	this->print(P1);
	this->flush();
	#ifdef DEBUG
	Serial.print(F("AT+IMME"));
	Serial.println(P1);
	#endif
	readLine();
}

/* Query/Set Module Work Mode */
void HM_10::atMODE(char P1)
{
	this->print(F("AT+MODE"));
	this->print(P1);
	this->flush();
	Serial.print(F("AT+MODE"));
	Serial.println(P1);
	
	readLine();
}

/* Query/Set Notify information */
void HM_10::atNOTI(char P1)
{
	this->print(F("AT+NOTI"));
	this->print(P1);
	this->flush();
	
	Serial.print(F("AT+NOTI"));
	Serial.println(P1);
	Serial.flush();
	
	readLine();
}

/* Query/Set notify mode */
void HM_10::atNOTP(char P1)
{
	this->print(F("AT+NOTP"));
	this->print(P1);
	this->flush();
	
	Serial.print(F("AT+NOTP"));
	Serial.println(P1);
	Serial.flush();
	
	readLine();
}

void HM_10::atRESET()
{
	this->print(F("AT+RESET"));
	this->flush();
	#ifdef DEBUG
	Serial.println(F("AT+RESET"));
	#endif
	readLine();
}

void HM_10::atROLE(char P1)
{
	this->print(F("AT+ROLE"));
	this->print(P1);
	this->flush();
	
	#ifdef DEBUG
	Serial.print(F("AT+ROLE"));
	Serial.println(P1);
	#endif
	readLine();
}

void HM_10::atPOWE(char P1)
{
	this->print(F("AT+POWE"));
	this->print(P1);
	this->flush();
	Serial.print(F("AT+POWE"));
	Serial.println(P1);
	
	readLine();
}

/* Query Software Version */
void HM_10::atVERS()
{
	this->print(F("AT+VERS?"));
	this->flush();
	Serial.println(F("AT+VERS?"));
	
	readLine();
}






