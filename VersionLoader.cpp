#include <windows.h>
#include <libloaderapi.h>
#include <tchar.h>

static HMODULE hOriginal = NULL;

#define FORWARD_PROC(DLLNAME, NAME, RETTYPE, ARGS, ARG_NAMES)              \
extern "C" RETTYPE WINAPI My_##NAME ARGS {                        \
    LoadOriginalDll(DLLNAME);                                            \
    using FuncType = RETTYPE (WINAPI*) ARGS;                      \
    static FuncType func = (FuncType)GetProcAddress(hOriginal, #NAME); \
    return func ARG_NAMES;                                        \
}                                                                 \
__pragma(comment(linker, "/export:" #NAME "=My_" #NAME))

void LoadOriginalDll(LPCWSTR dllName) {
    if (hOriginal) return;

    wchar_t systemPath[MAX_PATH];
    GetSystemDirectoryW(systemPath, MAX_PATH);
    wcscat_s(systemPath, L"\\");
    wcscat_s(systemPath, dllName);
    wcscat_s(systemPath, L".dll");
    hOriginal = LoadLibraryW(systemPath);
}

FORWARD_PROC(L"version",GetFileVersionInfoA, BOOL, (LPCSTR a, DWORD b, DWORD c, LPVOID d), (a,b,c,d))
FORWARD_PROC(L"version",GetFileVersionInfoByHandle, BOOL, (void* a, DWORD b, DWORD c, LPVOID d), (a,b,c,d))
FORWARD_PROC(L"version",GetFileVersionInfoExA, BOOL, (DWORD a, LPCSTR b, DWORD c, DWORD d, LPVOID e), (a,b,c,d,e))
FORWARD_PROC(L"version",GetFileVersionInfoExW, BOOL, (DWORD a, LPCWSTR b, DWORD c, DWORD d, LPVOID e), (a,b,c,d,e))
FORWARD_PROC(L"version",GetFileVersionInfoSizeA, DWORD, (LPCSTR a, LPDWORD b), (a,b))
FORWARD_PROC(L"version",GetFileVersionInfoSizeExA, DWORD, (DWORD a, LPCSTR b, LPDWORD c), (a,b,c))
FORWARD_PROC(L"version",GetFileVersionInfoSizeExW, DWORD, (DWORD a, LPCWSTR b, LPDWORD c), (a,b,c))
FORWARD_PROC(L"version",GetFileVersionInfoSizeW, DWORD, (LPCWSTR a, LPDWORD b), (a,b))
FORWARD_PROC(L"version",GetFileVersionInfoW, BOOL, (LPCWSTR a, DWORD b, DWORD c, LPVOID d), (a,b,c,d))
FORWARD_PROC(L"version",VerFindFileA, DWORD, (DWORD a, LPCSTR b, LPCSTR c, LPCSTR d, LPSTR e, PUINT f, LPSTR g, PUINT h), (a,b,c,d,e,f,g,h))
FORWARD_PROC(L"version",VerFindFileW, DWORD, (DWORD a, LPCWSTR b, LPCWSTR c, LPCWSTR d, LPWSTR e, PUINT f, LPWSTR g, PUINT h), (a,b,c,d,e,f,g,h))
FORWARD_PROC(L"version",VerInstallFileA, DWORD, (DWORD a, LPCSTR b, LPCSTR c, LPCSTR d, LPCSTR e, LPCSTR f, LPSTR g, PUINT h), (a,b,c,d,e,f,g,h))
FORWARD_PROC(L"version",VerInstallFileW, DWORD, (DWORD a, LPCWSTR b, LPCWSTR c, LPCWSTR d, LPCWSTR e, LPCWSTR f, LPWSTR g, PUINT h), (a,b,c,d,e,f,g,h))
FORWARD_PROC(L"version",VerLanguageNameA, DWORD, (DWORD a, LPSTR b, DWORD c), (a,b,c))
FORWARD_PROC(L"version",VerLanguageNameW, DWORD, (DWORD a, LPWSTR b, DWORD c), (a,b,c))
FORWARD_PROC(L"version",VerQueryValueA, BOOL, (LPCVOID a, LPCSTR b, LPVOID* c, PUINT d), (a,b,c,d))
FORWARD_PROC(L"version",VerQueryValueW, BOOL, (LPCVOID a, LPCWSTR b, LPVOID* c, PUINT d), (a,b,c,d))


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        SetDefaultDllDirectories(
                LOAD_LIBRARY_SEARCH_SYSTEM32 |
                LOAD_LIBRARY_SEARCH_APPLICATION_DIR |
                LOAD_LIBRARY_SEARCH_USER_DIRS
        );
    }
    return TRUE;
}
