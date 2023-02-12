#pragma once

#include "quantum.h"

enum layers {
    _L0 = 0,
    _L1,
    _L2,
    _L3,
};

#define L0  DF(_L0)
#define L1  MO(_L1)
#define L2  MO(_L2)
#define L3  MO(_L3)

