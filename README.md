# ltc2943-api

Basic API for Analog Devices - LTC2943 Multicell Battery Gas Gauge with Temperature, Voltage and Current Measurement.
[Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/2943fa.pdf "Analog Devices - LT2943")

## Functionality
### Get Adc Mode
You can get the configured Adc Mode with `ltc2943_getMode`

### Set Adc Mode
You can configure the Adc Mode with `ltc2943_setMode`

### Check for pending voltage alert
You can check if there is a pending voltage alert `ltc2943_checkVoltageAlertPending`

### Check for pending temperature alert
You can check if there is a pending temperature alert `ltc2943_checkTemperatureAlertPending`

## Test 
You can find the main.exe in the build directory which runs some basic tests.

## Build
The project was built on windows with g++ / make

