// Hub_lib version 1.0
// by Luis Ramirez
#include <Hub_Lib.h>



void BluetoothParser(void)
{
	byte ByteCount =  BTSerial.readBytesUntil('\n', Buffer, BUFF_SIZE-1);
  
	if(ByteCount  > 0) 
	{
		// Parse Command and Data parameters
		strcpy(Command,strtok(Buffer," "));             
		strcpy(Data,strtok(NULL,";"));

		// Protect from overflowing buffers
		Command[CMD_SIZE-1] = '\0';
		Data[DATA_SIZE-1] = '\0';

		// Convert command into a byte
		byte cmd = atoi(Command);

		// Check if Busy status needs to be set
		if(cmd > MIN_CMD && cmd < MAX_CMD)
		digitalWrite(BUSY_LED, HIGH);
      
		// Execute Command
		switch(cmd)
		{
			case 2: // Get Hub ID
				getHubID();
				break;
			case 3: // Set Hub ID
				setHubID();
				break;
			case 4:
				// getNumSensors();
				break;
			case 5: // Get List of Sensors
				getSensorList();
				break;
			case 8: // Add a Sensor
				addSensor();
				break;
			case 9: // Remove a Sensor
				removeSensor();
				break;
			case 10: // Remove all Sensors
				removeAllSensors();
				break;
			case 11: // Get Alert Phone #
				getAlertPhone();
				break;
			case 12: // Set Alert Phone #
				setAlertPhone();
				break;
			case 13: // Get Portal Phone #
				getPortalPhone();
				break;
			case 14: // Set Portal Phone #
				setPortalPhone();
				break;
			case 15: // Get Portal Notification Freq.
				getPortalFreq();
				break;
			case 16: // Set Portal Notification Freq.
				getPortalFreq();
				break;
			default:
				BTSerial.println("Invalid Command");
				break;
		}
	}

	// Clean up buffers
	clearAllBuffers();

	// Flush BTSerial TX
	BTSerial.flush();

	// Clean up the rest of BTSerial Rx
	while(BTSerial.available()) 
		BTSerial.read();

	// Clear Busy Status
	digitalWrite(BUSY_LED, LOW);
  
}

void clearAllBuffers()
{
	memset(Buffer, 0, BUFF_SIZE);   // Clear contents of Buffer
	memset(Command, 0, CMD_SIZE);   // Clear contents of Buffer
	memset(Data, 0, DATA_SIZE);     // Clear contents of Buffer
}

void clearBuffer()
{
	memset(Buffer, 0, BUFF_SIZE);   // Clear contents of main Buffer
}

void printBuffers()
{
	// Print out Command
	BTSerial.print("Command : ");
	BTSerial.println(Command);

	// Print out Data parameters
	BTSerial.print("Data    : ");
	BTSerial.println(Data);
}



/***** HUB_B SETUP COMMAND *****/
void sendSetupCommand(char * cmd, char * dest)
{
  // Send a command to Hub_B
  Serial.println(cmd);
  SerialB.println(cmd);
  SerialB.flush();

  delay(500);
  
  // Read Response from Hub_B
  byte bytesRead = SerialB.readBytesUntil('\n', Buffer, BUFF_SIZE-1);
  if(bytesRead > 0)
  {
    Serial.println(Buffer);
    strcpy(dest, Buffer);
  }
  
}

void sendCommand(char * cmd, char * dest)
{
  // Send a command to Hub_B
  Serial.println(cmd);
  SerialB.println(cmd);
  SerialB.flush();

  delay(500);
  
  // Read Response from Hub_B
  byte bytesRead = SerialB.readBytesUntil('\n', Buffer, BUFF_SIZE-1);
  if(bytesRead > 0)
  {
    Serial.println(Buffer);
    strcpy(dest, Buffer);
  }
  
}


void sendCommand(char * cmd)
{
  // Send a command to Hub_B
  Serial.print(cmd);
  Serial.print(' ');
  Serial.println(Data);
  Serial.flush();
  
  SerialB.print(cmd);
  SerialB.print(' ');
  SerialB.println(Data);
  SerialB.flush();

  delay(500);
  
  // Read Response from Hub_B
  byte bytesRead = SerialB.readBytesUntil('\n', Buffer, BUFF_SIZE-1);
  if(bytesRead > 0)
  {
    Serial.println(Buffer);

  }
  
}



/***** CASE 5 *****/
void getHubID()
{
  BTSerial.println(HubID);
}

/***** CASE 6 *****/
void setHubID()
{
  memcpy(HubID, Data, HUB_ID_SIZE);
  // Send TBD Command to Hub_B
  sendCommand("22");
}

/***** CASE 7 *****/
void getSensorList()
{
  if(SensorList.size() == 0)
    return;

  for(byte i = 0; i < SensorList.size(); i++)
  {
    Sensor * s = SensorList.get(i);
    BTSerial.print(s->address);
  }
}

/***** CASE 8 *****/
void addSensor()
{
  Sensor * newSensor = new Sensor();
  memcpy(newSensor->address, Data, ADDR_SIZE);
  newSensor->address[ADDR_SIZE] = '\0';

  SensorList.add(newSensor);
  SerialB.write("8");
  SerialB.write(" ");
  SerialB.write("0");
  SerialB.write(" ");
  SerialB.write(newSensor->address);
  SerialB.flush();


  // Send TBD Command to Hub_B
}

/***** CASE 9 *****/
void removeSensor()
{
  if(SensorList.size() == 0)
    return;
  for(byte i = 0; i < SensorList.size(); i++)
  {
    Sensor * currSensor = SensorList.get(i);
    if(memcmp(Data, currSensor->address, ADDR_SIZE) == 0)
    {
      SensorList.remove(i);
    }   
  }
  // Send TBD Command to Hub_B
}

/***** CASE 10 *****/
void removeAllSensors()
{
  SensorList.clear(); 
  // Send TBD Command to Hub_B
}

/***** CASE 11 *****/
void getAlertPhone()
{
  BTSerial.print(AlertPhone);
}

/***** CASE 12 *****/
void setAlertPhone()
{
  memcpy(AlertPhone, Data, PHONE_SIZE);
  // Send Set Command to Hub_B
}

/***** CASE 13 *****/
void getPortalPhone()
{
  BTSerial.println(PortalPhone);
}

/***** CASE 14 *****/
void setPortalPhone()
{
  memcpy(PortalPhone, Data, PHONE_SIZE);
  // Send Set Command to Hub_B
}

/***** CASE 15 *****/
void getPortalFreq()
{
  BTSerial.println(PortalFreq);
}

/***** CASE 16 *****/
void setPortalFreq()
{
  byte freq = atoi(Data);
  PortalFreq = freq;
  // Send set command to Hub_B
}

/***** CASE 17 *****/
/***** CASE 18 *****/
/***** CASE 19 *****/
/***** CASE 20 *****/




