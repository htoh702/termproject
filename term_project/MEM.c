#include "MIPS.h"

unsigned char p_Mem[0x100000], d_Mem[0x100000], s_Mem[0x100000];

int MEM(unsigned int a, int v, int nrw, int ss){
    unsigned int sel, offset;
    unsigned char *pM;
    sel = a >> 20;
    offset = a & 0xfffff;
    if(sel == 0x004){
        pM= p_Mem;
    }else if(sel == 0x100){
        pM=d_Mem;
    }else if(sel == 0x7ff){
        pM=s_Mem;
    }else{
        printf("Empty memory\n");
        return 1;
    }
    if(ss==0){

        if(nrw==0){     // read
            int v = *(pM + offset);
            return v;
        }else if(nrw==1){
            *(pM + offset) = v;
            return 0;
        }
    }else if(ss==1){
        if(nrw==0){
            v = (*(pM + offset) << 8) + *(pM+offset+1);
            return v;
        }else if(nrw==1){   // write
            *(pM + offset) = v >> 8;
            *(pM + offset + 1) = v &0xff;
        }
    }else if(ss==2){
        if(nrw==0){
            v = (*(pM + offset) << 24) + (*(pM + offset + 1) << 16)+(*(pM+offset+2) << 8) + (*(pM +offset+3));
            return v;
        }else if(nrw==1){
            *(pM + offset) = v >> 24;
            *(pM + offset + 1) = (v >> 16) & 0xFF;
            *(pM + offset + 2) = (v >> 8) & 0xFF;
            *(pM + offset + 3) = v & 0xFF;
        }
    }else{
        printf("error\n");
        return 1;
    }
}

int getMemory(unsigned int s_addr, unsigned int e_addr) {

    for (unsigned int i = s_addr; i <= e_addr; i += 4) {
        int result_Mem = MEM(i, 0, 0, 2);
        if(result_Mem ==1)
            return 1;
        else
            printf("Memory %#x = %d\n", i , result_Mem);
    }
    return 0;
}

int setMemory(unsigned int addr, int val) {
    int result_Mem = MEM(addr, val, 1, 2);

    if (result_Mem == 1) {
        return 0;
    }else{
        return 1;
    }
}