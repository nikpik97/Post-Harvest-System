#ifndef _TalkB2A_H
#define _TalkB2A_H
#include "Arduino.h"
#include <stdlib.h>
#include <SoftwareSerial.h>

#define BUFFERSIZE 35
#define PARAMETERSIZE 15 
#define TBUFFERSIZE 15

class TalkB2A : public SoftwareSerial {
public:
  TalkB2A(int rxpin,int txpin);
  void ReadCommand();
  void Tokenizer(char a[]);
  void StartGet(int p);
  void StartGet(char* p);
  void AddParameter(int p);
  void AddParameter(char* p);
  void SendData();
  void GetFilename(int a,int b,int c, int d);
  void TwoDigitFormat(int a);
  void ClearSerialBuffer();
  void ClearAllBuffer();
  void ReplyStatus(int ecode);
  int ByteCount;
  char Parameter[6][PARAMETERSIZE];
  char Buffer[BUFFERSIZE];
  char TimeBuffer[TBUFFERSIZE];//For data record

};
#endif
