#include "Arduino.h"
#include "MLX90316.h"
#include "Consts.h"

/**
 * Send bytes of data from Teensy and read bytes of data from MLX90316 sensor and
 * convert bytes of read data to angle in range [0,360] degrees.
 *
 * ...
 *
 * @param SS_PIN slave select pin
 * @param SCK_PIN clock pin
 * @param MOSI_PIN master out slave in pin
 */
MLX90316::MLX90316(int SS_PIN, int SCK_PIN, int MOSI_PIN)
{
    _SS_PIN = SS_PIN;
    _SCK_PIN = SCK_PIN;
    _MOSI_PIN = MOSI_PIN;

    pinMode(_SS_PIN, OUTPUT);
    pinMode(_SCK_PIN, OUTPUT);
    digitalWriteFast(_SS_PIN, HIGH);

    delay(T8);
}

/**
 * Read byte of data from sensor via bit banged SPI.
 *
 * @return data that has been read
 */
byte MLX90316::_read_byte()
{
    pinMode(_MOSI_PIN, INPUT_PULLUP);
    byte data = NULL_BYTE;
    for (int i = BIT_EIGHT_IDX; i >= BIT_ONE_IDX; i--)
    {
        // clock HI
        digitalWriteFast(_SCK_PIN, HIGH);

        // read value of bit halfway into clock HI pulse
        delayMicroseconds(T2 * HALF_SCK_PULSE);
        bitWrite(data, i, digitalReadFast(_MOSI_PIN));
        delayMicroseconds(T2 * HALF_SCK_PULSE);
        
        // clock LO
        digitalWriteFast(_SCK_PIN, LOW);
        delayMicroseconds(T2);
    }
    return data;
}

/**
 * Send byte of data to sensor via bit banged SPI.
 *
 * @param data Byte of data to be sent 
 */
void MLX90316::_send_byte(byte data)
{
    pinMode(_MOSI_PIN, OUTPUT);
    for (int i = BIT_ONE_IDX; i < BIT_NINE_IDX; i++)
    {
        // set or clear bit before clock HI pulse
        digitalWriteFast(_MOSI_PIN, bitRead(data, i)); 
        delayMicroseconds(T7);

        // clock HI
        digitalWriteFast(_SCK_PIN, HIGH);
        delayMicroseconds(T2);

        // clock LO
        digitalWriteFast(_SCK_PIN, LOW);
        // compensate for T7 delay from next iteration being part of clock LO delay
        delayMicroseconds(T2 - T7);
    }
}

/**
 * Send two start bytes of data frame to sensor.
 */
void MLX90316::_send_start_bytes()
{
    _send_byte(START_BYTE_1);
    // compensate for clock LO delay being part of interbyte delay
    delayMicroseconds(T3 - T2);

    _send_byte(START_BYTE_2);
    // compensate for clock LO delay being part of interbyte delay
    delayMicroseconds(T4 - T2);
}

/**
 * Read two bytes of data from sensor.
 */
void MLX90316::_read_data_bytes()
{
    _data_byte_1 = _read_byte();
    // compensate for clock LO delay being part of interbyte delay
    delayMicroseconds(T4 - T2);

    _data_byte_2 = _read_byte();
    // compensate for clock LO delay being part of interbyte delay
    delayMicroseconds(T4 - T2);
}

/**
 * Set slave select pin to low to start communication.
 * Send two start bytes of data frame to sensor.
 * Read two bytes of data from sensor.
 * Set slave select pin to high to end communication.
 */
void MLX90316::_transceive_data_frame()
{
    digitalWriteFast(_SS_PIN, LOW);
    delayMicroseconds(T1);

    _send_start_bytes();
    _read_data_bytes();

    digitalWriteFast(_SS_PIN, HIGH);
    delay(T6);
}

/**
 * Transmit and receive bytes of data between teensy and sensor.
 * Check if received bytes contain valid angle data.
 * Convert data and update the value of _angle if data is valid, else set _angle to 361.
 */
void MLX90316::read_angle()
{
    unsigned int data;

    _transceive_data_frame();

    if (_check_valid_angle()) // convert data and update value of _angle if data is valid
    {
        data = (uint16_t(_data_byte_1) << SHIFT_ONE_BYTE) + _data_byte_2;
        data = (data >> SHIFT_TWO_BITS);

        _angle = (double)data;
        _angle = _angle * CONVERSION_FACTOR; // convert angle to 360 degrees
    }

    else // set _angle to 361 if data is invalid
    {
        _angle = INVALID;
    }
}

/**
 * Check if received bytes contain valid angle data.
 * Bytes contain valid angle data if second byte ends in "01".
 *
 * @returns true if bytes contain valid angle data, else false
 */
bool MLX90316::_check_valid_angle()
{
    if ((bitRead(_data_byte_2, BIT_TWO_IDX) == 0) and (bitRead(_data_byte_2, BIT_ONE_IDX) == 1)) // if second data byte ends in "01", data is valid
    {
        return true;
    }

    else
    {
        return false;
    }
}

/**
 * Get angle read from sensor.
 *
 * @returns angle from sensor
 */
double MLX90316::get_angle()
{
    return _angle;
}