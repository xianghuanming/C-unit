#include "Socket.h"
#include <ctime>
#include <sstream>
#include <iomanip>

/*xhm::TainiSocket::TainiSocket(int domain, int type, int protocol)
    : fd(-1), isServerSocket(false) {
    fd = socket(domain, type, protocol);
    if (fd < 0) {
        throw std::runtime_error("Socket创建失败");
    }
    
    // 设置socket选项，避免地址占用
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
}

xhm::TainiSocket::TainiSocket(int socket_fd)
    : fd(socket_fd), isServerSocket(false) {
}

xhm::TainiSocket::~TainiSocket() {
    close();
}

void xhm::TainiSocket::close() {
    if (fd >= 0) {
        ::close(fd);
        fd = -1;
        std::cerr << "Socket已关闭" << std::endl;
    }
}

void xhm::TainiSocket::connect(const std::string& ip, uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("IP地址转换失败");
    }
    
    if (::connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        throw std::runtime_error("连接服务器失败");
    }
}

void xhm::TainiSocket::bind(uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    if (::bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        throw std::runtime_error("绑定端口失败");
    }
}

void xhm::TainiSocket::bind(const std::string& ip, uint16_t port) {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("IP地址转换失败");
    }
    
    if (::bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        throw std::runtime_error("绑定地址失败");
    }
}

void xhm::TainiSocket::listen(int backlog) {
    if (::listen(fd, backlog) < 0) {
        throw std::runtime_error("监听失败");
    }
    isServerSocket = true;
}

xhm::TainiSocket xhm::TainiSocket::accept() {
    sockaddr_in clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);
    
    int clientFd = ::accept(fd, (sockaddr*)&clientAddr, &addrLen);
    if (clientFd < 0) {
        throw std::runtime_error("接受连接失败");
    }
    
    // 输出客户端连接信息
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    std::cout << "客户端连接: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
    
    return TainiSocket(clientFd);
}

ssize_t xhm::TainiSocket::recv(void* buffer, size_t len) {
    return ::recv(fd, buffer, len, 0);
}

ssize_t xhm::TainiSocket::send(const void* data, size_t len) {
    return ::send(fd, data, len, 0);
}

// TimeServer实现
xhm::TimeServer::TimeServer(uint16_t port)
    : serverSocket(AF_INET, SOCK_STREAM, 0), running(false) {
    serverSocket.bind(port);
    serverSocket.listen();
    std::cout << "时间服务器初始化完成，监听端口: " << port << std::endl;
}

std::string xhm::TimeServer::getCurrentTime() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void xhm::TimeServer::handleClient(xhm::TainiSocket& client) {
    try {
        std::string timeStr = getCurrentTime();
        std::string message = "当前时间: " + timeStr + "\n";
        
        // 发送时间给客户端
        client.send(message.c_str(), message.length());
        std::cout << "已发送时间给客户端: " << timeStr << std::endl;
        
        // 等待客户端确认（可选）
        char buffer[256];
        ssize_t len = client.recv(buffer, sizeof(buffer) - 1);
        if (len > 0) {
            buffer[len] = '\0';
            std::cout << "客户端响应: " << buffer << std::endl;
        }
        
        client.close();
    } catch (const std::exception& e) {
        std::cerr << "处理客户端时出错: " << e.what() << std::endl;
    }
}

void xhm::TimeServer::start() {
    running = true;
    std::cout << "时间服务器启动..." << std::endl;
    
    while (running) {
        try {
            TainiSocket client = serverSocket.accept();
            handleClient(client);
        } catch (const std::exception& e) {
            if (running) {
                std::cerr << "接受连接时出错: " << e.what() << std::endl;
            }
        }
    }
}

void xhm::TimeServer::stop() {
    running = false;
    serverSocket.close();
    std::cout << "时间服务器已停止" << std::endl;
}

xhm::TimeServer::~TimeServer() {
    // 默认实现（可添加资源清理逻辑）
    std::cout << "TimeServer析构函数调用" << std::endl;
}*/