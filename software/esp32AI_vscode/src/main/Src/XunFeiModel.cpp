#include "../Inc/UserProcessing.h"


/****************************非模型部分处理******************************************** */
void response()
{
    // tft.fillScreen(TFT_WHITE);
    // tft.setCursor(0, 0);
    // tft.print("assistant: ");
	audio2.connecttospeech(Answer.c_str(), "zh");
	Serial.println(Answer.c_str());
	// displayWrappedText(Answer.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
	Answer = "";

	//串口通信 -- 待实现
	
}

// 移除LLM模型得到的回复中没用的符号
void removeChars(const char *input, char *output, const char *removeSet)
{
    int j = 0;
    for (int i = 0; input[i] != '\0'; ++i)
    {
        bool shouldRemove = false;
        for (int k = 0; removeSet[k] != '\0'; ++k)
        {
            if (input[i] == removeSet[k])
            {
                shouldRemove = true;
                break;
            }
        }
        if (!shouldRemove)
        {
            output[j++] = input[i];
        }
    }
    output[j] = '\0'; // 结束符
}


/****************************URL处理******************************************** */
// 拼接讯飞websocket鉴权参数
String getUrl(String Spark_url, String host, String path, String Date)
{
	// 拼接签名原始字符串
	String signature_origin = "host: " + host + "\n";
	signature_origin += "date: " + Date + "\n";
	signature_origin += "GET " + path + " HTTP/1.1";
	// 示例：signature_origin="host: spark-api.xf-yun.com\ndate: Mon, 04 Mar 2024 19:23:20 GMT\nGET /v3.5/chat HTTP/1.1";

	// 使用 HMAC-SHA256 进行加密
	unsigned char hmac[32];                                 // 存储HMAC结果
	mbedtls_md_context_t ctx;                               // HMAC上下文
	mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;          // 使用SHA256哈希算法
	const size_t messageLength = signature_origin.length(); // 签名原始字符串的长度
	const size_t keyLength = APISecret.length();            // 密钥的长度

	// 初始化HMAC上下文
	mbedtls_md_init(&ctx);
	mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
	// 设置HMAC密钥
	mbedtls_md_hmac_starts(&ctx, (const unsigned char*)APISecret.c_str(), keyLength);
	// 更新HMAC上下文
	mbedtls_md_hmac_update(&ctx, (const unsigned char*)signature_origin.c_str(), messageLength);
	// 完成HMAC计算
	mbedtls_md_hmac_finish(&ctx, hmac);
	// 释放HMAC上下文
	mbedtls_md_free(&ctx);

	// 将HMAC结果进行Base64编码
	String signature_sha_base64 = base64::encode(hmac, sizeof(hmac) / sizeof(hmac[0]));

	// 替换Date字符串中的特殊字符
	Date.replace(",", "%2C");
	Date.replace(" ", "+");
	Date.replace(":", "%3A");

	// 构建Authorization原始字符串
	String authorization_origin = "api_key=\"" + APIKey + "\", algorithm=\"hmac-sha256\", headers=\"host date request-line\", signature=\"" + signature_sha_base64 + "\"";

	// 将Authorization原始字符串进行Base64编码
	String authorization = base64::encode(authorization_origin);

	// 构建最终的URL
	String url = Spark_url + '?' + "authorization=" + authorization + "&date=" + Date + "&host=" + host;

	// 向串口输出生成的URL
	Serial.println(url);

	// 返回生成的URL
	return url;
}
/****************************模型（STT、LLM）响应******************************************** */

// 实时清理较早的历史对话记录
void checkLen()
{
    size_t totalBytes = 0;

    // 计算vector中每个字符串的长度
    for (const auto& jsonStr : text) {
        totalBytes += jsonStr.length();
    }
    // String note_output = "当前上下文占用字节数（text size）: " + String(totalBytes) + "/" + String(max_context_length);
    // Serial.println(note_output);

    // 当vector中的字符串总长度超过一定字节时，删除最开始的一对对话
    if (totalBytes > max_context_length)
    {
        // Serial.println("对话上下文占用字节数超过限制，删除最开始的一对对话");
        text.erase(text.begin(), text.begin() + 2);
    }
}

