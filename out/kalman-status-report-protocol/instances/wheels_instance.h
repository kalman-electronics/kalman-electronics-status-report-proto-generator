#ifndef KALMAN_STATUS_REPORT_WHEELS_INSTANCE_H_
#define KALMAN_STATUS_REPORT_WHEELS_INSTANCE_H_

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "kalman-status-report-protocol/frames.h"
#include "kalman-status-report-protocol/common.h"
#include "kalman-status-report-protocol/protocols/subsystems/wheels_protocol.h"

//TODO: Subscription to frame updates (callbacks)

typedef struct {
    KSRP_Wheels_WheelsStatus_Frame wheels_status_instance;
    
    uint32_t wheels_status_ms_since_last_update;
} KSRP_Wheels_Instance;

_nonnull_
KSRP_Status KSRP_Wheels_Instance_Init(KSRP_Wheels_Instance* instance) {
    if (KSRP_Wheels_WHEELS_STATUS_Frame_Init(&instance->wheels_status_instance) != KSRP_STATUS_OK) {
        return KSRP_STATUS_ERROR;
    }
    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Wheels_Instance_UpdateFrame(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id,
    void* frame, size_t frame_size) {

    switch(frame_id) {
        case KSRP_WHEELS_WHEELS_STATUS_FRAME_ID: {
            if (frame_size != KSRP_WHEELS_WHEELS_STATUS_FRAME_SIZE) {
                return KSRP_STATUS_INVALID_DATA_SIZE;
            }

            memcpy(&instance->wheels_status_instance, frame, frame_size);
            instance->wheels_status_ms_since_last_update = 0;

            break;
        }
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }

    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Wheels_Instance_UpdateFrameField(
    KSRP_Wheels_Instance* instance,
    KSRP_Wheels_FrameID frame_id, uint32_t field_id,
    void* value, size_t value_size) {

    switch(frame_id) {
        case KSRP_WHEELS_WHEELS_STATUS_FRAME_ID:
            switch(field_id) {
                case KSRP_WHEELS_WHEELS_STATUS_CONTROLLER_ID_FIELD_ID:
                    if (value_size != sizeof(instance->wheels_status_instance.controller_id)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    memcpy(&instance->wheels_status_instance.controller_id, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    break;
                case KSRP_WHEELS_WHEELS_STATUS_DRIVER_STATUS_FIELD_ID:
                    if (value_size != sizeof(instance->wheels_status_instance.driver_status)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    memcpy(&instance->wheels_status_instance.driver_status, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    break;
                case KSRP_WHEELS_WHEELS_STATUS_TEMPERATURE_FIELD_ID:
                    if (value_size != sizeof(instance->wheels_status_instance.temperature)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    memcpy(&instance->wheels_status_instance.temperature, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    break;
                case KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE_FIELD_ID:
                    if (value_size != sizeof(instance->wheels_status_instance.algorithm_type)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    memcpy(&instance->wheels_status_instance.algorithm_type, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    break;
                case KSRP_WHEELS_WHEELS_STATUS_ALGORITHM_TYPE2_FIELD_ID:
                    if (value_size != sizeof(instance->wheels_status_instance.algorithm_type2)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    memcpy(&instance->wheels_status_instance.algorithm_type2, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    break;
                case KSRP_WHEELS_WHEELS_STATUS_TESTBOOL_FIELD_ID:
                    if (value_size != sizeof(instance->wheels_status_instance.testbool)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    memcpy(&instance->wheels_status_instance.testbool, value, value_size);
                    instance->wheels_status_ms_since_last_update = 0;

                    break;
                default:
                    return KSRP_STATUS_INVALID_FIELD_TYPE;
            }
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }
    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Wheels_Instance_UpdateTime(
    KSRP_Wheels_Instance* instance, uint32_t ms_since_last_update) {
    instance->wheels_status_ms_since_last_update += ms_since_last_update;

    return KSRP_STATUS_OK;
}

_nonnull_
uint32_t KSRP_Wheels_Instance_GetTimeSinceLastUpdate(
    KSRP_Wheels_Instance* instance, KSRP_Wheels_FrameID frame_id) {

    switch(frame_id) {
        case KSRP_WHEELS_WHEELS_STATUS_FRAME_ID:
            return instance->wheels_status_ms_since_last_update;
        default:
            return 0;
    }
}

#endif // KALMAN_STATUS_REPORT_WHEELS_INSTANCE_H_