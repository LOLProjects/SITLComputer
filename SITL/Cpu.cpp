#include "Cpu.h"

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
    //Update the timestamp
    time(&timer);
    TS = difftime(timer, mktime(&date0));
    //TODO : Update the DelayTimer
    //std::cout << "Timestamp : " << TS << '\n';

    uint32_t opCode = ((MEM[PC] << 16) | (MEM[PC + 1] << 8) | (MEM[PC + 2]));    //Get 3 bytes : one op
    bool pcChanged = false;

    switch (opCode & 0xF00000)
    {
    case 0x000000:
        switch (opCode & 0X0F0000)
        {
            case 0x000000:  //NOP
                break;
            case 0x010000:  //JP addr
                pcChanged = true;
                PC = opCode & 0xFFFF;
                break;
            case 0x020000:  //JPIF addr
                if (N[0xF] & 0x1)
                {
                    pcChanged = true;
                    PC = opCode & 0xFFFF;
                }
                break;
            case 0x040000:  //CALL addr
                MEM[SP] = (PC & 0xFF00) >> 8;
                MEM[SP + 1] = (PC & 0x00FF);
                SP += 2;
                pcChanged = true;
                break;
            case 0x050000:
                switch (op & 0x00F000)
                {
                    case 0x000000:  //RET
                        SP -= 2;
                        PC = (MEM[SP] << 8) | (MEM[SP + 1]);
                        break;
                    case 0x001000:  //JP Ix
                        PC = I[op & 0x00000F] & 0xFFFF;
                        pcChanged = true;
                        break;
                    case 0x002000:  //JPIF Ix
                        if (N[0xF] & 0x1)
                        {
                            PC = I[op & 0x00000F] & 0xFFFF;
                            pcChanged = true;
                        }
                        break;
                    case 0x003000:  //JPNIF Ix
                        if (!(N[0xF] & 0x1))
                        {
                            PC = I[op & 0x00000F] & 0xFFFF;
                            pcChanged = true;
                        }
                        break;
                    default:
                        unknownOp(opCode);
                        break;
                }
                break;
            case 0x070000:  //PUSHW n
                MEM[SP] = (opCode & 0xFF00) >> 8;
                MEM[SP + 1] = (opCode & 0x00FF);
                SP += 2;
                break;
            case 0x080000:
                switch (opCode & 0x00F000)
                {
                    case 0x000000:  //PUSHB n
                        MEM[SP] = opCode & 0xFF;
                        SP++;
                        break;
                    case 0x001000:  //PUSH Bx
                        MEM[SP] = B[opCode & 0xF];
                        SP++;
                        break;
                    case 0x002000:  //PUSH Ix
                        uint32_t val = I[opCode & 0xF];
                        MEM[SP + 0] = (val & 0xFF000000) >> 24;
                        MEM[SP + 1] = (val & 0x00FF0000) >> 16;
                        MEM[SP + 2] = (val & 0x0000FF00) >> 8;
                        MEM[SP + 3] = (val & 0x000000FF);
                        SP += 4;
                        break;
                    default:
                        unknownOp(opCode);
                        break;
                }
                break;
            case 0x090000:
                switch (opCode & 0x00F000)
                {
                    case 0x000000:  //POP Bx
                        SP--;
                        B[opCode & 0xF] = MEM[SP];
                        break;
                    case 0x001000:  //POP Ix
                        SP -= 4;
                        I[opCode & 0xF] = (MEM[SP] << 24) | (MEM[SP + 1] << 16) | (MEM[SP + 2] << 8) | (MEM[SP + 3]);
                        break;
                    default:
                        unknownOp(opCode);
                        break;
                }
                break;
            default:
                unknownOp(opCode);
                break;
        }
        break;
    case 0x100000:
        //TODO
        break;
    case 0x200000:
        //TODO
        break;
    case 0x300000:
        //TODO
        break;
    case 0x400000:
        //TODO
        break;
    case 0x500000:
        //TODO
        break;
    case 0x600000:
        //TODO
        break;
    case 0x700000:
        //TODO
        break;
    case 0x800000:
        //TODO
        break;
    case 0x900000:
        //TODO
        break;
    case 0xA00000:
        //TODO
        break;
    case 0xB00000:
        //TODO
        break;
    case 0xC00000:
        //TODO
        break;
    case 0xD00000:
        //TODO
        break;
    case 0xE00000:
        //TODO
        break;
    case 0xF00000:
        //TODO
        break;
    }

    if (!pcChanged)
        PC += 3;

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
    for (int i = 0; i < 0x10000; i++)
        MEM[i] = 0;
    //TODO : Load the fontset
    date0.tm_year = 118;    //2018
    date0.tm_mday = 1;
}

