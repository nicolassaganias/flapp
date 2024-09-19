##Flapp has different layer according to your knowlodge of Electronics and C++ Programming

**Layer 1: User.** Knows how to use the devices and the app

**Layer 2: DIY/DIWO User.** Knows how to solder and upload code to ESP-32 board and can buy the Electronic components according to his/her needs

**Layer 3: Advanced User.** Knows how to modify systems and code and to make new devices. Makes contribution to Flapp community.


##Layer 1. User: Refer to "App Usage Instructions" in README.md file

##Layer 2: DIYO/DIWO User/s:

**Materials:**
In all cases we use ESP-32 board as main controller where the sensors are physically conected trhough soldering and cables and also the one that interacts with the mobile phone app, sending the data thrpugh a BLE adapter that is within the board. The enclosure can be hand made or 3D printed. All the 3D files are in .../3d-files

Regarding the hardware: According to your needs you will need different elements, for example a phSensorBoard and a probe to build a phSensor or a HC-05 to be able to read a digital Scale.
Materials used and already tested:

- [phSensor](https://www.dfrobot.com/product-1782.html)

- [ecSensor](https://www.dfrobot.com/product-1123.html)

- [ORPSensor](https://www.dfrobot.com/product-1071.html)

- [Isolator](https://www.dfrobot.com/product-1621.html)

- [HC-05 Bluetooth Adapter](https://www.amazon.es/Integrated-Bluetooth-Module-Wireless-Serial/dp/B0DC4BF6XZ/ref=sr_1_3?__mk_es_ES=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=2ZQKXG5YFH5CP&dib=eyJ2IjoiMSJ9.My2nDUk5kUWJe7vdMPrkIG8_1FW_rNLnrWMASAc58ePl7it4EwC6IxnyIGyvIj3IluZaSN-AEPKotG53HvxYMKw7cp_YlQO4Zv4vwJwUiex5_DBMfsgYuTutM2Rfa2TQ2aUTpC0gntxOKN-U0J8k9NmhXJDoUP64mDH233UCqC2C9cil6WY7luHshrhDeVv4T8cFWDLtEXTxJFfXWxZXOq9loDG4tPuZK6ZIf_e_I72hNoc-0cNgZD2C--hqYe6AEa475wotn2PvOhKoRfWBKnS6mBfBYEl_zp80QfQtKvk.RmY1g-m2Xmhrgq_j-53yDiUT1euN25DvwwxomNN1Y1c&dib_tag=se&keywords=hc-05&qid=1726765997&sprefix=hc-05%2Caps%2C113&sr=8-3)

- [RS232 to Bluetooth Adapter](https://www.amazon.es/DSD-TECH-SH-B35-Adaptador-Compatible/dp/B0BMPTXZCH/ref=sr_1_1_sspa?dib=eyJ2IjoiMSJ9.-_Gv7Xs0HhmMIW_16tFuo15aCqUuSYsUwDMZTpLjZkYwmMLiwkBgKuiAql4ap9MPZBgt6RwVB4P4mexyq4gzuWvkJ0hqF_oedkDZZZcVqT-x8016LIVwSR3VAi-HIrQe4pq_B0VSFBrhifTO23p7YIj-SF4SkUpa6pjDLqIRCvE8tJj4QaDnRtQ60TrBc8QfLsCJw8rit7O2RX75UPazOxfJTB589rBF5NBTXqOMP_rmybHGdmgaCTB_3_xWXk-sm_H6a3A3wZGJ3ACxJu9SueeEkPTqB5DdfMxEK7psFqs.TvLO_4K1FvXhO0OIlueCtYv4Wx-77woLZsK05VPnZBM&dib_tag=se&keywords=bluetooth+rs232+adapter&qid=1726765975&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1)

- [Pressure Sensor](https://www.dfrobot.com/product-1675.htmll)

Codes refer to (...)/Firmware/ESP32_Updated to see the codes to upload into the ESP32 Board.
Inside this codes you can find the instructions for the correct pin conection for every device. 
