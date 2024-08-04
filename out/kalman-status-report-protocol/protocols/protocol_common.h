#ifndef KALMAN_STATUS_REPORT_COMMON_H_
#define KALMAN_STATUS_REPORT_COMMON_H_

// Include standard libraries
#include <stdint.h>
#include <stdbool.h>

// Include user libraries
#include "kalman-status-report-protocol/frames.h"

// Enum for ID of each subsystem
// ASSUMPTION: values won't exceed 255
typedef enum {
    KSRP_MASTER_SUBSYSTEM_ID = 2,
    KSRP_WHEELS_SUBSYSTEM_ID = 1,
} KSRP_SubsystemID;

#endif // KALMAN_STATUS_REPORT_COMMON_H_