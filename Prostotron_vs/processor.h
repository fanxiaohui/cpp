#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include "gen.h"
#include "memory.h"
#include "mem_cell.h"

class Processor
{
/* Simulates a CPU device in a PC.
 * Accepts set of main Assembler's commands.
 * by Yuriy Senishch, 2005*/

public:

    Processor();
    ~Processor();    

    void decodeInstruction();
    void printProcessorState();

    void setAccumulator (int); // set
    int  getAccumulator ();     // get
    void printAccumulator();

    void setInstructionCounter(int);
    int  getInstructionCounter();
    int  incInctructionCounter();
    void printInstructionCounter();

    void setInstructionRegister(int);
    int  getInstructionRegister();
    void printInstrRegister();

    void setOpCode(int);
    int  getOpCode();
    void printOpCode();

    void setOperand(int);//
    int  getOperand();//
    void printOperand();
    void runProgramInMemory(int _n_trace = 0);

    void getMemory(Memory* externalMemoryP) {mMemory = externalMemoryP;}


private:
    Memory *mMemory;
    int mAccumulator;
    int mInstructionCounter;
    int mInstructionRegister;
    int mOpCode;
    int mOperand;//
    int mIsTrace;

    std::string getOpCodeDesctiption(int _opCode);

}; // end of the class Processor

// void RunMemoryProg(MemCell* memory /*pointer to an array!*/ , Processor *pProc, int Trace);


#endif //_PROCESSOR_H_
