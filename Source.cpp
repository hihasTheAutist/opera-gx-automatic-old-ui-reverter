#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <shellapi.h>
#include <fstream>
#include <string>
#include "json.hpp"
//includes defines technical shits

using json = nlohmann::json;
//download "json.hpp" from https://github.com/nlohmann/json/releases, i used version 3.12.0

#define WM_TRAYICON (WM_USER + 1)
#define TRAY_UID 1001
#define ID_EXIT 9001

NOTIFYICONDATAA nid = { 0 };
HMENU hMenu;
//tray ui shits

const std::string operaExe = "opera.exe";

std::string GetAppDataPath() {
    char* buffer = nullptr;
    size_t len = 0;
    errno_t err = _dupenv_s(&buffer, &len, "APPDATA");
    std::string result;
    if (err == 0 && buffer != nullptr) {
        result = std::string(buffer);
        free(buffer);
    }
    return result;
}

const std::string configPath = GetAppDataPath() + "\\Opera Software\\Opera GX Stable\\Local State";
// path to the shit file

bool hasPatched = false;
//sanity check
bool IsOperaRunning() {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(snapshot, &entry)) {
        do {
#ifdef UNICODE
            // If UNICODE (i dunno preference thing, do whatever ya want with it peeps) use wcsicmp with szExeFile as wchar_t[]
            if (_wcsicmp(entry.szExeFile, L"opera.exe") == 0) {
#else
            // ANSI version (for preferences)
            if (_stricmp(entry.szExeFile, "opera.exe") == 0) {
#endif
                CloseHandle(snapshot);
                return true;
            }
            } while (Process32Next(snapshot, &entry));
        }
    CloseHandle(snapshot);
    return false;
    }

void PatchConfig() {
    try {
        std::ifstream in(configPath);
        if (!in.is_open()) return;

        json j;
        in >> j;
        in.close();

        if (j.contains("gxx_flags")) {
            j["gxx_flags"]["enabled"] = false;
            j["gxx_flags"]["migrated"] = false;

            std::ofstream out(configPath);
            out << j.dump(4);
            out.close();
        }
    }
    catch (...) {
        // ignore (optionally add logs if someone wants
    }
}
//the config has been corrected at this point

DWORD WINAPI MonitorOpera(LPVOID) {
    while (true) {
        bool isRunning = IsOperaRunning();

        if (!isRunning && !hasPatched) {
            PatchConfig();
            hasPatched = true;
        }

        if (isRunning && hasPatched) {
            hasPatched = false;
        }

        Sleep(500);
    }

    return 0;
}
//monitoring of operagx process, tried to make it lightweight, if any other dev has better optimizations ideas feel free to edit

void AddTrayIcon(HWND hwnd) {
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = TRAY_UID;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_INFORMATION));
    strcpy_s(nid.szTip, sizeof(nid.szTip), "Opera GX Correcter");
    Shell_NotifyIconA(NIM_ADD, &nid);
}

void RemoveTrayIcon() {
    Shell_NotifyIconA(NIM_DELETE, &nid);
}

void ShowContextMenu(HWND hwnd) {
    POINT pt;
    GetCursorPos(&pt);
    SetForegroundWindow(hwnd);
    TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
    PostMessage(hwnd, WM_NULL, 0, 0);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_TRAYICON:
        if (lParam == WM_RBUTTONUP) {
            ShowContextMenu(hwnd);
        }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_EXIT) {
            RemoveTrayIcon();
            PostQuitMessage(0);
        }
        break;
    case WM_DESTROY:
        RemoveTrayIcon();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    const char CLASS_NAME[] = "OperaGXCorrecterWindowClass";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassA(&wc);
    HWND hwnd = CreateWindowExA(0, CLASS_NAME, "OperaGXCorrecter", 0,
        0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);

    hMenu = CreatePopupMenu();
    AppendMenuA(hMenu, MF_STRING, ID_EXIT, "Exit");

    AddTrayIcon(hwnd);

    CreateThread(NULL, 0, MonitorOpera, NULL, 0, NULL);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
