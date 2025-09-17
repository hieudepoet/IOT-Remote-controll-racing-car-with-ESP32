# Introduction

This a source code folder to buld and monitor a remote control robot racing car model. This readme file is written for people who have experience in the field of IOT or electronics, so it will be a bit difficult to understand for newbies or people who are not in this field, so do not hesitate to [CONTACT ME](https://github.com/hieudepoet/) to receive maximum support in your learning and exploration process.

## Installation
- Download VSCode and add basic extension to go live a .html web
- Download Arduino IDE 
- Clone this repository

## Usage

- First of all you must have a remote controll racing car model that is electronically designed according to the configurations in the ino code file.
- You should use a 4s Lipo pin to provide electricity for the robot (Based on my experience).
- You must have wifi or mobile data to monitor this model.
- Step 1: In the Arduino IDE, File -> Preferences -> Additional Boards Manager URLs. Paste this URLs: https://raw.githubusercontent.com/espressif/arduino-esp32/sh-pages/package_esp32_index.json
- Step 2: Tools -> Board. Choose the compatible dev module for your ESP32.
- Step 3: Make sure the libraries imported in the ino code file have been downloaded to your computer. Exp: <ESP32Servo.h>; <WebServer.h>; <AsyncTCP.h>; <stdio.h>; ... You can check in Sketch -> Include Library.
- Step 4: Connect your laptop or your PC to the ESP32 device by USB to USB-C cable.
- Step 5: Upload the code to ESP32 and wait until uploading done.
- Step 6: Tools -> ESP32 sketch data upload. Wait until uploading done.
- Step 7: Disconnect the Esp32 to your device and connect the Esp32 to the model. Engine it and wait until the Esp32's wifi is on-air.
- Step 8: Use the device your are coding or other mobile device to connect the esp32 and access 192.168.4.1 to controll the model by a virtual gamepad.   
## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## Contact

- Feel free to ask everywhen you need during building your own IOT model by emailling me or contacting me via other forms of social media communication ([Visit my Github profile](https://github.com/hieudepoet/)). I usually respond immediately.  

## License

[MIT](https://choosealicense.com/licenses/mit/)
