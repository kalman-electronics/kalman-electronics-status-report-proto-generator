#include <stdint.h>

// Protocol Includes
#include "kalman-status-report-protocol/common.h"
#include "kalman-status-report-protocol/frames.h"

// Health check values for driver_status
#define driver_status_HEALTH_CHECK_OK 0
#define driver_status_HEALTH_CHECK_CRITICAL 255

// Health check values for temperature
#define temperature_HEALTH_CHECK_OK_MIN 0
#define temperature_HEALTH_CHECK_OK_MAX 100
#define temperature_HEALTH_CHECK_WARNING_MIN 100
#define temperature_HEALTH_CHECK_WARNING_MAX 200
#define temperature_HEALTH_CHECK_CRITICAL_MIN 200
#define temperature_HEALTH_CHECK_CRITICAL_MAX 300

typedef enum {
	ALGORITHM_TYPE_POSITION,
	ALGORITHM_TYPE_VELOCITY,
	ALGORITHM_TYPE_TORQUE
} WheelsStatusFrame_AlgorithmTypeTypeDef;

typedef struct __attribute__((packed)) {
	uint8_t controller_id;
	uint8_t driver_status;
	float temperature;
	WheelsStatusFrame_AlgorithmTypeTypeDef algorithm_type;
} WheelsStatusFrame;

KalmanProtocol_StatusTypeDef WheelsStatusFrame_unpack(const RawDataFrame_TypeDef* raw_data, WheelsStatusFrame* frame) {
    if (raw_data->data_length != sizeof(WheelsStatusFrame) + KALMAN_PROTOCOL_STATUS_REPORT_ID_BYTES) {
        return KALMAN_PROTOCOL_STATUS_INVALID_FRAME_SIZE;
    }



    return KALMAN_PROTOCOL_STATUS_OK;
}