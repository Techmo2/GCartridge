/** This file contains the declarations for the gstdlib library.
 *  Author: Bradly Tillmann (Techmo)
 *  Last modified: 7/27/18
 */

#define GMMODULE

#ifndef GSTDSLIB_h
#define GSTDLIB_h

#include <GarrysMod\Lua\Interface.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "colors.h"
#include "cbase.h"
#include "io.h"
#include "eifaceV21.h"

// To load various game dlls as interfaces
#define LOADINTERFACE(_module_, _version_, _out_) Sys_LoadInterface(_module_, _version_, NULL, reinterpret_cast<void**>(& _out_ ))

namespace gstd {
	namespace console {
		/* Function: PrintC

		   Prints unformatted text to the console.
		   
		   Parameters:

			   msg - The message to print to the console.

		   Example:
		       
			   --- Code
			   PrintC("Plugin loading complete");
			   ---
		*/
		void PrintC(const char* msg, ...);

		/* Function: PrintC

		   Prints unformatted text to the console.

		   Parameters:

			   msg - The message to print to the console.

		   Example:
		       
			   --- Code
			   PrintC("Plugin loading complete");
			   ---
		*/
		void PrintC(std::string &msg, ...);

		/* Function: PrintC

		   Prints colored text to the console.

		   Parameters:

		       msg - The message to print to the console.
			   c - The color to use for the message.

		   Example:

			   --- Code
			   PrintC("Plugin loading complete", COLOR_RED);
			   PrintC("Custom colors are supported", Color(255, 150, 0, 255));
			   ---

		   See Also:

		       <Color>
		*/
		void PrintC(const char* msg, Color &c);

		/* Function: PrintC

		   Prints colored text to the console.

		   Parameters:

		       msg - The message to print to the console.
		       c - The color to use for the message.

		   Example:

			   --- Code
			   PrintC("Plugin loading complete", COLOR_RED);
			   PrintC("Custom colors are supported", Color(255, 150, 0, 255));
			   ---

		   See Also:

		       <Color>
		*/
		void PrintC(std::string &msg, Color &c);
	}

	template<typename T>
	std::string formstring(T t);

	/* Function: formstring

	   Combines multiple values into a single string.

	   Parameters:

	       t - The first string on which to add other strings.
		   others - A set of strings to add to the first.

	   Example:
	       
		   --- Code
		   PrintC(formstring("Player ", player_name, " has joined team ", team_number));
		   ---
	*/
	template<typename T, typename... Others>
	std::string formstring(T t, Others... others);

	namespace game {
		/* Function: RunCommand

		   Executes a console command.

		   Parameters:

		       state - The lua state to use for execution.
			   cmd - The string to use as the command.

		   Example:

			   --- Code
			   RunCommand(LUA, "npc_create npc_citizen");
			   ---
		*/
		void RunCommand(lua_State* state, const char* cmd);

		/* Function: RunLua

		   Compiles a string into lua bytecode, then executes it.

		   Parameters:

		       state - The lua state to use for execution.
		       lua - The string to be executed.

		   Example:

			   --- Code
			   RunLua(LUA, "Msg('sending a message from lua')");
			   ---
		*/
		void RunLua(lua_State* state, const char* lua); // Compiles a lua string, then executes it
		
		 /* Function: Hook

		    Hooks a CFunc into a game event.

		    Parameters:

		        state - The lua state to use for execution.
		        hook - The name of the hook to hook into.
				name - The name of the custom handler we are creating.
				func - The function to call when the hook is called.

		    Example:

				--- Code
				Hook(LUA, "PlayerSpawn", "awesome_spawnhandler", PlayerSpawnHandler);
				---
		 */
		void Hook(lua_State* state, const char* hook, const char* name, GarrysMod::Lua::CFunc func);
		
		/* Function: RegisterFunction

		   Registers a c++ function to make it accessible from within Garrys Mod lua.

		   Parameters:

		       state - The lua state to use for execution.
		       name - The name to use for the function within lua.
			   func - The function to be used when the call is made from within lua.

		   Example:

			   --- Code
			   RegisterFunction(LUA, "KillAllPlayers", KillAllPlayers);
			   ---
		*/
		void RegisterFunction(lua_State* state, const char* name, GarrysMod::Lua::CFunc func);
	}

	namespace chat {
		/* Function: Broadcast

		   Broadcasts a message to all players on the server. Will show up in chat, and in the console.

		   Parameters:

		       state - The lua state to use for execution.
		       msg - The message to broadcast.

		   Example:

			   --- Code
			   Broadcast(LUA, "A new event will begin in 30 seconds.");
			   ---
		*/
		void Broadcast(lua_State* state, const char* msg);
	}
}

#endif