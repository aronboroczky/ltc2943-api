#include "ltc2943.h"
#include "i2c_driver.h"

bool ltc2943_getMode(controlFields* controls)
{
	if(!i2cInitialize())
	{
		return false;
	}

	i2cWrite(LTC2943_ADDRESS << 1, CONTROL_REG, 1);
	uint8_t controlRegisterContent = 0x00;
	i2cRead(LTC2943_ADDRESS << 1, &controlRegisterContent, 1);

	
	controls->mode = controlRegisterContent & ADCMODE_MASK;
	controls->prescaler = controlRegisterContent & PRESCALER_MASK;
	controls->allcPinMode = controlRegisterContent & ALLCPIN_MASK;
	controls->shutDown = controlRegisterContent & SHUTDOWN_MASK;

	return true;
}

bool ltc2943_setMode(controlFields controls)
{
	return true;
}

bool ltc2943_checkVoltageAlertPending(bool *alertPending)
{
	return true;
}

bool ltc2943_checkTemperatureAlertPending(bool *alertPending)
{
	return true;
}

bool i2cInitialize()
{
	if(i2cIsInitialized())
	{
		return true;
	}

	return i2cInit();
}