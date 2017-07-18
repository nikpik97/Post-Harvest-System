#include <TalkB2A.h>

TalkB2A::TalkB2A(int rxpin,int txpin):
SoftwareSerial(rxpin,txpin){
}

void TalkB2A::ReadCommand(){//Read command from Hub A then store it in a buffer
	ByteCount =  this->readBytesUntil('\n',Buffer,BUFFERSIZE);
	Buffer[BUFFERSIZE-1]='\0';// In case buffer overflow
	Serial.print("Buffer: ");
	Serial.println(Buffer);
	Tokenizer(Buffer);
	memset(Buffer, 0, BUFFERSIZE);   // Clear contents of Buffer

}

void TalkB2A::Tokenizer(char a[]){//Tokenize the command in the buffer then store parameters in the parameter array
	char *p = a;
	char *token;
	int i = 0;
	while ((token = strtok_r(p, " ", &p)) != NULL){ 
		strcpy(Parameter[i++] , token);
	}
}
	
void TalkB2A::StartGet(int p){
	char x[5];
	itoa(p,x,10);
  	strcpy(Buffer, x);
}	
	
	
void TalkB2A::AddParameter(int p){
	char x[5];
	itoa(p,x,10);
  	strcat(Buffer, " ");
  	strcat(Buffer, x);
} 

void TalkB2A::StartGet(char* p){
  	strcpy(Buffer, p);
}	

void TalkB2A::AddParameter(char* p){
  	strcat(Buffer, " ");
  	strcat(Buffer, p);
} 

void TalkB2A::GetFilename(int a,int b,int c, int d){
	//strcpy(TimeBuffer, "20");
	TwoDigitFormat(a);
	TwoDigitFormat(b);
	TwoDigitFormat(c);
	TwoDigitFormat(d);
	strcat(TimeBuffer, ".csv");
}

void TalkB2A::TwoDigitFormat(int a){
	char x[3];
	if(a>9){
		itoa(a,x,10);	
		//Serial.println(x);
		strcat(TimeBuffer,x);

	}
	else{
		strcat(TimeBuffer, "0");
		itoa(a,x,10);
		//Serial.println(x);
		strcat(TimeBuffer,x);
	}
}
void TalkB2A::ClearSerialBuffer(){
  	while(Serial.available() > 0) { //Clear Serial buffer
    char t = Serial.read();
  }
    while(this->available() > 0) {//Clear SoftSerial Buffer
    char t = this->read();
  }
  
} 

void TalkB2A::SendData(){
	this->println(Buffer);
	this->flush();
	ClearAllBuffer();
}

void TalkB2A::ClearAllBuffer(){
	memset(Buffer, 0, BUFFERSIZE);   // Clear contents of Buffer
	memset(Parameter, 0, PARAMETERSIZE);
	memset(TimeBuffer, 0, TBUFFERSIZE);
}

void TalkB2A::ReplyStatus(int ecode){
	if(this->available()>0){
		Serial.println(F("Buffer too small"));
		ClearSerialBuffer();
	}
	if(ecode==0)
	this->println('d');//Nothing wrong. Reply 'd' for Done and wait for next command.
	else{
		this->print('e');
		this->print(' ');
		this->println(ecode);
	}
}
