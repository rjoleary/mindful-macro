#include <string>

#include <lua.hpp>

#include <Windows.h>


void RegisterLuaKeys(lua_State *L)
{
	lua_createtable(L, 0, 42);
	int keysTable = lua_gettop(L);
	auto AddKey = [&L, keysTable](std::string name, DWORD key)
	{
		lua_pushnumber(L, key);
		lua_setfield(L, keysTable, name.c_str());
	};

	AddKey("alt", VK_MENU);
	AddKey("lalt", VK_LMENU);
	AddKey("ralt", VK_RMENU);

	AddKey("ctrl", VK_CONTROL);
	AddKey("lctrl", VK_LCONTROL);
	AddKey("rctrl", VK_RCONTROL);

	AddKey("shift", VK_SHIFT);
	AddKey("lshift", VK_LSHIFT);
	AddKey("rshift", VK_RSHIFT);

	AddKey("enter", VK_RETURN);
	AddKey("backspace", VK_BACK);
	AddKey("tab", VK_TAB);

	AddKey("escape", VK_ESCAPE);
	AddKey("printscreen", VK_SNAPSHOT);
	AddKey("pause", VK_PAUSE);
	AddKey("break", VK_CANCEL);

	AddKey("insert", VK_INSERT);
	AddKey("9", VK_DELETE);
	AddKey("home", VK_HOME);
	AddKey("end", VK_END);
	AddKey("pageup", VK_PRIOR);
	AddKey("pagedown", VK_NEXT);

	AddKey("up", VK_UP);
	AddKey("down", VK_DOWN);
	AddKey("left", VK_LEFT);
	AddKey("right", VK_RIGHT);

	AddKey("capslock", VK_CAPITAL);
	AddKey("numlock", VK_NUMLOCK);
	AddKey("scrolllock", VK_SCROLL);

	AddKey("f1", VK_F1);
	AddKey("f2", VK_F2);
	AddKey("f3", VK_F3);
	AddKey("f4", VK_F4);
	AddKey("f5", VK_F5);
	AddKey("f6", VK_F6);
	AddKey("f7", VK_F7);
	AddKey("f8", VK_F8);
	AddKey("f9", VK_F9);
	AddKey("f10", VK_F10);
	AddKey("f11", VK_F11);
	AddKey("f12", VK_F12);
	
	lua_setglobal(L, "keys");
}
