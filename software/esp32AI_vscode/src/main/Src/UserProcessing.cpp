
#include "../Inc/UserProcessing.h"


/**********************************内部接口************************************************************ */

// 提取字符串中的数字
String extractNumber(const String& str) {
	String result;
	for (size_t i = 0; i < str.length(); i++) {
		if (isDigit(str[i])) {
			result += str[i];
		}
	}
	return result;
}

// 音量控制
void VolumeSet()
{
	String numberStr = extractNumber(askquestion);
	// 显示当前音量（声音）或者当前音量（声音）是多少
	if ((askquestion.indexOf("显示") > -1 && askquestion.indexOf("音") > -1) || (askquestion.indexOf("音") > -1 && askquestion.indexOf("多") > -1))
	{
		Serial.print("当前音量为: ");
		Serial.println(volume);
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);
		}
		else
		{

		}
		// tft.fillRect(66, 152, 62, 7, TFT_WHITE);    // 在屏幕上显示音量
	// tft.setCursor(66, 152);
	// tft.print("volume:");
	// tft.print(volume);

	//串口通信 -- 待实现



	}
	else if (numberStr.length() > 0)
	{
		volume = numberStr.toInt();
		audio2.setVolume(volume);
		Serial.print("音量已调到: ");
		Serial.println(volume);
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);
		}
		else
		{
			// tft.fillRect(66, 152, 62, 7, TFT_WHITE);    // 在屏幕上显示音量

		}
		// tft.setCursor(66, 152);
		// tft.print("volume:");
		// tft.print(volume);

		//串口通信 -- 待实现

	}
	else if (askquestion.indexOf("最") > -1 && (askquestion.indexOf("高") > -1 || askquestion.indexOf("大") > -1))
	{
		volume = 100;
		audio2.setVolume(volume);
		Serial.print("音量已调到: ");
		Serial.println(volume);
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);
		}
		else
		{
			// tft.fillRect(66, 152, 62, 7, TFT_WHITE);    // 在屏幕上显示音量

		}
		// tft.setCursor(66, 152);
		// tft.print("volume:");
		// tft.print(volume);

		//串口通信 -- 待实现

	}
	else if (askquestion.indexOf("高") > -1 || askquestion.indexOf("大") > -1)
	{
		volume += 10;
		if (volume > 100)
		{
			volume = 100;
		}
		audio2.setVolume(volume);
		Serial.print("音量已调到: ");
		Serial.println(volume);
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);
		}
		else
		{
			// tft.fillRect(66, 152, 62, 7, TFT_WHITE);    // 在屏幕上显示音量
		}
		// tft.setCursor(66, 152);
		// tft.print("volume:");
		// tft.print(volume);

		//串口通信 -- 待实现

	}
	else if (askquestion.indexOf("最") > -1 && (askquestion.indexOf("低") > -1 || askquestion.indexOf("小") > -1))
	{
		volume = 0;
		audio2.setVolume(volume);
		Serial.print("音量已调到: ");
		Serial.println(volume);
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);
		}
		else
		{
			// tft.fillRect(66, 152, 62, 7, TFT_WHITE);    // 在屏幕上显示音量

		}
		// tft.setCursor(66, 152);
		// tft.print("volume:");
		// tft.print(volume);

		//串口通信 -- 待实现

	}
	else if (askquestion.indexOf("低") > -1 || askquestion.indexOf("小") > -1)
	{
		volume -= 10;
		if (volume < 0)
		{
			volume = 0;
		}
		audio2.setVolume(volume);
		Serial.print("音量已调到: ");
		Serial.println(volume);
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);
		}
		else
		{
			// tft.fillRect(66, 152, 62, 7, TFT_WHITE);    // 在屏幕上显示音量

		}
		// tft.setCursor(66, 152);
		// tft.print("volume:");
		// tft.print(volume);

		//串口通信 -- 待实现
	}
}


