#include "dim.h"
#include "hsplua.h"
#include "chkstat.h"
#include "hsp/hsp3plugin.h"

struct DimWrapper {
    int level;
    int index[4];
    PVal* pval;
};

static int hl_dim_dimensions(DimWrapper* dim) {
    int dimensions = 0;
    for (int i = 1; i < 4; i++) {
        if (dim->pval->len[i] > 0)
            dimensions++;
        else
            break;
    }
    return dimensions;
}

void hsplua_cmd::hl_pushdim() {
    DimWrapper* p = (DimWrapper*)lua_newuserdata(currState(), sizeof(DimWrapper));
    p->pval = exinfo->HspFunc_prm_getpval();
    p->level = 1;
    p->index[0] = -1;
    p->index[1] = -1;
    p->index[2] = -1;
    p->index[3] = -1;
    luaL_getmetatable(currState(), "hsplua.dim");
    lua_setmetatable(currState(), -2);
}

static DimWrapper *hl_dim_check(lua_State *L) {
    DimWrapper*ud = (DimWrapper*)luaL_checkudata(L, 1, "hsplua.dim");
    luaL_argcheck(L, ud != NULL, 1, "`dim' expected");
    return ud;
}

static int hl_dim_len(lua_State* L) {
    DimWrapper *ud = hl_dim_check(L);
    lua_pushnumber(L, ud->pval->len[ud->level]);
    return 1;
}

static int hl_dim_index(lua_State* L) {
    DimWrapper *ud = hl_dim_check(L);
    int index = (int)luaL_checkinteger(L, 2);
    luaL_argcheck(L, 0 <= index && index <= ud->pval->len[ud->level]-1, 2, "index out of range");
    
    if (ud->level != hl_dim_dimensions(ud)) {
        DimWrapper* p = (DimWrapper*)lua_newuserdata(currState(), sizeof(DimWrapper));
        p->pval = ud->pval;
        p->level = ud->level + 1;
        p->index[0] = ud->index[0];
        p->index[1] = ud->index[1];
        p->index[2] = ud->index[2];
        p->index[3] = ud->index[3];
        p->index[ud->level] = index;
        luaL_getmetatable(currState(), "hsplua.dim");
        lua_setmetatable(currState(), -2);
    }
    else {
        ud->index[ud->level] = index;
        HspVarCoreReset(ud->pval);
        for (int i = 1; i <= ud->level; i++) {
            exinfo->HspFunc_array(ud->pval, ud->index[i]);
        }
        switch (ud->pval->flag) {
        case HSPVAR_FLAG_STR:
            lua_pushstring(L, (char *)exinfo->HspFunc_getproc(HSPVAR_FLAG_STR)->GetPtr(ud->pval));
            break;
        case HSPVAR_FLAG_INT:
            lua_pushinteger(L, *(int *)exinfo->HspFunc_getproc(HSPVAR_FLAG_INT)->GetPtr(ud->pval));
            break;
        case HSPVAR_FLAG_DOUBLE:
            lua_pushnumber(L, *(double*)exinfo->HspFunc_getproc(HSPVAR_FLAG_DOUBLE)->GetPtr(ud->pval));
            break;
        default:
            lua_pushnil(L);
            break;
        }
    }
    return 1;
}

static int hl_dim_newindex(lua_State* L) {
    int var_i;
    double var_d;
    const char* var_s;
    DimWrapper *ud = hl_dim_check(L);
    int index = (int)luaL_checkinteger(L, 2);
    luaL_argcheck(L, 0 <= index && index <= ud->pval->len[ud->level]-1, 2, "index out of range");

    if (ud->level != hl_dim_dimensions(ud)) {
        return 0;
    }

    ud->index[ud->level] = index;
    HspVarCoreReset(ud->pval);
    for (int i = 1; i <= ud->level; i++) {
        exinfo->HspFunc_array(ud->pval, ud->index[i]);
    }

    switch (ud->pval->flag) {
    case HSPVAR_FLAG_STR:
        var_s = luaL_checkstring(L, 3);
        exinfo->HspFunc_prm_setva(ud->pval, ud->pval->offset, HSPVAR_FLAG_STR, var_s);
        break;
    case HSPVAR_FLAG_INT:
        var_i = (int)luaL_checkinteger(L, 3);
        exinfo->HspFunc_prm_setva(ud->pval, ud->pval->offset, HSPVAR_FLAG_INT, &var_i);
        break;
    case HSPVAR_FLAG_DOUBLE:
        var_d = luaL_checknumber(L, 3);
        exinfo->HspFunc_prm_setva(ud->pval, ud->pval->offset, HSPVAR_FLAG_DOUBLE, &var_d);
        break;
    default:
        break;
    }
    return 0;
}

static int hl_dim_gc(lua_State* L) {
    return 0;
}

static luaL_Reg meta[] = {
    { "__len", hl_dim_len },
    { "__index", hl_dim_index },
    { "__newindex", hl_dim_newindex },
    { "__gc", hl_dim_gc },
    { NULL, NULL }
};

void hsplua_cmd::hl_openlibs_dim() {
    luaL_newmetatable(currState(), "hsplua.dim");
    luaL_setfuncs(currState(), meta, 0);
    lua_pop(currState(), 1);
}