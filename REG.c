#include "MIPS.h"

#define R_SIZE 32

extern char *s_Mem;
int *reg;
int pc = 0x00400000;
unsigned int Sp = 0x7ff00000;

unsigned int Reg(unsigned int a, unsigned int v, int nrw){
    if(a>31||a<0){
        printf("Invalid register number\n");
        return 1;
    }
    if(nrw == 0){   // read
        v = *(reg+a);
        return v;
    }else if(nrw == 1){     // write
        int temp_a = Reg(a, 0,0);
        *(reg+a) = v;
        if(temp_a!=Reg(a,0,0)){
            printf("register change r%d = %#x\n");
        }
    }
    return 0;
}

void getRegister(){
    for(int i=0;i<R_SIZE; i++){
        printf("r%d\t = %#x\n", i, Reg(i, 0, 0));
    }
}

void setPc(unsigned int val){
    pc = val;
}

int getPc(){
    return pc;
}

void allocate_register(){
    reg = (int*)calloc(32,sizeof(int));
    Reg(29, Sp, 1);
}
