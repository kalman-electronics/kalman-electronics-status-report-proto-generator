#ifndef KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_

#include <stdint.h>

#define KSRP_ID_BYTES 2

#define _packed_ __attribute__((packed))
#define _nonnull_ __attribute__((nonnull))

//TODO: ADD prefix to all enums
typedef enum {
    KSRP_RESULT_OK,
    KSRP_RESULT_WARNING,
    KSRP_RESULT_CRITICAL,

    KSRP_RESULT_UNKNOWN
} KSRP_HealthCheckResult;

#endif // KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_