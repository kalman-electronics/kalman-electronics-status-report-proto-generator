/**
 * @file master_instance.h
 * @brief Instance file for the master subsystem, containing structure managing subsystem's status
 */#ifndef KALMAN_STATUS_REPORT_MASTER_INSTANCE_H_
#define KALMAN_STATUS_REPORT_MASTER_INSTANCE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "ksrp/frames.h"
#include "ksrp/common.h"
#include "ksrp/protocols/subsystems/master_protocol.h"

//TODO: Automatic frame sending
/**
 * @brief Instance structure for the master subsystem
 */
typedef struct {
    KSRP_Master_MasterStatus_Frame master_status_instance;
    KSRP_Master_DevicesAlive_Frame devices_alive_instance;
    
    uint32_t master_status_ms_since_last_update;
    uint32_t devices_alive_ms_since_last_update;
    
    KSRP_FrameUpdateCallback master_status_callback;
    KSRP_FrameUpdateCallback devices_alive_callback;
} KSRP_Master_Instance;

/**
 * @brief Initialize all frames in the instance
 *
 * @param instance The instance to initialize
 * @return KSRP_Status The status of the initialization, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_Init_Master_Instance(KSRP_Master_Instance* instance) {
    if (KSRP_Init_Master_MasterStatus_Frame(&instance->master_status_instance) != KSRP_STATUS_OK) {
        return KSRP_STATUS_ERROR;
    }
    if (KSRP_Init_Master_DevicesAlive_Frame(&instance->devices_alive_instance) != KSRP_STATUS_OK) {
        return KSRP_STATUS_ERROR;
    }
    return KSRP_STATUS_OK;
}

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
KSRP_Status KSRP_UpdateFrame_Master_Instance(
    KSRP_Master_Instance* instance,
    KSRP_Master_FrameID frame_id,
    void* frame, size_t frame_size) {

    switch(frame_id) {
        case KSRP_MASTER_MASTER_STATUS_FRAME_ID: {
            if (frame_size != KSRP_MASTER_MASTER_STATUS_FRAME_SIZE) {
                return KSRP_STATUS_INVALID_DATA_SIZE;
            }

            bool change = memcmp(&instance->master_status_instance, frame, frame_size) != 0;

            memcpy(&instance->master_status_instance, frame, frame_size);
            instance->master_status_ms_since_last_update = 0;

            if (instance->master_status_callback != NULL)
                if (change)
                    if (instance->master_status_callback(
                                KSRP_MASTER_SUBSYSTEM_ID,
                                &instance->master_status_instance,
                                KSRP_MASTER_MASTER_STATUS_FRAME_ID,
                                KSRP_ILLEGAL_FIELD_ID) != KSRP_STATUS_OK)
                        return KSRP_STATUS_ERROR;

            break;
        }
        case KSRP_MASTER_DEVICES_ALIVE_FRAME_ID: {
            if (frame_size != KSRP_MASTER_DEVICES_ALIVE_FRAME_SIZE) {
                return KSRP_STATUS_INVALID_DATA_SIZE;
            }

            bool change = memcmp(&instance->devices_alive_instance, frame, frame_size) != 0;

            memcpy(&instance->devices_alive_instance, frame, frame_size);
            instance->devices_alive_ms_since_last_update = 0;

            if (instance->devices_alive_callback != NULL)
                if (change)
                    if (instance->devices_alive_callback(
                                KSRP_MASTER_SUBSYSTEM_ID,
                                &instance->devices_alive_instance,
                                KSRP_MASTER_DEVICES_ALIVE_FRAME_ID,
                                KSRP_ILLEGAL_FIELD_ID) != KSRP_STATUS_OK)
                        return KSRP_STATUS_ERROR;

            break;
        }
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }

    return KSRP_STATUS_OK;
}

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
KSRP_Status KSRP_UpdateFrameField_Master_Instance(
    KSRP_Master_Instance* instance,
    KSRP_Master_FrameID frame_id, uint32_t field_id,
    void* value, size_t value_size) {

    switch(frame_id) {
        case KSRP_MASTER_MASTER_STATUS_FRAME_ID:
            switch(field_id) {
                case KSRP_MASTER_MASTER_STATUS_CAN_STATUS_FIELD_ID:
                    if (value_size != sizeof(instance->master_status_instance.can_status)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->master_status_instance.can_status, value, value_size) != 0;

                    memcpy(&instance->master_status_instance.can_status, value, value_size);
                    instance->master_status_ms_since_last_update = 0;

                    if (instance->master_status_callback != NULL)
                        if (change)
                            if (instance->master_status_callback(
                                        KSRP_MASTER_SUBSYSTEM_ID,
                                        &instance->master_status_instance,
                                        KSRP_MASTER_MASTER_STATUS_FRAME_ID,
                                        KSRP_MASTER_MASTER_STATUS_CAN_STATUS_FIELD_ID) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;

                    break;
                default:
                    return KSRP_STATUS_INVALID_FIELD_TYPE;
            }

            break;
        case KSRP_MASTER_DEVICES_ALIVE_FRAME_ID:
            switch(field_id) {
                case KSRP_MASTER_DEVICES_ALIVE_WHEELS_FIELD_ID:
                    if (value_size != sizeof(instance->devices_alive_instance.wheels)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->devices_alive_instance.wheels, value, value_size) != 0;

                    memcpy(&instance->devices_alive_instance.wheels, value, value_size);
                    instance->devices_alive_ms_since_last_update = 0;

                    if (instance->devices_alive_callback != NULL)
                        if (change)
                            if (instance->devices_alive_callback(
                                        KSRP_MASTER_SUBSYSTEM_ID,
                                        &instance->devices_alive_instance,
                                        KSRP_MASTER_DEVICES_ALIVE_FRAME_ID,
                                        KSRP_MASTER_DEVICES_ALIVE_WHEELS_FIELD_ID) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;

                    break;
                default:
                    return KSRP_STATUS_INVALID_FIELD_TYPE;
            }

            break;
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }
    return KSRP_STATUS_OK;
}

/**
 * @brief Update the time since last update for all frames in the instance
 *
 * @param instance The instance to update
 * @param ms_since_last_update Time delta since last update (in ms)
 * @return KSRP_Status The status of the update, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_UpdateTime_Master_Instance(
    KSRP_Master_Instance* instance, uint32_t ms_since_last_update) {
    instance->master_status_ms_since_last_update += ms_since_last_update;
    instance->devices_alive_ms_since_last_update += ms_since_last_update;

    return KSRP_STATUS_OK;
}

/**
 * @brief Get the time since last update for a frame in the instance
 *
 * @param instance The instance to get the time from
 * @param frame_id The ID of the frame to get the time from
 * @return uint32_t The time since the last update (in ms)
 */
