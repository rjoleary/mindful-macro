#include <string>
#include <vector>
#include <iostream>

#include <lua.hpp>

#include <Windows.h>


int Lua_keyboard_down(lua_State *L);
int Lua_keyboard_up(lua_State *L);
int Lua_keyboard_press(lua_State *L);
int Lua_keyboard_combo(lua_State *L);
int Lua_keyboard_type(lua_State *L);


void RegisterLuaKeyboard(lua_State *L)
{
	lua_createtable(L, 0, 1);
	int keyboardTable = lua_gettop(L);

	lua_pushcfunction(L, Lua_keyboard_down);
	lua_setfield(L, keyboardTable, "down");
	lua_pushcfunction(L, Lua_keyboard_up);
	lua_setfield(L, keyboardTable, "up");
	lua_pushcfunction(L, Lua_keyboard_press);
	lua_setfield(L, keyboardTable, "press");
	lua_pushcfunction(L, Lua_keyboard_combo);
	lua_setfield(L, keyboardTable, "combo");
	lua_pushcfunction(L, Lua_keyboard_type);
	lua_setfield(L, keyboardTable, "type");

	lua_setglobal(L, "keyboard");
}


INPUT InputFromVkCode(WORD vkCode, DWORD flags)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = flags;
	input.ki.wVk = vkCode;
	// scan codes are required by some programs
	input.ki.wScan = MapVirtualKey(input.ki.wVk, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = GetMessageExtraInfo();
	return input;
}

INPUT InputFromChar(char c, DWORD flags)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = flags;
	input.ki.wVk = VkKeyScan(LOBYTE(c));
	// scan codes are required by some programs
	input.ki.wScan = MapVirtualKey(input.ki.wVk, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = GetMessageExtraInfo();
	return input;
}

int Lua_keyboard_down(lua_State *L)
{
	std::vector<INPUT> inputs;

	int stackSize = lua_gettop(L);
	inputs.reserve(stackSize);
	
	for (int i = 1; i <= stackSize; ++i)
	{
		if (lua_isnumber(L, i))
		{
			inputs.push_back(InputFromVkCode(static_cast<WORD>(lua_tonumber(L, i)), 0));
		}
		else if (lua_isstring(L, i))
		{
			std::string letter = lua_tostring(L, i);
			if (letter.length() > 1)
			{
				lua_pushstring(L, "String is larger than a letter");
				lua_error(L);
			}
			inputs.push_back(InputFromChar(letter[0], 0));
		}
		else
		{
			lua_pushstring(L, "Not a valid type");
			lua_error(L);
		}
	}

	if(SendInput(inputs.size(), inputs.data(), sizeof(INPUT)) != inputs.size())
		std::cerr << "Cannot simulate key\n";
	return 0;
}

int Lua_keyboard_up(lua_State *L)
{
	std::vector<INPUT> inputs;

	int stackSize = lua_gettop(L);
	inputs.reserve(stackSize);
	
	for (int i = 1; i <= stackSize; ++i)
	{
		if (lua_isnumber(L, i))
		{
			inputs.push_back(InputFromVkCode(static_cast<WORD>(lua_tonumber(L, i)), KEYEVENTF_KEYUP));
		}
		else if (lua_isstring(L, i))
		{
			std::string letter = lua_tostring(L, i);
			if (letter.length() > 1)
			{
				lua_pushstring(L, "String is larger than a letter");
				lua_error(L);
			}
			inputs.push_back(InputFromChar(letter[0], KEYEVENTF_KEYUP));
		}
		else
		{
			lua_pushstring(L, "Not a valid type");
			lua_error(L);
		}
	}

	if(SendInput(inputs.size(), inputs.data(), sizeof(INPUT)) != inputs.size())
		std::cerr << "Cannot simulate key\n";
	return 0;
}

int Lua_keyboard_press(lua_State *L)
{
	std::vector<INPUT> inputs;

	int stackSize = lua_gettop(L);
	inputs.reserve(stackSize * 2);
	
	for (int i = 1; i <= stackSize; ++i)
	{
		if (lua_isnumber(L, i))
		{
			inputs.push_back(InputFromVkCode(static_cast<WORD>(lua_tonumber(L, i)), 0));
			inputs.push_back(InputFromVkCode(static_cast<WORD>(lua_tonumber(L, i)), KEYEVENTF_KEYUP));
		}
		else if (lua_isstring(L, i))
		{
			std::string letter = lua_tostring(L, i);
			if (letter.length() > 1)
			{
				lua_pushstring(L, "String is larger than a letter");
				lua_error(L);
			}
			inputs.push_back(InputFromChar(letter[0], 0));
			inputs.push_back(InputFromChar(letter[0], KEYEVENTF_KEYUP));
		}
		else
		{
			lua_pushstring(L, "Not a valid type");
			lua_error(L);
		}
	}

	if(SendInput(inputs.size(), inputs.data(), sizeof(INPUT)) != inputs.size())
		std::cerr << "Cannot simulate key\n";
	return 0;
}

int Lua_keyboard_combo(lua_State *L)
{
	std::vector<INPUT> inputs;

	int stackSize = lua_gettop(L);
	inputs.reserve(stackSize * 2);
	
	for (int i = 1; i <= stackSize; ++i)
	{
		if (lua_isnumber(L, i))
		{
			inputs.push_back(InputFromVkCode(static_cast<WORD>(lua_tonumber(L, i)), 0));
		}
		else if (lua_isstring(L, i))
		{
			std::string letter = lua_tostring(L, i);
			if (letter.length() > 1)
			{
				lua_pushstring(L, "String is larger than a letter");
				lua_error(L);
			}
			inputs.push_back(InputFromChar(letter[0], 0));
		}
		else
		{
			lua_pushstring(L, "Not a valid type");
			lua_error(L);
		}
	}

	for (int i = stackSize; i > 0; --i)
	{
		if (lua_isnumber(L, i))
		{
			inputs.push_back(InputFromVkCode(static_cast<WORD>(lua_tonumber(L, i)), KEYEVENTF_KEYUP));
		}
		else if (lua_isstring(L, i))
		{
			std::string letter = lua_tostring(L, i);
			if (letter.length() > 1)
			{
				lua_pushstring(L, "String is larger than a letter");
				lua_error(L);
			}
			inputs.push_back(InputFromChar(letter[0], KEYEVENTF_KEYUP));
		}
		else
		{
			lua_pushstring(L, "Not a valid type");
			lua_error(L);
		}
	}

	if(SendInput(inputs.size(), inputs.data(), sizeof(INPUT)) != inputs.size())
		std::cerr << "Cannot simulate key\n";
	return 0;
}

int Lua_keyboard_type(lua_State *L)
{
	std::vector<INPUT> inputs;

	std::string text(luaL_checkstring(L, 1));
	
	auto i = text.begin(), e = text.end();
	for (; i != e; ++i)
	{
		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.dwFlags = KEYEVENTF_UNICODE;
		input.ki.wScan = static_cast<WORD>(*i);
		input.ki.wVk = 0;
		input.ki.time = 0;
		input.ki.dwExtraInfo = GetMessageExtraInfo();
		inputs.push_back(input);

		input.type = INPUT_KEYBOARD;
		input.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
		input.ki.wScan = static_cast<WORD>(*i);
		input.ki.wVk = 0;
		input.ki.time = 0;
		input.ki.dwExtraInfo = GetMessageExtraInfo();
		inputs.push_back(input);
	}

	if(SendInput(inputs.size(), inputs.data(), sizeof(INPUT)) != inputs.size())
		std::cerr << "Cannot simulate key\n";
	return 0;
}
