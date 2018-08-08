#include "Loader.h"

#define CONFIG_OPTION_VALUE_ERROR(_cfg_opt, _line_num) std::cout << "(line " << _line_num << ") " << "Error loading config file, invalid value '" << _cfg_opt.value << "' for option '" << _cfg_opt.name << "'" << std::endl
#define CONFIG_OPTION_ERROR(_cfg_opt, _line_num) std::cout << "(line " << _line_num << ") " << "Error loading config file, invalid option '" << _cfg_opt.name << "'" << std::endl

int LoadCartridge(std::string path, Cartridge & c_out)
{
	HMODULE hLib = NULL;

	hLib = LoadLibrary(TEXT(path.c_str()));

	if (hLib == NULL)
		return 1;

	c_out.hFunc_INIT = (CTGFunc)GetProcAddress(hLib, "_CartridgeStart");
	c_out.hFunc_STOP = (CTGFunc)GetProcAddress(hLib, "_CartridgeStop");
	c_out.hLib = hLib;

	if (c_out.hFunc_INIT == NULL || c_out.hFunc_STOP == NULL)
		return 1;

	c_out.loaded = true;
	return 0;
}

int ParseConfig(std::string path, LoaderConfig & out_cfg)
{
	std::vector<ConfigOption> cfg;
	std::ifstream config_file(path);
	LoaderConfig tmp_cfg;

	unsigned int line_num = 0;

	while (config_file.is_open()) {

		std::string line;
		while (getline(config_file, line)) {

			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
			if (line[0] == '#' || line.empty())
				continue;

			size_t del_pos = line.find("=");
			std::string name = line.substr(0, del_pos);
			std::string value = line.substr(del_pos + 1);
			cfg.push_back(ConfigOption(name, value));
		}
	}

	for (ConfigOption option : cfg) {

		if (option.name.compare("Enabled") == 0) {

			if (option.value.compare("true") == 0)
				tmp_cfg.enabled = true;

			else if (option.value.compare("false") == 0)
				tmp_cfg.enabled = false;

			else {
				CONFIG_OPTION_VALUE_ERROR(option, line_num);
				return 1;
			}
		}

		else if (option.value.compare("ListMode") == 0) {

			if (option.name.compare("whitelist") == 0)
				tmp_cfg.list_mode = WHITELIST;

			else if (option.name.compare("blacklist") == 0)
				tmp_cfg.list_mode = BLACKLIST;

			else {
				CONFIG_OPTION_VALUE_ERROR(option, line_num);
				return 1;
			}
		}

		else {
			CONFIG_OPTION_ERROR(option, line_num);
			return 1;
		}
	}

	out_cfg = tmp_cfg;
	return 0;
}