//识别指令是否为控制指令
int Control(void)
{
	if (askquestion.indexOf("开") > -1 && askquestion.indexOf("灯") > -1)
	{
		
		Answer = "已执行打开灯光操作";
		response();     //语音播放
		Answer = "";
		conflag = 1;

		return 0;
	}
	else if (askquestion.indexOf("关") > -1 && askquestion.indexOf("灯") > -1)
	{
		
		Answer = "已执行关闭灯光操作";
		response();     //语音播放
		Answer = "";
		conflag = 1;

		return 0;
	}

	return 1;
}

/**********************************公共接口************************************************************ */
// 处理用户的输入askquestion
void processAskquestion()
{

	//识别到为控制功能类的指令，直接结束
	// if (Control())
	// 	return;

	// 如果是调声音大小还有开关灯的指令，就不打断当前的语音
	if ((askquestion.indexOf("声音") == -1 && askquestion.indexOf("音量") == -1) && !((askquestion.indexOf("开") > -1 || askquestion.indexOf("关") > -1) && askquestion.indexOf("灯") > -1) && !(askquestion.indexOf("暂停") > -1 || askquestion.indexOf("恢复") > -1))
	{
		webSocketClient.close();    //关闭llm服务器，打断上一次提问的回答生成
		audio2.isplaying = 0;
		startPlay = false;

		Answer = "";
		flag = 0;
		subindex = 0;
		subAnswers.clear();
		text_temp = "";

		chouxiang = 0;
		hint = 0;
	}

	/******** 旧版本 ********/
	// // 如果正处于待机状态并且使用唤醒词唤醒，则判断唤醒词是否正确
	// if (await_flag == 1 && awake_flag == 1) 
	// {

	// 	if (askquestion.indexOf("小林") > -1)
    //     {
    //         askquestion.replace("小林", "小琳");
	// 	}
	// 	if (askquestion.indexOf("小灵") > -1)
	// 	{
	// 		askquestion.replace("小灵", "小琳");
	// 	}
	// 	if (askquestion.indexOf("小玲") > -1)
	// 	{
	// 		askquestion.replace("小玲", "小琳");
	// 	}

	// 	Serial.printf("processAskquestion1");
	// 	Serial.printf(askquestion.c_str());
	// 	if ( askquestion.indexOf("小琳") > -1)
	// 	{
	// 		start_con = 1;      // 对话开始标识
	// 		await_flag = 0;     // 退出待机状态
	// 		Answer = "在呢。";
	// 		response();     //语音播放
	// 		conflag = 1;
	// 		Serial.printf("processAskquestion2");
	// 	}
	// 	else
	// 	{
	// 		awake_flag = 0;     // 未唤醒，保持待机状态
	// 		Serial.printf("processAskquestion3");
	// 	}
		
	// 	return;
	// }
	/******** 旧版本 ********/
	
	// 如果问句为空，播放错误提示语音
	if (askquestion == "")
	{
		Answer = "我没有听清，请再说一遍吧";
		response();     //语音播放
		conflag = 1;
	}
	// else if (askquestion.indexOf("退下") > -1)
	// {
	// 	await_flag = 1;     // 进入待机状态
	// 	start_con = 0;      // 标识一次（包含多轮）对话结束

	// 	awake_flag = 0;      // 已唤醒，退出唤醒状态，进入待机状态
	// 	shuaxin = 1;
	// 	musicplay = 0;
	// 	Answer = "我先退下了，有事再找我";
	// 	response();     //语音播放
	// 	endTime = millis();
	// }
	// else if (askquestion.indexOf("再见") > -1 || askquestion.indexOf("拜拜") > -1 || askquestion.indexOf("休眠") > -1)
	// {
	// 	await_flag = 1;     // 进入待机状态
	// 	start_con = 0;      // 标识一次（包含多轮）对话结束

	// 	awake_flag = 0;      // 已唤醒，退出唤醒状态，进入待机状态
	// 	shuaxin = 1;
	// 	musicplay = 0;
	// 	Answer = "好的，我随时都在，有事请随时呼唤我，再见！";
	// 	response();     //语音播放
	// 	endTime = millis();

	// 	//ASRPRO
	// 	String data = "ture";
    //     Serial2.write(data.c_str(), data.length());

	// }
	else if (askquestion.indexOf("断开") > -1 && (askquestion.indexOf("网络") > -1 || askquestion.indexOf("连接") > -1))
	{
		// 断开当前WiFi连接
		WiFi.disconnect(true);
		// tft.fillScreen(TFT_WHITE);
		// tft.setCursor(0, 0);
		// displayWrappedText("网络连接已断开，请重启设备以再次建立连接！", tft.getCursorX(), tft.getCursorY() + 11, width);
		Serial.printf("网络连接已断开，请重启设备以再次建立连接！");
		//串口通信 -- 待实现
		openWeb();
		//串口通信 -- 待实现
		// displayWrappedText("热点ESP32-Setup已开启，密码为12345678，可在浏览器中打开http://192.168.4.1进行网络、音乐及大模型信息配置！", 0, u8g2.getCursorY() + 12, width);
	}
	else if (askquestion.indexOf("开") && (askquestion.indexOf("配置") > -1 || askquestion.indexOf("热点") > -1))
	{
		// tft.fillScreen(TFT_WHITE);
		// tft.setCursor(0, 0);
		openWeb();
		Answer = "好的~已经为你打开热点ESP32-Setup啦，密码是12345678哦，连接后在浏览器输入192.168.4.1就可以进入配置界面了哦~";
		response();
	}
	else if (audio2.isplaying == 1 && askquestion.indexOf("暂停") > -1)
	{
		if (chouxiang != 0)
		{
			// tft=ushImage(0, 0, width, height, guichu[chouxiang - 1]);

		}
		else
			// tft.fillRect(0, 148, 50, 12, TFT_WHITE);     // 清空左下角的“请说话！”提示
			//Serial.println("");

			if (audio2.isRunning())
			{
				Serial.println("已经暂停！");
				audio2.pauseResume();
			}
			else
			{
				Serial.println("当前没有音频正在播放！");
			}
	}
	else if (audio2.isplaying == 1 && askquestion.indexOf("恢复") > -1)
	{
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);

		}
		else
			// tft.fillRect(0, 148, 50, 12, TFT_WHITE);     // 清空左下角的“请说话！”提示

			if (!audio2.isRunning())
			{
				Serial.println("已经恢复！");
				audio2.pauseResume();
			}
			else
			{
				Serial.println("当前没有音频正在暂停！");
			}
	}
	else if (askquestion.indexOf("声音") > -1 || askquestion.indexOf("音量") > -1)
	{
		if (chouxiang != 0)
		{
			// tft.pushImage(0, 0, width, height, guichu[chouxiang - 1]);
		}
		else
			// tft.fillRect(0, 148, 50, 12, TFT_WHITE);     // 清空左下角的“请说话！”提示
			VolumeSet();    //  调整音量
		conflag = 1;
	}
	
	else if (askquestion.indexOf("播放电台") > -1)
	{
		// tft.fillScreen(TFT_WHITE);
		// tft.setCursor(0, 0);
		// tft.print("user: ");
		// displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
		// cursorY = u8g2.getCursorY() + 1;
		// tft.setCursor(0, u8g2.getCursorY() + 2);

		audio2.connecttohost("http://lhttp.qingting.fm/live/4915/64k.mp3");
		// displayWrappedText("正在播放：蜻蜓电台", tft.getCursorX(), tft.getCursorY() + 11, width);

		//串口通信 -- 待实现
		Serial.println("正在播放：蜻蜓电台");

		startPlay = true;   // 设置播放开始标志
		conStatus = 1;
		conflag = 1;
	}
	else if (conStatus == 1)
	{
		// tft.fillScreen(TFT_WHITE);
		// tft.setCursor(0, 0);
		// tft.print("user: ");
		// displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
		// cursorY = u8g2.getCursorY() + 1;
		// tft.setCursor(0, u8g2.getCursorY() + 2);

		String musicName = "";
		String musicID = "";
		preferences.begin("music_store", true);
		int numMusic = preferences.getInt("numMusic", 0);
		if (musicplay == 1)
			musicplay = 1;

		if (askquestion.indexOf("不想") > -1 || askquestion.indexOf("暂停") > -1)
		{
			musicplay = 0;
			// tft.print("assistant: ");
			Answer = "好的，那主人还有其它吩咐吗？";
			audio2.connecttospeech(Answer.c_str(), "zh");

			//串口通信 -- 待实现
			Serial.println("好的，那主人还有其它吩咐吗？");
			Answer = "";
			conStatus = 0;
		}
		else if (askquestion.indexOf("上一") > -1)
		{
			musicnum = musicnum - 1 >= 0 ? musicnum - 1 : numMusic - 1;
			musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
			musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
			Serial.println("音乐名称: " + musicName);
			Serial.println("音乐ID: " + musicID);

			String audioStreamURL = "https://music.163.com/song/media/outer/url?id=" + musicID + ".mp3";
			Serial.println(audioStreamURL.c_str());
			audio2.connecttohost(audioStreamURL.c_str());

			if (musicplay == 0)
				askquestion = "正在播放音乐：" + musicName;
			else
				askquestion = "正在顺序播放所有音乐，当前正在播放：" + musicName;
			Serial.println(askquestion);
			//displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
			//串口通信 -- 待实现
			startPlay = true;   // 设置播放开始标志
			if (musicplay == 0)
			{
				flag = 1;
				Answer = "音乐播放完了，主人还想听什么音乐吗？喵~";
			}
		}
		else if (askquestion.indexOf("下一") > -1)
		{
			musicnum = musicnum + 1 < numMusic ? musicnum + 1 : 0;
			musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
			musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
			Serial.println("音乐名称: " + musicName);
			Serial.println("音乐ID: " + musicID);

			String audioStreamURL = "https://music.163.com/song/media/outer/url?id=" + musicID + ".mp3";
			Serial.println(audioStreamURL.c_str());
			audio2.connecttohost(audioStreamURL.c_str());

			if (musicplay == 0)
				askquestion = "正在播放音乐：" + musicName;
			else
				askquestion = "正在顺序播放所有音乐，当前正在播放：" + musicName;
			Serial.println(askquestion);
			// displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
			//串口通信 -- 待实现
			startPlay = true;   // 设置播放开始标志
			if (musicplay == 0)
			{
				flag = 1;
				Answer = "音乐播放完了，主人还想听什么音乐吗？喵~";
			}
		}
		else if ((askquestion.indexOf("再听") > -1 || askquestion.indexOf("再放") > -1 || askquestion.indexOf("再来") > -1) && askquestion.indexOf("一") > -1)
		{
			musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
			musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
			Serial.println("音乐名称: " + musicName);
			Serial.println("音乐ID: " + musicID);

			String audioStreamURL = "https://music.163.com/song/media/outer/url?id=" + musicID + ".mp3";
			Serial.println(audioStreamURL.c_str());
			audio2.connecttohost(audioStreamURL.c_str());

			if (musicplay == 0)
				askquestion = "正在播放音乐：" + musicName;
			else
				askquestion = "正在顺序播放所有音乐，当前正在播放：" + musicName;
			Serial.println(askquestion);
			// displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
			//串口通信 -- 待实现
			startPlay = true;   // 设置播放开始标志
			if (musicplay == 0)
			{
				flag = 1;
				Answer = "音乐播放完了，主人还想听什么音乐吗？喵~";
			}
		}
		else if (askquestion.indexOf("听") > -1 || askquestion.indexOf("来") > -1 || askquestion.indexOf("放") > -1 || askquestion.indexOf("换") > -1)
		{
			if (numMusic == 0)
			{
				musicID == "";
			}
			else if (askquestion.indexOf("随便") > -1)
			{
				// 设置随机数种子
				srand(time(NULL));
				musicnum = rand() % numMusic;
				musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
				musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
				Serial.println("音乐名称: " + musicName);
				Serial.println("音乐ID: " + musicID);
			}
			else if (askquestion.indexOf("连续") > -1 || askquestion.indexOf("顺序") > -1 || askquestion.indexOf("所有") > -1)
			{
				musicplay = 1;
				if (askquestion.indexOf("继续") == -1)
					musicnum = 0;
				musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
				musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
			}
			else if (askquestion.indexOf("最喜欢的") > -1 || askquestion.indexOf("最爱的") > -1)
			{
				musicName = "Avid";
				musicID = "1862822901";
				Serial.println("音乐名称: " + musicName);
				Serial.println("音乐ID: " + musicID);
				for (int i = 0; i < numMusic; ++i)
				{
					if (preferences.getString(("musicId" + String(i)).c_str(), "") == musicID)  musicnum = i;
				}
			}
			else    // 查询歌名
			{
				for (int i = 0; i < numMusic; ++i)
				{
					musicName = preferences.getString(("musicName" + String(i)).c_str(), "");
					musicID = preferences.getString(("musicId" + String(i)).c_str(), "");
					Serial.println("音乐名称: " + musicName);
					Serial.println("音乐ID: " + musicID);
					if (askquestion.indexOf(musicName.c_str()) > -1)
					{
						Serial.println("找到了！");
						musicnum = i;
						break;
					}
					else
					{
						musicID = "";
					}
				}
			}

			if (musicID == "")
			{
				Serial.println("未找到对应的音乐！");
				// tft.print("assistant: ");
				Answer = "主人，曲库里还没有这首歌哦，换一首吧";
				audio2.connecttospeech(Answer.c_str(), "zh");
				// displayWrappedText(Answer.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
				//串口通信 -- 待实现
				Answer = "";
			}
			else
			{
				String audioStreamURL = "https://music.163.com/song/media/outer/url?id=" + musicID + ".mp3";
				Serial.println(audioStreamURL.c_str());
				audio2.connecttohost(audioStreamURL.c_str());

				if (musicplay == 0)
					askquestion = "正在播放音乐：" + musicName;
				else
					askquestion = "正在顺序播放所有音乐，当前正在播放：" + musicName;
				Serial.println(askquestion);
				// displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
				//串口通信 -- 待实现
				startPlay = true;   // 设置播放开始标志
				if (musicplay == 0)
				{
					flag = 1;
					Answer = "音乐播放完了，主人还想听什么音乐吗？喵~";
				}
			}
		}
		else    // 处理一般的问答请求
		{
			musicplay = 0;
			conStatus = 0;
			// tft.fillScreen(TFT_WHITE);
			// tft.setCursor(0, 0);
			getText("user", askquestion);
			if (askquestion.indexOf("天气") > -1 || askquestion.indexOf("几点了") > -1 || askquestion.indexOf("日期") > -1)
				LLM_request();

		}
		conflag = 1;
		preferences.end();
	}
	else if (((askquestion.indexOf("听") > -1 || askquestion.indexOf("放") > -1 || askquestion.indexOf("来") > -1) && (askquestion.indexOf("歌") > -1 || askquestion.indexOf("音乐") > -1) && askquestion.indexOf("九歌") == -1) || mainStatus == 1)
	{
		// tft.fillScreen(TFT_WHITE);
		// tft.setCursor(0, 0);
		// tft.print("user: ");
		// displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
		// cursorY = u8g2.getCursorY() + 1;
		// tft.setCursor(0, u8g2.getCursorY() + 2);
		//串口通信 -- 待实现
		Serial.println(askquestion.c_str());



		String musicName = "";
		String musicID = "";
		preferences.begin("music_store", true);
		int numMusic = preferences.getInt("numMusic", 0);

		if (askquestion.indexOf("不想") > -1)
		{
			mainStatus = 0;
			// tft.print("assistant: ");
			Answer = "好的，那主人还有其它吩咐吗？";
			audio2.connecttospeech(Answer.c_str(), "zh");
			// displayWrappedText(Answer.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
			//串口通信 -- 待实现
			Serial.println(Answer.c_str());

			Answer = "";
		}
		else
		{
			if (numMusic == 0)
			{
				musicID == "";
			}
			else if (askquestion.indexOf("随便") > -1)
			{
				// 设置随机数种子
				srand(time(NULL));
				musicnum = rand() % numMusic;
				musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
				musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
				Serial.println("音乐名称: " + musicName);
				Serial.println("音乐ID: " + musicID);
			}
			else if (askquestion.indexOf("连续") > -1 || askquestion.indexOf("顺序") > -1 || askquestion.indexOf("所有") > -1)
			{
				musicplay = 1;
				if (askquestion.indexOf("继续") == -1)
					musicnum = 0;
				musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
				musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
			}
			else if (askquestion.indexOf("最喜欢的") > -1 || askquestion.indexOf("最爱的") > -1)
			{
				musicName = "Avid";
				musicID = "1862822901";
				Serial.println("音乐名称: " + musicName);
				Serial.println("音乐ID: " + musicID);
				for (int i = 0; i < numMusic; ++i)
				{
					if (preferences.getString(("musicId" + String(i)).c_str(), "") == musicID)  musicnum = i;
				}
			}
			else    // 查询歌名
			{
				for (int i = 0; i < numMusic; ++i)
				{
					musicName = preferences.getString(("musicName" + String(i)).c_str(), "");
					musicID = preferences.getString(("musicId" + String(i)).c_str(), "");
					Serial.println("音乐名称: " + musicName);
					Serial.println("音乐ID: " + musicID);
					if (askquestion.indexOf(musicName.c_str()) > -1)
					{
						Serial.println("找到了！");
						musicnum = i;
						break;
					}
					else
					{
						musicID = "";
					}
				}
			}

			if (musicID == "")
			{
				mainStatus = 1;
				Serial.println("未找到对应的音乐！");
				// tft.print("assistant: ");
				Answer = "好的，主人，你想听哪首歌呢";
				audio2.connecttospeech(Answer.c_str(), "zh");
				// displayWrappedText(Answer.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
				//串口通信 -- 待实现
				Serial.println(Answer.c_str());

				Answer = "";
			}
			else
			{
				mainStatus = 0;
				// 自建音乐服务器（这里白嫖了网易云的音乐服务器），按照音乐数字id查找对应歌曲
				String audioStreamURL = "https://music.163.com/song/media/outer/url?id=" + musicID + ".mp3";
				Serial.println(audioStreamURL.c_str());
				audio2.connecttohost(audioStreamURL.c_str());

				if (musicplay == 0)
					askquestion = "正在播放音乐：" + musicName;
				else
					askquestion = "开始顺序播放所有音乐，当前正在播放：" + musicName;
				Serial.println(askquestion);
				// displayWrappedText(askquestion.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
				//串口通信 -- 待实现
				startPlay = true;   // 设置播放开始标志
				conStatus = 1;
				if (musicplay == 0)
				{
					flag = 1;
					Answer = "音乐播放完了，主人还想听什么音乐吗？";
				}
			}
		}
		conflag = 1;
		preferences.end();
	}
	else    // 处理一般的问答请求
	{
		// tft.fillScreen(TFT_WHITE);
		// tft.setCursor(0, 0);
		getText("user", askquestion);
		// if (askquestion.indexOf("天气") > -1 || askquestion.indexOf("几点了") > -1 || askquestion.indexOf("日期") > -1)
		// 	LLM_request(8);
		// else
		// 	LLM_request(llm);
		LLM_request();
	}
	recording = 0;
}

