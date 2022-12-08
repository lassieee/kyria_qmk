#pragma once

#include "quantum.h"

enum layers {
    _QWERTY0 = 0,
    _SYM1,
    _SYM2,
    _NAV3,
    _FKEYS4,
    _ADJUST5,
};

#define QWERTY0   DF(_QWERTY0)
#define SYM1     MO(_SYM1)
#define SYM2     MO(_SYM2)
#define NAV3     MO(_NAV3)
#define FKEYS4   MO(_FKEYS4)
#define ADJUST5  MO(_ADJUST5)