// 显示文本
void getText(String role, String content)
{
    // 检查并调整文本长度
    checkLen();

    // 创建一个静态JSON文档，容量为512字节
    StaticJsonDocument<512> jsoncon;

    // 设置JSON文档中的角色和内容
    jsoncon["role"] = role;
    jsoncon["content"] = content;

    // 将JSON文档序列化为字符串
    String jsonString;
    serializeJson(jsoncon, jsonString);

    // 将字符串存储到vector中
    text.push_back(jsonString);
    
    // 清空临时JSON文档
    jsoncon.clear();

    // tft.print(role);
    // tft.print(": ");
    // displayWrappedText(content.c_str(), tft.getCursorX(), tft.getCursorY() + 11, width);
	// tft.setCursor(0, u8g2.getCursorY() + 2);

	//串口通信 -- 待实现
	 Serial.println(content.c_str());
}

// 服务器响应数据处理
void processResponse(int status)
{
    // 如果Answer的长度超过180且音频没有播放
    if (Answer.length() >= 180 && (audio2.isplaying == 0) && flag == 0)
    {
        flag = 1;
        int subAnswerlength = 0;
        if (Answer.length() >= 300)
        {
            const char* symbols[] = {"。", "；", "？", "！"};
            int firstPeriodIndex = -1;
            for (int i = 0; i < 4 && firstPeriodIndex == -1; i++) {
                firstPeriodIndex = Answer.indexOf(symbols[i]);  // 查找出一个用来断句的符号的位置
            }
            if (firstPeriodIndex != -1)
                subAnswerlength = firstPeriodIndex + 3;
            else
                Serial.println("断句失败，大模型回复中无句号、分号、问号、感叹号断句！");
        }
        else
        {
            int lastCommaIndex = Answer.lastIndexOf("，");  // 查找最后一个逗号的位置
            if (lastCommaIndex != -1)
                subAnswerlength = lastCommaIndex + 3;
            else
                subAnswerlength = Answer.length();
        }
        String subAnswer1 = Answer.substring(0, subAnswerlength);    // 提取句子的一部分
        String note_output = "subAnswer1: " + subAnswer1;
        Serial.println(note_output);
        hint = 1;
        audio2.connecttospeech(subAnswer1.c_str(), "zh");           // 将提取的句子转换为语音
        getText("assistant", subAnswer1);                           // 显示提取的句子
        // tft.setCursor(54, 152);                                     // 在屏幕上显示对话轮次
		// tft.print(loopcount);
		//串口通信 -- 待实现
		
		Answer = Answer.substring(subAnswerlength);                 // 更新Answer，去掉已处理的部分
        startPlay = true;
        conflag = 1;
    }
    // 存储多段子音频
    while (Answer.length() >= 180)
    {
        int subAnswerlength = 0;
        if (Answer.length() >= 300)
        {
            const char* symbols[] = {"。", "；", "？", "！"};
            int firstPeriodIndex = -1;
            for (int i = 0; i < 4 && firstPeriodIndex == -1; i++) {
                firstPeriodIndex = Answer.indexOf(symbols[i]);  // 查找出一个用来断句的符号的位置
            }
            if (firstPeriodIndex != -1)
                subAnswerlength = firstPeriodIndex + 3;
            else
                Serial.println("断句失败，大模型回复中无句号、分号、问号、感叹号断句！");
        }
        else
        {
            int lastCommaIndex = Answer.lastIndexOf("，");
            if (lastCommaIndex != -1)
                subAnswerlength = lastCommaIndex + 3;
            else
                subAnswerlength = Answer.length();
        }
        subAnswers.push_back(Answer.substring(0, subAnswerlength));
        String note_output = "subAnswer" + String(subAnswers.size() + 1) + "：" + subAnswers[subAnswers.size() - 1];
        Serial.println(note_output);

        Answer = Answer.substring(subAnswerlength);
    }

    // 如果status为2（回复的内容接收完成），且回复的内容小于180字节
    if (status == 2 && flag == 0)
    {
        hint = 1;
        audio2.connecttospeech(Answer.c_str(), "zh");               // 将回复的内容转换为语音
        getText("assistant", Answer);                               // 显示回复的内容
        // tft.setCursor(54, 152);                                     // 在屏幕上显示对话轮次
        // tft.print(loopcount);
        Answer = "";                                                // 清空Answer
        startPlay = true;
        conflag = 1;  //启动连续对话，让用户可以开始下下一轮的对话模式
    }
}

