#pragma once

#include "device.h"

namespace stmcpp{
    class Application{
    public:
        int setup();
        virtual bool init() = 0;
    };
}
