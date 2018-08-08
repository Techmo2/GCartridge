#include <iostream>
#include "gstdlib.h"
#include "cartridge.h"

Cartridge("Example Cartridge v1.0")

Start() {
	gstd::console::PrintC("Hello from Example Cartridge!\n", Color(255, 255, 255, 255));
	return 0;
}

Stop() {
	return 0;
}