#ifndef KALMAN_STATUS_REPORT_WHEELS_H_
#define KALMAN_STATUS_REPORT_WHEELS_H_

// Include the standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include the user libraries
#include "kalman-status-report-protocol/frames.h"
#include "kalman-status-report-protocol/common.h"

#define KALMAN_STATUS_REPORT_WHEELS_SUBSYSTEM_ID 1

typedef enum {
    KALMAN_STATUS_REPORT_WHEELS_WHEELSSTATUS_FRAME_ID = 12,
} KalmanStatusReport_Wheels_FrameID_TypeDef;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef enum {
    KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1 = 0,
    KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2 = 255,
} WheelsStatus_DriverStatus_HealthCheck_TypeDef;

typedef enum {       
    KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN = 0,
    KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX = 100,       
    KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN = 100,
    KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX = 200,       
    KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN = 200,
    KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX = 300,
} WheelsStatus_Temperature_HealthCheck_TypeDef;

#define KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION "Driver is ready"
#define KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2_DESCRIPTION "Driver is not ready"
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_DESCRIPTION "Temperature is normal"
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_DESCRIPTION "Temperature is high"
#define KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_DESCRIPTION "Temperature is very high"

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

typedef struct _packed_ {
    uint8_t controller_id;
    uint8_t driver_status;
    float temperature;
    uint8_t algorithm_type;
    uint8_t algorithm_type2;
    uint8_t testbool;
} WheelsStatus_FrameTypeDef;

////////////////////////////////////////
/// Setters
////////////////////////////////////////
_nonnull_
void WheelsStatus_set_controller_id(WheelsStatus_FrameTypeDef* frame, uint8_t value) {
    frame->controller_id = value;
}

_nonnull_
void WheelsStatus_set_driver_status(WheelsStatus_FrameTypeDef* frame, uint8_t value) {
    frame->driver_status = value;
}

_nonnull_
void WheelsStatus_set_temperature(WheelsStatus_FrameTypeDef* frame, float value) {
    frame->temperature = value;
}

_nonnull_
void WheelsStatus_set_algorithm_type(WheelsStatus_FrameTypeDef* frame, AlgorithmType_TypeDef value) {
    frame->algorithm_type = (uint8_t)value;
}

_nonnull_
void WheelsStatus_set_algorithm_type2(WheelsStatus_FrameTypeDef* frame, AlgorithmType2_TypeDef value) {
    frame->algorithm_type2 = (uint8_t)value;
}

_nonnull_
void WheelsStatus_set_testbool(WheelsStatus_FrameTypeDef* frame, bool value) {
    frame->testbool = (uint8_t)value;
}


////////////////////////////////////////
/// Getters
////////////////////////////////////////
_nonnull_
uint8_t WheelsStatus_get_controller_id(const WheelsStatus_FrameTypeDef* frame) {
    return frame->controller_id;
}

_nonnull_
uint8_t WheelsStatus_get_driver_status(const WheelsStatus_FrameTypeDef* frame) {
    return frame->driver_status;
}

_nonnull_
float WheelsStatus_get_temperature(const WheelsStatus_FrameTypeDef* frame) {
    return frame->temperature;
}

_nonnull_
AlgorithmType_TypeDef WheelsStatus_get_algorithm_type(const WheelsStatus_FrameTypeDef* frame) {
    return (AlgorithmType_TypeDef)frame->algorithm_type;
}

_nonnull_
AlgorithmType2_TypeDef WheelsStatus_get_algorithm_type2(const WheelsStatus_FrameTypeDef* frame) {
    return (AlgorithmType2_TypeDef)frame->algorithm_type2;
}

_nonnull_
bool WheelsStatus_get_testbool(const WheelsStatus_FrameTypeDef* frame) {
    return (bool)frame->testbool;
}


////////////////////////////////////////
/// Frame Packing and Unpacking
////////////////////////////////////////
_nonnull_
KalmanStatusReport_StatusTypeDef WheelsStatus_init(WheelsStatus_FrameTypeDef* frame) {

    return KALMAN_STATUS_REPORT_OK;
}

