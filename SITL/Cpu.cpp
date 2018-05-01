#include "Cpu.h"
#include <iostream>

Cpu::Cpu()
{
    //ctor
}

Cpu::~Cpu()
{
    //dtor
}

void
Cpu::cycle()
{
    time(&timer);
    TS = difftime(timer, mktime(&date0));
    std::cout << "Timestamp : " << TS << '\n';
    //std::cout << asctime(&date0) << '\n';
}

void
Cpu::initialize()
{
    //Reset the registers
    for (int i = 0; i < 0x10; i++)
    {
        N[i] = 0;
        B[i] = 0;
        I[i] = 0;
    }
    PC = 0x1000;    //Where should it be initialized?
    SP = 0x500;     //The standard stack starts at 0x500 and finishes at 0xFFF
    for (int i = 0; i < 10000; i++)
        MEM[i] = 0;
    //TODO : Load the fontset
    date0.tm_year = 118;    //2018
    date0.tm_mday = 1;
}
