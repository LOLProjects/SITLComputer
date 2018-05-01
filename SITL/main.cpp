#include <iostream>
#include "Cpu.h"

using namespace std;

int main()
{
    Cpu cpu;
    cpu.initialize();
    while (1)
    {
        cpu.cycle();
    }
    return 0;
}
