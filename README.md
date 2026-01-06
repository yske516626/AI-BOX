# 前言

一个基于freertos和lvgl的ai智能盒

- 板子：stm32F411ret6、esp32-s3
- hal库
- 模块：具体使用到的模块在：./software/Watch_Lvgl_Freertos/BSP/README.md
- 工具：vscode（platfrom io插件、esp-idf、eide）
- 环境：esp-idf v5.3.3

功能：

- 心率血氧检测
- 步数检测
- 翻转唤醒
- 指南针
- 海拔检测
- 气压检测
- 小游戏（2048）
- 计算器
- ai对话功能
- 语音控制硬件
- 温湿度检测
- nfc（待实现）
- 实现家居控制（待实现）

"盒子"扩展出一个接口，该接口可以接上智能家居，进行语音控制，实现一个“携带式”的智能助手。

“户外+家居”双模式：

- 家居：回家后接上接口遍可以作为智能家居控制中心（在线模式），使用开关灯模拟，感兴趣的可以去实现，使用串口接收数据进行判断，实现相应操作

- 户外：温度、湿度、海拔等传感器可提供实时环境数据，对应露营、探险等
- 连上热点或者wifi，可以实现ai对话功能



# 项目展示图



![展示1](./images/效果/展示1.png)

仅展示部分图

演示视频可以点击：https://www.yuque.com/yeke5166226/if0kvg/myx7p4s4vs1yrl15?singleDoc# 

# 接线

**stm32：**

- IIC：
  - PA6：SCL引脚
  - PA7：SDA引脚
  - 各自连到对应IIC模块的SCL、SDA引脚
- LED：
  - PA3

**ASRPRO：**

- 5V：连接到stm32的5V引脚
- GND：stm32的GND
- PB6：stm32的PC6（串口TX）
- PB5：stm32的PC7（串口RX）

**ESP32-S3：**

- 麦克风：
  - VDD  ---- 3.3V(esp32-s3)
  - GND ---- GND
  - SD    ----- GPIO42
  - WS   ----- GPIO1
  - SCK  ----- GPIO2
- MAX98357音频放大模块：
  - Vin：V5IN(esp32-s3)
  - GND：GND
  - LRC: GPIO7
  - BCLK: GPIO6
  - DIN: GPIO5
- esp32-s3串口的RX引脚（GPIO19）：连接到ASRPRO的PB5





# 文件说明

DevelopmentDocuments：相关硬件模块资料

images：存储md文档一些图片

LVGL：基础的lvgl库

software：实际的代码文件

- esp32AI_vscode：esp32-s3相关代码
- Lvgl：codelvgl仿真文件
  - codeblocks：可运行的项目仿真效果
  - codeblocks_template_noused：仿真源代码，可在这里进行设计你的界面
- Watch_Lvgl_Freertos：stm32的相关代码（关键代码，暂不公开，因做毕设会在此基础上拓展）
- esp32AI_vscode：esp32-s3相关代码
- esp32AI助手.hd：天问模块代码



关于一些其它配置，对应的文件夹下，有各自的md文档说明





# ai对话

唤醒：

- 你好小琳：仅启动控制指令

控制指令：

- 关灯
- 开灯

命令：

- 对话：启动ai对话模式 --- 后续可以开始进行对话，如“有什么有趣的事情和我分享吗”

- 退下：关闭对话模式





其余的一些说明可以到各文件夹下查看README文档。
