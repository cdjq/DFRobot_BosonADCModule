/*!
 * @file  DFRobot_BosonAdcModule.h
 * @brief  Define infrastructure of DFRobot_BosonAdcModule class
 * @details  获取模块基本信息, 获取模拟量A1和A2
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-10-12
 * @url  https://github.com/DFRobot/DFRobot_BosonAdcModule
 */
#ifndef __DFROBOT_BOSON_ADC_MODULE_H__
#define __DFROBOT_BOSON_ADC_MODULE_H__

#include <Arduino.h>
#include <Wire.h>

#define ENABLE_DBG   //!< 打开这个宏, 可以看到程序的详细运行过程
#ifdef ENABLE_DBG
  #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
  #define DBG(...)
#endif

#define BOSON_ADC_MODULE_DEFAULT_IIC_ADDR   uint8_t(0x06)      ///< 默认的IIC通信地址
#define BOSON_ADC_MODULE_PID                uint16_t(0xC03F)   ///< 模块的PID (BOS0063)(最高两位作为种类判断00:SEN、01:DFR、10:TEL、11:BOS, 后面14位作为num)

/* BOSON_ADC_MODULE register address */
#define BOSON_ADC_MODULE_PID_MSB_REG                 uint8_t(0x00)   ///< 模块的PID存储寄存器, 默认值0xC03F (最高两位作为种类判断00：SEN、01：DFR、10：TEL、11:BOS, 后面14位作为num)
#define BOSON_ADC_MODULE_PID_LSB_REG                 uint8_t(0x01)
#define BOSON_ADC_MODULE_VID_MSB_REG                 uint8_t(0x02)   ///< 模块的VID存储寄存器, 默认值0x3343（代表厂商为DFRobot）
#define BOSON_ADC_MODULE_VID_LSB_REG                 uint8_t(0x03)
#define BOSON_ADC_MODULE_VERSION_MSB_REG             uint8_t(0x04)   ///< 固件版本号存储寄存器：0x0100代表V0.1.0.0
#define BOSON_ADC_MODULE_VERSION_LSB_REG             uint8_t(0x05)
#define BOSON_ADC_MODULE_ADDR_REG                    uint8_t(0x07)   ///< 模块的通信地址存储寄存器, 默认值0x06
#define BOSON_ADC_MODULE_ADC1_MSB_REG                uint8_t(0x08)   ///< 模拟信号A1
#define BOSON_ADC_MODULE_ADC1_LSB_REG                uint8_t(0x09)
#define BOSON_ADC_MODULE_ADC2_MSB_REG                uint8_t(0x0A)   ///< 模拟信号A2
#define BOSON_ADC_MODULE_ADC2_LSB_REG                uint8_t(0x0B)


class DFRobot_BosonAdcModule
{
public:
  #define NO_ERR             0     ///< No error
  #define ERR_DATA_BUS      (-1)   ///< 数据总线错误
  #define ERR_IC_VERSION    (-2)   ///< 芯片版本不匹配

  /**
   * @struct sBasicInfo_t
   * @brief  传感器的基本设备信息存储结构体
   */
  typedef struct
  {
    uint16_t PID;   /**< 模块的PID, 默认值0xC03F (最高两位作为种类判断00: SEN、01: DFR、10: TEL、11:BOS, 后面14位作为num)(BOS0063) */
    uint16_t VID;   /**< 模块的VID, 默认值0x3343(代表厂商为DFRobot) */
    uint16_t version;   /**< 固件版本号: 0x0100代表V0.1.0.0 */
    uint8_t iicAddr;   /**< 模块的通信地址, 默认值0x06 */
  }sBasicInfo_t;

public:
  /**
   * @fn DFRobot_BosonAdcModule
   * @brief 构造函数
   * @param iicAddr BosonAdcModule IIC communication address
   * @param pWire Wire.h里定义了Wire对象, 因此使用&Wire就能够指向并使用Wire中的方法
   * @return None
   */
  DFRobot_BosonAdcModule(uint8_t iicAddr=BOSON_ADC_MODULE_DEFAULT_IIC_ADDR, TwoWire *pWire = &Wire);

  /**
   * @fn begin
   * @brief 初始化函数
   * @return int类型, 表示返回初始化的状态
   * @retval 0 NO_ERROR
   * @retval -1 ERR_DATA_BUS
   * @retval -2 ERR_IC_VERSION
   */
  int begin(void);

  /**
   * @fn refreshBasicInfo
   * @brief 重新从传感器获取其基本信息, 并缓存到存储信息的结构体basicInfo里面
   * @n     basicInfo结构体的成员: PID, VID, version, iicAddr
   * @return None
   */
  void refreshBasicInfo(void);

  /**
   * @fn getAnalogSignalA1
   * @brief 获取模拟信号A1
   * @return 返回值范围为： 0-1023
   */
  uint16_t getAnalogSignalA1(void);

  /**
   * @fn getAnalogSignalA2
   * @brief 获取模拟信号A2
   * @return 返回值范围为： 0-1023
   */
  uint16_t getAnalogSignalA2(void);

protected:
/***************** 寄存器读写接口 ******************************/

  /**
   * @fn writeReg
   * @brief 通过IIC总线写入寄存器值
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return None
   */
  void writeReg(uint8_t reg, const void* pBuf, size_t size);

  /**
   * @fn readReg
   * @brief 通过IIC总线读取寄存器值
   * @param reg  寄存器地址 8bits
   * @param pBuf 要读取数据的存放缓存
   * @param size 要读取数据的长度
   * @return 返回读取的长度, 返回0表示读取失败
   */
  size_t readReg(uint8_t reg, void* pBuf, size_t size);

public:
  // 存放传感器基本信息的结构体
  sBasicInfo_t basicInfo;

private:
  TwoWire *_pWire;   // IIC通信方式的指针
  uint8_t _deviceAddr;   // IIC通信的设备地址
};

#endif
