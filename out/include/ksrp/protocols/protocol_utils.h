/**
 * @file protocol_util.h
 * @brief Utility functions for the Kalman Status Report protocol
 */
#ifndef KALMAN_STATUS_REPORT_UTIL_H_
#define KALMAN_STATUS_REPORT_UTIL_H_

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
#include "ksrp/protocols/subsystems/wheels_protocol.h"

/**
 * @brief Verify the type ID of a frame
 *
 * @param frame The frame to verify
 * @return KSRP_TypeID The type ID of the frame
 */
KSRP_TypeID KSRP_VerifyTypeID(const KSRP_RawData_Frame* frame);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KALMAN_STATUS_REPORT_UTIL_H_