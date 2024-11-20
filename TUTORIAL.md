**Flapp has different layer according to your knowlodge of Electronics and C++ Programming:**

**Layer 1: User.** Knows how to use the devices and the app

**Layer 2: DIY/DIWO User.** Knows how to solder and upload code to ESP-32 board and can buy the Electronic components according to his/her needs

**Layer 3: Advanced User.** Knows how to modify systems and code and to make new devices. Makes contribution to Flapp community.


##Layer 1. User: Refer to "App Usage Instructions" in README.md file

##Layer 2: DIYO/DIWO User/s:

# Tutorial FLAPP

## Elements (Buylist)
- **ESP32/DFRobot pH Sensor Kit**
- **ESP32/DFRobot EC Sensor Kit**
- **ESP32/Pressure Sensor**
- **ESP32/RS232 Bluetooth Adapter + HC-05 Module**
- **ESP32/DFRobot Water Temperature Sensor**

---

## Connections

### pH Sensor
| ESP32 Pin | pH Sensor Pin |
|-----------|---------------|
| +3.3V     | Vcc (+)       |
| GND       | GND (-)       |
| 13        | Vout (A)      |

### EC Sensor
| ESP32 Pin | EC Sensor Pin |
|-----------|---------------|
| +3.3V     | Vcc (+)       |
| GND       | GND (-)       |
| 13        | Vout (A)      |

### Pressure Sensor
| ESP32 Pin | Pressure Sensor Pin |
|-----------|----------------------|
| +3.3V     | Vcc (+)              |
| GND       | GND (-)              |
| 13        | Vout (A)             |

### HC-05 Module
| ESP32 Pin | HC-05 Module Pin |
|-----------|-------------------|
| +3.3V     | Vcc (+)           |
| GND       | GND (-)           |
| 16        | TX                |
| 17        | RX                |

---

## Upload Sensor Codes

1. **Download and Install Arduino IDE**

2. **Download Codes from GitHub Repository**  
   - Navigate to the main GitHub repository.  
   - Click the green **Code** button and select **Download ZIP** to download all codes, or copy and paste the desired code into your Arduino IDE.  
   - After downloading, go to `/Firmware/ESP32_updated` and open the required code.

3. **Install Necessary Libraries**  
   - Ensure all required libraries are installed.

4. **Connect ESP32 to Computer**  
   - Use a micro USB cable to connect the ESP32 to your computer.

5. **Upload Desired Code**  
   - Upload the selected code to the ESP32.

6. **Install FLAPP App on Android Device**  
   - In the previously downloaded repository, navigate to `/apk` and download the latest `.apk` file.  
   - Transfer the `.apk` file to your Android device:  
     - One method is to upload the `.apk` to a cloud service (e.g., Google Drive) and download it on your Android device.  
   - Install the `.apk` by tapping on it.  
     - For more information, refer to [this guide](https://www.androidcentral.com/sideload-apps-how-guide).  
   - If prompted, click **Scan app** during installation.

7. **Open FLAPP App**  
   - Upon first launch, the app will request permissions:  
     - **Location Access:** You may decline this permission.  
     - **Device Discovery:** Accept this permission; otherwise, the app may not function correctly.

8. **Using the App**  
   - Refer to the `readme.md` file for detailed instructions.

---

## Troubleshooting

If you encounter issues such as:
- Unintended sensors connecting
- Incorrect sensor names
- `.csv` file not populating with values

You can resolve these by clearing the storage and cache data of the FLAPP app:

1. Press and hold the FLAPP app icon on your Android device.
2. Select **App Info** (or an **i** icon).
3. Clear the cache and storage data.

For more details, refer to [this guide on clearing cache in Android](https://www.androidcentral.com/how-and-when-clear-app-cache-or-data-android-device).
