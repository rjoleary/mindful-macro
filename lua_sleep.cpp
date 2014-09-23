#include <lua.hpp>

#include <Windows.h>


int Lua_sleep( lua_State *L );


void RegisterLuaSleep( lua_State *L )
{
	lua_register( L, "sleep", Lua_sleep );
}


int Lua_sleep( lua_State *L )
{
	Sleep( static_cast<DWORD>( luaL_checknumber( L, 1 ) ) );
	return 0;
}
