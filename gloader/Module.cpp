#define GMMODULE
#include "GarrysMod/Lua/Interface.h"
#include "Loader.h"
#include "cbase.h"
#include "io.h"
#include "eifaceV21.h"
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>

#define GLOADER_VERSION "1.0"
#define COLOR_LIGHT_BLUE Color(100, 100, 255, 255)
#define COLOR_CYAN Color(0, 255, 255, 255)
#define COLOR_ORANGE Color(255, 100, 0, 255)
#define COLOR_RED Color(255, 0, 0, 255)
#define COLOR_WHITE Color(255, 255, 255, 255)

using namespace GarrysMod::Lua;

#ifdef _WIN32
#define  DLL_EXPORT extern "C" __declspec( dllexport )
#else
#define DLL_EXPORT	extern "C" __attribute__((visibility("default")))	
#endif

std::vector<Cartridge> cartridges;
LoaderConfig config;
bool enabled;

void GetCartridgePaths(std::vector<std::string> &paths) {
	namespace fs = std::filesystem;
	fs::path directory("./cartridges");
	fs::directory_iterator iterator(directory), end;

	for (; iterator != end; iterator++) {
		if (iterator->path().extension().compare(".ctg") == 0) {
			paths.push_back(iterator->path().filename().string());
		}
	}
}

DLL_EXPORT int gmod13_open(lua_State* state) {

	ConColorMsg(COLOR_LIGHT_BLUE, ("////////////////\n" + std::string("/ GLoader v") + GLOADER_VERSION + " /\n////////////////\n").c_str());
	enabled = true;

	ConColorMsg(COLOR_CYAN, "Loading config\n");
	int cfg_err = ParseConfig("gloader.cfg", config);

	if (cfg_err == 1) {
		ConColorMsg(COLOR_RED, "Error loading config file, cartridges disabled\n");
		enabled = false;
	}

	// Make sure required directories exist
	CreateDirectory("cartridges", NULL);
	CreateDirectory("profiles", NULL);

	if (enabled) {
		ConColorMsg(COLOR_CYAN, "\nLoading cartridges\n");
		std::vector<std::string> paths;
		GetCartridgePaths(paths);

		int c_count = 0;
		for (std::string path : paths) {
			ConColorMsg(COLOR_WHITE, ("Loading: " + path + '\n').c_str());
			cartridges.push_back(Cartridge());
			LoadCartridge("cartridges/" + path, cartridges[c_count]);
			cartridges[c_count].name = path;
			c_count++;
		}

		ConColorMsg(COLOR_CYAN, "\nInitializing Cartridges\n\n");
		for (Cartridge cartridge : cartridges) {
			//ConColorMsg(COLOR_WHITE, ("Initializing: " + cartridge.name + '\n').c_str());
			if (cartridge.loaded) {
				cartridge.hFunc_INIT(state);
			}
			else {
				ConColorMsg(COLOR_RED, ("Error: '" + cartridge.name + "' is invalid\n").c_str());
			}
		}
	}
	return 0;
}

DLL_EXPORT int gmod13_close(lua_State* state) {
	if (enabled) {
		ConColorMsg(COLOR_CYAN, "Stopping cartridges\n");
		for (Cartridge cartridge : cartridges) {
			if (cartridge.loaded) {
				cartridge.hFunc_STOP(state);
			}
			FreeLibrary(cartridge.hLib);
		}
	}
	return 0;
}