// HC_05 version 1.0
// by Luis Ramirez
#include <HC_05.h>




HC_05::HC_05(byte rxpin, byte txpin, byte atpin, byte statepin):
SoftwareSerial(rxpin,txpin)
{
	verbose = false;
	_atPin = atpin;
	_statePin = statepin;
	
	pinMode(_statePin, INPUT);
	pinMode(_atPin, OUTPUT);
	digitalWrite(_atPin, LOW);
}

void HC_05::atMode(bool mode)
{
	digitalWrite(_atPin, mode);
	delay(500);
}

bool HC_05::connected()
{
	return(digitalRead(_statePin)?true:false);
}

void HC_05::atTest()	// 1
{
	this->print(F("AT\r\n"));
	if(verbose)
		Serial.println(F("AT"));
	delay(200);

	// char ByteCount = this->readBytesUntil('\n', response, 10);
	// Serial.println(response);
	// memset(response, 0, sizeof(response));
	// this->flush();
	
	readLine();
}

void HC_05::atRESET()	// 2
{
	this->print(F("AT+RESET\r\n"));
	if(verbose)
		Serial.println(F("AT+RESET"));
	delay(200);
	readLine();
}

void HC_05::atVERSION()	// 3
{
	this->print(F("AT+VERSION?\r\n"));
	if(verbose)
		Serial.println(F("AT+VERSION?"));
	delay(200);
	readLine();
}

void HC_05::atORGL()	// 4
{
	this->print(F("AT+ORGL\r\n"));
	if(verbose)
		Serial.println(F("AT+ORGL"));
	delay(200);
	readLine();
}

void HC_05::atADDR()	// 5
{
	this->print(F("AT+ADDR?\r\n"));
	if(verbose)
		Serial.println(F("AT+ADDR?"));
	delay(200);
	readLine();
}

void HC_05::atNAME()	// 6
{
	this->print(F("AT+NAME?\r\n"));
	if(verbose)
		Serial.println(F("AT+NAME?"));
	delay(200);
	readLine();
}

void HC_05::atNAME(char * name)
{
	this->print(F("AT+NAME="));
	this->print(name);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+NAME="));
		Serial.println(name);
	}
	delay(200);
	readLine();
}

void HC_05::atRNAME(char * address)	// 7
{
	this->print(F("AT+RNAME?"));
	this->print(address);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+RNAME?"));
		Serial.println(address);
	}
	delay(200);
	readLine();
}

void HC_05::atROLE()	// 8
{
	this->print(F("AT+ROLE?\r\n"));
	if(verbose)
		Serial.println(F("AT+ROLE?"));
	delay(200);
	readLine();
}

void HC_05::atROLE(bool role)
{
	this->print(F("AT+ROLE="));
	this->print(role);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+ROLE="));
		Serial.println(role);
	}
	delay(200);
	readLine();
}

void HC_05::atCLASS()	// 9
{
	this->print(F("AT+CLASS?\r\n"));
	if(verbose)
		Serial.println(F("AT+CLASS?"));
	delay(200);
	readLine();
}

void HC_05::atCLASS(char * type)
{
	this->print(F("AT+CLASS="));
	this->print(type);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+CLASS="));
		Serial.println(type);
	}
	delay(200);
	readLine();
}

void HC_05::atIAC()	// 10
{
	this->print(F("AT+IAC?\r\n"));
	if(verbose)
		Serial.println(F("AT+IAC?"));
	delay(200);
	readLine();
}

void HC_05::atIAC(char * code)
{
	this->print(F("AT+IAC="));
	this->print(code);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+IAC="));
		Serial.println(code);
	}
	delay(200);
	readLine();
}

void HC_05::atINQM()	// 11
{
	this->print(F("AT+INQM?\r\n"));
	if(verbose)
		Serial.println(F("AT+INQM?"));
	delay(200);
	readLine();
}

void HC_05::atINQM(bool mode, byte max_devices, byte inq_time)
{
	this->print(F("AT+INQM="));
	this->print(mode);
	this->print(',');
	this->print(max_devices);
	this->print(',');
	this->print(inq_time);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+INQM="));
		Serial.print(mode);
		Serial.print(',');
		Serial.print(max_devices);
		Serial.print(',');
		Serial.println(inq_time);
	}
	delay(200);
	readLine();
}

void HC_05::atPSWD()	// 12
{
	this->print(F("AT+PSWD?\r\n"));
	if(verbose)
		Serial.println(F("AT+PSWD?"));
	delay(200);
	readLine();
}

void HC_05::atPSWD(char * pass)
{
	this->print(F("AT+PSWD="));
	this->print(pass);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+PSWD="));
		Serial.println(pass);
	}
	delay(200);
	readLine();
}