/****************************LLM模型服务：HTTP流式调用******************************************** */

// 生成发送请求所需要的json文档
DynamicJsonDocument createRequestBody(const char *model, const char *role_set)
{
    // 创建一个容量为4096字节的动态JSON文档
    DynamicJsonDocument data(4096);

    data["model"] = model;
    data["max_tokens"] = 1024;
    data["temperature"] = 0.7;
    data["presence_penalty"] = 1.5;
    data["stream"] = true;

    // 在message对象中创建一个名为text的嵌套数组
    JsonArray textArray = data.createNestedArray("messages");

    JsonObject systemMessage = textArray.createNestedObject();
    systemMessage["role"] = "system";
    systemMessage["content"] = role_set;

    // 将jsonVector中的内容添加到JsonArray中
    for (const auto& jsonStr : text) {
        DynamicJsonDocument tempDoc(512);
        DeserializationError error = deserializeJson(tempDoc, jsonStr);
        if (!error) {
            textArray.add(tempDoc.as<JsonVariant>());
        } else {
            Serial.print("反序列化失败: ");
            Serial.println(error.c_str());
        }
    }
    // 返回构建好的JSON文档
    return data;
}

// 大模型 HTTP 通用流式调用，基于 Server-Sent Events (SSE) 协议的流式处理，并不是websocket
void LLM_request()
{
    HTTPClient http;
    http.setTimeout(20000);     // 设置请求超时时间
    http.begin(llm_url);
    http.addHeader("Content-Type", "application/json");
    String token_key = String("Bearer ") + llm_apiKey;
    http.addHeader("Authorization", token_key);

    // 向串口输出提示信息
    Serial.print("Sending a message to ");
    Serial.println(llm_name);

    // 生成连接参数的JSON文档
    DynamicJsonDocument jsonData = createRequestBody(llm_model.c_str(), roleSettings.c_str());

    // 将JSON文档序列化为字符串
    String jsonString;
    serializeJson(jsonData, jsonString);

    Serial.println(jsonString);
    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode == 200) {
        // 在 stream（流式调用） 模式下，基于 SSE (Server-Sent Events) 协议返回生成内容，每次返回结果为生成的部分内容片段
        WiFiClient* stream = http.getStreamPtr();   // 返回一个指向HTTP响应流的指针，通过它可以读取服务器返回的数据

        while (stream->connected()) {   // 这个循环会一直运行，直到客户端（即stream）断开连接。
            String line = stream->readStringUntil('\n');    // 从流中读取一行字符串，直到遇到换行符\n为止
            if (llm_name == "Ollama" && line.length() > 50)
            {
                line = "data:" + line;
            }
            // 检查读取的行是否以data:开头。
            // 在SSE（Server-Sent Events）协议中，服务器发送的数据行通常以data:开头，这样客户端可以识别出这是实际的数据内容。
            if (line.startsWith("data:")) {
                // 如果行以data:开头，提取出data:后面的部分，并去掉首尾的空白字符。
                String data = line.substring(5);
                data.trim();
                
                int status = 0;
                if (data == "[DONE]")
                {
                    status = 2;
                    Serial.println("status: 2");
                    processResponse(status);
                    stream->stop();
                    break;
                }

                // 解析收到的数据
                StaticJsonDocument<1024> jsonResponse;
                DeserializationError error = deserializeJson(jsonResponse, data);

                // 如果解析没有错误
                if (!error)
                {
                    if (jsonResponse.containsKey("choices") && jsonResponse["choices"][0].containsKey("delta"))
                    {
                        if (jsonResponse["choices"][0]["delta"].containsKey("content") && !jsonResponse["choices"][0]["delta"]["content"].isNull())
                        {
                            const char *content = jsonResponse["choices"][0]["delta"]["content"];
                            char *cleanedContent = new char[strlen(content) + 1];
                            const char *removeSet = "\n*$"; // 定义需要移除的符号集
                            removeChars(content, cleanedContent, removeSet);
                            Serial.println(cleanedContent);

                            Answer += cleanedContent;
                            content = "";
                            delete[] cleanedContent;
                        }

                        if (jsonResponse["choices"][0].containsKey("finish_reason") && jsonResponse["choices"][0]["finish_reason"] == "stop")
                        {
                            status = 2;
                            Serial.println("status: 2");
                        }

                        processResponse(status);

                        if (status == 2)
                        {
                            stream->stop();
                            break;
                        }
                    }
                    else if (jsonResponse.containsKey("message"))
                    {
                        if (jsonResponse["message"].containsKey("content") && !jsonResponse["message"]["content"].isNull())
                        {
                            const char *content = jsonResponse["message"]["content"];
                            char *cleanedContent = new char[strlen(content) + 1];
                            const char *removeSet = "\n*$"; // 定义需要移除的符号集
                            removeChars(content, cleanedContent, removeSet);
                            Serial.println(cleanedContent);

                            Answer += cleanedContent;
                            content = "";
                            delete[] cleanedContent;
                        }

                        if (jsonResponse.containsKey("done") && jsonResponse["done"])
                        {
                            status = 2;
                            Serial.println("status: 2");
                        }

                        processResponse(status);

                        if (status == 2)
                        {
                            stream->stop();
                            break;
                        }
                    }
                    else {
                        Serial.println("choices not found");
                    }
                }    
                else 
                {
                    Serial.print("解析错误（Parsing Error）: ");
                    Serial.println(error.c_str());
                }
            }
        }
        http.end();
        return;
    } 
    else 
    {
        Serial.printf("Error %i \n", httpResponseCode);
        Serial.println(http.getString());
        http.end();
        return;
    }
}



