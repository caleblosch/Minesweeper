//
// Created by caleb on 11/21/2022.
//

#pragma
#include <random>

class Random {
    // static variables/functions exist for the lifetime of your program being run
    static std::mt19937 random;
public:
    // One and only one of this function
    static int Int(int min, int max);
    static float Float(float min, float max);
};


