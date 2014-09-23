#include <iostream>
#include <cstdio>
#include <string>
#include <memory>

#include <lua.hpp>

#include "windows.hpp"
#include "lua_registering.hpp"


void RunLua(const std::string &fileName);

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	int argc = __argc;
	char **argv = __argv;

	if(argc == 2 && std::string(argv[1]) == "-i")
	{
		std::cerr << "Interactive mode is not yet available\n";
	}
	else if(argc == 2)
	{
		RunLua(argv[1]);
	}
	else if(argc == 3 && std::string(argv[1]) == "-c")
	{
		// open a console window for standard output
		AllocConsole();
		std::FILE *stream;
		freopen_s(&stream, "CONOUT$", "wb", stdout);
		freopen_s(&stream, "CONOUT$", "wb", stderr);
		RunLua(argv[2]);
		system("PAUSE"); // TODO: replace
	}
	else if(argc == 3 && std::string(argv[1]) == "-l")
	{
		// open a log file for standard output
		std::cerr << "Log files are not available yet\n";
	}
	else
	{
		std::cerr << "Unknown combination of command line arguments\n";
	}
	
	return 0;
}

void RunLua(const std::string &fileName)
{
	// start a new lua state using RAII
	auto deleter = [](lua_State* p){ lua_close(p); };
	std::unique_ptr<lua_State,decltype(deleter)> L(luaL_newstate(), deleter);
	
	// use the stardard lua libraries
	luaL_openlibs(L.get());

	// register our own functions
	RegisterLuaClipboard(L.get());
	RegisterLuaSleep(L.get());
	RegisterLuaKeys(L.get());
	RegisterLuaKeyboard(L.get());
	
	// open and run the script file
	if(luaL_dofile(L.get(), fileName.c_str()))
	{
		std::cerr << "Error: " << lua_tostring(L.get(), -1) << '\n';
	}
}
