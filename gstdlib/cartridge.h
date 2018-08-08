#pragma once
#ifndef CARTRIDGE_h
#define CARTRIDGE_h

#include <GarrysMod\Lua\Interface.h>

#ifdef _WIN32
#define  DLL_EXPORT extern "C" __declspec( dllexport )
#else
#define DLL_EXPORT	extern "C" __attribute__((visibility("default")))	
#endif

#define Cartridge(name) DLL_EXPORT const char* _module_name = name;
#define Start() DLL_EXPORT int _CartridgeStart(lua_State* state)
#define Stop() DLL_EXPORT int _CartridgeStop(lua_State* state)

#endif