extern "C"
{
#include "lua.h"
}
#include <stdlib.h>
#include <string.h>
#include <iostream>

auto script = R"(
print('hello lua')
)";

static void *l_alloc(void *ud, void *ptr, size_t osize, size_t nsize)
{
    (void)ud;
    (void)osize; /* not used */
    if (nsize == 0)
    {
        free(ptr);
        return NULL;
    }
    else
        return realloc(ptr, nsize);
}

typedef struct LoadS
{
    const char *s;
    size_t size;
} LoadS;

static const char *getS(lua_State *L, void *ud, size_t *size)
{
    LoadS *ls = (LoadS *)ud;
    (void)L; /* not used */
    if (ls->size == 0)
        return NULL;
    *size = ls->size;
    ls->size = 0;
    return ls->s;
}

LUALIB_API int luaL_loadbufferx(lua_State *L, const char *buff, size_t size,
                                const char *name, const char *mode)
{
    LoadS ls;
    ls.s = buff;
    ls.size = size;
    return lua_load(L, getS, &ls, name, mode);
}

LUALIB_API int luaL_loadstring(lua_State *L, const char *s)
{
    return luaL_loadbufferx(L, s, strlen(s), s, NULL);
    // return luaL_loadbuffer(L, s, strlen(s), s);
}

int lua_print(lua_State *L)
{
    auto s = lua_tostring(L, -1);
    std::cout << s << std::endl;
    return 0;
}

int main()
{
    {
        auto L = lua_newstate(l_alloc, NULL);
        lua_pushcclosure(L, lua_print, 0);
        lua_setglobal(L, "print");

        {
            luaL_loadstring(L, script);
            lua_pcall(L, 0, LUA_MULTRET, 0);
        }
        lua_close(L);
    }

    return 0;
}