/****************************STT服务******************************************** */

// 接收stt返回的语音识别文本并做相应的逻辑处理 --- 回调函数
void onMessageCallback1(WebsocketsMessage message)
{
	// 创建一个动态JSON文档对象，用于存储解析后的JSON数据，最大容量为4096字节
	DynamicJsonDocument jsonDocument(4096);

	// 解析收到的JSON数据
	DeserializationError error = deserializeJson(jsonDocument, message.data());

	if (error)
	{
		// 如果解析出错，输出错误信息和收到的消息数据
		Serial.println("error:");
		Serial.println(error.c_str());
		Serial.println(message.data());
		return;
	}
	// 如果解析没有错误，从JSON数据中获取返回码，如果返回码不为0，表示出错
	if (jsonDocument["code"] != 0)
	{
		// 输出完整的JSON数据
		Serial.println(message.data());
		// 关闭WebSocket客户端
		webSocketClient1.close();
	}
	else
	{
		// 输出收到的讯飞云返回消息
		//Serial.println("xunfeiyun stt return message:");
		//Serial.println(message.data());

		// 获取JSON数据中的结果部分，并提取文本内容
		JsonArray ws = jsonDocument["data"]["result"]["ws"].as<JsonArray>();

		if (jsonDocument["data"]["status"] != 2)    //处理流式返回的内容，讯飞stt最后一次会返回一个标点符号，需要和前一次返回结果拼接起来
		{
			askquestion = "";
		}

		for (JsonVariant i : ws)
		{
			for (JsonVariant w : i["cw"].as<JsonArray>())
			{
				askquestion += w["w"].as<String>();
			}
		}

		// 输出提取的语音内容
		Serial.println(askquestion);
		Serial.println("识别。");

		// 获取状态码，等于2表示文本已经转换完成
		if (jsonDocument["data"]["status"] == 2)
		{
			// 如果状态码为2，表示消息处理完成
			Serial.println("status == 2");
			webSocketClient1.close();

			processAskquestion();
		}
	}
}

