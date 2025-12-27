/*
 * Copyright (c) 2025 Netkit Project
 * Licensed under the Apache License, Version 2.0
 */

#include "hilog_helper.h"
#include <cstdarg>

// 初始化静态成员变量
unsigned int HiLogHelper::globalDomain_ = LOG_DOMAIN;
const char* HiLogHelper::globalTag_ = LOG_TAG;

void HiLogHelper::SetGlobalTag(const char* tag) {
    if (tag != nullptr) {
        globalTag_ = tag;
    }
}

void HiLogHelper::SetGlobalDomain(unsigned int domain) {
    // 确保域值在有效范围内（0x0 - 0xFFFF）
    globalDomain_ = domain & 0xFFFF;
}

void HiLogHelper::SetMinLogLevel(LogLevel level) {
    OH_LOG_SetMinLogLevel(level);
}

bool HiLogHelper::IsLoggable(LogLevel level) {
    return OH_LOG_IsLoggable(globalDomain_, globalTag_, level);
}

void HiLogHelper::PrintLog(LogLevel level, const char* tag, const char* fmt, va_list args) {
    const char* actualTag = (tag != nullptr) ? tag : globalTag_;
    OH_LOG_VPrint(LOG_APP, level, globalDomain_, actualTag, fmt, args);
}

// Debug级别日志
void HiLogHelper::Debug(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PrintLog(LOG_DEBUG, tag, fmt, args);
    va_end(args);
}


// Info级别日志
void HiLogHelper::Info(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PrintLog(LOG_INFO, tag, fmt, args);
    va_end(args);
}

// Warn级别日志
void HiLogHelper::Warn(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PrintLog(LOG_WARN, tag, fmt, args);
    va_end(args);
}


// Error级别日志
void HiLogHelper::Error(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PrintLog(LOG_ERROR, tag, fmt, args);
    va_end(args);
}


// Fatal级别日志
void HiLogHelper::Fatal(const char* tag, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    PrintLog(LOG_FATAL, tag, fmt, args);
    va_end(args);
}
