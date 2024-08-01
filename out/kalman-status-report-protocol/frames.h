#ifndef KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_

#include <stdint.h>
#include <string.h>

typedef enum {
    KSRP_STATUS_OK,
    KSRP_STATUS_INVALID_DATA_SIZE,
    KSRP_STATUS_INVALID_FRAME_TYPE,

    KSRP_STATUS_ERROR
} KSRP_Status;

typedef struct {
    uint8_t* data;
    uint8_t length;
    uint8_t capacity;
} KSRP_RawData_Frame;

void RawDataFrame_Init(KSRP_RawData_Frame* raw_data, uint8_t* data, uint8_t capacity) {
    raw_data->data = data;
    raw_data->capacity = capacity;
    raw_data->length = 0;
}

KSRP_Status RawDataFrame_Append(KSRP_RawData_Frame* raw_data, uint8_t* bytes, uint8_t length) {
    if (raw_data->length + length < raw_data->capacity) {
        memcpy(&raw_data->data[raw_data->length], bytes, length);

        return KSRP_STATUS_OK;
    } else {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }
}

void RawDataFrame_Clear(KSRP_RawData_Frame* raw_data) {
    raw_data->length = 0;
}

#endif // KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_