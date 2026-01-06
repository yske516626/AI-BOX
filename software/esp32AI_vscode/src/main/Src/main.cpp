
// #include "guichu.h"
// #include "listening.h"


#include "../Inc/UserProcessing.h"
//  优先事项！！！一定要做，不做的话麦克风会因为引脚冲突无法工作
//  在vscode中打开文件夹，等待依赖库下载完成后,
//  找到.pio\libdeps\esp32-s3-devkitm-1\TFT_eSPI路径下的User_Setup.h文件，删除它，然后将根目录下的User_Setup.h文件剪切粘贴过去



String llm_name = "讯飞星火";

String llm_model = "4.0Ultra"; //使用的llm模型类型

String llm_apiKey = ""; //llm模型http服务器接口认证密钥

String llm_url = "https://spark-api-open.xf-yun.com/v1/chat/completions";  //llm模型http服务器接口地址

// 讯飞websocket调用stt和大模型服务的参数
String APPID = "";                             // App ID,必填
String APISecret = ""; // API Secret，必填
String APIKey = "";    // API Key，必填
String domain1 = "4.0Ultra";    // 根据需要更改
String websockets_server = "ws://spark-api.xf-yun.com/v4.0/chat";   //llm模型websocket服务器接口地址
String websockets_server1 = "ws://iat-api.xfyun.cn/v2/iat";			//stt语音转文字websocket服务器接口地址
// 讯飞stt语种设置
String language = "zh_cn";     //zh_cn：中文（支持简单的英文识别）en_us：English

//角色设定1
String roleSettings = "你的名字叫小灵，你性格温柔，非常体贴，对于我提出的问题你的回复要稍微简短一些";




// 创建WebSocket客户端对象
using namespace websockets; // 使用WebSocket命名空间
WebsocketsClient webSocketClient;   //与llm通信
WebsocketsClient webSocketClient1;  //与stt通信
// 创建音频对象
Audio1 audio1(PIN_I2S_BCLK, PIN_I2S_LRC, PIN_I2S_DIN);
Audio2 audio2(false, 3, I2S_NUM_1);

bool ledstatus = true;          // 控制led闪烁
bool startPlay = false;
unsigned long urlTime = 0;
int noise = 50;                 // 噪声门限值
int volume = 50;               // 初始音量大小（最小0，最大100）
//音乐播放
int mainStatus = 0;
int conStatus = 0;
int musicnum = 0;   //音乐位置下标
int musicplay = 0;  // 是否进入连续播放音乐状态
int cursorY = 0;

// 存储历史对话信息
std::vector<String> text;

// 定义字符串变量，用于存储鉴权参数
String url = ""; //存储llm链接时的url信息
String url1 = ""; //存储STT连接时的url信息 -- 语音转文字
String Date = "";

String askquestion = "";        //存储stt语音转文字信息，即用户的提问信息
String Answer = "";             //存储llm回答，用于语音合成（较短的回答）
std::vector<String> subAnswers; //存储llm回答，用于语音合成（较长的回答，分段存储）
int subindex = 0;               //subAnswers的下标，用于voicePlay()
String text_temp = "";          //存储超出当前屏幕的文字，在下一屏幕显示
int loopcount = 0;      // 对话次数计数器
int flag = 0;           // 用来确保subAnswer1一定是大模型回答最开始的内容
int conflag = 0;        // 用于连续对话
int await_flag = 1;     //待机标识
int start_con = 0;      //标识是否开启了一轮对话
int awake_flag = 0;     // 标识是否处于唤醒状态
int i = 0;              // 用于显示表情
unsigned long startTime = 0;
unsigned long endTime = 0;
int shuaxin = 0;
int chouxiang = 0;
int recording = 0;      // 确保在录音、语音转文字、处理文字、大模型给出回复之前的整个过程中不会触发ASRPRO指令，否则可能会导致对话被指令动作打断

int hint = 0;   // 提示音

CRGB leds[NUM_LEDS];
// 函数声明
using namespace websockets; // 使用WebSocket命名空间

//天文
#define RX2 19
#define TX2 20
const int BUFFER_SIZE = 5; // 每个命令包的大小
char buffer[BUFFER_SIZE];  // 接收缓冲区
int globalIndex = 0;             // 当前接收到的数据在缓冲区中的位置

