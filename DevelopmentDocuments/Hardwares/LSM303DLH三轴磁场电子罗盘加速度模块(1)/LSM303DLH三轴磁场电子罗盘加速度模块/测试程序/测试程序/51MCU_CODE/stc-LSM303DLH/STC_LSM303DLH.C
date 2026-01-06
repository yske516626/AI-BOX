//***************************************
// LSM303DLH IIC测试程序
// 使用单片机STC89C51 
// 晶振：11.0592M
// 显示：LCD1602
// 编译环境 Keil uVision2
// 参考宏晶网站24c04通信程序
// 时间：2011年3月1日
// QQ：531389319
//****************************************
#include  <REG51.H>	
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library	
#include  <INTRINS.H>
#define   uchar unsigned char
#define   uint unsigned int	
#define   DataPort P0    //LCD1602数据端口
sbit	  SCL=P1^0;      //IIC时钟引脚定义
sbit 	  SDA=P1^1;      //IIC数据引脚定义
sbit      LCM_RS=P2^0;   //LCD1602命令端口		
sbit      LCM_RW=P2^1;   //LCD1602命令端口		
sbit      LCM_EN=P2^2;   //LCD1602命令端口 

#define	LSM303A_SlaveAddress   0x30	  //定义器件在IIC总线中的从地址,(加速度)根据ALT  ADDRESS地址引脚不同修改 0x30（ADDRESS=0）                                 
#define	LSM303M_SlaveAddress   0x3C   //定义器件在IIC总线中的从地址,(磁场)根据ALT    ADDRESS地址引脚不同修改

							   
typedef unsigned char  BYTE;
typedef unsigned short WORD;

BYTE BUF[8];                         //接收数据缓存区      	
uchar ge,shi,bai,qian,wan;           //显示变量
int  dis_data;                       //变量

void delay(unsigned int k);
void InitLcd();                      //初始化lcd1602

void WriteDataLCM(uchar dataW);
void WriteCommandLCM(uchar CMD,uchar Attribc);
void DisplayOneChar(uchar X,uchar Y,uchar DData);
void conversion(uint temp_data);

void  Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data);   //单个写入数据
uchar Single_Read(uchar SlaveAddress,uchar REG_Address);                   //单个读取内部寄存器数据
void  Multiple_Read(uchar,uchar);                                          //连续的读取内部寄存器数据
//------------------------------------
void Delay5us();
void Delay5ms();
void LSM303_Start();
void LSM303_Stop();
void LSM303_SendACK(bit ack);
bit  LSM303_RecvACK();
void LSM303_SendByte(BYTE dat);
BYTE LSM303_RecvByte();
void LSM303_ReadPage();
void LSM303_WritePage();
//-----------------------------------

//*********************************************************
void conversion(uint temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	
}

/*******************************/
void delay(unsigned int k)	
{						
unsigned int i,j;				
for(i=0;i<k;i++)
{			
for(j=0;j<121;j++)			
{;}}						
}
/*******************************/
void WaitForEnable(void)	
{					
DataPort=0xff;		
LCM_RS=0;LCM_RW=1;_nop_();
LCM_EN=1;_nop_();_nop_();
while(DataPort&0x80);	
LCM_EN=0;				
}					
/*******************************/
void WriteCommandLCM(uchar CMD,uchar Attribc)
{					
if(Attribc)WaitForEnable();	
LCM_RS=0;LCM_RW=0;_nop_();
DataPort=CMD;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}					
/*******************************/
void WriteDataLCM(uchar dataW)
{					
WaitForEnable();		
LCM_RS=1;LCM_RW=0;_nop_();
DataPort=dataW;_nop_();	
LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}		
/***********************************/
void InitLcd()				
{			
WriteCommandLCM(0x38,1);	
WriteCommandLCM(0x08,1);	
WriteCommandLCM(0x01,1);	
WriteCommandLCM(0x06,1);	
WriteCommandLCM(0x0c,1);
}			
/***********************************/
void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
Y&=1;						
X&=15;						
if(Y)X|=0x40;					
X|=0x80;			
WriteCommandLCM(X,0);		
WriteDataLCM(DData);		
}						

/**************************************
延时5微秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
起始信号
**************************************/
void LSM303_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void LSM303_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void LSM303_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit LSM303_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void LSM303_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    LSM303_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE LSM303_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}

//单字节写入LSM303内部数据*******************************

void Single_Write(uchar SlaveAddress,uchar REG_Address,uchar REG_data)
{
    LSM303_Start();                  //起始信号
    LSM303_SendByte(SlaveAddress);   //发送设备地址+写信号
    LSM303_SendByte(REG_Address);    //内部寄存器地址
    LSM303_SendByte(REG_data);       //内部寄存器数据
    LSM303_Stop();                   //发送停止信号
}

//单字节读取LSM303内部数据********************************
uchar Single_Read(uchar SlaveAddress,uchar REG_Address)
{  uchar REG_data;
    LSM303_Start();                          //起始信号
    LSM303_SendByte(SlaveAddress);           //发送设备地址+写信号
    LSM303_SendByte(REG_Address);            //发送存储单元地址	
    LSM303_Start();                          //起始信号
    LSM303_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=LSM303_RecvByte();              //读出寄存器数据
	LSM303_SendACK(1);   
	LSM303_Stop();                           //停止信号
    return REG_data; 
}
//*********************************************************
//连续读出LSM303内部数据
//*********************************************************
void Multiple_read(uchar SlaveAddress,uchar ST_Address)
{   uchar i;
    LSM303_Start();                          //起始信号
    LSM303_SendByte(SlaveAddress);           //发送设备地址+写信号
    LSM303_SendByte(ST_Address);             //发送存储单元地址
    LSM303_Start();                          //起始信号
    LSM303_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                     //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = LSM303_RecvByte();          //BUF[0]存储
        if (i == 5)
        {
           LSM303_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          LSM303_SendACK(0);                //回应ACK
       }
   }
    LSM303_Stop();                          //停止信号
    Delay5ms();
}

