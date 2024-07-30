#ifndef KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_

#include <stdint.h>

#define KALMAN_PROTOCOL_STATUS_REPORT_ID_BYTES 2

#define _packed_ __attribute__((packed))
#define _nonnull_ __attribute__((nonnull))

typedef enum {
    OK,
    WARNING,
    CRITICAL,

    UNKNOWN
} StatusReportResult_TypeDef;

#endif // KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_