_nonnull_
uint32_t KSRP_Master_Instance_GetTimeSinceLastUpdate(
    KSRP_Master_Instance* instance, KSRP_Master_FrameID frame_id) {

    switch(frame_id) {
        case KSRP_MASTER_MASTER_STATUS_FRAME_ID:
            return instance->master_status_ms_since_last_update;
        case KSRP_MASTER_DEVICES_ALIVE_FRAME_ID:
            return instance->devices_alive_ms_since_last_update;
        default:
            return 0xFFFFFFFF;
    }
}

/**
 * @brief Set the callback for a frame in the instance, callback is called when frame value is changed
 *
 * @param instance The instance to set the callback for
 * @param frame_id The ID of the frame to set the callback for
 * @param callback The callback function to set
 * @return KSRP_Status The status of the operation, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_Master_Instance_SetCallback(
    KSRP_Master_Instance* instance,
    KSRP_Master_FrameID frame_id,
    KSRP_FrameUpdateCallback callback) {

    switch(frame_id) {
        case KSRP_MASTER_MASTER_STATUS_FRAME_ID:
            instance->master_status_callback = callback;
            break;
        case KSRP_MASTER_DEVICES_ALIVE_FRAME_ID:
            instance->devices_alive_callback = callback;
            break;
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }

    return KSRP_STATUS_OK;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KALMAN_STATUS_REPORT_MASTER_INSTANCE_H_