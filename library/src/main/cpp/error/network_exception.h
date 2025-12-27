//
// Created on 2025/12/27.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef NETKIT_NETWORK_EXCEPTION_H
#define NETKIT_NETWORK_EXCEPTION_H
// network_exception.h
#pragma once

#include <stdexcept>
#include <string>
#include <netdb.h>

// 类声明
class NetworkException : public std::runtime_error {
public:
    // 枚举类型声明    
    enum Type {
        DNS_RESOLUTION,  // DNS 解析失败
        CONNECTION,      // 连接失败
        TIMEOUT,         // 超时
        INVALID_PARAM,   // 参数错误
        UNKNOWN          // 未知错误
    };

    // 构造函数声明（只写函数头，不写函数体）
    NetworkException(Type type, int code, const std::string& message);

    // 成员函数声明（只写函数头）
    Type get_type() const;
    int get_error_code() const;

private:
    Type type_;
    int error_code_;
};

// 工具函数声明
inline NetworkException::Type map_error_type(int code){
    switch (code) {
        case EAI_NONAME: return NetworkException::DNS_RESOLUTION;
        case EAI_FAIL:   return NetworkException::DNS_RESOLUTION;
        case EAI_SERVICE: return NetworkException::INVALID_PARAM;
        case EAI_ADDRFAMILY: return NetworkException::INVALID_PARAM;
        case EAI_AGAIN:  return NetworkException::TIMEOUT;
        default:         return NetworkException::UNKNOWN;
    }
}

#endif //NETKIT_NETWORK_EXCEPTION_H
