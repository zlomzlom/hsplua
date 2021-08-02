#include "labelfunc.h"
#include <stdexcept>
#include "chkstat.h"
#include "hsplua.h"
#include "hsp/hsp3plugin.h"

int labelFunc(lua_State* l) {
	unsigned short* const label = (unsigned short*)lua_tointeger(l, lua_upvalueindex(1));
	code_call(label);
    if (ctx->retval_level == (ctx->sublev + 1)) {
        PVal* pvResult = *(exinfo->mpval);
        switch (pvResult->flag) {
            case HSPVAR_FLAG_INT:
                return *(int*)pvResult->pt;
            default:
                return 0;
        }
    }
    return 0;
}