// 录音 -- 回调函数
void onEventsCallback1(WebsocketsEvent event, String data)
{
	// 当WebSocket连接打开时触发
	if (event == WebsocketsEvent::ConnectionOpened)
	{
		// 向串口输出提示信息
		Serial.println("Send message to xunfeiyun stt!");

		// 初始化变量
		int silence = 0;
		int firstframe = 1;  //标识当前这轮录音内容是不是首段，因为一段录音周期可能讲不完想说的话
		int voicebegin = 0;
		int voice = 0;
		int null_voice = 0;

		// 创建一个静态JSON文档对象，2000一般够了，不够可以再加（最多不能超过4096），但是可能会发生内存溢出
		StaticJsonDocument<2000> doc;

		/********* 旧版本 *********/
		// if (await_flag == 1)
		// {
		// 	// tft.fillScreen(TFT_WHITE);
		// 	// u8g2.setCursor(0, 11);
		// 	// u8g2.print("待机中......");

		// 	//串口通信 -- 待实现
		// 	Serial.println("待机中.....\n");
		// }
		// else if (conflag == 1)
		// {
		// 	// tft.fillScreen(TFT_WHITE);
		// 	// u8g2.setCursor(0, 11);
		// 	// u8g2.print("连续对话中，请说话！");

		// 	//串口通信 -- 待实现
		// 	Serial.println("连续对话中，请说话！\n");
		// }
		// else
		// {
		// 	// u8g2.setCursor(0, 159);
		// 	// u8g2.print("请说话！");

		// 	//串口通信 -- 待实现
		// 	Serial.println("请说话！！\n");

		// }
		/********* 旧版本 *********/
		


		if (conflag == 1)
		{
			// tft.fillScreen(TFT_WHITE);
			// u8g2.setCursor(0, 11);
			// u8g2.print("连续对话中，请说话！");

			//串口通信 -- 待实现
			Serial.println("连续对话中，请说话！\n");
		}
		else
		{
			// u8g2.setCursor(0, 159);
			// u8g2.print("请说话！");

			//串口通信 -- 待实现
			Serial.println("请说话！！\n");

		}

		conflag = 0;
		Serial.println("开始录音");
		recording = 1;
		// 无限循环，用于录制和发送音频数据
		while (1)
		{
			
			/******** 旧版本 ********/
			// // 待机状态（语音唤醒状态）也可通过boot键启动
			// if ((digitalRead(key) == 0 || Serial.available()) && await_flag == 1)
			// {
			// 	start_con = 1;      // 对话开始标识
			// 	await_flag = 0;     // 退出待机状态
			// 	webSocketClient1.close();
			// 	break;
			// }
			/******** 旧版本 ********/


			// 清空JSON文档
			doc.clear();

			// 创建data对象
			JsonObject data = doc.createNestedObject("data");

			// 录制音频数据
			audio1.Record();

			// 计算音频数据的RMS值
			float rms = audio1.calculateRMS((uint8_t*)audio1.wavData[0], 1280);
			if (rms > 1000) // 抑制录音奇奇怪怪的噪声
			{
				rms = 8.6;
			}
			//printf("RMS: %f\n", rms);

			if (null_voice >= 80)    // 如果从录音开始过了8秒才说话，讯飞stt识别会超时，所以直接结束本次录音，重新开始录音
			{
				shuaxin = 1;

				//ASRPRO
				awake_flag = 0;      // 已唤醒，退出唤醒状态，进入待机状态
				Answer = "我先退下了，有事再找我呢";
				response();     //屏幕显示Answer以及语音播放

				/******** 旧版本 ********/
				// awake_flag = 0;     // 未唤醒，保持待机状态
				// await_flag = 1;     // 进入待机状态
				// if (start_con == 1)     // 表示正处于对话中，才回复退下，没有进入对话则继续待机
				// {
				// 	start_con = 0;      // 标识一次（包含多轮）对话结束
				// 	Answer = "主人，我先退下了，有事再找我";
				// 	response();     //屏幕显示Answer以及语音播放
				// }
				/******** 旧版本 ********/

				recording = 0;
				endTime = millis();
				// 录音超时，断开本次连接
				webSocketClient1.close();
				Serial.println("录音结束");
				return;
			}

			// 判断是否为噪音
			if (rms < noise)
			{
				null_voice++;
				if (voicebegin == 1)
				{
					silence++;
				}
			}
			else
			{
				if (null_voice > 0)
					null_voice--;
				voice++;
				if (voice >= 10)
				{
					voicebegin = 1;
				}
				else
				{
					voicebegin = 0;
				}
				silence = 0;
			}
			// 如果静音达到8个周期，发送结束标志的音频数据表示已经讲完了
			if (silence == 8)
			{
				data["status"] = 2;
				data["format"] = "audio/L16;rate=16000";
				data["audio"] = base64::encode((byte*)audio1.wavData[0], 1280);
				data["encoding"] = "raw";

				String jsonString;
				serializeJson(doc, jsonString);

				webSocketClient1.send(jsonString);
				delay(40);
				Serial.println("录音结束");
				break;  
			}

			// 处理第一帧音频数据
			if (firstframe == 1)
			{
				data["status"] = 0;
				data["format"] = "audio/L16;rate=16000";
				data["audio"] = base64::encode((byte*)audio1.wavData[0], 1280);
				data["encoding"] = "raw";

				JsonObject common = doc.createNestedObject("common");
				common["app_id"] = APPID.c_str();

				JsonObject business = doc.createNestedObject("business");
				business["domain"] = "iat";
				business["language"] = language.c_str();
				business["accent"] = "mandarin";
				// 不使用动态修正
				// business["vinfo"] = 1;
				// 使用动态修正
				business["dwa"] = "wpgs";
				business["vad_eos"] = 2000;

				String jsonString;
				serializeJson(doc, jsonString);

				webSocketClient1.send(jsonString);
				firstframe = 0;
				delay(40);
			}
			else
			{
				// 处理后续帧音频数据
				data["status"] = 1;
				data["format"] = "audio/L16;rate=16000";
				data["audio"] = base64::encode((byte*)audio1.wavData[0], 1280);
				data["encoding"] = "raw";

				String jsonString;
				serializeJson(doc, jsonString);

				webSocketClient1.send(jsonString);
				delay(40);
			}
		}
	}
	// 当WebSocket连接关闭时触发
	else if (event == WebsocketsEvent::ConnectionClosed)
	{
		// 向串口输出提示信息
		Serial.println("Connnection1 Closed");
	}
	// 当收到Ping消息时触发
	else if (event == WebsocketsEvent::GotPing)
	{
		// 向串口输出提示信息
		Serial.println("Got a Ping!");
	}
	// 当收到Pong消息时触发
	else if (event == WebsocketsEvent::GotPong)
	{
		// 向串口输出提示信息
		Serial.println("Got a Pong!");
	}
}

