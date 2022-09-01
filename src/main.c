#include <stdio.h>
#include <string.h>
#include "ltc2943.h"

bool test_ltc2943_getSetMode(void)
{
	printf("Testing \"ltc2943_getMode\"...\n\r");
	printf("Expected default Adc Mode: Sleep (0x00, 0).\n\r");
	printf("\n\r");

	// Set mode to Automatic (0xC0) to make sure I see the difference.
	adcMode mode = (adcMode)AUTOMATIC_MODE;

	printf("Getting mode...\n\r");
	ltc2943_getMode(&mode);

	bool getModeResult = false;
	char strResult[5] = "FAIL";
	if (mode == (adcMode)SLEEP_MODE)
	{
		strcpy(strResult, "PASS");
		getModeResult = true;
	}

	printf("%s | Mode equals: %d, expected %d. \n\r", strResult, mode, SLEEP_MODE);
	printf("\n\r");

	printf("Testing \"ltc2943_setMode\"...\n\r");
	printf("Setting mode to Scan Mode (0x80 , 128)...\n\r");
	ltc2943_setMode((adcMode)SCAN_MODE);
	printf("Mode set.\n\r");
	ltc2943_getMode(&mode);

	bool setModeResult = false;
	strcpy(strResult, "FAIL");
	if (mode == (adcMode)SCAN_MODE)
	{
		strcpy(strResult, "PASS");
		setModeResult = true;
	}

	printf("%s | Mode equals: %d, expected %d. \n\r", strResult, mode, SCAN_MODE);
	printf("\n\r");

	return getModeResult & setModeResult;
}

bool test_ltc2943_checkVoltageAlertPending(void)
{
	// register value with pending voltage alert: 0b00000011 -> 0x03 -> 3
	printf("Testing \"ltc2943_checkVoltageAlertPending\"...\n\r");
	printf("Expected default voltage alert: false\n\r");
	printf("\n\r");

	// Setting alert pending flag to true to see difference.
	bool isAlertPending = true;
	ltc2943_checkVoltageAlertPending(&isAlertPending);

	bool voltageAlertResult = false;
	char strResult[5] = "FAIL";
	if (!isAlertPending)
	{
		strcpy(strResult, "PASS");
		voltageAlertResult = true;
	}
	printf("%s | Voltage alert equals: %d, expected %d. \n\r", strResult, isAlertPending, false);

	return voltageAlertResult;
}

bool test_ltc2943_checkTemperatureAlertPending(void)
{
	// register value with pending temperature alert: 0b00010001 -> 0x11 -> 17
	printf("Testing \"ltc2943_checkTemperatureAlertPending\"...\n\r");
	printf("Expected default temperature alert: false\n\r");
	printf("\n\r");

	// Setting alert pending flag to true to see difference.
	bool isAlertPending = true;
	ltc2943_checkTemperatureAlertPending(&isAlertPending);

	bool temperatureAlertResult = false;
	char strResult[5] = "FAIL";
	if (!isAlertPending)
	{
		strcpy(strResult, "PASS");
		temperatureAlertResult = true;
	}
	printf("%s | Temperature alert equals: %d, expected %d. \n\r", strResult, isAlertPending, false);


	return temperatureAlertResult;
}

int main(int argc, char const *argv[])
{
	bool getSetModeResult = test_ltc2943_getSetMode();

	printf("\n\r");

	bool voltAlertResult = test_ltc2943_checkVoltageAlertPending();
	
	printf("\n\r");

	bool tempAlertersult = test_ltc2943_checkTemperatureAlertPending();
	
	printf("\n\r");

	printf("########################################## \n\r");

	if(getSetModeResult && voltAlertResult && tempAlertersult){
		printf("PASS | All tests ran successfully. \n\r");
		return 0;
	} 
	

	printf("FAIL | Some tests have failed. \n\r");
	return -1;
}
