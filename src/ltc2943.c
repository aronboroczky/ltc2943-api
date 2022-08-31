#include "ltc2943.h"
#include "i2c_driver.h"

bool ltc2943_getMode(controlFields *controls)
{
	if (!i2cInitialize())
	{
		return false;
	}

	if (!i2cWrite(LTC2943_ADDRESS << 1, CONTROL_REG, 1))
	{
		return false;
	}

	uint8_t controlRegisterContent = 0x00;

	if (!i2cRead(LTC2943_ADDRESS << 1, &controlRegisterContent, 1))
	{
		return false;
	}

	controls->mode = controlRegisterContent & ADCMODE_MASK;
	controls->prescaler = controlRegisterContent & PRESCALER_MASK;
	controls->allcPinMode = controlRegisterContent & ALLCPIN_MASK;
	controls->shutDown = controlRegisterContent & SHUTDOWN_MASK;

	return true;
}

bool ltc2943_setMode(controlFields controls)
{
	if (!i2cInitialize())
	{
		return false;
	}

	uint8_t controlData[2];
	controlData[0] = CONTROL_REG;
	controlData[1] = controls.mode | controls.prescaler | controls.allcPinMode | controls.shutDown;

	return i2cWrite(LTC2943_ADDRESS << 1, controlData, sizeof(controlData));
}

bool ltc2943_checkVoltageAlertPending(bool *alertPending)
{
	if (!i2cInitialize())
	{
		return false;
	}

	if (!i2cWrite(LTC2943_ADDRESS << 1, STATUS_REG, 1))
	{
		return false;
	}

	uint8_t statusRegisterContent = 0x00;

	if (!i2cRead(LTC2943_ADDRESS << 1, &statusRegisterContent, 1))
	{
		return false;
	}

	*alertPending = statusRegisterContent >> 1 & 1;

	return true;
}

bool ltc2943_checkTemperatureAlertPending(bool *alertPending)
{
	if (!i2cInitialize())
	{
		return false;
	}

	if (!i2cWrite(LTC2943_ADDRESS << 1, STATUS_REG, 1))
	{
		return false;
	}

	uint8_t statusRegisterContent = 0x00;

	if (!i2cRead(LTC2943_ADDRESS << 1, &statusRegisterContent, 1))
	{
		return false;
	}

	*alertPending = statusRegisterContent >> 4 & 1;

	return true;
}

bool i2cInitialize()
{
	if (i2cIsInitialized())
	{
		return true;
	}

	return i2cInit();
}