//连接STT语音websocket服务器
void ConnServer1()
{
	// Serial.println("url1:" + url1);

	webSocketClient1.onMessage(onMessageCallback1);  //接收文本
	webSocketClient1.onEvent(onEventsCallback1);  //发送录音

	// Connect to WebSocket
	Serial.println("开始连接讯飞STT语音转文字服务......Begin connect to server1(Xunfei STT)......");
	if (webSocketClient1.connect(url1.c_str()))
	{
		Serial.println("连接成功！Connected to server1(Xunfei STT)!");
	}
	else
	{
		Serial.println("连接失败！Failed to connect to server1(Xunfei STT)!");
	}
}




/****************************LLM模型服务：websocket流式连接******************************************** */


// // 生成连接（LLM）参数的JSON文档 -- websocket流式连接
// DynamicJsonDocument gen_params(const char *appid, const char *domain, const char *role_set)
// {
//     // 创建一个容量为1500字节的动态JSON文档
//     DynamicJsonDocument data(1500);

//     // 创建一个名为header的嵌套JSON对象，并添加app_id和uid字段
//     JsonObject header = data.createNestedObject("header");
//     header["app_id"] = appid;
//     header["uid"] = "1234";

//     // 创建一个名为parameter的嵌套JSON对象
//     JsonObject parameter = data.createNestedObject("parameter");

//     // 在parameter对象中创建一个名为chat的嵌套对象，并添加domain, temperature和max_tokens字段
//     JsonObject chat = parameter.createNestedObject("chat");
//     chat["domain"] = domain;
//     chat["temperature"] = 0.6;
//     chat["max_tokens"] = 1024;

//     // 创建一个名为payload的嵌套JSON对象
//     JsonObject payload = data.createNestedObject("payload");

//     // 在payload对象中创建一个名为message的嵌套对象
//     JsonObject message = payload.createNestedObject("message");

//     // 在message对象中创建一个名为text的嵌套数组
//     JsonArray textArray = message.createNestedArray("text");

//     JsonObject systemMessage = textArray.createNestedObject();
//     systemMessage["role"] = "system";
//     systemMessage["content"] = role_set;

//     // 将jsonVector中的内容添加到JsonArray中
//     for (const auto& jsonStr : text) {
//         DynamicJsonDocument tempDoc(512);
//         DeserializationError error = deserializeJson(tempDoc, jsonStr);
//         if (!error) {
//             textArray.add(tempDoc.as<JsonVariant>());
//         } else {
//             Serial.print("反序列化失败: ");
//             Serial.println(error.c_str());
//         }
//     }
//     // 返回构建好的JSON文档
//     return data;
// }



