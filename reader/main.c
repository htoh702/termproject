#include <stdio.h>
#include <stdlib.h>

int addSubtract( int x, int y, int s0){
    int ret;
    if(s0<0||s0>1){
        printf("error in addSubtract\n");
        exit(1);
    }
    if(s0==0){
        ret = x+y;
    }else{
        ret = x-y;
    }
    return ret;
}

int logicOperation(int x, int y, int s1s0){
    if(s1s0 <0 || s1s0 >3){
        printf("error in logic\n");
        exit(1);
    }
    if(s1s0 == 0){
        return x&y;
    }else if(s1s0 == 1){
        return x|y;
    }else if(s1s0 == 2){
        return x^y;
    }else{
        return ~(x|y);
    }
}

int shiftOperation(int v, int y, int s1s0){
    int ret;
    if(s1s0 < 0|| s1s0 > 3){
        printf("error in shift\n");
        exit(1);
    }
    if(s1s0 == 0){
        ret = v;
    }else if(s1s0 ==1){
        ret = v << y;
    }else if(s1s0 == 2){
        ret = v >> y;
        int a = 0;
        for(int i=0;i<y;i++){
            a |= 1<<i;
            ret = (v >> y) & ~(a << (32-y));
        }
    }else{
        int sign = y & (1 << 31);
        if(sign == 1 << 31){
            int a = 0;
            for(int i=0;i<y;i++){
                a |= 1<<i;
            }
            ret = (v >> y ) | (a << (32-y));
        }
        else{
            ret = v >> y;
        }
    }
    return ret;
}

int checkSetLess(int x, int y){
    int ret;
    if(x>y){
        ret = 0;
    }else{
        ret = 1;
    }
    return ret;
}

int checkZero(int oa){
    int ret;
    if(oa == 0){
        ret = 1;
    }else{
        ret = 0;
    }
    return ret;
}

int ALU(int x, int y, int s, int *z) {
    int s32, s10;
    int ret;

    s32 = (s >> 2) & 0x3;
    s10 = s & 0x3;
    if (s32 == 0) {
        ret = shiftOperation(x, y, s10);
    } else if (s32 == 1) {
        ret = checkSetLess(x, y);
    } else if (s32 == 2) {
        s10 = s10 & 0x1;
        ret = addSubtract(x, y, s10);
        *z = checkZero(ret);
    } else if (s32 == 3){
        ret = logicOperation(x, y, s10);
    }
    return ret;
}

void opcode(int s, char** op) {
    int s32, s10;

    s32 = (s >> 2) & 0x3;
    s10 = s & 0x3;
    if (s32 == 0) {
        if (s10 == 0) {
            *op = "No shift";
        } else if (s10 == 1) {
            *op = "SLL";
        } else if (s10 == 2) {
            *op = "SRL";
        } else if (s10 == 3) {
            *op = "SRA";
        }
    } else if (s32 == 1) {
        *op = "Set Less";
    } else if (s32 == 2) {
        if (s10 == 0 || s10 == 2) {
            *op = "Add";
        } else {
            *op = "Subtract";
        }
    } else if (s32 == 3) {
        if (s10 == 0) {
            *op = "AND";
        } else if (s10 == 1) {
            *op = "OR";
        } else if (s10 == 2) {
            *op = "XOR";
        } else if (s10 == 3) {
            *op = "NOR";
        }
    }
}

void test_vector(int x, int y){
    int s, z=-1, alu;
    char* op;
    printf("x: %8x, y: %8x\n", x, y);
    for(s=0;s<16;s++){
        if((s>=9&&s<=10) || (s>4&&s<=7)){
            continue;
        }
        z=-1;
        opcode(s, &op);
        alu = ALU(x,y,s, &z);
        printf("s : %x, ALU : %8x, z : %d, op: %s\n", s, alu, z, op);
    }
}

int main(){
    int test_x, test_y;

    test_x = 10;
    test_y = 20;

    test_vector(test_x, test_y);

    printf("\n");

    test_x = 32;
    test_y = -50;

    test_vector(test_x, test_y);

    printf("\n");

    test_x = -150;
    test_y = 50;

    test_vector(test_x, test_y);

    printf("\n");

    test_x = -1073741824;
    test_y = 1;

    test_vector(test_x, test_y);

    printf("\n");
    return 0;
}