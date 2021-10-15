/*!
 * @file        getData.ino
 * @brief       这个demo演示了如何获取模块基本信息, 获取模拟量A1和A2
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [qsjhyy](yihuan.huang@dfrobot.com)
 * @version     V1.0
 * @date        2021-10-12
 * @url         https://github.com/DFRobot/DFRobot_BosonAdcModule
 */
#include <DFRobot_BosonAdcModule.h>

/**
 * 实例化一个对象，来驱动我们的传感器;
 * IIC地址根据模块当前选择的设置即可，默认为0x06
 */
DFRobot_BosonAdcModule sensor(/*iicAddr = */0x06, /*iicBus = */&Wire);

void setup()
{
  Serial.begin(115200);

  // 初始化传感器
  while( NO_ERR != sensor.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * 重新从传感器获取其基本信息, 并缓存到存储信息的结构体basicInfo里面
   * basicInfo结构体的成员: PID, VID, version, iicAddr
   */
  sensor.refreshBasicInfo();

  /* 模块的PID存储寄存器, 默认值0xC03F (BOS0063)(最高两位作为种类判断00：SEN、01：DFR、10：TEL、11:BOS, 后面14位作为num) */
  Serial.print("PID: 0x");
  Serial.println(sensor.basicInfo.PID, HEX);

  /* 模块的VID, 默认值0x3343(代表厂商为DFRobot) */
  Serial.print("VID: 0x");
  Serial.println(sensor.basicInfo.VID, HEX);

  /* 固件版本号: 0x0100代表V0.1.0.0 */
  Serial.print("versions: 0x0");
  Serial.println(sensor.basicInfo.version, HEX);

  /* 模块的通信地址, 默认值0x06 */
  Serial.print("communication address:  0x0");
  Serial.println(sensor.basicInfo.iicAddr, HEX);

  Serial.println();
  delay(1000);
}

void loop()
{
  /**
   * 获取模拟信号A1
   * 返回值范围为： 0-1023
   */
  uint16_t analogSignalA1 = sensor.getAnalogSignalA1();
  Serial.print("Module current analog signal A1: ");
  Serial.println(analogSignalA1);

  /**
   * 获取模拟信号A2
   * 返回值范围为： 0-1023
   */
  uint16_t analogSignalA2 = sensor.getAnalogSignalA2();
  Serial.print("Module current analog signal A2: ");
  Serial.println(analogSignalA2);

  Serial.println();
  delay(1000);
}
