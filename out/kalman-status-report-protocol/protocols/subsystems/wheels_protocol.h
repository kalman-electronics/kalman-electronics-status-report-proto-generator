/**
 * @file wheels_status_report.h
 * @brief Status report protocol definitions for wheels subsystem
 */#ifndef KALMAN_STATUS_REPORT_WHEELS_H_
#define KALMAN_STATUS_REPORT_WHEELS_H_

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
    KSRP_WHEELS_WHEELS_STATUS_FRAME_ID = 12,
} KSRP_Wheels_FrameID;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Frame
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @defgroup WheelsStatus frame protocol
 *  @{
 */

/**
 * @brief Health check value mappings for results in WheelsStatus frame
 */
typedef enum {
    KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1 = 0,
    KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2 = 255,
} KSRP_Wheels_WheelsStatus_DriverStatus_HealthCheck;

/**
 * @brief Health check value mappings for results in WheelsStatus frame
 */
typedef enum {       
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MIN = 0,
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_MAX = 100,       
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MIN = 100,
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_MAX = 200,       
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MIN = 200,
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_MAX = 300,
} KSRP_Wheels_WheelsStatus_Temperature_HealthCheck;


/**
 * @brief Health check troubleshooting descriptions for WheelsStatus frame
 */

/**
 * @brief Health check descriptions for WheelsStatus frame
 */
#define KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_OK_1_DESCRIPTION "Driver is ready"
#define KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_HEALTH_CHECK_CRITICAL_2_DESCRIPTION "Driver is not ready"
#define KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_OK_1_DESCRIPTION "Temperature is normal"
#define KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_WARNING_2_DESCRIPTION "Temperature is high"
#define KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_HEALTH_CHECK_CRITICAL_3_DESCRIPTION "Temperature is very high"

/**
 * @brief Enum value declarations for algorithm_type in WheelsStatus frame
 */
typedef enum {
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE_POSITION,
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE_VELOCITY,
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE_TORQUE,
} KSRP_Wheels_WheelsStatus_AlgorithmType;

/**
 * @brief Enum value declarations for algorithm_type2 in WheelsStatus frame
 */
typedef enum {
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2_POSITION = 1,
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2_VELOCITY = 2,
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2_TORQUE = 3,
} KSRP_Wheels_WheelsStatus_AlgorithmType2;

/**
 * @brief WheelsStatus Frame definition
 */
typedef struct _packed_ {
    uint8_t device_id;
    uint8_t driver_status;
    float temperature;
    uint8_t algorithm_type;
    uint8_t algorithm_type2;
    uint8_t testbool;
} KSRP_Wheels_WheelsStatus_Frame;

/// @brief Type ID for WheelsStatus frame
#define KSRP_WHEELS_WHEELS_STATUS_TYPE_ID ( \
    KSRP_MAKE_TYPE_ID(KSRP_WHEELS_SUBSYSTEM_ID, \
    KSRP_WHEELS_WHEELS_STATUS_FRAME_ID))

/**
 * @brief Check if a type ID is an instance of WheelsStatus frame
 *
 * @param type_id The type ID to check
 * @return true if the type ID is an instance of WheelsStatus frame
 */
bool KSRP_IsTypeIDInstanceof_Wheels_WheelsStatus(KSRP_TypeID type_id) {
    return type_id == KSRP_WHEELS_WHEELS_STATUS_TYPE_ID;
}

/**
 * @brief Check if a raw data frame is an instance of WheelsStatus frame
 *
 * @param raw_data The raw data frame to check
 * @return true if the raw data frame is an instance of WheelsStatus frame
 */
bool KSRP_IsRawDataInstanceof_Wheels_WheelsStatus(const KSRP_RawData_Frame* raw_data) {
    return raw_data->length == sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES &&
        KSRP_IsTypeIDInstanceof_Wheels_WheelsStatus(KSRP_MAKE_TYPE_ID(raw_data->data[0], raw_data->data[1]));
}

/// @brief Size of WheelsStatus frame
#define KSRP_WHEELS_WHEELS_STATUS_FRAME_SIZE sizeof(KSRP_Wheels_WheelsStatus_Frame)

/**
 * @brief Enum with field IDs for WheelsStatus frame
 */
typedef enum {
    KSRP_WHEELS_WHEELS_STATUS_DEVICE_ID_FIELD_ID,
    KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_FIELD_ID,
    KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_FIELD_ID,
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE_FIELD_ID,
    KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2_FIELD_ID,
    KSRP_WHEELS_WHEELS_STATUS_TESTBOOL_FIELD_ID,
} KSRP_Wheels_WheelsStatus_FieldID;

/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Frame Construction
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize a WHEELS_STATUS frame
 *
 * @param frame The frame to initialize
 * @return KSRP_Status KSRP_STATUS_OK if the frame was initialized successfully
 */
_nonnull_
KSRP_Status KSRP_Init_Wheels_WheelsStatus_Frame(KSRP_Wheels_WheelsStatus_Frame* frame) {
    memset(frame, 0, sizeof(KSRP_Wheels_WheelsStatus_Frame));
    frame->driver_status = 15;
    frame->algorithm_type2 = (uint8_t) KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2;
    frame->testbool = (uint8_t)true;

    return KSRP_STATUS_OK;
}

/**
 * @brief Deserialize a raw data frame into a WHEELS_STATUS frame
 *
 * @param raw_data The raw data frame to unpack
 * @param frame The frame to unpack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was unpacked successfully
 */