// // LLM模型：将回复的文本转成语音  --- 回调函数
// void onMessageCallback(WebsocketsMessage message)
// {
// 	// 创建一个静态JSON文档对象，用于存储解析后的JSON数据，最大容量为4096字节，硬件限制，无法再增加
// 	StaticJsonDocument<1024> jsonDocument;

// 	// 解析收到的JSON数据
// 	DeserializationError error = deserializeJson(jsonDocument, message.data());

// 	// 如果解析没有错误
// 	if (!error)
// 	{
// 		// 从JSON数据中获取返回码
// 		int code = jsonDocument["header"]["code"];

// 		// 如果返回码不为0，表示出错
// 		if (code != 0)
// 		{
// 			// 输出错误信息和完整的JSON数据
// 			Serial.print("sth is wrong: ");
// 			Serial.println(code);
// 			Serial.println(message.data());

// 			// 关闭WebSocket客户端
// 			webSocketClient.close();
// 		}
// 		else
// 		{
// 			// 获取JSON数据中的payload部分
// 			JsonObject choices = jsonDocument["payload"]["choices"];

// 			// 获取status状态
// 			int status = choices["status"];

// 			// 获取文本内容
// 			const char* content = choices["text"][0]["content"];

// 			char* cleanedContent = new char[strlen(content) + 1];
// 			const char* removeSet = "\n*$"; // 定义需要移除的符号集
// 			removeChars(content, cleanedContent, removeSet);
// 			Serial.println(cleanedContent);

// 			Answer += cleanedContent;
// 			content = "";
// 			delete[] cleanedContent;

// 			processResponse(status);
// 		}
// 	}
// }

// // LLM模型：问题发送给讯飞星火大模型 --- 回调函数
// void onEventsCallback(WebsocketsEvent event, String data)
// {
// 	// 当WebSocket连接打开时触发
// 	if (event == WebsocketsEvent::ConnectionOpened)
// 	{
// 		// 向串口输出提示信息
// 		Serial.println("Send message to server0!");

// 		// 生成连接参数的JSON文档
// 		DynamicJsonDocument jsonData = gen_params(appId1.c_str(), domain1.c_str(), roleSettings.c_str());

// 		// 将JSON文档序列化为字符串
// 		String jsonString;
// 		serializeJson(jsonData, jsonString);

// 		// 向串口输出生成的JSON字符串
// 		Serial.println(jsonString);

// 		// 通过WebSocket客户端发送JSON字符串到服务器
// 		webSocketClient.send(jsonString);
// 	}
// 	// 当WebSocket连接关闭时触发
// 	else if (event == WebsocketsEvent::ConnectionClosed)
// 	{
// 		// 向串口输出提示信息
// 		Serial.println("Connnection0 Closed");
// 	}
// 	// 当收到Ping消息时触发
// 	else if (event == WebsocketsEvent::GotPing)
// 	{
// 		// 向串口输出提示信息
// 		Serial.println("Got a Ping!");
// 	}
// 	// 当收到Pong消息时触发
// 	else if (event == WebsocketsEvent::GotPong)
// 	{
// 		// 向串口输出提示信息
// 		Serial.println("Got a Pong!");
// 	}
// }

// //连接讯飞LLM模型 -- 流式连接
// void ConnServer()
// {
//     // Serial.println("url:" + url);                    // 向串口输出WebSocket服务器的URL
    
//     webSocketClient.onMessage(onMessageCallback);       // 设置WebSocket客户端的消息回调函数
//     webSocketClient.onEvent(onEventsCallback);          // 设置WebSocket客户端的事件回调函数

//     // 开始连接WebSocket服务器
//     Serial.println("开始连接讯飞星火大模型服务......Begin connect to server0(Xunfei Spark LLM)......");

//     // 尝试连接到WebSocket服务器
//     if (webSocketClient.connect(url.c_str()))
//     {
//         // 如果连接成功，输出成功信息
//         Serial.println("连接LLM成功！Connected to server0(Xunfei Spark LLM)!");
//     }
//     else
//     {
//         // 如果连接失败，输出失败信息
//         Serial.println("连接LLM失败！Failed to connect to server0(Xunfei Spark LLM)!");
//     }
// }
