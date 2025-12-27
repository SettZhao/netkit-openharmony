//
// Created on 2025/12/26.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "socket/dns.h"
#include "error/network_exception.h"
#include "utils/hilog_helper.h"
#include <cstddef>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

// RAII 释放器
struct AddrInfoDeleter {
    void operator()(addrinfo* p) const { if (p) freeaddrinfo(p); }
};

// 构造函数
InetAddress::InetAddress(std::string ip, uint16_t port, InetFamily family): ip_(ip), port_(port), family_(family){
    if (ip_.empty()) {
        throw std::invalid_argument("Invalid InetAddress parameters");
    }
    LOGD("InetAddress: Constructor - %{public}s", ip_.c_str());
}
// 析构函数
InetAddress::~InetAddress() {
    LOGD("InetAddress: Destructor - %{public}s", ip_.c_str());
}

// 拷贝构造函数
InetAddress::InetAddress(const InetAddress& other)
    : ip_(other.ip_), host_(other.host_), port_(other.port_), family_(other.family_) {
    LOGD("InetAddress: Copy Constructor - %{public}s", ip_.c_str());
}

// 移动构造函数
InetAddress::InetAddress(InetAddress&& other) noexcept
    : ip_(std::move(other.ip_)), host_(std::move(other.host_)), port_(other.port_), family_(other.family_) {
    LOGD("InetAddress: Move Constructor - %{public}s", ip_.c_str());
}

// 拷贝赋值运算符
InetAddress& InetAddress::operator=(const InetAddress& other) {
    if (this != &other) {
        ip_ = other.ip_;
        host_ = other.host_;
        port_ = other.port_;
        family_ = other.family_;
        LOGD("InetAddress: Copy Assignment - %{public}s", ip_.c_str());
    }
    return *this;
}

// 移动赋值运算符
InetAddress& InetAddress::operator=(InetAddress&& other) noexcept {
    if (this != &other) {
        ip_ = std::move(other.ip_);
        host_ = std::move(other.host_);
        port_ = other.port_;
        family_ = other.family_;
        LOGD("InetAddress: Move Assignment - %{public}s", ip_.c_str());
    }
    return *this;
}

// dns查询
InetAddress InetAddress::getByName(const std::string& host){
    int status;
    addrinfo hints{}, *res;
    hints.ai_family = AF_UNSPEC; // 不指定版本
    hints.ai_socktype = SOCK_STREAM; // TCP类型
    if ((status = getaddrinfo(host.c_str(), nullptr, &hints, &res)) != 0){
        // 没有网络权限会报错: Invalid flags
        LOGE("getaddrinfo error: %{public}s", gai_strerror(status));
        throw NetworkException(map_error_type(status), status, "getaddrinfo failed: " + std::string(gai_strerror(status)));
    }
    std::unique_ptr<addrinfo, AddrInfoDeleter> res_ptr(res);
    in_port_t net_port;
    InetFamily family;
    char ipstr[INET6_ADDRSTRLEN];
    if (res->ai_family == AF_INET){
        auto *ipv4 = (sockaddr_in *)res->ai_addr;
        inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, sizeof ipstr);
        net_port = ntohs(ipv4->sin_port);
        family = InetFamily::Ipv4;
    } else {
        auto *ipv6 = (sockaddr_in6 *)res->ai_addr;
        inet_ntop(AF_INET6, &ipv6->sin6_addr, ipstr, sizeof ipstr);
        net_port = ntohs(ipv6->sin6_port);
        family = InetFamily::Ipv6;
    }
    LOGD("Resolved %{public}s -> %{public}s:%{public}u",host.c_str(), ipstr, net_port);
    // unique_ptr 会自动调用 freeaddrinfo
    return InetAddress(ipstr, net_port, family);
}

// dns查询
std::vector<InetAddress> InetAddress::getAllByName(const std::string& host){
    int status;
    addrinfo hints{}, *res;
    hints.ai_family = AF_UNSPEC; // 不指定版本
    hints.ai_socktype = SOCK_STREAM; // TCP类型
    if ((status = getaddrinfo(host.c_str(), nullptr, &hints, &res)) != 0){
        // 没有网络权限会报错: Invalid flags
        LOGE("getaddrinfo error: %{public}s", gai_strerror(status));
        throw NetworkException(map_error_type(status), status, "getaddrinfo failed: " + std::string(gai_strerror(status)));
    }
    std::unique_ptr<addrinfo, AddrInfoDeleter> res_ptr(res);
    
    std::vector<InetAddress> addresses;
    // 预留空间避免 vector 扩容时的移动操作
    addresses.reserve(8);
    char ipstr[INET6_ADDRSTRLEN];
    for (addrinfo *p = res; p != nullptr; p = p->ai_next){
        in_port_t net_port;
        InetFamily family;
        if (p->ai_family == AF_INET){
            auto *ipv4 = (sockaddr_in *)p->ai_addr;
            inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, sizeof ipstr);
            net_port = ntohs(ipv4->sin_port);
            family = InetFamily::Ipv4;
        } else {
            auto *ipv6 = (sockaddr_in6 *)p->ai_addr;
            inet_ntop(AF_INET6, &ipv6->sin6_addr, ipstr, sizeof ipstr);
            net_port = ntohs(ipv6->sin6_port);
            family = InetFamily::Ipv6;
        }
        addresses.emplace_back(ipstr, net_port, family);
        LOGD("Found address: %{public}s:%{public}u--%{public}d--%{public}d--%{public}u", ipstr, net_port, p->ai_socktype, p->ai_protocol, family);
    }
    return addresses;
}

std::string InetAddress::getHostName(const std::string& ip){
    return "";
}
