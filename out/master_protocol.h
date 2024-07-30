#ifndef KALMAN_STATUS_REPORT_MASTER_H_
#define KALMAN_STATUS_REPORT_MASTER_H_

// Include the standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include the user libraries
#include "kalman-status-report-protocol/frames.h"
#include "kalman-status-report-protocol/common.h"

#define KALMAN_STATUS_REPORT_PROTOCOL_SUBSYSTEM_ID 2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MasterStatus Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define KALMAN_STATUS_REPORT_MASTERSTATUS_ID 13

typedef enum {
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1 = 0,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2 = 1,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3 = 2,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_4 = 255,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_5 = 255,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_6 = 255,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_7 = 255,
} MasterStatus_CanStatus_HealthCheck_TypeDef;

typedef struct __attribute__((packed)) {
    uint8_t can_status;
} MasterStatus_FrameTypeDef;

KalmanProtocol_StatusTypeDef MasterStatus_unpack(const RawDataFrame_TypeDef* raw_data, MasterStatus_FrameTypeDef* frame) {
    if (raw_data->length != sizeof(MasterStatus_FrameTypeDef) + KALMAN_PROTOCOL_STATUS_REPORT_ID_BYTES) {
        return KALMAN_PROTOCOL_STATUS_INVALID_FRAME_SIZE;
    }

    if (raw_data->data[0] != KALMAN_STATUS_REPORT_PROTOCOL_SUBSYSTEM_ID || raw_data->data[1] != KALMAN_STATUS_REPORT_MASTERSTATUS_ID) {
        return KALMAN_PROTOCOL_STATUS_INVALID_FRAME_TYPE;
    }
    frame->can_status = *((uint8_t*)&raw_data->data[2]);

    return KALMAN_PROTOCOL_STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DevicesAlive Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define KALMAN_STATUS_REPORT_DEVICESALIVE_ID 14

typedef enum {
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1 = 0,       
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN = 1,
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX = 3,
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_OK_3 = 4,
} DevicesAlive_Wheels_HealthCheck_TypeDef;

typedef struct __attribute__((packed)) {
    uint8_t wheels;
} DevicesAlive_FrameTypeDef;

KalmanProtocol_StatusTypeDef DevicesAlive_unpack(const RawDataFrame_TypeDef* raw_data, DevicesAlive_FrameTypeDef* frame) {
    if (raw_data->length != sizeof(DevicesAlive_FrameTypeDef) + KALMAN_PROTOCOL_STATUS_REPORT_ID_BYTES) {
        return KALMAN_PROTOCOL_STATUS_INVALID_FRAME_SIZE;
    }

    if (raw_data->data[0] != KALMAN_STATUS_REPORT_PROTOCOL_SUBSYSTEM_ID || raw_data->data[1] != KALMAN_STATUS_REPORT_DEVICESALIVE_ID) {
        return KALMAN_PROTOCOL_STATUS_INVALID_FRAME_TYPE;
    }
    frame->wheels = *((uint8_t*)&raw_data->data[2]);

    return KALMAN_PROTOCOL_STATUS_OK;
}

#endif // KALMAN_STATUS_REPORT__H_