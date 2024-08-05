#ifndef KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_

#include <stdint.h>
#include <string.h>

#include "common.h"

typedef enum {
    KSRP_STATUS_OK,
    KSRP_STATUS_INVALID_DATA_SIZE,
    KSRP_STATUS_INVALID_FRAME_TYPE,
    KSRP_STATUS_INVALID_FIELD_TYPE,

    KSRP_STATUS_ERROR
} KSRP_Status;

typedef struct {
    uint8_t* data;
    uint8_t length;
    uint8_t capacity;
} KSRP_RawData_Frame;

typedef uint16_t KSRP_TypeID;

#define KSRP_MAKE_TYPE_ID(subsystem_id, type_id) ((subsystem_id << 8) | type_id)
#define KSRP_GET_SUBSYSTEM_ID_FROM_TYPE_ID(type_id) (type_id >> 8)
#define KSRP_GET_TYPE_ID_FROM_TYPE_ID(type_id) (type_id & 0xFF)
#define KSRP_ILLEGAL_TYPE_ID 0xFFFF

void KSRP_RawDataFrame_Init(KSRP_RawData_Frame* raw_data, uint8_t* data, uint8_t capacity) {
    raw_data->data = data;
    raw_data->capacity = capacity;
    raw_data->length = 0;
}

KSRP_Status KSRP_RawDataFrame_Append(KSRP_RawData_Frame* raw_data, uint8_t* bytes, uint8_t length) {
    if (raw_data->length + length < raw_data->capacity) {
        memcpy(&raw_data->data[raw_data->length], bytes, length);

        return KSRP_STATUS_OK;
    } else {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }
}

KSRP_TypeID KSRP_RawData_Frame_GetTypeID(const KSRP_RawData_Frame* raw_data) {
    if (raw_data->length < KSRP_ID_BYTES) {
        return KSRP_ILLEGAL_TYPE_ID;
    }

    return (raw_data->data[0] << 8) | raw_data->data[1];
}

void KSRP_RawDataFrame_Clear(KSRP_RawData_Frame* raw_data) {
    raw_data->length = 0;
}

#endif // KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_