#include "ltc2943.h"
#include "i2c_driver.h"

bool i2cInitialize(void);
bool getControlRegister(controlFields *controls);
bool setControlRegister(controlFields controls);
bool getStatusRegister(uint8_t *status);

bool ltc2943_getMode(adcMode *mode)
{
	controlFields controls;
	if (!getControlRegister(&controls))
	{
		return false;
	}

	*mode = controls.mode;

	return true;
}

bool ltc2943_setMode(adcMode mode)
{
	if (!i2cInitialize())
	{
		return false;
	}

	controlFields controls;
	if (!getControlRegister(&controls))
	{
		return false;
	}

	controls.mode = mode;

	return setControlRegister(controls);
}

bool ltc2943_checkVoltageAlertPending(bool *alertPending)
{

	uint8_t statusRegisterContent = 0x00;

	if (getStatusRegister(&statusRegisterContent))
	{
		return false;
	}

	*alertPending = statusRegisterContent >> 1 & 1;

	return true;
}

bool ltc2943_checkTemperatureAlertPending(bool *alertPending)
{
	uint8_t statusRegisterContent = 0x00;

	if (getStatusRegister(&statusRegisterContent))
	{
		return false;
	}

	*alertPending = statusRegisterContent >> 4 & 1;

	return true;
}

bool i2cInitialize(void)
{
	if (i2cIsInitialized())
	{
		return true;
	}

	return i2cInit();
}

bool getControlRegister(controlFields *controls)
{
	if (!i2cInitialize())
	{
		return false;
	}

	uint8_t controlRegister[1] = {CONTROL_REG};
	if (!i2cWrite(LTC2943_ADDRESS << 1, controlRegister, 1))
	{
		return false;
	}

	uint8_t controlRegisterContent = 0x00;

	if (!i2cRead(LTC2943_ADDRESS << 1, &controlRegisterContent, 1))
	{
		return false;
	}

	controls->mode = (adcMode)(controlRegisterContent & ADCMODE_MASK);
	controls->prescaler = (prescalerSet)(controlRegisterContent & PRESCALER_MASK);
	controls->allcPinMode = (alccPinMode)(controlRegisterContent & ALLCPIN_MASK);
	controls->shutDown = (uint8_t)(controlRegisterContent & SHUTDOWN_MASK);

	return true;
}

bool setControlRegister(controlFields controls)
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

bool getStatusRegister(uint8_t *status)
{
	if (!i2cInitialize())
	{
		return false;
	}

	if (!i2cWrite(LTC2943_ADDRESS << 1, STATUS_REG, 1))
	{
		return false;
	}

	return i2cRead(LTC2943_ADDRESS << 1, status, 1);
}