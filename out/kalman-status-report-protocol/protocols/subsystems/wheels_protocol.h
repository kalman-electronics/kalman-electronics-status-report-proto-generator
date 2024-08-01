#ifndef KALMAN_STATUS_REPORT_WHEELS_H_
#define KALMAN_STATUS_REPORT_WHEELS_H_

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "kalman-status-report-protocol/frames.h"
#include "kalman-status-report-protocol/common.h"
#include "kalman-status-report-protocol/protocols/protocol_common.h"

// Enum for all frame IDs in given subsystem
// ASSUMPTION: Values won't exceed 1 byte (255)
typedef enum {
    KSRP_WHEELS_WHEELS_STATUS_FRAME_ID = 12,
} KSRP_Wheels_FrameID;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {
    KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1 = 0,
    KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2 = 255,
} KSRP_Wheels_WheelsStatus_DriverStatus_HealthCheck;

typedef enum {       
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN = 0,
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX = 100,       
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN = 100,
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX = 200,       
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN = 200,
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX = 300,
} KSRP_Wheels_WheelsStatus_Temperature_HealthCheck;

#define KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION "Driver is ready"
#define KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2_DESCRIPTION "Driver is not ready"
#define KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_DESCRIPTION "Temperature is normal"
#define KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_DESCRIPTION "Temperature is high"
#define KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_DESCRIPTION "Temperature is very high"

typedef enum {
    ALGORITHM_TYPE_POSITION,
    ALGORITHM_TYPE_VELOCITY,
    ALGORITHM_TYPE_TORQUE,
} KSRP_Wheels_WheelsStatus_AlgorithmType;

typedef enum {
    ALGORITHM_TYPE2_POSITION = 1,
    ALGORITHM_TYPE2_VELOCITY = 2,
    ALGORITHM_TYPE2_TORQUE = 3,
} KSRP_Wheels_WheelsStatus_AlgorithmType2;

typedef struct _packed_ {
    uint8_t controller_id;
    uint8_t driver_status;
    float temperature;
    uint8_t algorithm_type;
    uint8_t algorithm_type2;
    uint8_t testbool;
} KSRP_Wheels_WheelsStatus_Frame;

#define KSRP_WHEELS_WHEELS_STATUS_TYPE_ID ( \
    KSRP_MAKE_TYPE_ID(KSRP_WHEELS_SUBSYSTEM_ID, \
    KSRP_WHEELS_WHEELS_STATUS_FRAME_ID))

bool KSRP_IsTypeIDInstanceof_Wheels_WheelsStatus(KSRP_TypeID type_id) {
    return type_id == KSRP_WHEELS_WHEELS_STATUS_TYPE_ID;
}

bool KSRP_IsRawDataInstanceof_Wheels_WheelsStatus(const KSRP_RawData_Frame* raw_data) {
    return raw_data->length == sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES &&
        KSRP_IsTypeIDInstanceof_Wheels_WheelsStatus(KSRP_MAKE_TYPE_ID(raw_data->data[0], raw_data->data[1]));
}

/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Setters
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_ControllerId(KSRP_Wheels_WheelsStatus_Frame* frame, uint8_t value) {
    frame->controller_id = value;
}

_nonnull_
void KSRP_Set_Wheels_WheelsStatus_DriverStatus(KSRP_Wheels_WheelsStatus_Frame* frame, uint8_t value) {
    frame->driver_status = value;
}

_nonnull_
void KSRP_Set_Wheels_WheelsStatus_Temperature(KSRP_Wheels_WheelsStatus_Frame* frame, float value) {
    frame->temperature = value;
}

_nonnull_
void KSRP_Set_Wheels_WheelsStatus_AlgorithmType(KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_Wheels_WheelsStatus_AlgorithmType value) {
    frame->algorithm_type = (uint8_t)value;
}

_nonnull_
void KSRP_Set_Wheels_WheelsStatus_AlgorithmType2(KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_Wheels_WheelsStatus_AlgorithmType2 value) {
    frame->algorithm_type2 = (uint8_t)value;
}

_nonnull_
void KSRP_Set_Wheels_WheelsStatus_Testbool(KSRP_Wheels_WheelsStatus_Frame* frame, bool value) {
    frame->testbool = (uint8_t)value;
}


/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Getters
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
uint8_t KSRP_Get_Wheels_WheelsStatus_ControllerId(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return frame->controller_id;
}

_nonnull_
uint8_t KSRP_Get_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return frame->driver_status;
}

