#pragma once

#ifndef LOADER_h
#define LOADER_h

#include <array>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include <conio.h>
#include <GarrysMod\Lua\Interface.h>

typedef int(*CTGFunc)(lua_State*);

enum ListMode {
	WHITELIST,
	BLACKLIST
};

struct Cartridge {
	bool loaded = false;
	CTGFunc hFunc_INIT;
	CTGFunc hFunc_STOP;
	HMODULE hLib;
	std::string name;

	Cartridge(CTGFunc _hFunc_INIT, CTGFunc _hFunc_STOP, HMODULE _hLib) {
		hFunc_INIT = _hFunc_INIT;
		hFunc_STOP = _hFunc_STOP;
		hLib = _hLib;
	}

	Cartridge() {
		hFunc_INIT = NULL;
		hFunc_STOP = NULL;
		hLib = NULL;
	}
};

struct ConfigOption {
	std::string name;
	std::string value;

	ConfigOption(std::string _name, std::string _value) {
		name = _name;
		value = _value;
	}
};

struct LoaderConfig {
	bool enabled;
	ListMode list_mode;
	std::vector<std::string> cartridge_blacklist;
	std::vector<std::string> cartridge_whitelist;
};

int LoadCartridge(std::string path, Cartridge & c_out);
int ParseConfig(std::string path, LoaderConfig & out_cfg);

#endif
