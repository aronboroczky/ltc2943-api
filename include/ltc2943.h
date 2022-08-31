#ifndef LTC2943_H_
#define LTC2943_H_

#include <stdint.h>
#include <stdbool.h>

#define LTC2943_ADDRESS 0b1100100

/**
 * @brief LTC2943 Register map
 */
#define STATUS_REG									0x00
#define CONTROL_REG									0x01
#define ACCUMULATED_CHARGE_MSB_REG	0x02
#define ACCUM_CHARGE_LSB_REG				0x03
#define CHARGE_THRSH_HIGH_MSB_REG		0x04
#define CHARGE_THRSH_HIGH_LSB_REG		0x05
#define CHARGE_THRSH_LOW_MSB_REG		0x06
#define CHARGE_THRSH_LOW_LSB_REG		0x07
#define VOLTAGE_MSB_REG							0x08
#define VOLTAGE_LSB_REG							0x09
#define VOLTAGE_THRSH_HIGH_MSB_REG	0x0A
#define VOLTAGE_THRSH_HIGH_LSB_REG	0x0B
#define VOLTAGE_THRSH_LOW_MSB_REG		0x0C
#define VOLTAGE_THRSH_LOW_LSB_REG		0x0D
#define CURRENT_MSB_REG							0x0E
#define CURRENT_LSB_REG							0x0F
#define CURRENT_THRSH_HIGH_MSB_REG	0x10
#define CURRENT_THRSH_HIGH_LSB_REG	0x11
#define CURRENT_THRSH_LOW_MSB_REG		0x12
#define CURRENT_THRSH_LOW_LSB_REG		0x13
#define TEMPERATURE_MSB_REG					0x14
#define TEMPERATURE_LSB_REG					0x15
#define TEMPERATURE_THRSH_HIGH_REG	0x16
#define TEMPERATURE_THRSH_LOW_REG		0x17

/**
 * @brief Control register and its bits. 
 * ADC Modes. Default 0x00 - Sleep
 */
#define AUTOMATIC_MODE							0xC0
#define SCAN_MODE										0x80
#define MANUAL_MODE									0x40
#define SLEEP_MODE									0x00
#define ADCMODE_MASK								(3 << 6)

/**
 * @brief Sets coulomb counter prescaling factor M between 1 and 4096. Default is 111 - 0x30 - 4096.
 * 
 */
#define PRESCALER_1									0x00
#define PRESCALER_4									0x08
#define PRESCALER_16								0x10
#define PRESCALER_64								0x18
#define PRESCALER_256								0x20
#define PRESCALER_1024							0x28
#define PRESCALER_4096							0x30
#define PRESCALER_MASK							(7 << 3)

/**
 * @brief ALCC (active-low) pin configuration. Default is 10 - 0x04 - Alert Mode
 * 
 */
#define ALERT_MODE									0x04
#define CHARGE_COMPLETE_MODE				0x02
#define DISABLE_ALCC_PIN						0x00
#define ALLCPIN_MASK								(3 << 1)

#define SHUTDOWN_MASK								1

typedef enum adcModes
{
	Automatic = AUTOMATIC_MODE,
	Scan = SCAN_MODE,
	Manual = MANUAL_MODE,
	Sleep = MANUAL_MODE
} adcMode;

typedef enum prescalerSets
{
	M1 = PRESCALER_1,
	M4 = PRESCALER_4,
	M16 = PRESCALER_16,
	M64 = PRESCALER_64,
	M256 = PRESCALER_256,
	M1024 = PRESCALER_1024,
	M4096 = PRESCALER_4096
} prescalerSet;

typedef enum alccPinModes
{
	Alert = ALERT_MODE,
	ChargeComplete = CHARGE_COMPLETE_MODE,
	Disable = DISABLE_ALCC_PIN
} alccPinMode;

typedef struct controlFields
{
	adcMode mode;
	prescalerSet prescaler;
	alccPinMode allcPinMode;
	uint8_t shutDown;
} controlFields;

bool ltc2943_getMode(controlFields* controls);
bool ltc2943_setMode(controlFields controls);
bool ltc2943_checkVoltageAlertPending(bool *alertPending);
bool ltc2943_checkTemperatureAlertPending(bool *alertPending);

#endif //LTC2943_H_