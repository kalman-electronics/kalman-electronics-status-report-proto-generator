#ifndef KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_
#define KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_

#include <stdint.h>
#include <string.h>

typedef enum {
    KALMAN_PROTOCOL_STATUS_OK,
    KALMAN_PROTOCOL_STATUS_INVALID_DATA_SIZE,
    KALMAN_PROTOCOL_STATUS_INVALID_FRAME_TYPE,

    KALMAN_PROTOCOL_STATUS_ERROR
} KalmanProtocol_StatusTypeDef;

typedef struct {
    uint8_t* data;
    uint8_t length;
    uint8_t capacity;
} RawDataFrame_TypeDef;

void RawDataFrame_Init(RawDataFrame_TypeDef* raw_data, uint8_t* data, uint8_t capacity) {
    raw_data->data = data;
    raw_data->capacity = capacity;
    raw_data->length = 0;
}

KalmanProtocol_StatusTypeDef RawDataFrame_Append(RawDataFrame_TypeDef* raw_data, uint8_t* bytes, uint8_t length) {
    if (raw_data->length + length < raw_data->capacity) {
        memcpy(&raw_data->data[raw_data->length], bytes, length);

        return KALMAN_PROTOCOL_STATUS_OK;
    } else {
        return KALMAN_PROTOCOL_STATUS_INVALID_DATA_SIZE;
    }
}

void RawDataFrame_Clear(RawDataFrame_TypeDef* raw_data) {
    raw_data->length = 0;
}

#endif // KALMAN_PROTOCOL_STATUS_REPORT_FRAMES_H_