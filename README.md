# GT-Arduino-to-MIT-App-inventor

I'm trying to do a re-make of Dataworks project ([attached](https://github.com/GizanTech/GT-Arduino-to-MIT-App-inventor/blob/main/resources/CustomControlUnit-eC%20(2)%20instrument%20works.pdf)). Here you can see the actual source code and almost everything that we need to do. In this project they used EZO EC Sensor but now I'm using EC Meter from DFRobots.

Basically I have 5 different kits (change Arduino BLE for Bluno Nano from DFRobot):
![image](https://github.com/GizanTech/GT-Arduino-to-MIT-App-inventor/assets/65446169/d96708ea-2c4a-493c-ae0c-5e2ae26f8d52)

All of this kits can be paired separately or all together to the bluetooth app (MIT App Inventor) that works for IOS and Android.

When client opens the app:
1.	Select to which kit or kits to connect and connect
2.	See data in real time
a.	Or Calibrate the sensor (send commands and wait for responses)
3.	Choose name of the project and time of data gathering (maybe save data every 30 seconds or 5 minutes)
4.	Start the project
5.	Finish project and export data to .csv format and send it via e-mail
The app should not stop the experiment if it is in background task (if the app is minimized) 

All the kits are already working (reading the sensor and saving it to SD), I can send you all the codes but with the RS232 kit I may be needing help because I could not test it yet because I don't have a device that outputs RS232 yet.

I think with this we have almost everything. Any doubt you may tell me.
