/*!
 * @file DFRobot_EC10.cpp
 * @brief Define the basic structure of class DFRobot_EC10 
 * @details This library is used to drive the analog electrical conductivity meter to measure solution EC. 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-5-5
 * @https://github.com/DFRobot/DFRobot_EC10
 */
#include "DFRobot_EC10.h"
#include <EEPROM.h>

#define EEPROM_write(address, p) \
  { \
    int i = 0; \
    byte* pp = (byte*)&(p); \
    for (; i < sizeof(p); i++) EEPROM.write(address + i, pp[i]); \
  }
#define EEPROM_read(address, p) \
  { \
    int i = 0; \
    byte* pp = (byte*)&(p); \
    for (; i < sizeof(p); i++) pp[i] = EEPROM.read(address + i); \
  }

#define KVALUEADDR 0x0F  //the start address of the K value stored in the EEPROM
#define RES2 (7500.0 / 0.66)
#define ECREF 20.0

char* DFRobot_EC10::strupr(char* str) {
  if (str == NULL) return NULL;
  char* ptr = str;
  while (*ptr != ' ') {
    *ptr = toupper((unsigned char)*ptr);
    ptr++;
  }
  return str;
}

DFRobot_EC10::DFRobot_EC10() {
  this->_ecvalue = 0.0;
  this->_kvalue = 10.0;
  this->_cmdReceivedBufferIndex = 0;
  this->_voltage = 0.0;
  this->_temperature = 25;
}

DFRobot_EC10::~DFRobot_EC10() {
}

void DFRobot_EC10::begin() {
  EEPROM_read(KVALUEADDR, this->_kvalue);  //read the calibrated K value from EEPROM
  if ((EEPROM.read(KVALUEADDR) == 0xFF && EEPROM.read(KVALUEADDR + 1) == 0xFF && EEPROM.read(KVALUEADDR + 2) == 0xFF && EEPROM.read(KVALUEADDR + 3) == 0xFF) || (this->_kvalue > 100) || (this->_kvalue < 0.01)) {
    this->_kvalue = 10.0;
    EEPROM_write(KVALUEADDR, this->_kvalue);
  }
  Serial.print("_kvalue:");
  Serial.println(this->_kvalue);
}

float DFRobot_EC10::readEC(float voltage, float temperature) {
  float value = 0;
  this->_ecvalueRaw = 1000 * voltage / RES2 / ECREF * this->_kvalue * 10.0;
  value = this->_ecvalueRaw / (1.0 + 0.0185 * (temperature - 25.0));  //temperature compensation
  this->_ecvalue = value;                                             //store the EC value for Serial CMD calibration
  return value;
}

int DFRobot_EC10::calibration(float voltage, float temperature, char* cmd) {
  _voltage = voltage;
  _temperature = temperature;
  //strupr(cmd);
  return ecCalibration(cmdParse(cmd));
}

void DFRobot_EC10::calibration(float voltage, float temperature) {
  this->_voltage = voltage;
  this->_temperature = temperature;

  if (cmdSerialDataAvailable() > 0) {
    ecCalibration(cmdParse());  // if received Serial CMD from the serial monitor, enter into the calibration mode
  }
}

boolean DFRobot_EC10::cmdSerialDataAvailable() {
//  char cmdReceivedChar;
//  static unsigned long cmdReceivedTimeOut = millis();
//  while (Serial.available() > 0) {
//    if (millis() - cmdReceivedTimeOut > 500U) {
//      this->_cmdReceivedBufferIndex = 0;
//      memset(this->_cmdReceivedBuffer, 0, (ReceivedBufferLength));
//    }
//    cmdReceivedTimeOut = millis();
//    cmdReceivedChar = Serial.read();
//    if (cmdReceivedChar == '\n' || this->_cmdReceivedBufferIndex == ReceivedBufferLength - 1) {
//      this->_cmdReceivedBufferIndex = 0;
//      strupr(this->_cmdReceivedBuffer);
//      return true;
//    } else {
//      this->_cmdReceivedBuffer[this->_cmdReceivedBufferIndex] = cmdReceivedChar;
//      this->_cmdReceivedBufferIndex++;
//    }
//  }
//  return false;
}

