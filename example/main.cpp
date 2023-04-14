#include <Arduino.h>
#include <MLX90316.h>

// Baudrate and all pins can be changed as desired
const int BAUDRATE = 115200;
const int SS_PIN = 5;
const int SCK_PIN = 3;
const int MOSI_PIN = 4;

MLX90316 mlx90316(SS_PIN, SCK_PIN, MOSI_PIN);

void setup()
{
  Serial.begin(BAUDRATE);
  // wait for Serial to initialize
  while (!Serial) {;}
}

void loop()
{
  // continuosly read and print angle
  mlx90316.read_angle();
  Serial.println(mlx90316.get_angle());
}
