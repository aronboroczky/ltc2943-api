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

#pragma region Mock_stuff_for_testing
/**
 * @brief Indicator which register to read
 * 
 */
uint8_t registerToRead = 0x00;
/**
 * @brief Default register values for status and control geristers.
 * 
 */
uint8_t mockRegisterValues[2] = {0b00000001, 0b00111100}; 
#pragma endregion Mock_stuff_for_testing

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

	memset(pDst, mockRegisterValues[registerToRead], dataSize);

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

	//TODO: This is just for testing, replace it with proper i2c stuff.
	registerToRead = pSrc[0];

	if(dataSize > 1){
		mockRegisterValues[registerToRead] = pSrc[1];
	}

	return true;
}