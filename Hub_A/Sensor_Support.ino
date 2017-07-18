// This function is used to check and individual sensor given a sensor number

void checkSensor(byte num)
{
  // Get Sensor MAC Address from SensorList
  Serial.println(F("\n\n------------------"));
  Serial.print(F("Checking Sensor "));
  Serial.println(num);
  Sensor * s = SensorList.get(num);

  // Connect to the Sensor
  Serial.print(F("Connecting to Sensor..."));  
  BTSerial.atCO('N',s->address);
  delay(1000);

  //Serial.print(F("Requesting Data from Sensor..."));
  float t = -1.0;
  float h = -1.0;

  if(BTSerial.connected())
  {
    Serial.println(F("Connected!"));
    // Get Temperature from the sensor
    BTSerial.println("1");
    delay(1000);
    if(BTSerial.available())
    {
      t = BTSerial.parseFloat();
      Serial.print(F("Temperature: "));
      Serial.print(t);          // Prints Temperature as Float
      Serial.write(176);        // Prints Degree Symbol
      Serial.println(F("C"));   // Prints Celsius
    }

    // Wait before Sending Another Command
    delay(1000);
  
    // Get Humidity from the sensor
    BTSerial.println("2");
    delay(1000);
    if(BTSerial.available())
    {
      h = BTSerial.parseFloat();
      Serial.print(F("Humidity: "));
      Serial.print(h);
      Serial.println(F(" %RH"));
    }

    // Disconnnect from the sensor
    BTSerial.atTEST();

    // Send Data To Be Recorded In SD Card
    SerialB.listen();
    clearAllBuffers();
    sendData(num, t, h, s->address);
  }
  else
  {
    Serial.println(F("Fail!"));
  }
  

  // Check if critical Temperature or Humidity
  if(t >= critTemp && h >= critHum)
    sendAlert(1);
  else if(t >= critTemp)
    sendAlert(2);
  else if(h >= critHum)
    sendAlert(3);

  Serial.print(F("Done Checking Sensor "));
  Serial.println(num);
  
  // Return to listening to Bluetooth
  BTSerial.listen();
}

/* checkAllSensors()
 * - Used to loop through all sensors and check for 
 * temperature and humidity.
 */
 
void checkAllSensors()
{
  // Set Busy Status
  digitalWrite(BUSY_LED, HIGH);
  
  Serial.println(F("\n\nPerforming a Sensor Check!"));

  // Loop through and check each sensor 
  for(byte i = 0; i < SensorList.size(); i++)
    checkSensor(i);

  Serial.println(F("Done Checking All Sensors!"));
  
  // Notify Hub_B that the sensor check is done
  sendGetCommand(5);
  
  // Clear Busy Status
  digitalWrite(BUSY_LED, LOW);
}


/* NEEDS TESTING */
/*
void checkSensor(byte num, String * message)
{
  // Get Sensor MAC Address from SensorList
  Serial.println(F("\n\n------------------"));
  Serial.print(F("Checking Sensor "));
  Serial.println(num);
  Sensor * s = SensorList.get(num);

  // Connect to the Sensor
  Serial.print(F("Connecting to Sensor..."));  
  BTSerial.atCO('N',s->address);
  delay(1000);

  float t = -1.0;
  float h = -1.0;
  String report = "SENREP*";
  
  if(BTSerial.connected())
  {
    Serial.println(F("Connected!"));
    // Get Temperature from the sensor
    //message += hubID;   // Appends the Major number
    report += (int)num;  // Appends the Minor number
    //message += (int)num;  // Appends the Minor number
    BTSerial.println("1");
    delay(1000);
    if(BTSerial.available())
    {
      t = BTSerial.parseFloat();
      //message += "*";
      //message += String(t,2);
      report += "*";
      report += String(t,2);
      Serial.print(F("Temperature: "));
      Serial.print(t);          // Prints Temperature as Float
      Serial.write(176);        // Prints Degree Symbol
      Serial.println(F("C"));   // Prints Celsius
    }

    // Wait before Sending Another Command
    delay(2000);
  
    // Get Humidity from the sensor
    BTSerial.println("2");
    delay(1000);
    if(BTSerial.available())
    {
      h = BTSerial.parseFloat();
//      message += "*";
//      message += String(h,2);
      report += "*";
      report += String(h,2);
      Serial.print(F("Humidity: "));
      Serial.print(h);
      Serial.println(F(" %RH"));
    }

    // Disconnnect from the sensor
    BTSerial.atTEST();

    // Send Data To Be Recorded In SD Card
    SerialB.listen();
    clearAllBuffers();
    sendData(num, t, h, s->address);
  }
  else
  {
    //message.concat("err!");
    Serial.println(F("Fail!"));
  }

  // Check if critical Temperature or Humidity
  if(t >= critTemp && h >= critHum)
  {
    //message += " ";
    //message.concat(1);
    sendAlert(1);
  }
  else if(t >= critTemp)
  {
    //message += " ";
    //message.concat(2);
    sendAlert(2);
  } 
  else if(h >= critHum)
  {
    //message += " ";
    //message.concat(3);
    sendAlert(3);
  }
  //message.concat("\n");
  message += '\n';
  // Send report to portal
  cell.listen();
  delay(500);
  cell.Rcpt(PortalPhone);
  strcpy(cell.outmessage, report.c_str());
  cell.SendSMS();
  cell.flush();
  delay(3000);
  while(cell.available())
  {
    Serial.print(cell.readString());
  }
  cell.flush();
  Serial.flush();
  delay(3000);

  
  Serial.print(F("Done Checking Sensor "));
  Serial.println(num);
  
  // Return to listening to Bluetooth
  BTSerial.listen();
  //return message;
}


// Function to check every stored sensor
void checkAllSensors()
{
  // Set Busy Status
  digitalWrite(BUSY_LED, HIGH);
  
  Serial.println(F("Performing a Sensor Check!"));
  String Message;
 
  // Loop through and check each sensor 
  for(byte i = 0; i < SensorList.size(); i++)
    checkSensor(i, &Message);
    //Message += checkSensor(i, &Message);
  
  //char __message[Message.length() + 1];
  //Message.toCharArray(__message, Message.length() + 1);
  
  //alertPortal(__message);
  alertPortal(Message.c_str());
  Serial.println(F("Done Checking All Sensors!"));
  
  // Notify Hub_B that the sensor check is done
  sendGetCommand(5);
  
  // Clear Busy Status
  digitalWrite(BUSY_LED, LOW);
}


*/


