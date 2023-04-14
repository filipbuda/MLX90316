# MLX90316

## Description

Library for interfacing Teensy 4.1 and MLX90316 rotary position sensor IC.

## Dependencies

### Hardware
* Teensy 4.1
  * Might work with other Teensy versions, but tested only on Teensy 4.1
* Bi-directional Logic Level Converter
  * Tested on Adafruit BSS138 breakout
* MLX90316 sensor
* Magnet

### Software
* Teensy compatible IDE

## Instructions

### Hardware
* Mount magnet over MLX90316, see link below
  * https://www.eeweb.com/magnet-selection-for-mlx90316/
* Use the logic level converter to connect the /SS, SCLK, and MOSI pins on the MLX90316 to the corresponding pins on the Teensy (by default: /SS -> Teensy pin 5, SCLK -> Teensy pin 3, and MOSI -> Teensy pin 4)
   * WARNING: Do not form a direct connection between the Teensy and MLX90316 pins, as it will damage the Teensy
* Connect the Teensy, MLX90316, and logic level converter to power

### Software

#### If Using Arduino IDE with Teensyduino Add-On ...
* Add MLX90316.cpp, MLX90316.h, and Consts.h to folder titled MLX90316
* Create .zip archive from MLX90316 folder
* Follow these instructions to install library
  * https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries
* Paste code from main.cpp in repository example folder into sketch
* Verify and upload code to Teensy
* Open serial monitor (configured to 115200 baud by default) and angle will be printed continously
  
#### If using other IDE ...
* Add MLX90316.cpp to src folder in project directory 
* Add MLX90316.h and Consts.h to include folder in project directory 
* Add main.cpp in repository example folder to src folder in project directory
* Build and upload code to Teensy
* Open serial monitor (configured to 115200 baud by default) and angle will be printed continously

## Reference Material
* MLX90316 datasheet
  * https://media.melexis.com/-/media/files/documents/datasheets/mlx90316-datasheet-melexis.pdf
