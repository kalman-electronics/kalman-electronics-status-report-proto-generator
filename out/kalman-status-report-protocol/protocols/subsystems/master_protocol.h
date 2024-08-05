#ifndef KALMAN_STATUS_REPORT_MASTER_H_
#define KALMAN_STATUS_REPORT_MASTER_H_

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
    KSRP_MASTER_MASTER_STATUS_FRAME_ID = 13,
    KSRP_MASTER_DEVICES_ALIVE_FRAME_ID = 14,
} KSRP_Master_FrameID;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1 = 0,
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2 = 1,
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3 = 2,
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_4 = 255,
} KSRP_Master_MasterStatus_CanStatus_HealthCheck;

#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1_TROUBLESHOOT "Nic nie rób"
#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION "Fajen"
#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2_DESCRIPTION "Nie działa ueuos"
#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3_DESCRIPTION " Nie działa uniwvrsal"

typedef struct _packed_ {
    uint8_t can_status;
} KSRP_Master_MasterStatus_Frame;

#define KSRP_MASTER_MASTER_STATUS_TYPE_ID ( \
    KSRP_MAKE_TYPE_ID(KSRP_MASTER_SUBSYSTEM_ID, \
    KSRP_MASTER_MASTER_STATUS_FRAME_ID))

bool KSRP_IsTypeIDInstanceof_Master_MasterStatus(KSRP_TypeID type_id) {
    return type_id == KSRP_MASTER_MASTER_STATUS_TYPE_ID;
}

bool KSRP_IsRawDataInstanceof_Master_MasterStatus(const KSRP_RawData_Frame* raw_data) {
    return raw_data->length == sizeof(KSRP_Master_MasterStatus_Frame) + KSRP_ID_BYTES &&
        KSRP_IsTypeIDInstanceof_Master_MasterStatus(KSRP_MAKE_TYPE_ID(raw_data->data[0], raw_data->data[1]));
}

#define KSRP_MASTER_MASTER_STATUS_FRAME_SIZE sizeof(KSRP_Master_MasterStatus_Frame)

typedef enum {
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_FIELD_ID,
} KSRP_Master_MasterStatus_FieldID;

/////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Setters
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
void KSRP_Set_Master_MasterStatus_CanStatus(KSRP_Master_MasterStatus_Frame* frame, uint8_t value) {
    frame->can_status = value;
}


/////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Getters
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
uint8_t KSRP_Get_Master_MasterStatus_CanStatus(const KSRP_Master_MasterStatus_Frame* frame) {
    return frame->can_status;
}


