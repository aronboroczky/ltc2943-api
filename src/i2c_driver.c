#include "i2c_driver.h"
#include <string.h>

bool initialized = false;

bool i2cInit(void)
{
	if (i2cIsInitialized())
	{
		return initialized;
	}
	
	initialized = true;
	return true;
}

bool i2cDeinit(void)
{
	if (!i2cIsInitialized())
	{
		return initialized;
	}

	initialized = false;
	return true;
}

bool i2cIsInitialized(void)
{
	return initialized;
}

bool i2cRead(uint8_t address, uint8_t *pDst, uint16_t dataSize)
{
	if (!initialized)
	{
		return false;
	}

	if (dataSize < 1)
	{
		return false;
	}

	memset(pDst, 0xaa, dataSize);

	return true;
}

bool i2cWrite(uint8_t address, const uint8_t *pSrc, uint16_t dataSize)
{
	if (!initialized)
	{
		return false;
	}

	if (dataSize < 1)
	{
		return false;
	}

	return true;
}