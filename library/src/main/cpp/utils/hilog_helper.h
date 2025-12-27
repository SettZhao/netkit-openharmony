/*
 * Copyright (c) 2025 Netkit Project
 * Licensed under the Apache License, Version 2.0
 */

#ifndef HILOG_HELPER_H
#define HILOG_HELPER_H

#include <hilog/log.h>

/**
 * 日志助手类
 * 提供便捷的日志打印接口，封装鸿蒙HiLog
 */
class HiLogHelper {
public:
    /**
     * 设置全局日志标签
     * @param tag 日志标签
     */
    static void SetGlobalTag(const char* tag);
    
    /**
     * 设置全局日志域
     * @param domain 日志域
     */
    static void SetGlobalDomain(unsigned int domain);
    
    /**
     * 设置日志级别
     * @param level 日志级别
     */
    static void SetMinLogLevel(LogLevel level);
    
    /**
     * 检查指定级别的日志是否可以输出
     * @param level 日志级别
     * @return true表示可以输出，false表示不可以
     */
    static bool IsLoggable(LogLevel level);
    
    /**
     * 打印DEBUG级别日志
     * @param tag 日志标签（可选，为nullptr则使用全局标签）
     * @param fmt 格式化字符串
     * @param ... 可变参数
     */
    static void Debug(const char* tag, const char* fmt, ...);
    
    /**
     * 打印INFO级别日志
     * @param tag 日志标签（可选，为nullptr则使用全局标签）
     * @param fmt 格式化字符串
     * @param ... 可变参数
     */
    static void Info(const char* tag, const char* fmt, ...);

    /**
     * 打印WARN级别日志
     * @param tag 日志标签（可选，为nullptr则使用全局标签）
     * @param fmt 格式化字符串
     * @param ... 可变参数
     */
    static void Warn(const char* tag, const char* fmt, ...);

    /**
     * 打印ERROR级别日志
     * @param tag 日志标签（可选，为nullptr则使用全局标签）
     * @param fmt 格式化字符串
     * @param ... 可变参数
     */
    static void Error(const char* tag, const char* fmt, ...);

    /**
     * 打印FATAL级别日志
     * @param tag 日志标签（可选，为nullptr则使用全局标签）
     * @param fmt 格式化字符串
     * @param ... 可变参数
     */
    static void Fatal(const char* tag, const char* fmt, ...);


private:
    static unsigned int globalDomain_;
    static const char* globalTag_;
    /**
     * 内部日志打印函数
     * @param level 日志级别
     * @param tag 日志标签
     * @param fmt 格式化字符串
     * @param args 可变参数列表
     */
    static void PrintLog(LogLevel level, const char* tag, const char* fmt, va_list args);
};

// 便捷宏定义
#define LOGD(...) HiLogHelper::Debug("NetKit", __VA_ARGS__)
#define LOGI(...) HiLogHelper::Info("NetKit", __VA_ARGS__)
#define LOGW(...) HiLogHelper::Warn("NetKit", __VA_ARGS__)
#define LOGE(...) HiLogHelper::Error("NetKit", __VA_ARGS__)
#define LOGF(...) HiLogHelper::Fatal("NetKit", __VA_ARGS__)

// 带标签的便捷宏
#define LOGD_TAG(tag, ...) HiLogHelper::Debug(tag, __VA_ARGS__)
#define LOGI_TAG(tag, ...) HiLogHelper::Info(tag, __VA_ARGS__)
#define LOGW_TAG(tag, ...) HiLogHelper::Warn(tag, __VA_ARGS__)
#define LOGE_TAG(tag, ...) HiLogHelper::Error(tag, __VA_ARGS__)
#define LOGF_TAG(tag, ...) HiLogHelper::Fatal(tag, __VA_ARGS__)

#endif // HILOG_HELPER_H