uint8_t AI_Page = 0; //标识当前是否为ai对话界面

uint8_t Contorl = 1;  //标识是不是控制指令

int wifiConnect()
{
	// 断开当前WiFi连接
	WiFi.disconnect(true);

	preferences.begin("wifi_store");
	int numNetworks = preferences.getInt("numNetworks", 0);
	if (numNetworks == 0)
	{

		Serial.println("无任何wifi存储信息！");
		Serial.println("请连接热点ESP32-Setup密码为12345678，然后在浏览器中打开http://192.168.4.1添加新的网络！");
		//串口通信 --- 待实现


		preferences.end();
		return 0;
	}

	// 获取存储的 WiFi 配置
	for (int i = 0; i < numNetworks; ++i)
	{
		String ssid = preferences.getString(("ssid" + String(i)).c_str(), "");
		String password = preferences.getString(("password" + String(i)).c_str(), "");

		// 尝试连接到存储的 WiFi 网络
		if (ssid.length() > 0 && password.length() > 0)
		{
			Serial.print("Connecting to ");
			Serial.println(ssid);
			Serial.print("password:");
			Serial.println(password);
			// 在屏幕上显示每个网络的连接情况
			//串口通信 --- 待实现

			uint8_t count = 0;
			WiFi.begin(ssid.c_str(), password.c_str());
			// 等待WiFi连接成功
			while (WiFi.status() != WL_CONNECTED)
			{
				// 闪烁板载LED以指示连接状态
				digitalWrite(led, ledstatus);
				ledstatus = !ledstatus;
				count++;

				// 如果尝试连接超过30次，则认为连接失败
				if (count >= 30)
				{
					Serial.printf("\r\n-- wifi connect fail! --\r\n");
					// 在屏幕上显示连接失败信息
					//串口通信 --- 待实现
					break;
				}

				vTaskDelay(100);
			}

			if (WiFi.status() == WL_CONNECTED)
			{
				// 向串口输出连接成功信息和IP地址
				Serial.printf("\r\n-- wifi connect success! --\r\n");
				Serial.print("IP address: ");
				Serial.println(WiFi.localIP());

				// 输出当前空闲堆内存大小
				Serial.println("Free Heap: " + String(ESP.getFreeHeap()));
				// 在屏幕上显示连接成功信息
				//串口通信 --- 待实现
				// Serial.print("Connected!");

				preferences.end();
				return 1;
			}
		}
	}
	// // 清空屏幕
	// tft.fillScreen(TFT_WHITE);
	// // 在屏幕上输出提示信息
	// u8g2.setCursor(0, 11);
	// u8g2.print("网络连接失败！请检查");
	// u8g2.setCursor(0, u8g2.getCursorY() + 12);
	// u8g2.print("网络设备，确认可用后");
	// u8g2.setCursor(0, u8g2.getCursorY() + 12);
	// u8g2.print("重启设备以建立连接！");
	// displayWrappedText("或者连接热点ESP32-Setup密码为12345678，然后在浏览器中打开http://192.168.4.1添加新的网络！", 0, u8g2.getCursorY() + 12, width);

	//串口通信 --- 待实现

	preferences.end();
	return 0;
}

//获取当前时间
void getTimeFromServer()
{
	String timeurl = "https://www.baidu.com";   // 定义用于获取时间的URL
	HTTPClient http;                // 创建HTTPClient对象
	http.begin(timeurl);            // 初始化HTTP连接
	const char* headerKeys[] = { "Date" };        // 定义需要收集的HTTP头字段
	http.collectHeaders(headerKeys, sizeof(headerKeys) / sizeof(headerKeys[0]));    // 设置要收集的HTTP头字段
	int httpCode = http.GET();      // 发送HTTP GET请求
	Date = http.header("Date");     // 从HTTP响应头中获取Date字段
	Serial.println(Date);           // 输出获取到的Date字段到串口
	http.end();                     // 结束HTTP连接

	// delay(50); // 根据实际情况可以添加延时，以便避免频繁请求
}



