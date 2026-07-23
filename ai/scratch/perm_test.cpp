#include "Unknown/Common.hpp"
#include "global.h"

void UnkSystem7::func_ov000_020a0304() {
    UnkSystem7_UnkStruct_00 *p;
    u32 v;

    p = this->mUnk_00;
    if (p == NULL) {
        return;
    }
    v = p->mUnk_24 & ~4;
    p->mUnk_24 = v;
    p = this->mUnk_00;
    v = (p->mUnk_24 & ~1) | 1;
    p->mUnk_24 = v;
}
