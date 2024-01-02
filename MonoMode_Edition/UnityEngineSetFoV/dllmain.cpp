// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h> 
#include <format>
#include "UnityResolveByIssuimo/UnityResolve.hpp"
#include "CMDFix.h"
#include <exception>
using I = UnityResolve;
using IM = UnityResolve::Method;
using IC = UnityResolve::Class;
using IT = UnityResolve::Type;
using IF = UnityResolve::Field;
using IA = UnityResolve::Assembly;
using II = UnityResolve::UnityType;
DWORD WINAPI ThreadZ() 
{
    HMODULE mod = GetModuleHandleA("mono-2.0-bdwgc.dll");
    UnityResolve::Init(mod); //It is Mono Library(mono for Unity3D is Fully Free)
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    AllocConsole();
    SetConsoleTitleA("UnityEngineSetFoV by RiritoNinigaya");
    PrintCMD("Welcome to my New DLL Library for Set FoV or Get FoV Value... Made by RiritoNinigaya");
    for (;;) {
        if (GetAsyncKeyState(VK_DELETE) & 1) {
            auto CoreModule = UnityResolve::Get("UnityEngine.CoreModule.dll");
            auto camerafunction = CoreModule->Get("Camera", "UnityEngine");
            auto instance = UnityResolve::UnityType::Camera::GetMain();
            float fov = camerafunction->GetValue<float>(instance, "fieldOfView");
            std::string formattio = std::format("{}", fov);
            std::string str_fov = (std::string)"FoV Value: " + formattio.c_str();
            PrintCMD(str_fov.c_str());
        }
        else if (GetAsyncKeyState(VK_INSERT) & 1) {
            auto CoreModule = UnityResolve::Get("UnityEngine.CoreModule.dll");
            auto camerafunction = CoreModule->Get("Camera", "UnityEngine");
            auto instance = UnityResolve::UnityType::Camera::GetMain();
            camerafunction->SetValue<float>(instance, "fieldofView", 120.F);
        }
        
    }
    return TRUE;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadZ, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

