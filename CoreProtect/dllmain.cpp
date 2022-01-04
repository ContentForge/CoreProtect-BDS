#include "pch.h"
#pragma comment(lib, "C:/Users/KocTu4eK/Desktop/SDK/Lib/bedrock_server_api.lib")
#pragma comment(lib, "C:/Users/KocTu4eK/Desktop/SDK/Lib/bedrock_server_var.lib")
#pragma comment(lib, "C:/Users/KocTu4eK/Desktop/SDK/Lib/SymDBHelper.lib")
#pragma comment(lib, "C:/Users/KocTu4eK/Desktop/SDK/Lib/LiteLoader.lib")
#pragma comment(lib, "C:/Users/KocTu4eK/Desktop/SDK/Lib/sqlite3-64.lib")


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        LL::registerPlugin("CoreProtect", "", LL::Version(0, 0, 1));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


extern void plugin();

extern "C"
{
    _declspec(dllexport) void onPostInit()
    {
        std::ios::sync_with_stdio(false);
        plugin();
    }
}