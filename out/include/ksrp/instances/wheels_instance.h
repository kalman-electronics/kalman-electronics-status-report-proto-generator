/**
 * @file wheels_instance.h
 * @brief Instance file for the wheels subsystem, containing structure managing subsystem's status
 */#ifndef KALMAN_STATUS_REPORT_WHEELS_INSTANCE_H_
#define KALMAN_STATUS_REPORT_WHEELS_INSTANCE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "ksrp/frames.h"
#include "ksrp/common.h"
#include "ksrp/protocols/protocol_utils.h"

//TODO: Automatic frame sending
/**
 * @brief Instance structure for the wheels subsystem
 */
typedef struct {
    KSRP_Wheels_WheelsStatus_Frame wheels_status_instance;
    
    uint32_t wheels_status_ms_since_last_update;
    
    KSRP_FrameUpdateCallback wheels_status_callback;
} KSRP_Wheels_Instance;

/**
 * @brief Initialize all frames in the instance
 *
 * @param instance The instance to initialize
 * @return KSRP_Status The status of the initialization, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_Init_Wheels_Instance(KSRP_Wheels_Instance* instance);

/**
 * @brief Update a frame in the instance
 *
 * @param instance The instance to update
 * @param frame_id The ID of the frame to update
 * @param frame The new frame data
 * @param frame_size The size of the new frame data
 * @return KSRP_Status The status of the update, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_UpdateFrame_Wheels_Instance(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id,
    void* frame, size_t frame_size);

/**
 * @brief Update a field in a frame in the instance
 *
 * @param instance The instance to update
 * @param frame_id The ID of the frame to update
 * @param field_id The ID of the field to update
 * @param value The new field data
 * @param value_size The size of the new field data
 * @return KSRP_Status The status of the update, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_UpdateFrameField_Wheels_Instance(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id, uint32_t field_id,
    void* value, size_t value_size);

/**
 * @brief Update the time since last update for all frames in the instance
 *
 * @param instance The instance to update
 * @param ms_since_last_update Time delta since last update (in ms)
 * @return KSRP_Status The status of the update, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_UpdateTime_Wheels_Instance(
    KSRP_Wheels_Instance* instance,
    uint32_t ms_since_last_update);

/**
 * @brief Get the time since last update for a frame in the instance
 *
 * @param instance The instance to get the time from
 * @param frame_id The ID of the frame to get the time from
 * @return uint32_t The time since the last update (in ms)
 */
_nonnull_
uint32_t KSRP_Wheels_Instance_GetTimeSinceLastUpdate(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id);

/**
 * @brief Set the callback for a frame in the instance, callback is called when frame value is changed
 *
 * @param instance The instance to set the callback for
 * @param frame_id The ID of the frame to set the callback for
 * @param callback The callback function to set
 * @return KSRP_Status The status of the operation, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_Wheels_Instance_SetCallback(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id,
    KSRP_FrameUpdateCallback callback);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KALMAN_STATUS_REPORT_WHEELS_INSTANCE_H_