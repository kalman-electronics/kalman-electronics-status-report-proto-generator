#include <stdint.h>

#include "kalman-status-report-protocol/common.h"

// Health check values for can_status
#define can_status_HEALTH_CHECK_OK 0
#define can_status_HEALTH_CHECK_CRITICAL 255

typedef struct __attribute__((packed)) {
	uint8_t can_status;
} MasterStatusFrame;

// Health check values for wheels
#define wheels_HEALTH_CHECK_CRITICAL 0
#define wheels_HEALTH_CHECK_WARNING_MIN 1
#define wheels_HEALTH_CHECK_WARNING_MAX 3
#define wheels_HEALTH_CHECK_OK 4

typedef struct __attribute__((packed)) {
	uint8_t wheels;
} DevicesAliveFrame;