#ifndef LUA_FUNCTIONS_HPP__INCLUDED
#define LUA_FUNCTIONS_HPP__INCLUDED

struct lua_State;

void RegisterLuaClipboard( lua_State *L );
void RegisterLuaSleep( lua_State *L );
void RegisterLuaKeys( lua_State *L );
void RegisterLuaKeyboard( lua_State *L );

#endif // LUA_FUNCTIONS_HPP__INCLUDED
