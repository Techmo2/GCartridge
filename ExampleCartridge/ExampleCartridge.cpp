#include <iostream>
#include "cartridge.h"

Cartridge("Example Cartridge v1.0")

Start() {
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Push the global table
	LUA->GetField(-1, "print"); // Get the print function
	LUA->PushString("Hello from example cartridge"); // Push our argument
	LUA->Call(1, 0); // Call the function
	LUA->Pop(); // Pop the global table off the stack
	return 0;
}

Stop() {
	return 0;
}