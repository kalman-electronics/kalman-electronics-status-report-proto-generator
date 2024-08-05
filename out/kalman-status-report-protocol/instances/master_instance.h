#ifndef KALMAN_STATUS_REPORT_MASTER_INSTANCE_H_
#define KALMAN_STATUS_REPORT_MASTER_INSTANCE_H_

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "kalman-status-report-protocol/frames.h"
#include "kalman-status-report-protocol/common.h"
#include "kalman-status-report-protocol/protocols/subsystems/master_protocol.h"

typedef struct {
    KSRP_Master_MasterStatus_Frame master_status_instance;
    KSRP_Master_DevicesAlive_Frame devices_alive_instance;
    
    uint32_t master_status_ms_since_last_update;
    uint32_t devices_alive_ms_since_last_update;
} KSRP_Master_Instance;

_nonnull_
KSRP_Status KSRP_Master_Instance_Init(KSRP_Master_Instance* instance) {
    // TODO: Initialize all the instances
    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Master_Instance_UpdateFrame(
    KSRP_Master_Instance* instance,
    KSRP_Master_FrameID frame_id,
    void* frame, size_t frame_size) {

    switch(frame_id) {
        case KSRP_MASTER_MASTER_STATUS_FRAME_ID: {
            if (frame_size != KSRP_MASTER_MASTER_STATUS_FRAME_SIZE) {
                return KSRP_STATUS_INVALID_DATA_SIZE;
            }

            memcpy(&instance->master_status_instance, frame, frame_size);
            instance->master_status_ms_since_last_update = 0;

            break;
        }
        case KSRP_MASTER_DEVICES_ALIVE_FRAME_ID: {
            if (frame_size != KSRP_MASTER_DEVICES_ALIVE_FRAME_SIZE) {
                return KSRP_STATUS_INVALID_DATA_SIZE;
            }

            memcpy(&instance->devices_alive_instance, frame, frame_size);
            instance->devices_alive_ms_since_last_update = 0;

            break;
        }
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }

    return KSRP_STATUS_OK;
}

_nonnull_
KSRP_Status KSRP_Master_Instance_UpdateFrameField(
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

                    memcpy(&instance->master_status_instance.can_status, value, value_size);
                    instance->master_status_ms_since_last_update = 0;

                    break;
                default:
                    return KSRP_STATUS_INVALID_FIELD_TYPE;
            }
        case KSRP_MASTER_DEVICES_ALIVE_FRAME_ID:
            switch(field_id) {
                case KSRP_MASTER_DEVICES_ALIVE_WHEELS_FIELD_ID:
                    if (value_size != sizeof(instance->devices_alive_instance.wheels)) {
                        return KSRP_STATUS_INVALID_DATA_SIZE;
                    }

                    memcpy(&instance->devices_alive_instance.wheels, value, value_size);
                    instance->devices_alive_ms_since_last_update = 0;

                    break;
                default:
                    return KSRP_STATUS_INVALID_FIELD_TYPE;
            }
        default:
            return KSRP_STATUS_INVALID_FRAME_TYPE;
    }
    return KSRP_STATUS_OK;
}

#endif // KALMAN_STATUS_REPORT_MASTER_INSTANCE_H_