void StartConversation()
{
	if (isWebServerStarted) {
		server.end();
		Serial.println("WebServer stopped");
		isWebServerStarted = false;
	}

	if (isSoftAPStarted) {
		WiFi.softAPdisconnect(true);
		Serial.println("Access Point disconnected");
		isSoftAPStarted = false;
	}
	askquestion = "";
	Serial.printf("Start recognition\r\n\r\n");
	// 如果距离上次时间同步超过4分钟
	if (urlTime + 240000 < millis()) // 超过4分钟，重新做一次鉴权
	{
		// 更新时间戳
		urlTime = millis();
		// 从服务器获取当前时间
		getTimeFromServer();
		// 更新WebSocket连接的URL
		url = getUrl(websockets_server, "spark-api.xf-yun.com", websockets_server.substring(25), Date);
		url1 = getUrl(websockets_server1, "iat-api.xfyun.cn", "/v2/iat", Date);
	}
	// 连接到WebSocket服务器1讯飞stt
	ConnServer1();
}



void processCommand(uint8_t command)
{
	switch (command) {
	case 0x00:
		shuaxin = 0;
		awake_flag = 1;      //离线唤醒模型，唤醒成功
		Contorl = 1; //默认为控制指令
		Answer = "我在的。";
		AI_Page = 1; //当前为对话界面
		response();     //屏幕显示Answer以及语音播放
		break;
	case 0x01:
		if (AI_Page == 1)
		{
			Contorl = 1;  //标识为控制指令
			Answer = "已为你打开灯光";
			response();  //屏幕显示Answer以及语音播放
		}
			   
		break;
	case 0x02:
		if (AI_Page == 1)
		{
			Contorl = 1;  //标识为控制指令
			Answer = "已为你关闭灯光";
			response();     //屏幕显示Answer以及语音播放
		}	
		break;
	case 0x03:  //说：对话，启动连续对话模式
		if (AI_Page == 1) {
			shuaxin = 0;
			awake_flag = 1;      //离线唤醒模型，唤醒成功
			conflag = 1; //启动连续对话
			Contorl = 0;  //标识非控制指令
			Answer = "有什么想和我说的吗？";
			response();     //屏幕显示Answer以及语音播放
		}
		
		break;
	case 0x04:	  //退下
		if (AI_Page == 1) {
			await_flag = 1;     // 进入待机状态
			start_con = 0;      // 标识一次（包含多轮）对话结束

			awake_flag = 0;      // 已唤醒，退出唤醒状态，进入待机状态
			shuaxin = 1;
			musicplay = 0;
			conflag = 0;  //关闭连续对话
			Contorl = 1;	//启动默认为连续控制指令
			AI_Page = 0; //标识为当前非AI对话界面
			Answer = "我先退下了，有事再找我";
			response();     //语音播放
			endTime = millis();
		}
		break;
	default:
		//Contorl = 0;
		Serial.println("Unknown command received.");
		break;
	}
}

void setup()
{
	// 初始化串口通信，波特率为115200
	Serial.begin(115200);

	// 初始化 唤醒引脚
	// pinMode(awake, INPUT);
	Serial2.begin(115200, SERIAL_8N1, RX2, TX2);
	// 配置引脚模式
	pinMode(key, INPUT_PULLUP);     // 配置按键引脚为上拉输入模式，用于boot按键检测

	// 将led设置为输出模式
	pinMode(led, OUTPUT);
	// 将light设置为输出模式
	pinMode(light, OUTPUT);
	// 将light初始化为低电平
	digitalWrite(light, LOW);

	Serial.println("引脚初始化完成！");



	// 初始化音频模块audio1
	audio1.init();
	// 设置音频输出引脚和音量
	audio2.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
	audio2.setVolume(volume);

	// 初始化Preferences
	preferences.begin("wifi_store");
	preferences.begin("music_store");
	preferences.begin("llm_store");

	Serial.println("正在连接网络······");
	//串口输出 --- 待实现

	int result = wifiConnect();

	if (result == 1)
	{
		// Serial.println("音频模块初始化完成！网络连接成功！开始加载大模型参数！");
		//串口输出 --- 待实现
		// loadModel(); 

		// 从百度服务器获取当前时间
		getTimeFromServer();
		// 使用当前时间生成WebSocket连接的URL
		url = getUrl(websockets_server, "spark-api.xf-yun.com", websockets_server.substring(25), Date);
		url1 = getUrl(websockets_server1, "iat-api.xfyun.cn", "/v2/iat", Date);
		// 记录当前时间，用于后续时间戳比较
		urlTime = millis();

		// 清空屏幕，在屏幕上输出提示信息
		// tft.fillScreen(TFT_WHITE);
		// u8g2.setCursor(0, 11);
		// u8g2.print("网络连接成功！");
		Serial.println("请进行语音唤醒或按boot键开始对话！");

		//串口输出 --- 待实现

		audio2.connecttospeech("系统初始化完毕，请使用唤醒词唤醒我。", "zh");
	}
	else
	{
		awake_flag = 1;
		openWeb();
	}

	// 清空串口数据
	while (Serial2.available())
	{
		Serial2.read();
	}
	// 初始化SPIFFS文件系统
	if (!SPIFFS.begin(true))
	{
		Serial.println("初始化SPIFFS时发生错误");
		return;
	}

}

