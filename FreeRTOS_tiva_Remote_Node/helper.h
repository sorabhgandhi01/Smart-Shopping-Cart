/*
 * helper.h
 *
 *  Created on: Apr 24, 2019
 *      Author: omrah
 */

#ifndef HELPER_H_
#define HELPER_H_


typedef struct
{
    char msgID[20];
    uint32_t TaskData;
}TaskData_t;

#include <stdint.h>

#define NUM_LOG_LEVELS 5
#define NUM_MSG_TYPE 12

typedef enum MSG_TYPE_T
{
    HEART_BEAT = 0,
    SENSOR_START_UP_TEST_PASSED,
    SENSOR_START_UP_TEST_FAILED,
    TASK_START_UP_TEST_PASSED,
    TASK_START_UP_TEST_FAILED,
    GESTURE_SENSOR_INACTIVE,
    DISTANCE_SENSOR_INACTIVE,
    RFID_SENSOR_INACTIVE,
    PUSH_BUTTON_SENSOR_DATA,
    DISTANCE_SENSOR_DATA,
    GESTURE_SENSOR_DATA,
    RFID_SENSOR_DATA,
}MSG_TYPE;

typedef enum PB_DATA_T
{
    NO_PB_UPDATE = -1,
    FORWARD_BUTTON_PRESSED,
    FORWARD_BUTTON_RELEASED,
    BACKWARD_BUTTON_PRESSED,
    BACKWARD_BUTTON_RELEASED,
    LEFT_BUTTON_PRESSED,
    LEFT_BUTTON_RELEASED,
    RIGHT_BUTTON_PRESSED,
    RIGHT_BUTTON_RELEASED,
}PB_DATA;

typedef enum GS_DATA_T
{
    GS_ERROR = -1,
    GS_FORWARD,
    GS_BACKWARD,
    GS_RIGHT,
    GS_LEFT,
    GS_NEAR,
    GS_FAR,
    GS_NO_GESTURE,
}GS_DATA;

typedef enum LOG_LEVELS_T
{
    ERROR_T = 0,
    WARNING,
    DEBUG_T,
    INFO,
    ALERT,
}LOG_LEVELS;

typedef struct TIVA_MSG_T
{
    uint8_t msg_type;
    uint8_t log_level;
    uint32_t sensor_data;
}TIVA_MSG;

const static char *const LOG_LEVEL_STRING[NUM_LOG_LEVELS] =
{
    "Error",
    "WARNING",
    "DEBUG",
    "INFO",
    "ALERT",
};

const static char *const MSG_TYPE_STRING[NUM_MSG_TYPE] =
{
    "HEART-BEAT DATA",
    "SENSOR BIST PASSED",
    "SENSOR BIST FAILED",
    "TASK CREATION BIST PASSED",
    "TASK CREATION BIST FAILED",
    "GESTURE SENSOR INACTIVE",
    "DISTANCE SENSOR INACTIVE",
    "RFID SENSOR INACTIVE",
    "PUSH BUTTON SENSOR DATA",
    "DISTANCE SENSOR DATA",
    "GESTURE SENSOR DATA",
    "RFID SENSOR DATA",
};

#endif /* HELPER_H_ */
