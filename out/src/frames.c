#include "common.h"

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