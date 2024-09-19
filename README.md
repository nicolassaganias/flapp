# Flapp

This Bluetooth Low Energy (BLE) App is responsible of gathering data values from different arduino-based sensors.
At the moment the app is designed for it to communicate with 5 types of water-sensing sensors:
```
pH Sensor
EC Sensor
Pressure Sensor
Weight Sensor (digital scales with RS232 or analog output)
Temperature Sensor
```
All this sensors can be connected at the same time and after finishing the experiment, be sent in .csv format to any e-mail address or saved in the internal mobile phone/tablet memory.

# App Usage Instructions
When the app is opened you see an empty screen where you can search new device by clicking in the magnifying glass icon.



When you click the magnifying glass all the Bluetooth available devices are shown. 
Select the device/s to pair and start seeing data in real time.
![Devices Display](images/app_devicesView.png)
_maybe device will ask to pair with a new device. it is not necesary to pair with the device, the app will ask you to do it.

Once device is connected, see the data being received in Data Display:

![Data Display](images/app_liveView.png)

User can Start a New Project to save the data for a period of time. Also user can adjust the interval in which the app will record the data values and also assign a project name:

![New Project](images/app_newProject.png)

When New Project's duration is over or button "Stop" is pressed, user will have the choice of sharing the data over e-mail or saving into the internal mobile memory

If Share is selected the app will bring up the default mail app and will compress the .csv file to be sent

Once data is shared user will be able to see a table-formated .csv file:
