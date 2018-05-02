#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include <time.h>
#include <ctime>
#include <iostream>

class Cpu
{
    public:
        Cpu();
        virtual ~Cpu();
        void initialize();          //Initialize all variables
        void cycle();
    private:
        //Registers
        uint8_t B[0x10];    //8 bit registers
        uint8_t N[0x10];    //4 bit registers
        uint32_t I[0x10];   //32 bit registers

        uint16_t PC;        //Program counter
        uint16_t SP;        //Stack pointer

        uint32_t DT;        //Delay timer
        uint32_t TS;        //Time stamp

        uint32_t IMASK;     //Interrupt mask
        //Time
        time_t timer;
        std::tm date0;

        //Memory
        uint8_t MEM[0x10000]; //The machine's memory

        inline void unknownOp(uint32_t op)
        {
            std::cout << "Unknown op : " << std::hex << op << '\n';
        };
};

#endif // CPU_H
