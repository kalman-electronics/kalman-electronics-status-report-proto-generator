/**
 * @file wheels_instance.c
 * @brief Instance file for the wheels subsystem, containing structure managing subsystem's status
 */// Include standard libraries

// Include user libraries
#include "ksrp/instances/wheels_instance.h"

/**
 * @brief Initialize all frames in the instance
 *
 * @param instance The instance to initialize
 * @return KSRP_Status The status of the initialization, KSRP_STATUS_OK if successful
 */
_nonnull_
KSRP_Status KSRP_Init_Wheels_Instance(KSRP_Wheels_Instance* instance) {
    if (KSRP_Init_Wheels_WheelsStatus_Frame(&instance->wheels_status_instance) != KSRP_STATUS_OK) {
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
KSRP_Status KSRP_UpdateFrame_Wheels_Instance(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id,
    void* frame, size_t frame_size) {

    switch(frame_id) {
        case KSRP_WHEELS_WHEELS_STATUS_FRAME_ID: {
            if (frame_size != KSRP_WHEELS_WHEELS_STATUS_FRAME_SIZE) {
                return KSRP_STATUS_INVALID_DATA_SIZE;
            }

            bool change = memcmp(&instance->wheels_status_instance, frame, frame_size) != 0;

            memcpy(&instance->wheels_status_instance, frame, frame_size);
            instance->wheels_status_ms_since_last_update = 0;

            if (instance->wheels_status_callback != NULL)
                if (change)
                    if (instance->wheels_status_callback(
                        KSRP_WHEELS_SUBSYSTEM_ID,
                        &instance->wheels_status_instance,
                        KSRP_WHEELS_WHEELS_STATUS_FRAME_ID,
                        KSRP_ILLEGAL_FIELD_ID) != KSRP_STATUS_OK)
                    return KSRP_STATUS_ERROR;

            if (instance->send_frame_callback != NULL)
                if (change) {
                    KSRP_RawData_Frame raw_frame;
                    KSRP_RawDataFrame_Init(&raw_frame);
                    if (KSRP_Pack_Wheels_WheelsStatus != KSRP_STATUS_OK)
                        return KSRP_STATUS_ERROR;
                    if (instance->send_frame_callback(&raw_frame) != KSRP_STATUS_OK)
                        return KSRP_STATUS_ERROR;
                }

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
KSRP_Status KSRP_UpdateFrameField_Wheels_Instance(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id, uint32_t field_id,
    void* value, size_t value_size) {

    switch(frame_id) {
        case KSRP_WHEELS_WHEELS_STATUS_FRAME_ID: {
            switch(field_id) {
                case KSRP_WHEELS_WHEELS_STATUS_DEVICE_ID_FIELD_ID: {
                    if (value_size != sizeof(instance->wheels_status_instance.device_id)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->wheels_status_instance.device_id, value, value_size) != 0;

                    memcpy(&instance->wheels_status_instance.device_id, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    if (instance->wheels_status_callback != NULL)
                        if (change)
                            if (instance->wheels_status_callback(
                                KSRP_WHEELS_SUBSYSTEM_ID,
                                &instance->wheels_status_instance,
                                KSRP_WHEELS_WHEELS_STATUS_FRAME_ID,
                                KSRP_WHEELS_WHEELS_STATUS_DEVICE_ID_FIELD_ID) != KSRP_STATUS_OK)
                            return KSRP_STATUS_ERROR;

                    if (instance->send_frame_callback != NULL)
                        if (change) {
                            KSRP_RawData_Frame raw_frame;
                            KSRP_RawDataFrame_Init(&raw_frame);
                            if (KSRP_Pack_Wheels_WheelsStatus != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                            if (instance->send_frame_callback(&raw_frame) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                    }

                    break;
                }
                case KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_FIELD_ID: {
                    if (value_size != sizeof(instance->wheels_status_instance.driver_status)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->wheels_status_instance.driver_status, value, value_size) != 0;

                    memcpy(&instance->wheels_status_instance.driver_status, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    if (instance->wheels_status_callback != NULL)
                        if (change)
                            if (instance->wheels_status_callback(
                                KSRP_WHEELS_SUBSYSTEM_ID,
                                &instance->wheels_status_instance,
                                KSRP_WHEELS_WHEELS_STATUS_FRAME_ID,
                                KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_FIELD_ID) != KSRP_STATUS_OK)
                            return KSRP_STATUS_ERROR;

                    if (instance->send_frame_callback != NULL)
                        if (change) {
                            KSRP_RawData_Frame raw_frame;
                            KSRP_RawDataFrame_Init(&raw_frame);
                            if (KSRP_Pack_Wheels_WheelsStatus != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                            if (instance->send_frame_callback(&raw_frame) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                    }

                    break;
                }
                case KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_FIELD_ID: {
                    if (value_size != sizeof(instance->wheels_status_instance.temperature)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->wheels_status_instance.temperature, value, value_size) != 0;

                    memcpy(&instance->wheels_status_instance.temperature, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    if (instance->wheels_status_callback != NULL)
                        if (change)
                            if (instance->wheels_status_callback(
                                KSRP_WHEELS_SUBSYSTEM_ID,
                                &instance->wheels_status_instance,
                                KSRP_WHEELS_WHEELS_STATUS_FRAME_ID,
                                KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_FIELD_ID) != KSRP_STATUS_OK)
                            return KSRP_STATUS_ERROR;

                    if (instance->send_frame_callback != NULL)
                        if (change) {
                            KSRP_RawData_Frame raw_frame;
                            KSRP_RawDataFrame_Init(&raw_frame);
                            if (KSRP_Pack_Wheels_WheelsStatus != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                            if (instance->send_frame_callback(&raw_frame) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                    }

                    break;
                }
                case KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE_FIELD_ID: {
                    if (value_size != sizeof(instance->wheels_status_instance.algorithm_type)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->wheels_status_instance.algorithm_type, value, value_size) != 0;

                    memcpy(&instance->wheels_status_instance.algorithm_type, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    if (instance->wheels_status_callback != NULL)
                        if (change)
                            if (instance->wheels_status_callback(
                                KSRP_WHEELS_SUBSYSTEM_ID,
                                &instance->wheels_status_instance,
                                KSRP_WHEELS_WHEELS_STATUS_FRAME_ID,
                                KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE_FIELD_ID) != KSRP_STATUS_OK)
                            return KSRP_STATUS_ERROR;

                    if (instance->send_frame_callback != NULL)
                        if (change) {
                            KSRP_RawData_Frame raw_frame;
                            KSRP_RawDataFrame_Init(&raw_frame);
                            if (KSRP_Pack_Wheels_WheelsStatus != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                            if (instance->send_frame_callback(&raw_frame) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                    }

                    break;
                }
                case KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2_FIELD_ID: {
                    if (value_size != sizeof(instance->wheels_status_instance.algorithm_type2)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->wheels_status_instance.algorithm_type2, value, value_size) != 0;

                    memcpy(&instance->wheels_status_instance.algorithm_type2, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    if (instance->wheels_status_callback != NULL)
                        if (change)
                            if (instance->wheels_status_callback(
                                KSRP_WHEELS_SUBSYSTEM_ID,
                                &instance->wheels_status_instance,
                                KSRP_WHEELS_WHEELS_STATUS_FRAME_ID,
                                KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2_FIELD_ID) != KSRP_STATUS_OK)
                            return KSRP_STATUS_ERROR;

                    if (instance->send_frame_callback != NULL)
                        if (change) {
                            KSRP_RawData_Frame raw_frame;
                            KSRP_RawDataFrame_Init(&raw_frame);
                            if (KSRP_Pack_Wheels_WheelsStatus != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                            if (instance->send_frame_callback(&raw_frame) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                    }

                    break;
                }
                case KSRP_WHEELS_WHEELS_STATUS_TESTBOOL_FIELD_ID: {
                    if (value_size != sizeof(instance->wheels_status_instance.testbool)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    bool change = memcmp(&instance->wheels_status_instance.testbool, value, value_size) != 0;

                    memcpy(&instance->wheels_status_instance.testbool, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    if (instance->wheels_status_callback != NULL)
                        if (change)
                            if (instance->wheels_status_callback(
                                KSRP_WHEELS_SUBSYSTEM_ID,
                                &instance->wheels_status_instance,
                                KSRP_WHEELS_WHEELS_STATUS_FRAME_ID,
                                KSRP_WHEELS_WHEELS_STATUS_TESTBOOL_FIELD_ID) != KSRP_STATUS_OK)
                            return KSRP_STATUS_ERROR;

                    if (instance->send_frame_callback != NULL)
                        if (change) {
                            KSRP_RawData_Frame raw_frame;
                            KSRP_RawDataFrame_Init(&raw_frame);
                            if (KSRP_Pack_Wheels_WheelsStatus != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                            if (instance->send_frame_callback(&raw_frame) != KSRP_STATUS_OK)
                                return KSRP_STATUS_ERROR;
                    }

                    break;
                }
                default:
                    return KSRP_STATUS_INVALID_FIELD_TYPE;
            }
            break;
        }
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
KSRP_Status KSRP_UpdateTime_Wheels_Instance(
    KSRP_Wheels_Instance* instance, uint32_t ms_since_last_update) {
    instance->wheels_status_ms_since_last_update += ms_since_last_update;

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
uint32_t KSRP_Wheels_Instance_GetTimeSinceLastUpdate(
    KSRP_Wheels_Instance* instance, KSRP_Wheels_FrameID frame_id) {

    switch(frame_id) {
        case KSRP_WHEELS_WHEELS_STATUS_FRAME_ID:
            return instance->wheels_status_ms_since_last_update;
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
KSRP_Status KSRP_Wheels_Instance_SetCallback(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id,
    KSRP_FrameUpdateCallback callback) {

    switch(frame_id) {
        case KSRP_WHEELS_WHEELS_STATUS_FRAME_ID:
            instance->wheels_status_callback = callback;
            break;
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }

    return KSRP_STATUS_OK;
}