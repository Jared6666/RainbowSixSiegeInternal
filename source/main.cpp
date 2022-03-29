#include <iostream>
#include <thread>
#include <memory>
#include <windows.h>
#include "../headers/features/features.hpp"

using namespace std;

void start() {

    globals::game.get();
    std::thread(features::outlines).detach();
    std::thread(features::nospread).detach();
}

BOOL APIENTRY DllMain
(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(&start).detach();
        break;
    }
    return TRUE;
}