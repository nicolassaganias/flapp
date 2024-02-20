# instructions for binding devices

For binding HC-05 module of weight sensor with bluetooth rs232 module.
AT commands for configurating ESP-32

** to check the bluetooth address use "Bluetooth Scanner" app in android
```
AT
AT+ROLE=1
AT+CMODE=0
AT+BIND=98D3,51,FEE015 // code for rs232 bluetooth module
```
ESP32 sketch for communicating with HC-05 module through rx2 and tx2 (Serial2) like in our conection.
```
void setup()
{

  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  Serial2.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (Serial2.available())
    Serial.write(Serial2.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    Serial2.write(Serial.read());
}
```

# PIN FOR "B35" RS232_MODULE: 1234
