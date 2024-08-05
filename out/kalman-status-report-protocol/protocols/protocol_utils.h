/**
 * @file protocol_util.h
 * @brief Utility functions for the Kalman Status Report protocol
 */
#ifndef KALMAN_STATUS_REPORT_UTIL_H_
#define KALMAN_STATUS_REPORT_UTIL_H_

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "kalman-status-report-protocol/protocols/subsystems/master_protocol.h"
#include "kalman-status-report-protocol/protocols/subsystems/wheels_protocol.h"

/**
 * @brief Verify the type ID of a frame
 *
 * @param frame The frame to verify
 * @return KSRP_TypeID The type ID of the frame
 */
KSRP_TypeID KSRP_VerifyTypeID(const KSRP_RawData_Frame* frame) {
    if (frame->length < KSRP_ID_BYTES) {
        return KSRP_ILLEGAL_TYPE_ID;
    }

    switch (KSRP_RawData_Frame_GetTypeID(frame)) {
        case KSRP_MASTER_MASTER_STATUS_TYPE_ID:
            return KSRP_MASTER_MASTER_STATUS_TYPE_ID;
        case KSRP_MASTER_DEVICES_ALIVE_TYPE_ID:
            return KSRP_MASTER_DEVICES_ALIVE_TYPE_ID;
        case KSRP_WHEELS_WHEELS_STATUS_TYPE_ID:
            return KSRP_WHEELS_WHEELS_STATUS_TYPE_ID;
    }

    return KSRP_ILLEGAL_TYPE_ID;
}

#endif // KALMAN_STATUS_REPORT_UTIL_H_