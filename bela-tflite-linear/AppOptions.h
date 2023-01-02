#pragma once

#include <string>

struct AppOptions
{
    std::string modelPath = "";
    int input = 2;
    int frontend = 0;
    bool useArmnn = false;
};
