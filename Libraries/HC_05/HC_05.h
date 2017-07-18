#ifndef _HC_05_H
#define _HC_05_H

#include "Arduino.h"
#include <SoftwareSerial.h>

//#define VERBOSE
#define TIMEOUT 60 		// Seconds
#define INQM_TIMEOUT 47	// 47 * 1.28 = 60.16 ≈ TIMEOUT

class HC_05 : public SoftwareSerial
{
	public:
		HC_05(byte rxpin, byte txpin, byte atpin, byte statepin);
		void atMode(bool mode);
		bool connected();
		
		void atTest();						// 1
		void atRESET();						// 2
		void atVERSION();					// 3
		void atORGL();						// 4
		void atADDR();						// 5
		void atNAME();						// 6
		void atNAME(char * name);
		void atRNAME(char * address);		// 7
		void atROLE();						// 8
		void atROLE(bool role);
		void atCLASS();						// 9
		void atCLASS(char * type);
		void atIAC();						// 10
		void atIAC(char * code);
		void atINQM();						// 11
		void atINQM(bool mode, byte max_devices, byte inq_time = INQM_TIMEOUT);
		void atPSWD();						// 12
		void atPSWD(char * pass);
		void atUART();						// 13
		void atUART(unsigned long baud, byte stop, byte parity);
		void atCMODE();						// 14
		void atCMODE(byte mode);
		void atBIND();						// 15
		void atBIND(char * address);
		void atPOLAR();						// 16
		void atPOLAR(bool PIO8, bool PIO9);
		void atPIO(byte PIO, bool status);	// 17
		void atIPSCAN();					// 18
		void atIPSCAN(int time, int duration, int paging, int call);
		void atSNIFF();						// 19
		void atSNIFF(byte max_time, byte min_time, byte retry_time, byte timeout);
		void atSENM();						// 20
		void atSENM(byte sec_mode, byte hci_enc_mode);
		void atPMSAD(char * address);		// 21 Delete Authenticated Device
		void atRMAAD();						// 22 Delete All Authenticated Device
		void atFSAD(char * address);		// 23 Search Authenticated Device
		void atADCN();						// 24 Get Authenticated Device Count
		void atMRAD();						// 25 Most Recently Used Authenticated Device
		void atSTATE();						// 26
		void atINIT();						// 27
		void atINQ();						// 28
		void atINQ(char * inq_buffer);
		
		void atINQC();						// 29
		void atPAIR(char * address, byte timeout);	// 30
		void atLINK(char * address);		// 31
		void atDISC();						// 32
		void atENSNIFF(char * address);		// 33
		void atEXSNIFF(char * address);		// 34
		
		void readLine();
		void endLine();
		
		bool verbose;
		
	private:
		byte _atPin;
		byte _statePin;

		
};

#endif /* not defined _HC_05_H */