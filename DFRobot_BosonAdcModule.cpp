/*!
 * @file  DFRobot_BosonAdcModule.cpp
 * @brief  DFRobot_BosonAdcModule.cpp Initialize the IIC, 
 * @n      获取模块基本信息, 获取模拟量A1和A2
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-10-12
 * @url  https://github.com/DFRobot/DFRobot_BosonAdcModule
 */
#include "DFRobot_BosonAdcModule.h"

DFRobot_BosonAdcModule::DFRobot_BosonAdcModule(uint8_t iicAddr, TwoWire *pWire)
{
  _deviceAddr = iicAddr;
  _pWire = pWire;
}


int DFRobot_BosonAdcModule::begin(void)
{
  _pWire->begin();   // Wire.h (IIC)library function initialize wire library
  delay(50);

  uint8_t idBuf[2];
  if(0 == readReg(BOSON_ADC_MODULE_PID_MSB_REG, idBuf, sizeof(idBuf))){   // Judge whether the data bus is successful
    DBG("ERR_DATA_BUS");
    return ERR_DATA_BUS;
  }

  DBG("real sensor id="); DBG( (uint16_t)idBuf[0] << 8 | (uint16_t)idBuf[1], HEX );
  if( BOSON_ADC_MODULE_PID != ( (uint16_t)idBuf[0] << 8 | (uint16_t)idBuf[1] ) ){   // Judge whether the chip version matches
    DBG("ERR_IC_VERSION");
    return ERR_IC_VERSION;
  }

  delay(200);
  DBG("begin ok!");
  return NO_ERR;
}

void DFRobot_BosonAdcModule::refreshBasicInfo(void)
{
  uint8_t tempBuf[8] = {0};
  readReg(BOSON_ADC_MODULE_PID_MSB_REG, tempBuf, sizeof(tempBuf));
  basicInfo.PID = (uint16_t)tempBuf[0] << 8 | (uint16_t)tempBuf[1];   // PID
  basicInfo.VID = (uint16_t)tempBuf[2] << 8 | (uint16_t)tempBuf[3];   // VID
  basicInfo.version = (uint16_t)tempBuf[4] << 8 | (uint16_t)tempBuf[5];   // version
  basicInfo.iicAddr = (uint16_t)tempBuf[7];   // IIC addr
}

uint16_t DFRobot_BosonAdcModule::getAnalogSignalA1(void)
{
  uint8_t analogSignalValue[2] = {0};
  readReg(BOSON_ADC_MODULE_ADC1_MSB_REG, analogSignalValue, sizeof(analogSignalValue));

  return (uint16_t)analogSignalValue[0] << 8 | (uint16_t)analogSignalValue[1];
}

uint16_t DFRobot_BosonAdcModule::getAnalogSignalA2(void)
{
  uint8_t analogSignalValue[2] = {0};
  readReg(BOSON_ADC_MODULE_ADC2_MSB_REG, analogSignalValue, sizeof(analogSignalValue));

  return (uint16_t)analogSignalValue[0] << 8 | (uint16_t)analogSignalValue[1];
}

void DFRobot_BosonAdcModule::writeReg(uint8_t reg, const void* pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);

  for(size_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }

  _pWire->endTransmission();
}

size_t DFRobot_BosonAdcModule::readReg(uint8_t reg, void* pBuf, size_t size)
{
  size_t count = 0;
  if(NULL == pBuf){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t*)pBuf;

  _pWire->beginTransmission(_deviceAddr);
  _pWire -> write(reg);
  uint8_t ret = _pWire->endTransmission();
  if(0 != ret){
    // Used Wire.endTransmission() to end a slave transmission started by beginTransmission() and arranged by write().
    DBG("endTransmission ERROR!!");
    DBG(ret);
  }else{
    // Master device requests size bytes from slave device, which can be accepted by master device with read() or available()
    _pWire->requestFrom( _deviceAddr, (uint8_t)size );

    while (_pWire->available()){
      _pBuf[count++] = _pWire->read();   // Use read() to receive and put into buf
      // DBG(_pBuf[count-1], HEX);
    }
  }

  return count;
}
