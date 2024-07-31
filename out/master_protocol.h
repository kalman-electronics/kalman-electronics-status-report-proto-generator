#ifndef KALMAN_STATUS_REPORT_MASTER_H_
#define KALMAN_STATUS_REPORT_MASTER_H_

// Include the standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include the user libraries
#include "kalman-status-report-protocol/frames.h"
#include "kalman-status-report-protocol/common.h"

#define KALMAN_STATUS_REPORT_MASTER_SUBSYSTEM_ID 2

typedef enum {
    KALMAN_STATUS_REPORT_MASTER_MASTERSTATUS_FRAME_ID = 13,
    KALMAN_STATUS_REPORT_MASTER_DEVICESALIVE_FRAME_ID = 14,
} KalmanStatusReport_Master_FrameID_TypeDef;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef enum {
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1 = 0,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2 = 1,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3 = 2,
    KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_4 = 255,
} MasterStatus_CanStatus_HealthCheck_TypeDef;

#define KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1_TROUBLESHOOT "Nic nie rób"
#define KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION "Fajen"
#define KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2_DESCRIPTION "Nie działa ueuos"
#define KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3_DESCRIPTION " Nie działa uniwvrsal"

typedef struct _packed_ {
    uint8_t can_status;
} MasterStatus_FrameTypeDef;

////////////////////////////////////////
/// Setters
////////////////////////////////////////
_nonnull_
void MasterStatus_set_can_status(MasterStatus_FrameTypeDef* frame, uint8_t value) {
    frame->can_status = value;
}


////////////////////////////////////////
/// Getters
////////////////////////////////////////
_nonnull_
uint8_t MasterStatus_get_can_status(const MasterStatus_FrameTypeDef* frame) {
    return frame->can_status;
}


////////////////////////////////////////
/// Frame Packing and Unpacking
////////////////////////////////////////
_nonnull_
KalmanStatusReport_StatusTypeDef MasterStatus_init(MasterStatus_FrameTypeDef* frame) {

    return KALMAN_STATUS_REPORT_OK;
}

_nonnull_
KalmanStatusReport_StatusTypeDef MasterStatus_unpack(const RawDataFrame_TypeDef* raw_data, MasterStatus_FrameTypeDef* frame) {
    if (raw_data->length != sizeof(MasterStatus_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES) {
        return KALMAN_STATUS_REPORT_INVALID_DATA_SIZE;
    }

    if (raw_data->data[0] != KALMAN_STATUS_REPORT_MASTER_SUBSYSTEM_ID ||
        raw_data->data[1] != KALMAN_STATUS_REPORT_MASTER_MASTERSTATUS_FRAME_ID) {
        return KALMAN_STATUS_REPORT_INVALID_FRAME_TYPE;
    }
    
    frame->can_status = raw_data->data[0 + KALMAN_STATUS_REPORT_ID_BYTES];

    return KALMAN_STATUS_REPORT_OK;
}

_nonnull_
KalmanStatusReport_StatusTypeDef MasterStatus_pack(const MasterStatus_FrameTypeDef* frame, RawDataFrame_TypeDef* raw_data) {
    if (raw_data->capacity < sizeof(MasterStatus_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES) {
        return KALMAN_STATUS_REPORT_INVALID_DATA_SIZE;
    }

    raw_data->data[0] = KALMAN_STATUS_REPORT_MASTER_SUBSYSTEM_ID;
    raw_data->data[1] = KALMAN_STATUS_REPORT_MASTER_MASTERSTATUS_FRAME_ID;
    
    raw_data->data[0 + KALMAN_STATUS_REPORT_ID_BYTES] = frame->can_status;

    raw_data->length = sizeof(MasterStatus_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES;

    return KALMAN_STATUS_REPORT_OK;
}

////////////////////////////////////////
/// Health Checks
////////////////////////////////////////
_nonnull_
KalmanStatusReport_StatusTypeDef MasterStatus_CanStatus_HealthCheckResult(const MasterStatus_FrameTypeDef* frame) {
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1) {
        return OK;
    }
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2) {
        return WARNING;
    }
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3) {
        return WARNING;
    }
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_4) {
        return CRITICAL;
    }
    return UNKNOWN;
}

_nonnull_
const char* MasterStatus_CanStatus_HealthCheckTroubleshoot(const MasterStatus_FrameTypeDef* frame) {
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1) {
        return KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1_TROUBLESHOOT;
    }
    return "Unknown troubleshoot";
}

