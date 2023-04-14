#ifndef Consts_h
#define Consts_h

#include "Arduino.h"

const double T1 = 20.2; // time between /SS = Lo and the first clock edge, microsec
const double T2 = 14.8; // SCK HI/LO time, microsec
const double T3 = 50.0; // time between first two bytes, microsec
const double T4 = 38.5; // time between all other bytes, microsec
const double T5 = 14.8; // time between last clock and /SS=high=chip de-selection, microsec
const double T6 = 1.5;  // time between frames, millisec
const double T7 = 7.2;  // time between writing bit and rising SCK edge, microsec
const double T8 = 16.0; // slave slave start-up time, millisec

const double CONVERSION_FACTOR = 360.0 / 16384.0; //  (Angle Span)/2^14

const double HALF_SCK_PULSE = 0.5;

const int SHIFT_TWO_BITS = 2;
const int SHIFT_ONE_BYTE = 8;
const int BIT_ONE_IDX = 0;
const int BIT_TWO_IDX = 1;
const int BIT_NINE_IDX = 8;
const int BIT_EIGHT_IDX = 7;

const int START_BYTE_1 = 0x55;
const int START_BYTE_2 = 0xFF;

const double INVALID = 361;

const byte NULL_BYTE = 0;

#endif