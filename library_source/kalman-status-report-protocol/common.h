#ifndef KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_

#include <stdint.h>

typedef enum {
    OK,
    WARNING,
    CRITICAL,
} StatusReportResult_TypeDef;

#endif // KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_