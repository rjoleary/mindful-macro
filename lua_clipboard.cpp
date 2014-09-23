#include <string>

#include <lua.hpp>

#include <Windows.h>


int Lua_clipboard_gettext(lua_State *L);


void RegisterLuaClipboard(lua_State *L)
{
	lua_createtable(L, 0, 1);
	int clipboardTable = lua_gettop(L);
	lua_pushcfunction(L, Lua_clipboard_gettext);
	lua_setfield(L, clipboardTable, "gettext");
	lua_setglobal(L, "clipboard");
}


int Lua_clipboard_gettext(lua_State *L)
{
	std::string result;
	if(OpenClipboard(NULL))
	{
		result = reinterpret_cast<const char*>(GetClipboardData(CF_TEXT));
		CloseClipboard();
	}
	lua_pushstring(L, result.c_str());
	return 1;
}
