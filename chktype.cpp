#include "chktype.h"
#include "hsplua.h"
#include "chkstat.h"
#include "hsp/hsp3plugin.h"

int hsplua_func::hl_isboolean() {
	ref_val.ival = lua_isboolean(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_iscfunction() {
	ref_val.ival = lua_iscfunction(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isfunction() {
	ref_val.ival = lua_isfunction(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_islightuserdata() {
	ref_val.ival = lua_islightuserdata(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isnil() {
	ref_val.ival = lua_isnil(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isnone() {
	ref_val.ival = lua_isnone(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isnoneornil() {
	ref_val.ival = lua_isnoneornil(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isnumber() {
	ref_val.ival = lua_isnumber(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isinteger() {
	ref_val.ival = lua_isinteger(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isstring() {
	ref_val.ival = lua_isstring(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_istable() {
	ref_val.ival = lua_istable(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isthread() {
	ref_val.ival = lua_isthread(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_isuserdata() {
	ref_val.ival = lua_isuserdata(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_checknumber() {
	ref_val.dval = luaL_checknumber(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_DOUBLE;
}

int hsplua_func::hl_checkinteger() {
	ref_val.ival = luaL_checkinteger(currState(), exinfo->HspFunc_prm_geti());
	return HSPVAR_FLAG_INT;
}

int hsplua_func::hl_checkstring() {
	size_t strsz = 0;
	const char* const tmpstr = luaL_checkstring(currState(), exinfo->HspFunc_prm_geti());
	char* const tmp_sval = ref_sval; // reallocé∏îsëŒçÙ
	ref_sval = hspexpand(ref_sval, strsz + 1);
	if (ref_sval == NULL) { // realloc é∏îséû
		ref_sval = tmp_sval;
		throw HSPERR_OUT_OF_MEMORY;
	}
	strncpy(ref_sval, tmpstr, strsz + 1);
	ref_sval[strsz] = '\0'; // à¿ëSÇÃÇΩÇﬂ
	ref_val.sval = ref_sval;
	return HSPVAR_FLAG_STR;
}

int hsplua_func::hl_checklstring() {
	size_t strsz = 0;
	const char* const tmpstr = luaL_checklstring(currState(), exinfo->HspFunc_prm_geti(), &strsz);
	char* const tmp_sval = ref_sval; // reallocé∏îsëŒçÙ
	ref_sval = hspexpand(ref_sval, strsz + 1);
	if (ref_sval == NULL) { // realloc é∏îséû
		ref_sval = tmp_sval;
		throw HSPERR_OUT_OF_MEMORY;
	}
	strncpy(ref_sval, tmpstr, strsz + 1);
	ref_sval[strsz] = '\0'; // à¿ëSÇÃÇΩÇﬂ
	ref_val.sval = ref_sval;
	return HSPVAR_FLAG_STR;
}