_nonnull_
const char* MasterStatus_CanStatus_HealthCheckDescription(const MasterStatus_FrameTypeDef* frame) {
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1) {
        return KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION;
    }
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2) {
        return KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2_DESCRIPTION;
    }
    if (frame->can_status == KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3) {
        return KALMAN_STATUS_MASTERSTATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3_DESCRIPTION;
    }
    return "Unknown description";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef enum {
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1 = 0,       
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN = 1,
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX = 3,
    KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_OK_3 = 4,
} DevicesAlive_Wheels_HealthCheck_TypeDef;

#define KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1_TROUBLESHOOT "Check CAN and power connection to wheels controllers"
#define KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_DESCRIPTION "Some wheels are not responding"
#define KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_OK_3_DESCRIPTION "All wheels are alive"

typedef struct _packed_ {
    uint8_t wheels;
} DevicesAlive_FrameTypeDef;

////////////////////////////////////////
/// Setters
////////////////////////////////////////
_nonnull_
void DevicesAlive_set_wheels(DevicesAlive_FrameTypeDef* frame, uint8_t value) {
    frame->wheels = value;
}


////////////////////////////////////////
/// Getters
////////////////////////////////////////
_nonnull_
uint8_t DevicesAlive_get_wheels(const DevicesAlive_FrameTypeDef* frame) {
    return frame->wheels;
}


////////////////////////////////////////
/// Frame Packing and Unpacking
////////////////////////////////////////
_nonnull_
KalmanStatusReport_StatusTypeDef DevicesAlive_init(DevicesAlive_FrameTypeDef* frame) {

    return KALMAN_STATUS_REPORT_OK;
}

_nonnull_
KalmanStatusReport_StatusTypeDef DevicesAlive_unpack(const RawDataFrame_TypeDef* raw_data, DevicesAlive_FrameTypeDef* frame) {
    if (raw_data->length != sizeof(DevicesAlive_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES) {
        return KALMAN_STATUS_REPORT_INVALID_DATA_SIZE;
    }

    if (raw_data->data[0] != KALMAN_STATUS_REPORT_MASTER_SUBSYSTEM_ID ||
        raw_data->data[1] != KALMAN_STATUS_REPORT_MASTER_DEVICESALIVE_FRAME_ID) {
        return KALMAN_STATUS_REPORT_INVALID_FRAME_TYPE;
    }
    
    frame->wheels = raw_data->data[0 + KALMAN_STATUS_REPORT_ID_BYTES];

    return KALMAN_STATUS_REPORT_OK;
}

_nonnull_
KalmanStatusReport_StatusTypeDef DevicesAlive_pack(const DevicesAlive_FrameTypeDef* frame, RawDataFrame_TypeDef* raw_data) {
    if (raw_data->capacity < sizeof(DevicesAlive_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES) {
        return KALMAN_STATUS_REPORT_INVALID_DATA_SIZE;
    }

    raw_data->data[0] = KALMAN_STATUS_REPORT_MASTER_SUBSYSTEM_ID;
    raw_data->data[1] = KALMAN_STATUS_REPORT_MASTER_DEVICESALIVE_FRAME_ID;
    
    raw_data->data[0 + KALMAN_STATUS_REPORT_ID_BYTES] = frame->wheels;

    raw_data->length = sizeof(DevicesAlive_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES;

    return KALMAN_STATUS_REPORT_OK;
}

////////////////////////////////////////
/// Health Checks
////////////////////////////////////////
_nonnull_
KalmanStatusReport_StatusTypeDef DevicesAlive_Wheels_HealthCheckResult(const DevicesAlive_FrameTypeDef* frame) {
    if (frame->wheels == KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1) {
        return CRITICAL;
    }
    if (frame->wheels >= KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN
            && frame->wheels < KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX) {
        return WARNING;
    }
    if (frame->wheels == KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_OK_3) {
        return OK;
    }
    return UNKNOWN;
}

_nonnull_
const char* DevicesAlive_Wheels_HealthCheckTroubleshoot(const DevicesAlive_FrameTypeDef* frame) {
    if (frame->wheels == KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1) {
        return KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1_TROUBLESHOOT;
    }
    return "Unknown troubleshoot";
}

_nonnull_
const char* DevicesAlive_Wheels_HealthCheckDescription(const DevicesAlive_FrameTypeDef* frame) {
    if (frame->wheels >= KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN
            && frame->wheels < KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX) {
        return KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_WARNING_2_DESCRIPTION;    
    }
    if (frame->wheels == KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_OK_3) {
        return KALMAN_STATUS_DEVICESALIVE_WHEELS_HEALTH_CHECK_OK_3_DESCRIPTION;
    }
    return "Unknown description";
}


#endif // KALMAN_STATUS_REPORT__H_