void sendAlert(byte txt)
{ 
  cell.listen();
  delay(500);
  //cell.Rcpt(AlertPhone);
  //cell.Rcpt("9546621746");
  //cell.Rcpt("6302176714");
  String s;
  switch(txt)
  {
    case 1:
      s = "Critical Temperature and Humidity!";
      break;
    case 2:
      s = "Critical Temperature!";
      break;
    case 3:
      s = "Critical Humidity!";
      break;
  }
  Serial.println(s);
//  strcpy(cell.outmessage, s.c_str());
//  cell.SendSMS();
//  cell.flush();
//  delay(5000);
//  while(cell.available())
//  {
//    Serial.print(cell.readString());
//    Serial.flush();
//  }
//  cell.flush();
//  delay(3000);
  //cell.DeleteAllSMS();  
}

void alertPortal(char * message)
{
  cell.listen();
  delay(500);
  cell.SendSMS(PortalPhone, message);
  cell.flush();
  delay(3000);
  while(cell.available())
  {
    Serial.print(cell.readString());
  }
  cell.flush();
  Serial.flush();
  delay(3000);
}


