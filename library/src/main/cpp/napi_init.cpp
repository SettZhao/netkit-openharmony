#include "napi/native_api.h"
#include "socket/dns.h"
#include "utils/hilog_helper.h"

static napi_value GetByName(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc < 1) {
        LOGE("GetByName: Invalid argument count, expected 2, got %{public}zu", argc);
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    // 获取第一个参数 (host)
    size_t hostLen = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &hostLen);
    char* hostBuffer = new char[hostLen + 1];
    napi_get_value_string_utf8(env, args[0], hostBuffer, hostLen + 1, &hostLen);
    std::string host(hostBuffer);
    delete[] hostBuffer;

    LOGD("GetByName called: host=%{public}s", host.c_str());

    try {
        auto addr = InetAddress::getByName(host);
        napi_value result;
        napi_create_string_utf8(env, addr.getIP().c_str(), NAPI_AUTO_LENGTH, &result);
        return result;
    } catch (const std::exception& e) {
        LOGE("GetByName failed: %{public}s", e.what());
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }
}

static napi_value GetAllByName(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc < 1) {
        LOGE("GetAllByName: Invalid argument count, expected 2, got %{public}zu", argc);
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    // 获取第一个参数 (host)
    size_t hostLen = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &hostLen);
    char* hostBuffer = new char[hostLen + 1];
    napi_get_value_string_utf8(env, args[0], hostBuffer, hostLen + 1, &hostLen);
    std::string host(hostBuffer);
    delete[] hostBuffer;

    LOGD("GetAllByName called: host=%{public}s", host.c_str());

    try {
        auto addrs = InetAddress::getAllByName(host);
        napi_value array = nullptr;
        napi_create_array(env, &array);
        for (size_t i = 0; i < addrs.size(); i++){
            napi_value element;
            const auto& addr = addrs[i]; // 使用引用避免拷贝
            napi_create_string_utf8(env, addr.getIP().c_str(), NAPI_AUTO_LENGTH, &element);
            napi_set_element(env, array, i, element);
        }
        return array;
    } catch (const std::exception& e) {
        LOGE("GetAllByName failed: %{public}s", e.what());
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }
}

static napi_value GetHostName(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc < 1) {
        LOGE("GetAllByName: Invalid argument count, expected 2, got %{public}zu", argc);
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }

    // 获取第一个参数 (host)
    size_t ipLen = 0;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &ipLen);
    char* ipBuffer = new char[ipLen + 1];
    napi_get_value_string_utf8(env, args[0], ipBuffer, ipLen + 1, &ipLen);
    std::string ip(ipBuffer);
    delete[] ipBuffer;

    LOGD("GetAllByName called: host=%{public}s", ip.c_str());

    try {
        auto host = InetAddress::getHostName(ip);
        napi_value result;
        napi_create_string_utf8(env, host.c_str(), NAPI_AUTO_LENGTH, &result);
        return result;
    } catch (const std::exception& e) {
        LOGE("GetAllByName failed: %{public}s", e.what());
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "getByName", nullptr, GetByName, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getAllByName", nullptr, GetAllByName, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getHostName", nullptr, GetHostName, nullptr, nullptr, nullptr, napi_default, nullptr },
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "library",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterLibraryModule(void)
{
    napi_module_register(&demoModule);
}
