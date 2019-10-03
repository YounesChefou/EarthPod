/**
 * @file      MMA8451.h
 * @brief     Driver for the MMA8451 3-axis Accelerometer
 * @author    Wilmin Ceballos (wceballos)
 * @version   1.0
 * @see       https://www.nxp.com/docs/en/data-sheet/MMA8451Q.pdf
 * @license   MIT License
 *
 * Copyright (c) 2019 Wilmin Ceballos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MMA8451_H
#define MMA8451_H

#include "mbed.h"

#define MMA8451_I2C_CLOCK 400000 // 400 kHz is the max rate.

/**
 *  Factory default addresses for i2c interface.
 */
#define MMA8451_ADDRESS_SA0_0      0x1C // SA0 = 0
#define MMA8451_ADDRESS_SA0_1      0x1D // SA0 = 1 (default)

/**
 *  MMA8451 Registers.
 */
#define MMA8451_STATUS             0x00 // Data Status / F_mode
#define MMA8451_OUT_X_MSB          0x01 // 14 bit X Data (MSB)
#define MMA8451_OUT_X_LSB          0x02 // 14 bit X Data (LSB)
#define MMA8451_OUT_Y_MSB          0x03 // 14 bit Y Data (MSB)
#define MMA8451_OUT_Y_LSB          0x04 // 14 bit Y Data (LSB)
#define MMA8451_OUT_Z_MSB          0x05 // 14 bit Z Data (MSB)
#define MMA8451_OUT_Z_LSB          0x06 // 14 bit Z Data (LSB)
#define MMA8451_F_SETUP            0x09 // FIFO Setup
#define MMA8451_TRIG_CFG           0x0A // FIFO Triggers
#define MMA8451_SYSMOD             0x0B // System Mode
#define MMA8451_INT_SOURCE         0x0C // Interrupt Status 
#define MMA8451_WHO_AM_I           0x0D // ID Register = 0b00011010
#define MMA8451_XYZ_DATA_CFG       0x0E // Data config (sensitivity adjustment)
#define MMA8451_HP_FILTER_CUTOFF   0x0F // HP Filter Settings
#define MMA8451_PL_STATUS          0x10 // PL Status
#define MMA8451_PL_CFG             0x11 // PL Config
#define MMA8451_PL_COUNT           0x12 // PL Debounce
#define MMA8451_PL_BF_ZCOMP        0x13 // PL Back/Front Z Comp
#define MMA8451_P_L_THS_REG        0x14 // PL Threshold
#define MMA8451_FF_MT_CFG          0x15 // Freefall/Motion Config
#define MMA8451_FF_MT_SRC          0x16 // Freefall/Motion Source
#define MMA8451_FF_MT_THS          0x17 // Freefall/Motion Threshold
#define MMA8451_FF_MT_COUNT        0x18 // Freefall/Motion Debounce
#define MMA8451_TRANSIENT_CFG      0x1D // Transient Config
#define MMA8451_TRANSIENT_SRC      0x1E // Transient Source
#define MMA8451_TRANSIENT_THS      0x1F // Transient Threshold
#define MMA8451_TRANSIENT_COUNT    0x20 // Transient Debounce
#define MMA8451_PULSE_CFG          0x21 // Pulse Config
#define MMA8451_PULSE_SRC          0x22 // Pulse Source
#define MMA8451_PULSE_THSX         0x23 // Pulse X Threshold
#define MMA8451_PULSE_THSY         0x24 // Pulse Y Threshold
#define MMA8451_PULSE_THSZ         0x25 // Pulse Z Threshold
#define MMA8451_PULSE_TMLT         0x26 // Pulse First Timer
#define MMA8451_PULSE_LTCY         0x27 // Pulse Latency
#define MMA8451_PULSE_WIND         0x28 // Pulse Second Window
#define MMA8451_ASLP_COUNT         0x29 // Auto-sleep Counter
#define MMA8451_CTRL_REG1          0x2A // Control Register 1
#define MMA8451_CTRL_REG2          0x2B // Control Register 2
#define MMA8451_CTRL_REG3          0x2C // Control Register 3: Wake Interrupts
#define MMA8451_CTRL_REG4          0x2D // Control Register 4: Interrupt Enable
#define MMA8451_CTRL_REG5          0x2E // Control Register 5: Interrupt Config
#define MMA8451_OFF_X              0x2F  // X 8-bit Offset
#define MMA8451_OFF_Y              0x30 // Y 8-bit Offset
#define MMA8451_OFF_Z              0x31 // Z 8-bit Offset

