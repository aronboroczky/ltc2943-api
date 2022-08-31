#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Initializes i2c peripheral. 
 * Retrurns true if initialization was successful.
 * 
 * @return true
 * @return false 
 */
bool i2cInit(void);

/**
 * @brief Deinitializes i2c peripheral. 
 * Retrurns true if deinitialization was successful.
 * 
 * @return true 
 * @return false 
 */
bool i2cDeinit(void);

/**
 * @brief returns whether the i2c peripheral is initialized or not.
 * Retrurns true if initialized.
 * 
 * @return true 
 * @return false 
 */
bool i2cIsInitialized(void);

/**
 * @brief Reads data from i2c device on "address" to the pDst buffer.
 * Returns true if reading was successfull, false in case of an error.
 * 
 * @param address Device's adress
 * @param pDst Data is read to this buffer
 * @param dataSize Size of data to read
 * @return true 
 * @return false 
 */

bool i2cRead(uint8_t address, uint8_t *pDst, uint16_t dataSize);

/**
 * @brief Writes data to i2c device on "address" to the pDst buffer.
 * Returns true if reading was successfull, false in case of an error.
 * 
 * @param address Device's adress
 * @param pSrc Data buffer to be written onto the device
 * @param dataSize Size of data to write
 * @return true 
 * @return false 
 */
bool i2cWrite(uint8_t address, const uint8_t *pSrc, uint16_t dataSize);

#endif //I2C_DRIVER_H_