
void clearAllBuffers()
{
  memset(Buffer, 0, BUFF_SIZE);   // Clear contents of Buffer
  memset(Command, 0, CMD_SIZE);   // Clear contents of Buffer
  memset(Data, 0, DATA_SIZE);     // Clear contents of Buffer
}

void clearBuffer()
{
  memset(Buffer, 0, BUFF_SIZE);   // Clears main Buffer
}

void clearData()
{
  memset(Data, 0, DATA_SIZE);   // Clears main Buffer
}

void clearSettings()
{
  memset(HubID, '0', HUB_ID_SIZE);
  memset(AlertPhone, '0', PHONE_SIZE);
  memset(PortalPhone, '0', PHONE_SIZE);

  PortalFreq = 0;
  LoggingFreq = 0;

  critTemp = 100;
  critHum = 100;
}

bool checkAlarm()
{
  return digitalRead(FLAG);
}

// Used to check if there has been a change in the mode switch
bool checkModeChange()
{
  return digitalRead(MODE_SWITCH) != HubMode;
}

// Used for switching between modes
void switchMode()
{
  if(digitalRead(MODE_SWITCH) != HubMode)
  {
    // Set Busy LED
    digitalWrite(BUSY_LED, HIGH);
    
    HubMode = !HubMode; // Invert the HubMode
    BTSerial.atTEST();  // Make sure the module is disconnected
    
    // Switch to the correct role
    if(HubMode)
    {
      BTSerial.atROLE('1'); // Set to Master
      Serial.println(F("Entering Hub Mode"));
    }
    else
    {
      BTSerial.atROLE('0'); // Set to Slave
      Serial.println(F("Entering Config Mode"));
    }
    
    // Reset Bluetooth Module
    BTSerial.atRESET();

    // Set the Mode LED
    digitalWrite(MODE_LED, HubMode);

    // Clear Busy LED
    digitalWrite(BUSY_LED, LOW);
  }
}

// This is used when there is an issue with the initial setup process
void errorBlink()
{
  Serial.println(F("Error Initializing Hub!"));
  while(1)
  {
    digitalWrite(BUSY_LED, LOW);
    delay(500);
    digitalWrite(BUSY_LED, HIGH);
    delay(500);
  }
}












