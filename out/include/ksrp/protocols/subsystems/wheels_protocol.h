/**
 * @file wheels_status_report.h
 * @brief Status report protocol definitions for wheels subsystem
 */#ifndef KALMAN_STATUS_REPORT_WHEELS_H_
#define KALMAN_STATUS_REPORT_WHEELS_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "ksrp/frames.h"
#include "ksrp/common.h"

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
bool KSRP_IsTypeIDInstanceof_Wheels_WheelsStatus(KSRP_TypeID type_id);

/**
 * @brief Check if a raw data frame is an instance of WheelsStatus frame
 *
 * @param raw_data The raw data frame to check
 * @return true if the raw data frame is an instance of WheelsStatus frame
 */
bool KSRP_IsRawDataInstanceof_Wheels_WheelsStatus(const KSRP_RawData_Frame* raw_data);

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
KSRP_Status KSRP_Init_Wheels_WheelsStatus_Frame(KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Deserialize a raw data frame into a WHEELS_STATUS frame
 *
 * @param raw_data The raw data frame to unpack
 * @param frame The frame to unpack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was unpacked successfully
 */
_nonnull_
KSRP_Status KSRP_Unpack_Wheels_WheelsStatus(const KSRP_RawData_Frame* raw_data, KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Serialize a WHEELS_STATUS frame into a raw data frame
 *
 * @param frame The frame to pack
 * @param raw_data The raw data frame to pack into
 * @return KSRP_Status KSRP_STATUS_OK if the frame was packed successfully
 */
_nonnull_
KSRP_Status KSRP_Pack_Wheels_WheelsStatus(const KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_RawData_Frame* raw_data);

/**
 * @brief Compare two WHEELS_STATUS frames
 *
 * @param frame1 The first frame to compare
 * @param frame2 The second frame to compare
 * @return int 0 if the frames are equal, -1 if frame1 is less than frame2, 1 if frame1 is greater than frame2
 */
int KSRP_Wheels_WheelsStatus_Frame_Compare(const KSRP_Wheels_WheelsStatus_Frame* frame1, const KSRP_Wheels_WheelsStatus_Frame* frame2);

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
void KSRP_Set_Wheels_WheelsStatus_DeviceId(KSRP_Wheels_WheelsStatus_Frame* frame, uint8_t value);

/**
 * @brief Set the value of driver_status in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_DriverStatus(KSRP_Wheels_WheelsStatus_Frame* frame, uint8_t value);

/**
 * @brief Set the value of temperature in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_Temperature(KSRP_Wheels_WheelsStatus_Frame* frame, float value);

/**
 * @brief Set the value of algorithm_type in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_AlgorithmType(KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_Wheels_WheelsStatus_AlgorithmType value);

/**
 * @brief Set the value of algorithm_type2 in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_AlgorithmType2(KSRP_Wheels_WheelsStatus_Frame* frame, KSRP_Wheels_WheelsStatus_AlgorithmType2 value);

/**
 * @brief Set the value of testbool in a WHEELS_STATUS frame
 *
 * @param frame The frame to set the value in
 * @param value The value to set
 */
_nonnull_
void KSRP_Set_Wheels_WheelsStatus_Testbool(KSRP_Wheels_WheelsStatus_Frame* frame, bool value);


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
uint8_t KSRP_Get_Wheels_WheelsStatus_DeviceId(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the value of driver_status in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of driver_status
 */
_nonnull_
uint8_t KSRP_Get_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the value of temperature in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of temperature
 */
_nonnull_
float KSRP_Get_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the value of algorithm_type in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of algorithm_type
 */
_nonnull_
KSRP_Wheels_WheelsStatus_AlgorithmType KSRP_Get_Wheels_WheelsStatus_AlgorithmType(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the value of algorithm_type2 in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of algorithm_type2
 */
_nonnull_
KSRP_Wheels_WheelsStatus_AlgorithmType2 KSRP_Get_Wheels_WheelsStatus_AlgorithmType2(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the value of testbool in a WHEELS_STATUS frame
 *
 * @param frame The frame to get the value from
 * @return The value of testbool
 */
_nonnull_
bool KSRP_Get_Wheels_WheelsStatus_Testbool(const KSRP_Wheels_WheelsStatus_Frame* frame);


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
KSRP_HealthCheckResult KSRP_HealthCheckResult_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Perform health check on temperature in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return KSRP_HealthCheckResult The result of the health check
 */
_nonnull_
KSRP_HealthCheckResult KSRP_HealthCheckResult_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the troubleshooting description for the health check on driver_status in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The troubleshooting description
 */
_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the troubleshooting description for the health check on temperature in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The troubleshooting description
 */
_nonnull_
const char* KSRP_HealthCheckTroubleshoot_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the description for the health check on driver_status in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The description
 */
_nonnull_
const char* KSRP_HealthCheckDescription_Wheels_WheelsStatus_DriverStatus(const KSRP_Wheels_WheelsStatus_Frame* frame);

/**
 * @brief Get the description for the health check on temperature in WHEELS_STATUS frame
 *
 * @param frame The frame to check
 * @return const char* The description
 */
_nonnull_
const char* KSRP_HealthCheckDescription_Wheels_WheelsStatus_Temperature(const KSRP_Wheels_WheelsStatus_Frame* frame);
/**
 * @}
 */



#ifdef __cplusplus
}
#endif //__cplusplus

#endif // KALMAN_STATUS_REPORT__H_