_nonnull_
KSRP_Status KSRP_Unpack_Wheels_WheelsStatus(const KSRP_RawData_Frame* raw_data, KSRP_Wheels_WheelsStatus_Frame* frame) {
    if (raw_data->length != sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }

    if (!KSRP_IsRawDataInstanceof_Wheels_WheelsStatus(raw_data)) {
        return KSRP_STATUS_INVALID_FRAME_TYPE;
    }
    
    frame->device_id = *((uint8_t*)&raw_data->data[0 + KSRP_ID_BYTES]);
    frame->driver_status = raw_data->data[1 + KSRP_ID_BYTES];
    frame->temperature = *((float*)&raw_data->data[2 + KSRP_ID_BYTES]);
    frame->algorithm_type = raw_data->data[6 + KSRP_ID_BYTES];
    frame->algorithm_type2 = raw_data->data[7 + KSRP_ID_BYTES];
    frame->testbool = raw_data->data[8 + KSRP_ID_BYTES];

    return KSRP_STATUS_OK;
}

/**
 * @brief Serialize a WHEELS_STATUS frame into a raw data frame
 *
 * @param frame The frame to pack
 * @param raw_data The raw data frame to pack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was packed successfully
 */
_nonnull_
KSRP_Status KSRP_Pack_Wheels_WheelsStatus(const KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_RawData_Frame* raw_data) {
    if (raw_data->capacity < sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }

    raw_data->data[0] = KSRP_WHEELS_SUBSYSTEM_ID;
    raw_data->data[1] = KSRP_WHEELS_WHEELS_STATUS_FRAME_ID;
    
    *((uint8_t*)&raw_data->data[0 + KSRP_ID_BYTES]) = frame->device_id;
    raw_data->data[1 + KSRP_ID_BYTES] = frame->driver_status;
    *((float*)&raw_data->data[2 + KSRP_ID_BYTES]) = frame->temperature;
    raw_data->data[6 + KSRP_ID_BYTES] = frame->algorithm_type;
    raw_data->data[7 + KSRP_ID_BYTES] = frame->algorithm_type2;
    raw_data->data[8 + KSRP_ID_BYTES] = frame->testbool;

    raw_data->length = sizeof(KSRP_Wheels_WheelsStatus_Frame) + KSRP_ID_BYTES;

    return KSRP_STATUS_OK;
}


/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Setters
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Set the value of device_id in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_DeviceId(KSRP_Wheels_WheelsStatus_Frame* frame, uint8_t value) {
    frame->device_id = value;
}

/**
 * @brief Set the value of driver_status in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_DriverStatus(KSRP_Wheels_WheelsStatus_Frame* frame, uint8_t value) {
    frame->driver_status = value;
}

/**
 * @brief Set the value of temperature in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_Temperature(KSRP_Wheels_WheelsStatus_Frame* frame, float value) {
    frame->temperature = value;
}

/**
 * @brief Set the value of algorithm_type in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_AlgorithmType(KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_Wheels_WheelsStatus_AlgorithmType value) {
    frame->algorithm_type = (uint8_t)value;
}

/**
 * @brief Set the value of algorithm_type2 in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_AlgorithmType2(KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_Wheels_WheelsStatus_AlgorithmType2 value) {
    frame->algorithm_type2 = (uint8_t)value;
}

/**
 * @brief Set the value of testbool in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_Testbool(KSRP_Wheels_WheelsStatus_Frame* frame, bool value) {
    frame->testbool = (uint8_t)value;
}


/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Getters
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Get the value of device_id in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of device_id
 */
_nonnull_
uint8_t KSRP_Get_Wheels_WheelsStatus_DeviceId(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return frame->device_id;
}

/**
 * @brief Get the value of driver_status in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of driver_status
 */
_nonnull_
uint8_t KSRP_Get_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return frame->driver_status;
}

/**
 * @brief Get the value of temperature in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of temperature
 */
_nonnull_
float KSRP_Get_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return frame->temperature;
}

/**
 * @brief Get the value of algorithm_type in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of algorithm_type
 */
_nonnull_
KSRP_Wheels_WheelsStatus_AlgorithmType KSRP_Get_Wheels_WheelsStatus_AlgorithmType(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return (KSRP_Wheels_WheelsStatus_AlgorithmType)frame->algorithm_type;
}

/**
 * @brief Get the value of algorithm_type2 in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of algorithm_type2
 */
_nonnull_
KSRP_Wheels_WheelsStatus_AlgorithmType2 KSRP_Get_Wheels_WheelsStatus_AlgorithmType2(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return (KSRP_Wheels_WheelsStatus_AlgorithmType2)frame->algorithm_type2;
}

/**
 * @brief Get the value of testbool in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of testbool
 */
_nonnull_
bool KSRP_Get_Wheels_WheelsStatus_Testbool(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return (bool)frame->testbool;
}


/////////////////////////////////////////////////////////////////////////////////
/// WheelsStatus Health Checks
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Perform health check on driver_status in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return KSRP_HealthCheckResult The result of the health check
 */
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

/**
 * @brief Perform health check on temperature in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return KSRP_HealthCheckResult The result of the health check
 */
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

/**
 * @brief Get the troubleshooting description for the health check on driver_status in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The troubleshooting description
 */
_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return "Unknown troubleshoot";
}

/**
 * @brief Get the troubleshooting description for the health check on temperature in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The troubleshooting description
 */
_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame) {
    return "Unknown troubleshoot";
}

/**
 * @brief Get the description for the health check on driver_status in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The description
 */
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

/**
 * @brief Get the description for the health check on temperature in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The description
 */
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
/**
 * @}
 */



#ifdef __cplusplus
}
#endif

#endif // KALMAN_STATUS_REPORT__H_