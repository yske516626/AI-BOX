#ifndef _XUNFEIMODEL_H
#define _XUNFEIMODEL_H

#include "../Inc/main.h"

// 拼接讯飞websocket鉴权参数
String getUrl(String Spark_url, String host, String path, String Date);
//显示文本
void getText(String role, String content);
void response();
//连接STT语音websocket服务器
void ConnServer1();
// //连接讯飞LLM模型 --websocket流式连接
// void ConnServer();
// 大模型 HTTP 通用流式调用，基于 Server-Sent Events (SSE) 协议的流式处理，并不是websocket
void LLM_request();

#endif