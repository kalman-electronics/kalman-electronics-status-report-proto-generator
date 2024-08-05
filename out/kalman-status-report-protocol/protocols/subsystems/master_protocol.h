/**
 * @file master_status_report.h
 * @brief Status report protocol definitions for master subsystem
 */#ifndef KALMAN_STATUS_REPORT_MASTER_H_
#define KALMAN_STATUS_REPORT_MASTER_H_

#ifdef __cplusplus
extern "C" {
#endif

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
/** @defgroup MasterStatus frame protocol
 *  @{
 */

/**
 * @brief Health check value mappings for results in MasterStatus frame
 */
typedef enum {
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1 = 0,
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2 = 1,
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3 = 2,
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_CRITICAL_4 = 255,
} KSRP_Master_MasterStatus_CanStatus_HealthCheck;


/**
 * @brief Health check troubleshooting descriptions for MasterStatus frame
 */
#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1_TROUBLESHOOT "Nic nie rAlb"

/**
 * @brief Health check descriptions for MasterStatus frame
 */
#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION "Fajen"
#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_2_DESCRIPTION "Nie dziaL,a ueuos"
#define KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_WARNING_3_DESCRIPTION "Nie dziaL,a uniwvrsal"

/**
 * @brief MasterStatus Frame definition
 */
typedef struct _packed_ {
    uint8_t can_status;
} KSRP_Master_MasterStatus_Frame;

/// @brief Type ID for MasterStatus frame
#define KSRP_MASTER_MASTER_STATUS_TYPE_ID ( \
    KSRP_MAKE_TYPE_ID(KSRP_MASTER_SUBSYSTEM_ID, \
    KSRP_MASTER_MASTER_STATUS_FRAME_ID))

/**
 * @brief Check if a type ID is an instance of MasterStatus frame
 *
 * @param type_id The type ID to check
 * @return true if the type ID is an instance of MasterStatus frame
 */
bool KSRP_IsTypeIDInstanceof_Master_MasterStatus(KSRP_TypeID type_id) {
    return type_id == KSRP_MASTER_MASTER_STATUS_TYPE_ID;
}

/**
 * @brief Check if a raw data frame is an instance of MasterStatus frame
 *
 * @param raw_data The raw data frame to check
 * @return true if the raw data frame is an instance of MasterStatus frame
 */
bool KSRP_IsRawDataInstanceof_Master_MasterStatus(const KSRP_RawData_Frame* raw_data) {
    return raw_data->length == sizeof(KSRP_Master_MasterStatus_Frame) + KSRP_ID_BYTES &&
        KSRP_IsTypeIDInstanceof_Master_MasterStatus(KSRP_MAKE_TYPE_ID(raw_data->data[0], raw_data->data[1]));
}

/// @brief Size of MasterStatus frame
#define KSRP_MASTER_MASTER_STATUS_FRAME_SIZE sizeof(KSRP_Master_MasterStatus_Frame)

/**
 * @brief Enum with field IDs for MasterStatus frame
 */
typedef enum {
    KSRP_MASTER_MASTER_STATUS_CAN_STATUS_FIELD_ID,
} KSRP_Master_MasterStatus_FieldID;

/////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Frame Construction
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize a MASTER_STATUS frame
 *
 * @param frame The frame to initialize
 * @return KSRP_Status KSRP_STATUS_OK if the frame was initialized successfully
 */
_nonnull_
KSRP_Status KSRP_Init_Master_MasterStatus_Frame(KSRP_Master_MasterStatus_Frame* frame) {
    memset(frame, 0, sizeof(KSRP_Master_MasterStatus_Frame));

    return KSRP_STATUS_OK;
}

/**
 * @brief Deserialize a raw data frame into a MASTER_STATUS frame
 *
 * @param raw_data The raw data frame to unpack
 * @param frame The frame to unpack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was unpacked successfully
 */
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

/**
 * @brief Serialize a MASTER_STATUS frame into a raw data frame
 *
 * @param frame The frame to pack
 * @param raw_data The raw data frame to pack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was packed successfully
 */
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
/// MasterStatus Setters
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Set the value of can_status in a MASTER_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Master_MasterStatus_CanStatus(KSRP_Master_MasterStatus_Frame* frame, uint8_t value) {
    frame->can_status = value;
}


/////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Getters
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Get the value of can_status in a MASTER_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of can_status
 */
_nonnull_
uint8_t KSRP_Get_Master_MasterStatus_CanStatus(const KSRP_Master_MasterStatus_Frame* frame) {
    return frame->can_status;
}


/////////////////////////////////////////////////////////////////////////////////
/// MasterStatus Health Checks
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Perform health check on can_status in MASTER_STATUS frame
 *
 * @param frame The frame to check
 * @return KSRP_HealthCheckResult The result of the health check
 */
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

/**
 * @brief Get the troubleshooting description for the health check on can_status in MASTER_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The troubleshooting description
 */
_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Master_MasterStatus_CanStatus(const KSRP_Master_MasterStatus_Frame* frame) {
    if (frame->can_status ==KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1) {
        return KSRP_MASTER_MASTER_STATUS_CAN_STATUS_HEALTH_CHECK_OK_1_TROUBLESHOOT;
    }
    return "Unknown troubleshoot";
}