void loop()
{
	// 轮询处理WebSocket客户端消息
	webSocketClient.poll();
	webSocketClient1.poll();

	// 如果有多段语音需要播放
	if (startPlay)
		voicePlay();    // 调用voicePlay函数播放后续的语音

	// 音频处理循环
	audio2.loop();

	// 如果音频正在播放
	if (audio2.isplaying == 1)
		digitalWrite(led, HIGH);    // 点亮板载LED指示灯
	else
		digitalWrite(led, LOW);     // 熄灭板载LED指示灯


	// 唤醒词识别，并触发唤醒语音
	// if (digitalRead(awake) == 0 && awake_flag == 0)
	// {
	// 	shuaxin = 0;
	// 	awake_flag = 1;      //离线唤醒模型，唤醒成功
	// 	Answer = "我在的。";
	// 	response();     //屏幕显示Answer以及语音播放
	// 	conflag = 1; //启动连续对话
	// }

	 // 接受并处理ASRPRO识别到的指令
	while (Serial2.available() && recording == 0)
	{
		char incomingByte = Serial2.read();
		// 将接收到的字节添加到缓冲区
		buffer[globalIndex] = incomingByte;
		globalIndex++;
		Serial.print((int)incomingByte, HEX);
		// 如果接收到完整的命令包
		if (globalIndex == BUFFER_SIZE)
		{
			if (buffer[0] == 0xAA && buffer[1] == 0x55 &&
				buffer[3] == 0x55 && buffer[4] == 0xAA)
			{
				uint8_t command = buffer[2]; // 提取命令字节
				processCommand(command);
			}
			// 清空缓冲区
			memset(buffer, 0, BUFFER_SIZE);
			globalIndex = 0;
			while (Serial2.available())
			{
				Serial2.read();
			}
		}
	}


	/******** 旧版本 ********/
	// // 唤醒词识别 -- 比较耗费stt资源
	// if (audio2.isplaying == 0 && awake_flag == 0 && await_flag == 1)
	// {
	// 	awake_flag = 1;     // 在线唤醒模式，唤醒成功
	// 	StartConversation();
	// }
	/******** 旧版本 ********/

	//通过串口进行对话
	if (Serial.available())
	{
		String r = Serial.readString();
		r.trim();
		if (r.length() >= 2) // 一个中文字符的长度为3，一个英文字符的长度为1
		{
			if (r.startsWith("音乐http"))
			{
				r.replace("音乐", "");
				audio2.connecttohost(r.c_str());    // 播放音乐
			}
			// else if (r.startsWith("图片http"))
			// {
			//     r.replace("图片", "");
			//     draw_image(r.c_str());   // 绘制图片测试
			// }
			else
			{
				askquestion = r;
				processAskquestion(); // 处理用户的输入askquestion
				hint = 0;       // 关闭提示音
				conflag = 0;    // 关闭连续对话
			}
		}
	}

	// 检测boot按键是否按下
	if (digitalRead(key) == 0)
	{
		shuaxin = 0;
		conflag = 0;
		awake_flag = 1;      // boot唤醒模式，唤醒成功
		loopcount++;
		Serial.print("loopcount：");
		Serial.println(loopcount);
		StartConversation();
	}
	// 连续对话
	if (audio2.isplaying == 0 && Answer == "" && subindex == subAnswers.size() && musicplay == 0 && conflag == 1 && hint == 0 && Contorl == 0)
	{
		loopcount++;
		Serial.print("loopcount：");
		Serial.println(loopcount);
		StartConversation();
	}
}

