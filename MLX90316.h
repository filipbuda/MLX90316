/*
  MLX90316.h - Library for interfacing Teensy 4.1 to MLX90316.
  Created by Filip Buda.
  Released into the public domain.
*/
#ifndef MLX90316_h
#define MLX90316_h

#include "Arduino.h"

class MLX90316
{
public:
    MLX90316(int SS_PIN, int SCK_PIN, int MOSI_PIN);
    void read_angle();
    double get_angle();

private:
    byte _read_byte();
    void _send_byte(byte data);
    void _send_start_bytes();
    void _read_data_bytes();
    void _transceive_data_frame();
    bool _check_valid_angle();
    int _SS_PIN;
    int _SCK_PIN;
    int _MOSI_PIN;
    double _angle;
    byte _data_byte_1;
    byte _data_byte_2;
};

#endif