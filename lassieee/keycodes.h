#pragma once

#include "quantum.h"

enum layers {
    _L0 = 0,
    _L1,
    _L2,
    _L3,
    _L4,
    _L5,
};

#define QWERTY DF(_L0)
#define L0 TO(_L0)
#define L1 TO(_L1)
#define L2 TO(_L2)
#define L3 TO(_L3)
#define L4 TO(_L4)
#define L5 TO(_L5)