_nonnull_
float KSRP_Get_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return frame->temperature;
}

_nonnull_
KSRP_Wheels_WheelsStatus_AlgorithmType KSRP_Get_Wheels_WheelsStatus_AlgorithmType(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return (KSRP_Wheels_WheelsStatus_AlgorithmType)frame->algorithm_type;
}

_nonnull_
KSRP_Wheels_WheelsStatus_AlgorithmType2 KSRP_Get_Wheels_WheelsStatus_AlgorithmType2(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return (KSRP_Wheels_WheelsStatus_AlgorithmType2)frame->algorithm_type2;
}

_nonnull_
bool KSRP_Get_Wheels_WheelsStatus_Testbool(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return (bool)frame->testbool;
}


/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Frame Construction
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
KSRP_Status KSRP_Init_Wheels_WheelsStatus(KSRP_Wheels_WheelsStatus_Frame* frame) {

    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Unpack_Wheels_WheelsStatus(const KSRP_RawData_Frame* raw_data, KSRP_Wheels_WheelsStatus_Frame* frame) {
    if (raw_data->length != sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }

    if (!KSRP_IsRawDataInstanceof_Wheels_WheelsStatus(raw_data)) {
        return KSRP_STATUS_INVALID_FRAME_TYPE;
    }
    
    frame->controller_id = raw_data->data[0 + KSRP_ID_BYTES];
    frame->driver_status = raw_data->data[1 + KSRP_ID_BYTES];
    frame->temperature = *((float*)&raw_data->data[2 + KSRP_ID_BYTES]);
    frame->algorithm_type = raw_data->data[6 + KSRP_ID_BYTES];
    frame->algorithm_type2 = raw_data->data[7 + KSRP_ID_BYTES];
    frame->testbool = raw_data->data[8 + KSRP_ID_BYTES];

    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Pack_Wheels_WheelsStatus(const KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_RawData_Frame* raw_data) {
    if (raw_data->capacity < sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }

    raw_data->data[0] = KSRP_WHEELS_SUBSYSTEM_ID;
    raw_data->data[1] = KSRP_WHEELS_WHEELS_STATUS_FRAME_ID;
    
    raw_data->data[0 + KSRP_ID_BYTES] = frame->controller_id;
    raw_data->data[1 + KSRP_ID_BYTES] = frame->driver_status;
    *((float*)&raw_data->data[2 + KSRP_ID_BYTES]) = frame->temperature;
    raw_data->data[6 + KSRP_ID_BYTES] = frame->algorithm_type;
    raw_data->data[7 + KSRP_ID_BYTES] = frame->algorithm_type2;
    raw_data->data[8 + KSRP_ID_BYTES] = frame->testbool;

    raw_data->length = sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES;

    return KSRP_STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Health Checks
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
KSRP_HealthCheckResult KSRP_HealthCheckResult_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    if (frame->driver_status == KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1) {
        return KSRP_RESULT_OK;
    }
    if (frame->driver_status == KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2) {
        return KSRP_RESULT_CRITICAL;
    }
    return KSRP_RESULT_UNKNOWN;
}

_nonnull_
KSRP_HealthCheckResult KSRP_HealthCheckResult_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    if (frame->temperature >= KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN
            && frame->temperature < KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX) {
        return KSRP_RESULT_OK;
    }
    if (frame->temperature >= KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN
            && frame->temperature < KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX) {
        return KSRP_RESULT_WARNING;
    }
    if (frame->temperature >= KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN
            && frame->temperature < KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX) {
        return KSRP_RESULT_CRITICAL;
    }
    return KSRP_RESULT_UNKNOWN;
}

_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return "Unknown troubleshoot";
}

_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return "Unknown troubleshoot";
}

_nonnull_
const char* KSRP_HealthCheckDescription_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    if (frame->driver_status == KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1) {
        return KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION;
    }
    if (frame->driver_status == KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2) {
        return KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2_DESCRIPTION;
    }
    return "Unknown description";
}

_nonnull_
const char* KSRP_HealthCheckDescription_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    if (frame->temperature >= KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN
            && frame->temperature < KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX) {
        return KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_DESCRIPTION;
    }
    if (frame->temperature >= KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN
            && frame->temperature < KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX) {
        return KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_DESCRIPTION;
    }
    if (frame->temperature >= KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN
            && frame->temperature < KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX) {
        return KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_DESCRIPTION;
    }
    return "Unknown description";
}


#endif // KALMAN_STATUS_REPORT__H_