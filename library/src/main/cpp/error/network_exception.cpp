//
// Created on 2025/12/27.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

// network_exception.cpp
#include "network_exception.h"  // 包含自己的头文件

// 构造函数实现
NetworkException::NetworkException(Type type, int code, const std::string& message)
    : std::runtime_error(message),  // 调用父类构造函数
      type_(type),                  // 初始化成员
      error_code_(code) {}

// get_type() 函数实现
NetworkException::Type NetworkException::get_type() const {
    return type_;
}

// get_error_code() 函数实现
int NetworkException::get_error_code() const {
    return error_code_;
}
