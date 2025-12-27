//
// Created on 2025/12/26.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef NETKIT_SOCKETADDR_H
#define NETKIT_SOCKETADDR_H

#include <cstdint>
#include <string>

enum class InetFamily : uint8_t{
    Ipv4 = 1,
    Ipv6 = 2
};

class InetAddress {
public:
    
    InetAddress(std::string ip, uint16_t port = 0, InetFamily family = InetFamily::Ipv4);
    ~InetAddress();
    InetAddress(const InetAddress& other);
    InetAddress(InetAddress&& other) noexcept;
    InetAddress& operator=(const InetAddress& other);
    InetAddress& operator=(InetAddress&& other) noexcept;
    static InetAddress getByName(const std::string& host);
    static std::vector<InetAddress> getAllByName(const std::string& host);
    static std::string getHostName(const std::string& ip);
    
    std::string getIP() const {return ip_;}
    uint16_t getPort() const {return port_;}
    std::string getHost() const {return host_;}
    InetFamily getFamilt() const {return family_;}
    
private:
    std::string ip_;
    std::string host_;
    uint16_t port_;
    InetFamily family_; // 1=IPv4, 2=IPv6
};

#endif //NETKIT_SOCKETADDR_H
