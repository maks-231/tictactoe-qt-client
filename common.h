#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

const uint8_t EMPTY = 0;
const uint8_t CROS = 1;
const uint8_t CIRCLE = 2;
const uint8_t CROS2 = 11;
const uint8_t CIRCLE2 = 22;

const uint8_t COMMAND = 1;
const uint8_t NEXT_STEP_BY = 3;
const uint8_t PLAY_FOR = 4;

const int SERVICE_FIELDS = 5;
const int MAX_ROW = 3;
const int MAX_COL = 3;

const int COMMANDS_BUFFER_SIZE = 2;

const int INITIAL_WIDGET_WIDTH = 50;
const int INITIAL_WIDGET_HIGHT = 50;

const int BUFF_SIZE = 1024;
const int SERVICE_DATA_SIZE = 2;
const int DATA_SIZE = 14;

#endif // COMMON_H