/**
 *  Sensitivity measured in counts/g.
 *  Set using XYZ_DATA_CFG[1:0] -> FS[1:0].
 */
typedef enum _mma8451_sensitivity_t {
  MMA8451_SENSITIVITY_2G = 0x00, // +/- 2g, 4096 counts/g (default)
  MMA8451_SENSITIVITY_4G = 0x01, // +/- 4g, 2048 counts/g
  MMA8451_SENSITIVITY_8G = 0x02  // +/- 8g, 1024 counts/g
} mma8451_sensitivity_t;

/**
 *  Supported output data rates (ODR) from 1.56 Hz to 800 Hz.
 */
typedef enum _mma8451_dataRate_t {
  MMA8451_ODR_800_HZ     = 0x00, // Default
  MMA8451_ODR_400_HZ     = 0x01,
  MMA8451_ODR_200_HZ     = 0x02,
  MMA8451_ODR_100_HZ     = 0x03,
  MMA8451_ODR_50_HZ      = 0x04,
  MMA8451_ODR_12_5_HZ    = 0x05,
  MMA8451_ODR_6_25_HZ    = 0x06,
  MMA8451_ODR_1_56_HZ    = 0x07
} mma8451_dataRate_t;

/**
 *  @class MMA8451
 *  @brief API for the MMA8451
 */
class MMA8451 {
public:

  /**
   *  Constructor.
   *  All settings are set to default.
   *  @param i2c I2C object
   *  @param i2cAddr the device address
   */
  MMA8451(I2C &i2c, uint8_t i2cAddr = MMA8451_ADDRESS_SA0_1);

  /**
   *  Destructor.
   */
  ~MMA8451();

  /**
   * Initialize MMA8451 with defaults.
   */
  bool init();

  /**
   * Updates the x, y, z member variables with accelerometer data.
   * Reads all 3 axes quickly by using the multi-read functionality.
   */
  void getXYZ();

  /**
   * Reads accelerometer x-axis data registers directly.
   * @returns Member variable x.
   */
  float getX();

  /**
   * Reads accelerometer y-axis data registers directly.
   * @returns Member variable y.
   */
  float getY();

  /**
   * Reads accelerometer z-axis data registers directly.
   * @returns Member variable z.
   */
  float getZ();

  /**
   * @returns Value at register WHO_AM_I
   */  
  uint8_t id();

  /**
   * Read a single byte from a MMA8451 register directly.
   * All 44 registers can be read from. All registers are 8-bit registers.
   * @param reg An MMA8451 register
   * @param data Where data read will be stored
   * @returns
   *   true on success (ack)
   *   false on failure (nak)
   */
  bool readRegister(uint8_t reg, uint8_t *data);

  /**
   * Write to a MMA8451 register directly.
   * @returns
   *   true on success (ack)
   *   false on failure (nak)
   */
  bool writeRegister(uint8_t reg, uint8_t data);

  void setStandbyMode();
  void setActiveMode();
  void setDataRate(mma8451_dataRate_t rate);
  void setSensitivity(mma8451_sensitivity_t sens);

  float x, y, z;

private:
  float _readAxis(uint8_t reg);

  I2C *_i2c;
  uint8_t _i2cAddr;
  uint8_t _whoami;
  mma8451_sensitivity_t _sens;
};

#endif


