#include "MIPS.h"

#define R_SIZE 32

extern char *s_Mem;
int *reg;
int pc = 0x00400000;
unsigned int Sp = 0x80000000;

unsigned int Reg(unsigned int a, unsigned int v, int nrw){
    if(a>31||a<0){
        printf("Invalid register number\n");
        return 1;
    }
    if(nrw == 0){   // read
        v = *(reg+a);
        return v;
    }else if(nrw == 1){     // write

        if(a == 29){
            *(reg+a) = *(reg+a) - v;
            printf("register change R%d = %#x\n", a, Reg(a, 0, 0));
        }else{
            *(reg+a) = v;
            printf("register change R%d = %#x\n", a, Reg(a, 0, 0));
        }
    }
    return 0;
}


void getRegister(){
    for(int i=0;i<R_SIZE; i++){
        printf("R%d\t = %#x\n", i, Reg(i, 0, 0));
    }
}

void setPc(unsigned int val){
    pc = val;
}

void allocate_register(){   // 초기값 설정
    reg = (int*)calloc(32,sizeof(int));
    *(reg+29) = Sp;
}
