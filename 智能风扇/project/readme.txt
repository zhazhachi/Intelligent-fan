editor;池建明
email：chijianming@126.com
document:自动定位智能变频风扇
mcu：stm32f103C8T6


/***********硬件接线说明***********/
1、温度传感器ds18b20：红黑电源正负极(3.3~5.0V），黄色信号PB11;	
2、x轴舵机：红棕电源正负极（5V），黄色信号PA8
3、SRF05超声波传感器：电源DC5V TRIG=PB12 ECHO=PB13 
4、蓝牙模块：电源DC3.3~5.0V PA10接TX PA9接RX




/***********硬件与安卓APP通讯协议***********/

通信方式：蓝牙

数据包总长度：5byte

第一字节开头：0xAA 

第二字节消息类型定义：
0x00：温度信息
0x01：舵机x轴左转 第三字节为转角
0x02：舵机x轴右转 第三字节为转角
0x03：舵机y轴上转 第三字节为转角
0x04：舵机y轴下转 第三字节为转角
0x05：风扇模式选择 第三字节0x00手动  0x01自动
第三四字节数据内容

第五字节结尾：0x0D