byte DFRobot_EC10::cmdParse(const char* cmd) {
  byte modeIndex = 0;
  if (strstr(cmd, "ENTEREC") != NULL)
    modeIndex = 1;
  else if (strstr(cmd, "EXITEC") != NULL)
    modeIndex = 3;
  else if (strstr(cmd, "CALEC") != NULL)
    modeIndex = 2;
  //Serial.println(modeIndex);
  return modeIndex;
}

byte DFRobot_EC10::cmdParse() {
  byte modeIndex = 0;
  if (strstr(this->_cmdReceivedBuffer, "ENTEREC") != NULL)
    modeIndex = 1;
  else if (strstr(this->_cmdReceivedBuffer, "EXITEC") != NULL)
    modeIndex = 3;
  else if (strstr(this->_cmdReceivedBuffer, "CALEC") != NULL)
    modeIndex = 2;
  return modeIndex;
}

int DFRobot_EC10::ecCalibration(byte mode) {
  char* receivedBufferPtr;
  static boolean ecCalibrationFinish = 0;
  static boolean enterCalibrationFlag = 0;
  static float rawECsolution;
  float KValueTemp;
  int sts;
  switch (mode) {
    case 0:
      if (enterCalibrationFlag)
        //  Serial.println(F(">>>Command Error<<<"));
        Serial.println("ec:0");
        sts = 0;
      break;

    case 1:
      enterCalibrationFlag = 1;
      ecCalibrationFinish = 0;
      // Serial.println();
      // Serial.println(F(">>>Enter Calibration Mode<<<"));
      // Serial.println(F(">>>Please put the probe into the 12.88ms/cm buffer solution<<<"));
      // Serial.println();
      Serial.println("ec:1");
      sts = 1;
      break;

    case 2:
      if (enterCalibrationFlag) {
        if ((this->_ecvalueRaw > 6) && (this->_ecvalueRaw < 18))  //recognize 12.88ms/cm buffer solution
        {
          rawECsolution = 12.9 * (1.0 + 0.0185 * (this->_temperature - 25.0));  //temperature compensation
        } else {
          // Serial.print(F(">>>Buffer Solution Error<<<   "));
          Serial.println("ec:5");
          sts = 5;
          ecCalibrationFinish = 0;
        }

        KValueTemp = RES2 * ECREF * rawECsolution / 1000.0 / this->_voltage / 10.0;  //calibrate the k value
        //Serial.print("Kvaluetemp");
        //Serial.println(KValueTemp);
        if ((KValueTemp > 0.5) && (KValueTemp < 1.5)) {
          // Serial.println();
          // Serial.print(F(">>>Successful,K:"));
          // Serial.print(KValueTemp);
          // Serial.println(F(", Send EXIT to Save and Exit<<<"));
          Serial.println("ec:8");
          sts = 8;
          this->_kvalue = KValueTemp;

          ecCalibrationFinish = 1;
        } else {
          // Serial.println();
          // Serial.println(F(">>>Failed,Try Again<<<"));
          // Serial.println();
          Serial.println("ec:9");
          sts = 9;
          ecCalibrationFinish = 0;
        }
      }
      break;

    case 3:
      if (enterCalibrationFlag) {
        Serial.println();
        if (ecCalibrationFinish) {
          if ((this->_ecvalueRaw > 6) && (this->_ecvalueRaw < 18)) {
            EEPROM_write(KVALUEADDR, this->_kvalue);
            // Serial.print(F(">>>Calibration Successful"));
            Serial.println("ec:6");
            sts = 6;
          }


        } else {
          // Serial.print(F(">>>Calibration Failed"));
          Serial.println("ec:7");
          sts = 7;
        }
        // Serial.println(F(",Exit Calibration Mode<<<"));
        // Serial.println();
        ecCalibrationFinish = 0;
        enterCalibrationFlag = 0;
      }
      break;
  }
  return sts;
}