void HC_05::atUART()	// 13
{
	this->print(F("AT+UART?\r\n"));
	if(verbose)
		Serial.println(F("AT+UART?"));
	delay(200);
	readLine();
}

void HC_05::atUART(unsigned long baud, byte stop, byte parity)
{
	this->print(F("AT+UART="));
	this->print(baud);
	this->print(',');
	this->print(stop);
	this->print(',');
	this->print(parity);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+UART="));
		Serial.print(baud);
		Serial.print(',');
		Serial.print(stop);
		Serial.print(',');
		Serial.println(parity);
	}
	delay(200);
	readLine();
}

void HC_05::atCMODE()	// 14
{
	this->print(F("AT+CMODE?\r\n"));
	if(verbose)
		Serial.println(F("AT+CMODE?"));
	delay(200);
	readLine();
}

void HC_05::atCMODE(byte mode)
{
	this->print(F("AT+CMODE="));
	this->print(mode);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+CMODE="));
		Serial.println(mode);
	}
	delay(200);
	readLine();
}

void HC_05::atBIND()	// 15
{
	this->print(F("AT+BIND?\r\n"));
	if(verbose)
		Serial.println(F("AT+BIND?"));
	delay(200);
	readLine();
}

void HC_05::atBIND(char * address)
{
	this->print(F("AT+BIND="));
	this->print(address);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+BIND="));
		Serial.println(address);
	}
	delay(200);
	readLine();
}

void HC_05::atPMSAD(char * address)	// 21
{
	this->print(F("AT+PMSAD="));
	this->print(address);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+PMSAD="));
		Serial.println(address);
	}
	delay(200);
	readLine();
}

void HC_05::atRMAAD()	// 22
{
	this->print(F("AT+RMAAD\r\n"));
	if(verbose)
		Serial.println(F("AT+RMAAD"));
	delay(200);
	readLine();
}

void HC_05::atFSAD(char * address)	// 23
{
	this->print(F("AT+FSAD="));
	this->print(address);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+FSAD="));
		Serial.println(address);
	}
	delay(200);
	readLine();
}

void HC_05::atADCN()	// 24
{
	this->print(F("AT+ADCN?\r\n"));
	if(verbose)
		Serial.println(F("AT+ADCN?"));
	delay(200);
	readLine();
}

void HC_05::atMRAD()	// 25
{
	this->print(F("AT+MRAD?\r\n"));
	if(verbose)
		Serial.println(F("AT+MRAD?"));
	delay(200);
	readLine();
}

void HC_05::atSTATE()	// 26
{
	this->print(F("AT+STATE?\r\n"));
	if(verbose)
		Serial.println(F("AT+STATE?"));
	delay(200);
	readLine();
}

void HC_05::atINIT()	// 27
{
	this->print(F("AT+INIT\r\n"));
	if(verbose)
		Serial.println(F("AT+INIT"));
	delay(200);
	readLine();
}

void HC_05::atINQ()	// 28
{
	this->print(F("AT+INQ\r\n"));
	if(verbose)
		Serial.println(F("AT+INQ"));
	delay(200);
	readLine(); 
}

void HC_05::atINQ(char * inq_buffer)
{
	this->print(F("AT+INQ\r\n"));
	if(verbose)
		Serial.println(F("AT+INQ"));
	
	delay(200);
	readLine();
	// char ByteCount = this->readBytesUntil('\n', response, sizeof(response));
	// Serial.println(response);
	// memset(response, 0, sizeof(response));
	// this->flush();
}

void HC_05::atINQC()	// 29
{
	this->print(F("AT+INQC\r\n"));
	if(verbose)
		Serial.println(F("AT+INQC"));
	delay(200);
	readLine();
}

void HC_05::atPAIR(char * address, byte timeout)	// 30
{
	this->print(F("AT+PAIR="));
	this->print(address);
	this->print(',');
	this->print(timeout);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+PAIR="));
		Serial.println(address);
	}
	delay(200);
	
	byte i = 0;
	while(!this->available() && i++ <= timeout)
	{
		delay(1000);
		if(verbose)
			Serial.print(".");
	}
	readLine();
}

void HC_05::atLINK(char * address)	// 31
{
	this->print(F("AT+LINK="));
	this->print(address);
	endLine();
	if(verbose)
	{
		Serial.print(F("AT+LINK="));
		Serial.println(address);
	}
	delay(200);
	readLine();
}

void HC_05::atDISC()	// 32
{
	this->print(F("AT+DISC\r\n"));
	if(verbose)
		Serial.println(F("AT+DISC"));
	delay(200);
	readLine();
}

void HC_05::readLine()
{
	if(verbose)
	{
		while(this->available())
			Serial.write(this->read());
	}
	else
	{
		while(this->available())
			this->read();
	}	
}

void HC_05::endLine()
{
	this->print(F("\r\n"));
}







