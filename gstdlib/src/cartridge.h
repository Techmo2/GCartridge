#pragma once
#ifndef CARTRIDGE_h
#define CARTRIDGE_h
#define GMMODULE

#include <GarrysMod\Lua\Interface.h>

#ifdef _WIN32
#define  DLL_EXPORT extern "C" __declspec( dllexport )
#else
#define DLL_EXPORT	extern "C" __attribute__((visibility("default")))	
#endif

// Some helpful preprocessor macros to make life easier

#define ReturnBool(value) state->luabase->PushBool(value); return 1
#define ReturnString(value) state->luabase->PushString(value); return 1
#define ReturnNumber(value) state->luabase->PushNumber(value); return 1

#define Error(msg) gstd::game::PrintError(state, msg)
#define FatalError(msg) gstd::game::ThrowError(state, msg)

#define Type GarrysMod::Lua::Type

#define Function(name) int name(lua_State* state)
#define RegisterFunction(func) gstd::game::RegisterFunction(state,#func,func)
#define print(msg) gstd::console::PrintC(msg)
#define Cartridge(name) DLL_EXPORT const char* _module_name = name;
#define Start() DLL_EXPORT int _CartridgeStart(lua_State* state)
#define Stop() DLL_EXPORT int _CartridgeStop(lua_State* state)


#endif