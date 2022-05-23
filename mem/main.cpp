#include <stdio.h>
#include <stdlib.h>

#define max_size 0x1000000
unsigned char textMEM[max_size];
unsigned char dataMEM[max_size];
unsigned char stackMEM[max_size];

int endian(int value){
    unsigned char bytes[4];
    int result;

    for(int i=0;i<4;i++){
        bytes[i] = (unsigned)((value >> i*8) & 0xff);
    }

    result = (int)bytes[0] << 3*8;

    for(int i=1;i<4;i++){
        result = result | ((int)bytes[i] << (3-i)*8);
    }

    return result;
}

int half_endian(int value){
    unsigned char bytes[2];
    int result;

    for(int i=0;i<2;i++){
        bytes[i] = (unsigned)((value >> i*16) & 0xffff);
    }

    result = (int)bytes[0] << 1*16;

    result = result | ((int)bytes[1] << (0)*16);


    return result;
}

int MEM(unsigned int a, int v, int nrw, int s){
    unsigned int sel, offset;
    unsigned char *pM;
    sel = a >> 20;
    offset = a & 0xfffff;
    if(sel == 0x004){
        pM=textMEM;
    }else if(sel == 0x100){
        pM=dataMEM;
    }else if(sel == 0x7ff){
        pM=stackMEM;
    }else{
        printf("Empty memory\n");
        exit(1);
    }
    if(s==0){

        if(nrw==0){
            return *((char*)pM + offset);
        }else if(nrw==1){
            printf("pm : %08x, offset : %x, pM + offset : %8x\n", pM, offset, pM + offset);
            printf("sb = %d\n", v);
            *((char*)pM+offset) = v;
        }
    }else if(s==1){
        offset = offset&0xffffc;
        if(nrw==0){
            return *((short*)pM + offset);
        }else if(nrw==1){
            printf("pm : %08x, offset : %x, pM + offset : %8x\n", pM, offset, pM + offset);
            printf("sh = %d\n", v);
            *((short*)pM+offset) = v;
        }
    }else if(s==2){
        offset = offset&0xffffe;
        if(nrw==0){
            return *((int*)pM + offset);
        }else if(nrw==1){
            printf("pm : %08x, offset : %x, pM + offset : %8x\n", pM, offset, pM + offset);
            printf("sw = %d\n", v);
            *((int*)pM+offset) = v;
        }
    }else{
        printf("error\n");
        exit(1);
    }
    return 0;
}

void test_case(){
    int value[3][2] = {{0x01, 0x0f},{0x0123, 0x0fff},{0x01234567, 0x0fffffff}};
    int address[3][2] = {{0x00400000, 0x004fffff},{0x10000000,0x100fffff}, {0x7ff00000,0x7fffffff}};
    int size;
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            size = i;
            if(size==0){
                MEM(address[i][j], value[i][j], 1, size);
                printf("lb = %d\n", MEM(address[i][j], (char)value[i][j], 0, size));
                printf("lbu = %d\n", MEM(address[i][j], (unsigned char)value[i][j], 0, size));
            }else if(size == 1){
                MEM(address[i][j], value[i][j], 1, size);
                printf("lh = %d\n", MEM(address[i][j], (short)half_endian(value[i][j]), 0, size));
                printf("lhu = %d\n", MEM(address[i][j], (unsigned short)half_endian(value[i][j]), 0, size));
            }else if(size == 2){
                MEM(address[i][j], value[i][j], 1, size);
                printf("lw = %d\n", MEM(address[i][j], (int)endian(value[i][j]), 0, size));
            }
            printf("\n");
        }
    }
}

int main() {

    test_case();

    return 0;
}
