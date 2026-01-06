#ifndef _MAIN_H
#define _MAIN_H
#include "../../Web/Web_Scr_set.h"


#define led 8       //板载led引脚
#define light 38     // 灯光引脚
#define max_context_length 3200

#define NUM_LEDS 1
#define DATA_PIN 48 // 灯光引脚
extern CRGB leds[NUM_LEDS];


// 定义音频放大模块的I2S引脚定义
#define I2S_DOUT 5 // DIN引脚
#define I2S_BCLK 6 // BCLK引脚
#define I2S_LRC 7  // LRC引脚
// 定义麦克风引脚
#define PIN_I2S_BCLK 2  // 时钟线，对应INMP441的SCK
#define PIN_I2S_LRC  1  // 声道选择线，对应INMP441的WS，由主机发送给从机，WS低电平时，从机发送左声道数据，高电平时发送右声道数据
#define PIN_I2S_DIN 42  // 数据线，对应INMP441的SD

#define key 0       //boot按键引脚

// stm32
#define awake 3     // 唤醒引脚


extern String llm_name;

extern String llm_model; 
extern String llm_apiKey;
extern String llm_url;  

extern String APPID;                             
extern String APISecret;
extern String APIKey;   
extern String domain1;    
extern String websockets_server;  
extern String websockets_server1;

extern String language;     
extern String roleSettings;  

// 创建WebSocket客户端对象
using namespace websockets; 
extern WebsocketsClient webSocketClient;   
extern WebsocketsClient webSocketClient1; 
// 创建音频对象
extern Audio1 audio1;
extern Audio2 audio2;

extern bool ledstatus;         
extern bool startPlay;
extern unsigned long urlTime;
extern int noise;                 
extern int volume;               
//音乐播放
extern int mainStatus;
extern int conStatus;
extern int musicnum;   
extern int musicplay;  
extern int cursorY;

// 存储历史对话信息
extern std::vector<String> text;

// 定义字符串变量，用于存储鉴权参数
extern String url; 
extern String url1; 
extern String Date;

extern String askquestion;       
extern String Answer;            
extern std::vector<String> subAnswers; 
extern int subindex;              
extern String text_temp;         
extern int loopcount;      
extern int flag;           
extern int conflag;       
extern int await_flag;     
extern int start_con;     
extern int awake_flag;    
extern int i;             
extern unsigned long startTime;
extern unsigned long endTime;
extern int shuaxin;
extern int chouxiang;
extern int recording;     

extern int hint; 



#endif