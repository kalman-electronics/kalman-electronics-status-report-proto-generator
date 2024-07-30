#ifndef KALMAN_STATUS_REPORT_WHEELS_H_
#define KALMAN_STATUS_REPORT_WHEELS_H_

// Include the standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include the user libraries
#include "kalman-status-report-protocol/frames.h"
#include "kalman-status-report-protocol/common.h"

#define KALMAN_STATUS_REPORT_PROTOCOL_SUBSYSTEM_ID 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WheelsStatus Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define KALMAN_STATUS_REPORT_WHEELSSTATUS_ID 12

#define KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1 0
#define KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2 255
       
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN 0
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX 100       
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN 100
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX 200       
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN 200
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX 300

typedef enum {
    ALGORITHM_TYPE_POSITION,
    ALGORITHM_TYPE_VELOCITY,
    ALGORITHM_TYPE_TORQUE,
} AlgorithmType_TypeDef;

typedef enum {
    ALGORITHM_TYPE2_POSITION = 1,
    ALGORITHM_TYPE2_VELOCITY = 2,
    ALGORITHM_TYPE2_TORQUE = 3,
} AlgorithmType2_TypeDef;

typedef struct __attribute__((packed)) {
    uint8_t controller_id;
    uint8_t driver_status;
    float temperature;
    AlgorithmType_TypeDef algorithm_type;
    AlgorithmType2_TypeDef algorithm_type2;
    bool testbool;
} WheelsStatus_FrameTypeDef;

KalmanProtocol_StatusTypeDef WheelsStatus_unpack(const RawDataFrame_TypeDef* raw_data, WheelsStatus_FrameTypeDef* frame) {
    if (raw_data->length != sizeof(WheelsStatus_FrameTypeDef) + KALMAN_PROTOCOL_STATUS_REPORT_ID_BYTES) {
        return KALMAN_PROTOCOL_STATUS_INVALID_FRAME_SIZE;
    }

    if (raw_data->data[0] != KALMAN_STATUS_REPORT_PROTOCOL_SUBSYSTEM_ID || raw_data->data[1] != KALMAN_STATUS_REPORT_WHEELSSTATUS_ID) {
        return KALMAN_PROTOCOL_STATUS_INVALID_FRAME_TYPE;
    }
    frame->controller_id = *((uint8_t*)&raw_data->data[2]);
    frame->driver_status = *((uint8_t*)&raw_data->data[3]);
    frame->temperature = *((float*)&raw_data->data[4]);
    frame->algorithm_type = (AlgorithmType_TypeDef)raw_data->data[5];
    frame->algorithm_type2 = (AlgorithmType2_TypeDef)raw_data->data[6];
    frame->testbool = *((bool*)&raw_data->data[7]);

    return KALMAN_PROTOCOL_STATUS_OK;
}

#endif // KALMAN_STATUS_REPORT__H_