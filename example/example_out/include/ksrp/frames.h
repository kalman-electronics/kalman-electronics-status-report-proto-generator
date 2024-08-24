#ifndef KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>
#include <string.h>

#include "ksrp/common.h"

#define KSRP_RAW_DATA_FRAME_BUFFER_SIZE (KSRP_MAX_FRAME_SIZE + KSRP_ID_BYTES)

typedef struct {
    uint8_t data[KSRP_RAW_DATA_FRAME_BUFFER_SIZE];
    uint8_t length;
} KSRP_RawData_Frame;

typedef uint16_t KSRP_TypeID;

#define KSRP_MAKE_TYPE_ID(subsystem_id, type_id) ((subsystem_id << 8) | type_id)
#define KSRP_GET_SUBSYSTEM_ID_FROM_TYPE_ID(type_id) (type_id >> 8)
#define KSRP_GET_TYPE_ID_FROM_TYPE_ID(type_id) (type_id & 0xFF)
#define KSRP_ILLEGAL_TYPE_ID 0xFFFF

_nonnull_
void KSRP_RawDataFrame_Init(KSRP_RawData_Frame* raw_data);

_nonnull_
KSRP_Status KSRP_RawDataFrame_Append(KSRP_RawData_Frame* raw_data, uint8_t* bytes, uint8_t length);

_nonnull_
KSRP_TypeID KSRP_RawData_Frame_GetTypeID(const KSRP_RawData_Frame* raw_data);

_nonnull_
KSRP_Status KSRP_RawData_Frame_GetData(const KSRP_RawData_Frame* raw_data, uint8_t* buffer, uint8_t* length);

_nonnull_
void KSRP_RawDataFrame_Clear(KSRP_RawData_Frame* raw_data);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_