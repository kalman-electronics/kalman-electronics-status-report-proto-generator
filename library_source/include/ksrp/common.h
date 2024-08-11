#ifndef KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

#define KSRP_ID_BYTES 2
#define KSRP_MAX_FRAME_SIZE 64 - KSRP_ID_BYTES

#define _packed_ __attribute__((packed))
#define _nonnull_ __attribute__((nonnull))

typedef enum {
    KSRP_RESULT_OK,
    KSRP_RESULT_WARNING,
    KSRP_RESULT_CRITICAL,

    KSRP_RESULT_UNKNOWN
} KSRP_HealthCheckResult;

typedef enum {
    KSRP_STATUS_OK,
    KSRP_STATUS_INVALID_DATA_SIZE,
    KSRP_STATUS_INVALID_FRAME_TYPE,
    KSRP_STATUS_INVALID_FIELD_TYPE,

    KSRP_STATUS_ERROR
} KSRP_Status;

#define KSRP_ILLEGAL_FRAME_ID 0xFFFFFFFF
#define KSRP_ILLEGAL_FIELD_ID 0xFFFFFFFF
typedef KSRP_Status (*KSRP_FrameUpdateCallback)(uint32_t subsystem_id, void* frame_instance, uint32_t frame_id, uint32_t field_id);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KALMAN_PROTOCOL_STATUS_REPORT_COMMON_H_