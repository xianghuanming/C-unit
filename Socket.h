#pragma once
#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<string>
#include<stdexcept>  // 添加异常头文件
#include <cstdint>  // 添加cstdint头文件

namespace xhm {
class TinySocket {
private:
    int fd;
    bool isServerSocket;
    
public:
    // 客户端socket构造函数
    TinySocket(int domain, int type, int protocol = 0);
    
    // 服务器socket构造函数（通过accept创建）
    TinySocket(int socket_fd);
    
    ~TinySocket();
    
    // 客户端方法
    void connect(const std::string& ip, uint16_t port);
    
    // 服务器方法
    void bind(uint16_t port);
    void bind(const std::string& ip, uint16_t port);
    void listen(int backlog = 10);
    TinySocket accept();
    
    // 通用方法
    ssize_t send(const void* data, size_t len);
    ssize_t recv(void* buffer, size_t len);
    void close();
    int getFd() const { return fd; }
};

// 服务器类
class TimeServer {
private:
    TinySocket serverSocket;
    bool running;
    
public:
~TimeServer();
    TimeServer(uint16_t port);
    void start();
    void stop();
    
private:
    std::string getCurrentTime();
    void handleClient(TinySocket& client);
};
}