# instructions for binding devices

For binding HC-05 module of weight sensor with bluetooth rs232 module.
AT commands for configurating ESP-32

** rs232 module needs the jumpers to be connected to "device" 
** to check the bluetooth address use "Bluetooth Scanner" app in android
** open file named "AT_COMANDS.ino"
++ use 9600 as Baud Rate and Both Ln and C 
** put hc-05 module into AT MODE: 
				1. unplug the module
				2. hold push button
				3. while holding plug the module
```
AT
AT+ROLE=1
AT+CMODE=0
AT+BIND=98D3,51,FEE015 // code for rs232 bluetooth module BC53 (new models) code for SH-B30 (old modules) is 0014,03,05071E or 6D
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

# instructions for updating Flapp:
for devices connected to lequiamembranes google account:
1. long hold Flapp's icon
2. select "i" or "information" according to the device
3. clear all data (storage and caché)
4. uninstall the app
5. go to google drive app
6. look for Flapp's desired version, download and install
