/*
 * general configuration file
 *
 *
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

//============================
//
//MCU configuratoin
//
//============================

//clock
#define RUN_MODE_CORE_CLOCK                               47972352U  /*!< Core clock frequency: 47972352Hz */
#define OSC_CAP0P                                         0U  /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE                                0U  /*!< Disable external reference clock */


//GPIO
//bit mask for GPIO A output pins
//bit31 bit30 bit29 .... bit2 bit1 bit0
//pin31 pin30 pin29 .... pin2 pin1 pin0
#define GPIO_A_OUTPUT_PINS 0b00000000000000000000001000000000
#define GPIO_B_OUTPUT_PINS 0b00000000000000000000110000000000
#define GPIO_A_INPUT_PINS 0b00000000000000000000000000000000
#define GPIO_B_INPUT_PINS 0b00000000000000000000000000000000

//SPI
#define USE_SPI
#define DEFAULT_SPI_MASTER (SPI0)
#define DEFAULT_SPI_MASTER_SOURCE_CLOCK (kCLOCK_BusClk)
#define DEFAULT_SPI_MASTER_CLK_FREQ CLOCK_GetFreq((kCLOCK_BusClk))


//UART
#define USE_UART0

#define UART_BAUDRATE 115200

#ifdef USE_UART0
#define UART0_DEBUG
#endif


//ADC


//I2C
#ifndef USE_I2C
#define USE_I2C
#define I2C_BASE_ADDR (I2C0)
#define I2C_PORT (PORTB)
#define I2C_GPIO_PORT (GPIOB)
#define I2C_BAUDRATE 100000U

#define I2C_SDA_PORT I2C_PORT 
#define I2C_SCL_PORT I2C_PORT
#define I2C_SDA_GPIO_PORT I2C_GPIO_PORT
#define I2C_SDA_PIN 4U
#define I2C_SCL_GPIO_PORT I2C_GPIO_PORT
#define I2C_SCL_PIN 3U
#define I2C_RELEASE_BUS_COUNT 100U

#endif

//============================
//
//Devices configuration
//
//============================

//lcd

#define LCD_SPI (SPI0)
#define LCD_SPI_IRQ (SPI0_IRQn)
//gpio used for lcd must be set in GPIO section

//data/command pin, output, 0 for data, 1 for command
#define LCD_DC_GPIO_PORT GPIOB
#define LCD_DC_GPIO_PIN  10U

//chip enable pin, output, 1 for enable
#define LCD_CE_GPIO_PORT GPIOB
#define LCD_CE_GPIO_PIN  11U

//reset pin, output, ---__---, low level
#define LCD_RST_GPIO_PORT GPIOA
#define LCD_RST_GPIO_PIN 9U

// each charactor take 6X8 pixel
// display buffer same as pixel buffer 14X6(columnXrow) character
#define LCD_DISPLAY_BUFFER_COLUMN (14)
#define LCD_DISPLAY_BUFFER_ROW (6)


