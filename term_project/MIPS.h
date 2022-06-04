#ifndef MIPS_H_
#define MIPS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#endif

// loadToMem.c
int endian(unsigned int value , int s);
unsigned int n_instruction(FILE * file);
unsigned int n_data(FILE* file);



// REG.c
unsigned int Reg(unsigned int a, unsigned int v, int nrw);
void getRegister();
void setPc(unsigned int val);
void allocate_register();

// MEM.c
int MEM(unsigned int a, int v, int nrw, int ss);
int getMemory(unsigned int s_addr, unsigned int e_addr);
int setMemory(unsigned int addr, int val);

// representIR.c
char *convertBinary(int IR);
int convertDecimal(char * binString);
char *splitIR(char *input, int start, int len);
void convertIR(char * bin, int *op, int * rs, int *rt, int* rd, int *sh, int *fn, int *offset, int *jta);

// ALU.c
int addSubtract (int X, int Y, int S);
int logicOperation (int X, int Y, int S);
int shiftOperation (int X, int Y, int S);
int checkSetLess (int X, int Y);
int checkZero (int Oa);
int ALU(int X, int Y, int S);
#define ADD 8
#define SUB 9
#define SLL 1
#define SRL 2
#define SRA 3
#define SL 4
#define NOSHIFT 0
#define AND 12
#define OR 13
#define XOR 14
#define NOR 15


//step.c
int step();
void setBreakPoint(unsigned int argv1);

// registers
#define zero 0
#define at 1
#define v0 2
#define v1 3
#define a0 4
#define a1 5
#define a2 6
#define a3 7
#define t0 8
#define t1 9
#define t2 10
#define t3 11
#define t4 12
#define t5 13
#define t6 14
#define t7 15
#define s0 16
#define s1 17
#define s2 18
#define s3 19
#define s4 20
#define s5 21
#define s6 22
#define s7 23
#define t8 24
#define t9 25
#define k0 26
#define k1 27
#define gp 28
#define sp 29
#define fp 30
#define ra 31