// 播放后续的语音
void voicePlay()
{
	// if (audio2.isplaying == 0 && chouxiang != 0)
	// {
	//     if (chouxiang == 1)
	//     {
	//         audio2.connecttohost((dufs + "dingzhen.mp3").c_str());

	//     }
	//     else if (chouxiang == 2)
	//     {
	//         audio2.connecttohost((dufs + "kunkun.mp3").c_str());

	//     }
	//     else
	//     {
	//         audio2.connecttohost((dufs + "laoda.mp3").c_str());

	//     }
	//     startPlay = false;
	//     return;
	// }
	// 检查音频是否正在播放以及回答内容是否为空
	if ((audio2.isplaying == 0) && (Answer != "" || subindex < subAnswers.size()))
	{
		if (subindex < subAnswers.size())
		{
			audio2.connecttospeech(subAnswers[subindex].c_str(), "zh");
			// 在屏幕上显示文字
			// if (text_temp != "" && flag == 1)
			// {
			//     // 清空屏幕
			//     // tft.fillScreen(TFT_WHITE);
			//     // 显示剩余的文字
			//     displayWrappedText(text_temp.c_str(), 0, 11, width);
			//     text_temp = "";
			//     displayWrappedText(subAnswers[subindex].c_str(), u8g2.getCursorX(), u8g2.getCursorY(), width);
			// }
			// else if (flag == 1)
			// {
			//     // 清空屏幕
			//     tft.fillScreen(TFT_WHITE);
			//     displayWrappedText(subAnswers[subindex].c_str(), 0, 11, width);
			// }
			subindex++;
		}
		else
		{
			audio2.connecttospeech(Answer.c_str(), "zh");
			// 在屏幕上显示文字
			// if (text_temp != "" && flag == 1)
			// {
			//     // 清空屏幕
			//     tft.fillScreen(TFT_WHITE);
			//     // 显示剩余的文字
			//     displayWrappedText(text_temp.c_str(), 0, 11, width);
			//     text_temp = "";
			//     displayWrappedText(Answer.c_str(), u8g2.getCursorX(), u8g2.getCursorY(), width);
			// }
			// else if (flag == 1)
			// {
			//     // 清空屏幕
			//     tft.fillScreen(TFT_WHITE);
			//     displayWrappedText(Answer.c_str(), 0, 11, width);
			// }
			Answer = "";
		}
		// 设置开始播放标志
		startPlay = true;
	}
	else if (audio2.isplaying == 0 && subindex == subAnswers.size() && hint == 1)
	{
		audio2.connecttoFS(SPIFFS, "/hint1.mp3"); // SPIFFS
		hint = 0;
	}
	else if (audio2.isplaying == 0 && musicplay == 1)   // 处理连续播放音乐逻辑
	{
		preferences.begin("music_store", true);
		int numMusic = preferences.getInt("numMusic", 0);
		musicnum = musicnum + 1 < numMusic ? musicnum + 1 : 0;

		String musicName = preferences.getString(("musicName" + String(musicnum)).c_str(), "");
		String musicID = preferences.getString(("musicId" + String(musicnum)).c_str(), "");
		Serial.println("音乐名称: " + musicName);
		Serial.println("音乐ID: " + musicID);

		String audioStreamURL = "https://music.163.com/song/media/outer/url?id=" + musicID + ".mp3";
		Serial.println(audioStreamURL.c_str());
		audio2.connecttohost(audioStreamURL.c_str());

		// tft.fillRect(0, cursorY, width, 50, TFT_WHITE);
		askquestion = "正在顺序播放所有音乐，当前正在播放：" + musicName;
		Serial.println(askquestion);
		// 打印内容
		// displayWrappedText(askquestion.c_str(), 0, cursorY + 11, width);
		Serial.printf(askquestion.c_str());
		askquestion = "";
		preferences.end();
		startPlay = true;
	}
	else
	{
		// 如果音频正在播放或回答内容为空，不做任何操作
	}
}
