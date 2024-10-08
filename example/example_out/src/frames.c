#include "ksrp/frames.h"

_nonnull_
void KSRP_RawDataFrame_Init(KSRP_RawData_Frame* raw_data) {
    raw_data->length = 0;
}

_nonnull_
KSRP_Status KSRP_RawDataFrame_Append(KSRP_RawData_Frame* raw_data, uint8_t* bytes, uint8_t length) {
    if (raw_data->length + length < KSRP_RAW_DATA_FRAME_BUFFER_SIZE) {
        memcpy(&raw_data->data[raw_data->length], bytes, length);
        raw_data->length += length;

        return KSRP_STATUS_OK;
    } else {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }
}

_nonnull_
KSRP_TypeID KSRP_RawData_Frame_GetTypeID(const KSRP_RawData_Frame* raw_data) {
    if (raw_data->length < KSRP_ID_BYTES) {
        return KSRP_ILLEGAL_TYPE_ID;
    }

    return (raw_data->data[0] << 8) | raw_data->data[1];
}

_nonnull_
KSRP_Status KSRP_RawData_Frame_GetData(const KSRP_RawData_Frame* raw_data, uint8_t* buffer, uint8_t* length) {
    if (raw_data->length < KSRP_ID_BYTES) {
        return KSRP_STATUS_INVALID_DATA_SIZE;
    }

    if (buffer != NULL)
        memcpy(buffer, &raw_data->data[KSRP_ID_BYTES], *length);
    if (length != NULL)
        *length = raw_data->length - KSRP_ID_BYTES;

    return KSRP_STATUS_OK;
}

_nonnull_
void KSRP_RawDataFrame_Clear(KSRP_RawData_Frame* raw_data) {
    raw_data->length = 0;
}