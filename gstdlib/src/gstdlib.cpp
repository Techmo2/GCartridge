/** This file contains the implementations for the gstdlib library.
 *  For more information about each function, see the header file.
 *  Author: Bradly Tillmann (Techmo)
 *  Last modified: 7/27/18
 */

#include "gstdlib.h"

namespace gstd {
	namespace console {
		void PrintC(const char * msg, ...)
		{
			Msg((const tchar*)(msg + '\n'));
		}

		void PrintC(std::string & msg, ...)
		{
			Msg((const tchar*)(msg + std::string("\n")).c_str());
		}

		void PrintC(const char * msg, Color & c)
		{
			ConColorMsg(c, msg);
		}

		void PrintC(std::string & msg, Color & c)
		{
			ConColorMsg(c, msg.c_str());
		}
	}

	template<typename T>
	std::string formstring(T t) {
		return std::string(t);
	}

	template<typename T, typename... Others>
	std::string formstring(T t, Others... others) {
		return std::string(t) + formstring(others...);
	}

	namespace game {
		void RunCommand(lua_State* state, const char * cmd)
		{
			state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			state->luabase->GetField(-1, "RunConCommand");
			state->luabase->PushString(cmd);
			state->luabase->Call(1, 0); // Call with 1 arg, expecting 0 return value
			state->luabase->Pop();
		}

		void RunLua(lua_State * state, const char * lua)
		{
			state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			state->luabase->GetField(-1, "RunString");
			state->luabase->PushString(lua);
			state->luabase->Call(1, 0); // Call with 1 arg, expecting 0 return value
			state->luabase->Pop();
		}

		void Hook(lua_State * state, const char * hook, const char * name, GarrysMod::Lua::CFunc func)
		{
			state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			state->luabase->GetField(-1, "hook");
			state->luabase->GetField(-1, "Add");
			state->luabase->PushString(hook);
			state->luabase->PushString(name);
			state->luabase->PushCFunction(func);
			state->luabase->Pop();
		}

		void RegisterFunction(lua_State * state, const char * name, GarrysMod::Lua::CFunc func)
		{
			state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			state->luabase->PushString(name);
			state->luabase->PushCFunction(func);
			state->luabase->SetTable(-3);
			state->luabase->Pop();
		}

		void PrintError(lua_State * state, const char * error)
		{
			state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			state->luabase->GetField(-1, "ErrorNoHalt");
			state->luabase->PushString(error);
			state->luabase->Call(1, 0);
			state->luabase->Pop();
		}

		void ThrowError(lua_State * state, const char * error) {
			state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			state->luabase->GetField(-1, "error");
			state->luabase->PushString(error);
			state->luabase->Call(1, 0);
			state->luabase->Pop();
		}
	}

	namespace chat {
		void Broadcast(lua_State * state, const char * msg)
		{
			state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			state->luabase->GetField(-1, "PrintMessage"); // Get the function field from lua
			state->luabase->PushNumber(3); // Push a function parameter to the global stack. Print to game chat and console, from the Garry's mod HUD enumerations (3 = chat + console)
			state->luabase->PushString(msg); // Push the string to the global stack
			state->luabase->Call(2, 0); // Call with 2 arguments, expecting 0 return value
			state->luabase->Pop(); // Pop the values from the lua stack
		}
	}
}