/**
 * @brief Get the description for the health check on can_status in MASTER_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The description
 */
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
/**
 * @}
 */


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @defgroup DevicesAlive frame protocol
 *  @{
 */

/**
 * @brief Health check value mappings for results in DevicesAlive frame
 */
typedef enum {
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1 = 0,       
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MIN = 1,
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_MAX = 3,
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_OK_3 = 4,
} KSRP_Master_DevicesAlive_Wheels_HealthCheck;


/**
 * @brief Health check troubleshooting descriptions for DevicesAlive frame
 */
#define KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1_TROUBLESHOOT "Check CAN and power connection to wheels controllers"

/**
 * @brief Health check descriptions for DevicesAlive frame
 */
#define KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_WARNING_2_DESCRIPTION "Some wheels are not responding"
#define KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_OK_3_DESCRIPTION "All wheels are alive"

/**
 * @brief DevicesAlive Frame definition
 */
typedef struct _packed_ {
    uint8_t wheels;
} KSRP_Master_DevicesAlive_Frame;

/// @brief Type ID for DevicesAlive frame
#define KSRP_MASTER_DEVICES_ALIVE_TYPE_ID ( \
    KSRP_MAKE_TYPE_ID(KSRP_MASTER_SUBSYSTEM_ID, \
    KSRP_MASTER_DEVICES_ALIVE_FRAME_ID))

/**
 * @brief Check if a type ID is an instance of DevicesAlive frame
 *
 * @param type_id The type ID to check
 * @return true if the type ID is an instance of DevicesAlive frame
 */
bool KSRP_IsTypeIDInstanceof_Master_DevicesAlive(KSRP_TypeID type_id) {
    return type_id == KSRP_MASTER_DEVICES_ALIVE_TYPE_ID;
}

/**
 * @brief Check if a raw data frame is an instance of DevicesAlive frame
 *
 * @param raw_data The raw data frame to check
 * @return true if the raw data frame is an instance of DevicesAlive frame
 */
bool KSRP_IsRawDataInstanceof_Master_DevicesAlive(const KSRP_RawData_Frame* raw_data) {
    return raw_data->length == sizeof(KSRP_Master_DevicesAlive_Frame) + KSRP_ID_BYTES &&
        KSRP_IsTypeIDInstanceof_Master_DevicesAlive(KSRP_MAKE_TYPE_ID(raw_data->data[0], raw_data->data[1]));
}

/// @brief Size of DevicesAlive frame
#define KSRP_MASTER_DEVICES_ALIVE_FRAME_SIZE sizeof(KSRP_Master_DevicesAlive_Frame)

/**
 * @brief Enum with field IDs for DevicesAlive frame
 */
typedef enum {
    KSRP_MASTER_DEVICES_ALIVE_WHEELS_FIELD_ID,
} KSRP_Master_DevicesAlive_FieldID;

/////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Frame Construction
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize a DEVICES_ALIVE frame
 *
 * @param frame The frame to initialize
 * @return KSRP_Status KSRP_STATUS_OK if the frame was initialized successfully
 */
_nonnull_
KSRP_Status KSRP_Init_Master_DevicesAlive_Frame(KSRP_Master_DevicesAlive_Frame* frame) {
    memset(frame, 0, sizeof(KSRP_Master_DevicesAlive_Frame));

    return KSRP_STATUS_OK;
}

/**
 * @brief Deserialize a raw data frame into a DEVICES_ALIVE frame
 *
 * @param raw_data The raw data frame to unpack
 * @param frame The frame to unpack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was unpacked successfully
 */
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

/**
 * @brief Serialize a DEVICES_ALIVE frame into a raw data frame
 *
 * @param frame The frame to pack
 * @param raw_data The raw data frame to pack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was packed successfully
 */
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
/// DevicesAlive Setters
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Set the value of wheels in a DEVICES_ALIVE frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Master_DevicesAlive_Wheels(KSRP_Master_DevicesAlive_Frame* frame, uint8_t value) {
    frame->wheels = value;
}


/////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Getters
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Get the value of wheels in a DEVICES_ALIVE frame
 *
 * @param frame The frame to get the value from
 * @return The value of wheels
 */
_nonnull_
uint8_t KSRP_Get_Master_DevicesAlive_Wheels(const KSRP_Master_DevicesAlive_Frame* frame) {
    return frame->wheels;
}


/////////////////////////////////////////////////////////////////////////////////
/// DevicesAlive Health Checks
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Perform health check on wheels in DEVICES_ALIVE frame
 *
 * @param frame The frame to check
 * @return KSRP_HealthCheckResult The result of the health check
 */
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

/**
 * @brief Get the troubleshooting description for the health check on wheels in DEVICES_ALIVE frame
 *
 * @param frame The frame to check
 * @return const char* The troubleshooting description
 */
_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Master_DevicesAlive_Wheels(const KSRP_Master_DevicesAlive_Frame* frame) {
    if (frame->wheels ==KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1) {
        return KSRP_MASTER_DEVICES_ALIVE_WHEELS_HEALTH_CHECK_CRITICAL_1_TROUBLESHOOT;
    }
    return "Unknown troubleshoot";
}

/**
 * @brief Get the description for the health check on wheels in DEVICES_ALIVE frame
 *
 * @param frame The frame to check
 * @return const char* The description
 */
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
/**
 * @}
 */



#ifdef __cplusplus
}
#endif

#endif // KALMAN_STATUS_REPORT__H_