//**************************************************************

//初始化LSM303A(加速度)，根据需要请参考pdf进行修改**************
void Init_LSM303A()
{
   Single_Write(LSM303A_SlaveAddress,0x20,0x27);   //测量范围,正负2g，16位模式
}

//初始化LSM303M(磁场)，根据需要请参考pdf进行修改****
void Init_LSM303M()
{
     Single_Write(LSM303M_SlaveAddress,0x02,0x00);  //
}
//**************************************************************
//加速度显示x轴
void display_x()
{   float temp; 
    BUF[0]=Single_Read(LSM303A_SlaveAddress,0x28);//OUT_X_L_A
	BUF[1]=Single_Read(LSM303A_SlaveAddress,0x29);//OUT_X_H_A

    dis_data=(BUF[1]<<8)+BUF[0];  //合成数据   
	
	if(dis_data<0){
	dis_data=-dis_data;
    DisplayOneChar(2,0,'-');      //显示正负符号位
	}
	else DisplayOneChar(2,0,' '); //显示空格
   
    temp=(float)dis_data/16.383;  //
    conversion(temp);          //转换出显示需要的数据
	DisplayOneChar(0,0,'X');   //第0行，第0列 显示X
    DisplayOneChar(1,0,':'); 
    DisplayOneChar(3,0,qian); 
	DisplayOneChar(4,0,'.'); 
    DisplayOneChar(5,0,bai); 
	DisplayOneChar(6,0,'g'); 
}

//***************************************************************
//加速度显示y轴
void display_y()
{    float temp; 
     BUF[2]=Single_Read(LSM303A_SlaveAddress,0x2a);//OUT_Y_L_A
	 BUF[3]=Single_Read(LSM303A_SlaveAddress,0x2b);//OUT_Y_H_A


    dis_data=(BUF[3]<<8)+BUF[2];  //合成数据   
	if(dis_data<0){
	dis_data=-dis_data;
    DisplayOneChar(2,1,'-');      //显示正负符号位
	}
	else DisplayOneChar(2,1,' '); //显示空格

    temp=(float)dis_data/16.383;  //计算数据和显示
    conversion(temp);          //转换出显示需要的数据
	DisplayOneChar(0,1,'Y');   //第1行，第0列 显示y
    DisplayOneChar(1,1,':'); 
    DisplayOneChar(3,1,qian); 
	DisplayOneChar(4,1,'.'); 
    DisplayOneChar(5,1,bai); 
  //  DisplayOneChar(6,1,shi);  
	DisplayOneChar(6,1,'g');  
}

//**************************************************************
//加速度显示z轴
void display_z()
{    float temp;
     BUF[4]=Single_Read(LSM303A_SlaveAddress,0x2c);//OUT_Z_L_A
	 BUF[5]=Single_Read(LSM303A_SlaveAddress,0x2d);//OUT_Z_H_A

    dis_data=(BUF[5]<<8)+BUF[4];  //合成数据   
	if(dis_data<0){
	dis_data=-dis_data;
    DisplayOneChar(11,1,'-');     //显示负符号位
	}
	else DisplayOneChar(11,1,' ');//显示空格

    temp=(float)dis_data/16.383;  //计算数据和显示
    conversion(temp);             //转换出显示需要的数据
	DisplayOneChar(9,1,'Z');      //第0行，第10列 显示Z
    DisplayOneChar(10,1,':'); 
    DisplayOneChar(12,1,qian); 
	DisplayOneChar(13,1,'.'); 
    DisplayOneChar(14,1,bai); 
   // DisplayOneChar(14,1,shi); 
	DisplayOneChar(15,1,'g');  
}

void display_Angle(void)
   {  int x,y,z;
      double  angle;
 
    x=BUF[0] << 8 | BUF[1]; //Combine MSB and LSB of X Data output register
    y=BUF[2] << 8 | BUF[3]; //Combine MSB and LSB of Z Data output register
    z=BUF[4] << 8 | BUF[5]; //Combine MSB and LSB of Y Data output register

    angle= atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
    angle*=10;

    conversion(angle);       //计算数据和显示
	DisplayOneChar(9,0,'A'); 
    DisplayOneChar(10,0,':'); 
    DisplayOneChar(11,0,qian); 
    DisplayOneChar(12,0,bai); 
    DisplayOneChar(13,0,shi); 
    DisplayOneChar(14,0,'.'); 
	DisplayOneChar(15,0,ge); 
	}

//*********************************************************
//******主程序********
//*********************************************************
void main()
{ 
    delay(50);	                   //上电延时		
    InitLcd();                     //液晶初始化
    Init_LSM303A();                //初始化LSM303 加速度
    Init_LSM303M();                //初始化LSM303 磁场
  while(1)                         //循环
  { 
    delay(10);                     //延时 
    display_x();                   //---------加速度，显示X轴
    display_y();                   //---------加速度，显示Y轴
    display_z();                   //---------加速度，显示Z轴

    delay(10);                     //延时 
	Multiple_Read(LSM303M_SlaveAddress,0X03); //连续读出数据，存储在BUF中  
    display_Angle();               //---------磁场，显示角度
	delay(100); 
  }
} 