_nonnull_
KalmanStatusReport_StatusTypeDef WheelsStatus_unpack(const RawDataFrame_TypeDef* raw_data, WheelsStatus_FrameTypeDef* frame) {
    if (raw_data->length != sizeof(WheelsStatus_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES) {
        return KALMAN_STATUS_REPORT_INVALID_DATA_SIZE;
    }

    if (raw_data->data[0] != KALMAN_STATUS_REPORT_WHEELS_SUBSYSTEM_ID ||
        raw_data->data[1] != KALMAN_STATUS_REPORT_WHEELS_WHEELSSTATUS_FRAME_ID) {
        return KALMAN_STATUS_REPORT_INVALID_FRAME_TYPE;
    }
    
    frame->controller_id = raw_data->data[0 + KALMAN_STATUS_REPORT_ID_BYTES];
    frame->driver_status = raw_data->data[1 + KALMAN_STATUS_REPORT_ID_BYTES];
    frame->temperature = *((float*)&raw_data->data[2 + KALMAN_STATUS_REPORT_ID_BYTES]);
    frame->algorithm_type = raw_data->data[6 + KALMAN_STATUS_REPORT_ID_BYTES];
    frame->algorithm_type2 = raw_data->data[7 + KALMAN_STATUS_REPORT_ID_BYTES];
    frame->testbool = raw_data->data[8 + KALMAN_STATUS_REPORT_ID_BYTES];

    return KALMAN_STATUS_REPORT_OK;
}

_nonnull_
KalmanStatusReport_StatusTypeDef WheelsStatus_pack(const WheelsStatus_FrameTypeDef* frame, RawDataFrame_TypeDef* raw_data) {
    if (raw_data->capacity < sizeof(WheelsStatus_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES) {
        return KALMAN_STATUS_REPORT_INVALID_DATA_SIZE;
    }

    raw_data->data[0] = KALMAN_STATUS_REPORT_WHEELS_SUBSYSTEM_ID;
    raw_data->data[1] = KALMAN_STATUS_REPORT_WHEELS_WHEELSSTATUS_FRAME_ID;
    
    raw_data->data[0 + KALMAN_STATUS_REPORT_ID_BYTES] = frame->controller_id;
    raw_data->data[1 + KALMAN_STATUS_REPORT_ID_BYTES] = frame->driver_status;
    *((float*)&raw_data->data[2 + KALMAN_STATUS_REPORT_ID_BYTES]) = frame->temperature;
    raw_data->data[6 + KALMAN_STATUS_REPORT_ID_BYTES] = frame->algorithm_type;
    raw_data->data[7 + KALMAN_STATUS_REPORT_ID_BYTES] = frame->algorithm_type2;
    raw_data->data[8 + KALMAN_STATUS_REPORT_ID_BYTES] = frame->testbool;

    raw_data->length = sizeof(WheelsStatus_FrameTypeDef) + KALMAN_STATUS_REPORT_ID_BYTES;

    return KALMAN_STATUS_REPORT_OK;
}

////////////////////////////////////////
/// Health Checks
////////////////////////////////////////
_nonnull_
KalmanStatusReport_StatusTypeDef WheelsStatus_DriverStatus_HealthCheckResult(const WheelsStatus_FrameTypeDef* frame) {
    if (frame->driver_status == KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1) {
        return OK;
    }
    if (frame->driver_status == KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2) {
        return CRITICAL;
    }
    return UNKNOWN;
}

_nonnull_
KalmanStatusReport_StatusTypeDef WheelsStatus_Temperature_HealthCheckResult(const WheelsStatus_FrameTypeDef* frame) {
    if (frame->temperature >= KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN
            && frame->temperature < KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX) {
        return OK;
    }
    if (frame->temperature >= KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN
            && frame->temperature < KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX) {
        return WARNING;
    }
    if (frame->temperature >= KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN
            && frame->temperature < KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX) {
        return CRITICAL;
    }
    return UNKNOWN;
}

_nonnull_
const char* WheelsStatus_DriverStatus_HealthCheckTroubleshoot(const WheelsStatus_FrameTypeDef* frame) {
    return "Unknown troubleshoot";
}

_nonnull_
const char* WheelsStatus_Temperature_HealthCheckTroubleshoot(const WheelsStatus_FrameTypeDef* frame) {
    return "Unknown troubleshoot";
}

_nonnull_
const char* WheelsStatus_DriverStatus_HealthCheckDescription(const WheelsStatus_FrameTypeDef* frame) {
    if (frame->driver_status == KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1) {
        return KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION;
    }
    if (frame->driver_status == KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2) {
        return KALMAN_STATUS_WHEELSSTATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2_DESCRIPTION;
    }
    return "Unknown description";
}

_nonnull_
const char* WheelsStatus_Temperature_HealthCheckDescription(const WheelsStatus_FrameTypeDef* frame) {
    if (frame->temperature >= KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN
            && frame->temperature < KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX) {
        return KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_OK_1_DESCRIPTION;    
    }
    if (frame->temperature >= KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN
            && frame->temperature < KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX) {
        return KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_DESCRIPTION;    
    }
    if (frame->temperature >= KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN
            && frame->temperature < KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX) {
        return KALMAN_STATUS_WHEELSSTATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_DESCRIPTION;    
    }
    return "Unknown description";
}


#endif // KALMAN_STATUS_REPORT__H_