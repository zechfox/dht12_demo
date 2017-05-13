#include "fsl_common.h"
#include "fsl_i2c.h"
#include "fsl_debug_console.h"

#include "mcu_MKL02Z32VFM4.h"
#include "configuration.h"

#include "dht12.h"

status_t dht12_get_temp_humi(char * temp_str, char * humi_str)
{
  i2c_master_transfer_t masterXfer;
  status_t result = kStatus_Success;
  uint8_t dht12_data[DHT12_DATA_SIZE];
  uint8_t humi_high = 0;
  uint8_t humi_low = 0;
  uint8_t temp_high = 0;
  uint8_t temp_low = 0;
  uint8_t checksum = 0;
  uint8_t my_checksum = 0;

  uint16_t temperature = 0;
  uint16_t humidity = 0;

  dht12_data[0] = 0x00;
  dht12_data[1] = 0x00;
  dht12_data[2] = 0x00;
  dht12_data[3] = 0x00;
  dht12_data[4] = 0xFF;

  memset(&masterXfer, 0, sizeof(masterXfer));
  masterXfer.slaveAddress = DHT12_I2C_ADDR;
  masterXfer.direction = kI2C_Read;
  masterXfer.subaddress = DHT12_I2C_REG_START_ADDR;
  masterXfer.subaddressSize = 1;
  masterXfer.data = &dht12_data[0];
  masterXfer.dataSize = DHT12_DATA_SIZE;
  masterXfer.flags = kI2C_TransferDefaultFlag;

  /*  direction=write : start+device_write;cmdbuff;xBuff; */
  /*  direction=recive : start+device_write;cmdbuff;repeatStart+device_read;xBuff; */

  //result = I2C_MasterTransferBlocking(I2C_BASE_ADDR, &masterXfer);
  result = I2C_MasterTransferNonBlocking(I2C_BASE_ADDR, get_i2c_handler(), &masterXfer);

  if(kStatus_Success == result)
  {
#if 1
    /*  wait for transfer completed. */
    while ((!nakFlag) && (!completionFlag))
    {
    }
 
    PRINTF("Transfer status, nakFlag:%d, completionFlag:%d \r\n", nakFlag, completionFlag);
    nakFlag = false;
 
    if (completionFlag == true)
    {
      completionFlag = false;
    }
    else
    {
      result = kStatus_Fail;
    }
#endif

    humi_high = dht12_data[0];
    humi_low = dht12_data[1]; 
    temp_high = dht12_data[2];
    temp_low = dht12_data[3];
    checksum = dht12_data[4];

    my_checksum = (uint8_t) humi_high + humi_low + temp_high + temp_low;

    //receive correct data
    if(my_checksum == checksum)
    {
      humidity = humi_high * 10 + humi_low; 

      if(temp_low & 0X80) //negative
      {
        temperature = 0 - (temp_high * 10 + ((temp_low & 0x7F)));
      }
      else
      {
        temperature =temp_high * 10 + temp_low;
      }

      if(humidity > DHT12_MAX_HUMI)
      {
        humidity = DHT12_MAX_HUMI;
      }
      if(humidity < DHT12_MIN_HUMI)
      {
        humidity = DHT12_MIN_HUMI;
      }
      if(temperature > DHT12_MAX_TEMP)
      {
        temperature = DHT12_MAX_TEMP;
      }
      if(temperature < DHT12_MIN_TEMP)
      {
        temperature = DHT12_MIN_TEMP;
      }

      // compose 1 digital sign, 2 digital integer, 1 digital dot, 1 digital decimal, 1 digital end mark
      // total 6 digital
      if(temperature > 0)
        *temp_str++ = ' ';
      else
	*temp_str++ = '-';
      //number to ascii
      *temp_str++ = (char)(temperature / 100 + 48);
      *temp_str++ = (char)(temperature % 100 / 10 + 48);
      *temp_str++ = '.';
      *temp_str++ = (char)(temperature % 10 + 48);
      *temp_str = '\0';

      if(humidity > 0)
        *humi_str++ = ' ';
      else
	*temp_str++ = '-';
      //number to ascii
      *humi_str++ = (char)(humidity / 100 + 48);
      *humi_str++ = (char)(humidity % 100 / 10 + 48);
      *humi_str++ = '.';
      *humi_str++ = (char)(humidity % 10 + 48);
      *humi_str = '\0';


      temperature = temperature / 10;
      humidity = humidity / 10;
    }
    else 
    {
      PRINTF("read out 0~5 bytes: %d, %d, %d ,%d, %d \r\n", dht12_data[0], dht12_data[1], dht12_data[2], dht12_data[3], dht12_data[4]);
      result = kStatus_Fail;
    }

  }

  return result;

}