/////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Frame Construction
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
KSRP_Status KSRP_Init_Master_MasterStatus_Frame(KSRP_Master_MasterStatus_Frame* frame) {
    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Unpack_Master_MasterStatus(const KSRP_RawData_Frame* raw_data, KSRP_Master_MasterStatus_Frame* frame) {
    if (raw_data->length != sizeof(KSRP_Master_MasterStatus_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }

    if (!KSRP_IsRawDataInstanceof_Master_MasterStatus(raw_data)) {
        return KSRP_STATUS_INVALID_FRAME_TYPE;
    }
    
    frame->can_status = raw_data->data[0 + KSRP_ID_BYTES];

    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Pack_Master_MasterStatus(const KSRP_Master_MasterStatus_Frame* frame, KSRP_RawData_Frame* raw_data) {
    if (raw_data->capacity < sizeof(KSRP_Master_MasterStatus_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }
    raw_data->data[0] = KSRP_MASTER_SUBSYSTEM_ID;
    raw_data->data[1] = KSRP_MASTER_MASTER_STATUS_FRAME_ID;
    
    raw_data->data[0 + KSRP_ID_BYTES] = frame->can_status;

    raw_data->length = sizeof(KSRP_Master_MasterStatus_Frame) + KSRP_ID_BYTES;

    return KSRP_STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Health Checks
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
KSRP_HealthCheckResult KSRP_HealthCheckResult_Master_MasterStatus_CanStatus(const KSRP_Master_MasterStatus_Frame* frame) {
    if (frame->can_status == KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1) {
        return KSRP_RESULT_OK;
    }
    if (frame->can_status == KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2) {
        return KSRP_RESULT_WARNING;
    }
    if (frame->can_status == KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3) {
        return KSRP_RESULT_WARNING;
    }
    if (frame->can_status == KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_4) {
        return KSRP_RESULT_CRITICAL;
    }
    return KSRP_RESULT_UNKNOWN;
}

_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Master_MasterStatus_CanStatus(const KSRP_Master_MasterStatus_Frame* frame) {
    if (frame->can_status ==KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1) {
        return KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1_TROUBLESHOOT;
    }
    return "Unknown troubleshoot";
}

_nonnull_
const char* KSRP_HealthCheckDescription_Master_MasterStatus_CanStatus(const KSRP_Master_MasterStatus_Frame* frame) {
    if (frame->can_status == KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1) {
        return KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION;
    }
    if (frame->can_status == KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2) {
        return KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2_DESCRIPTION;
    }
    if (frame->can_status == KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3) {
        return KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3_DESCRIPTION;
    }
    return "Unknown description";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1 = 0,       
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN = 1,
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX = 3,
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_OK_3 = 4,
} KSRP_Master_DevicesAlive_Wheels_HealthCheck;

#define KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1_TROUBLESHOOT "Check CAN and power connection to wheels controllers"
#define KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_DESCRIPTION "Some wheels are not responding"
#define KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_OK_3_DESCRIPTION "All wheels are alive"

typedef struct _packed_ {
    uint8_t wheels;
} KSRP_Master_DevicesAlive_Frame;

#define KSRP_MASTER_DEVICES_ALIVE_TYPE_ID ( \
    KSRP_MAKE_TYPE_ID(KSRP_MASTER_SUBSYSTEM_ID, \
    KSRP_MASTER_DEVICES_ALIVE_FRAME_ID))

bool KSRP_IsTypeIDInstanceof_Master_DevicesAlive(KSRP_TypeID type_id) {
    return type_id == KSRP_MASTER_DEVICES_ALIVE_TYPE_ID;
}

bool KSRP_IsRawDataInstanceof_Master_DevicesAlive(const KSRP_RawData_Frame* raw_data) {
    return raw_data->length == sizeof(KSRP_Master_DevicesAlive_Frame) + KSRP_ID_BYTES &&
        KSRP_IsTypeIDInstanceof_Master_DevicesAlive(KSRP_MAKE_TYPE_ID(raw_data->data[0], raw_data->data[1]));
}

#define KSRP_MASTER_DEVICES_ALIVE_FRAME_SIZE sizeof(KSRP_Master_DevicesAlive_Frame)

typedef enum {
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_FIELD_ID,
} KSRP_Master_DevicesAlive_FieldID;

/////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Setters
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
void KSRP_Set_Master_DevicesAlive_Wheels(KSRP_Master_DevicesAlive_Frame* frame, uint8_t value) {
    frame->wheels = value;
}


/////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Getters
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
uint8_t KSRP_Get_Master_DevicesAlive_Wheels(const KSRP_Master_DevicesAlive_Frame* frame) {
    return frame->wheels;
}


/////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Frame Construction
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
KSRP_Status KSRP_Init_Master_DevicesAlive_Frame(KSRP_Master_DevicesAlive_Frame* frame) {
    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Unpack_Master_DevicesAlive(const KSRP_RawData_Frame* raw_data, KSRP_Master_DevicesAlive_Frame* frame) {
    if (raw_data->length != sizeof(KSRP_Master_DevicesAlive_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }

    if (!KSRP_IsRawDataInstanceof_Master_DevicesAlive(raw_data)) {
        return KSRP_STATUS_INVALID_FRAME_TYPE;
    }
    
    frame->wheels = raw_data->data[0 + KSRP_ID_BYTES];

    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Pack_Master_DevicesAlive(const KSRP_Master_DevicesAlive_Frame* frame, KSRP_RawData_Frame* raw_data) {
    if (raw_data->capacity < sizeof(KSRP_Master_DevicesAlive_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }
    raw_data->data[0] = KSRP_MASTER_SUBSYSTEM_ID;
    raw_data->data[1] = KSRP_MASTER_DEVICES_ALIVE_FRAME_ID;
    
    raw_data->data[0 + KSRP_ID_BYTES] = frame->wheels;

    raw_data->length = sizeof(KSRP_Master_DevicesAlive_Frame) + KSRP_ID_BYTES;

    return KSRP_STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Health Checks
/////////////////////////////////////////////////////////////////////////////////
_nonnull_
KSRP_HealthCheckResult KSRP_HealthCheckResult_Master_DevicesAlive_Wheels(const KSRP_Master_DevicesAlive_Frame* frame) {
    if (frame->wheels == KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1) {
        return KSRP_RESULT_CRITICAL;
    }
    if (frame->wheels >= KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN
            && frame->wheels < KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX) {
        return KSRP_RESULT_WARNING;
    }
    if (frame->wheels == KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_OK_3) {
        return KSRP_RESULT_OK;
    }
    return KSRP_RESULT_UNKNOWN;
}

_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Master_DevicesAlive_Wheels(const KSRP_Master_DevicesAlive_Frame* frame) {
    if (frame->wheels ==KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1) {
        return KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1_TROUBLESHOOT;
    }
    return "Unknown troubleshoot";
}

_nonnull_
const char* KSRP_HealthCheckDescription_Master_DevicesAlive_Wheels(const KSRP_Master_DevicesAlive_Frame* frame) {
    if (frame->wheels >= KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN
            && frame->wheels < KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX) {
        return KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_DESCRIPTION;
    }
    if (frame->wheels == KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_OK_3) {
        return KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_OK_3_DESCRIPTION;
    }
    return "Unknown description";
}


#endif // KALMAN_STATUS_REPORT__H_