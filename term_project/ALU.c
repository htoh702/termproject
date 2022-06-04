#include "MIPS.h"

int addSubtract (int X, int Y, int S)
{
    int ret;

    if (S < 0 || S > 1)
    {
        printf("error in addSubtract\n");
        exit(1);
    }

    if (S == 0)			// S1S0이 0이면 add
    {
        ret = X + Y;
    }
    else		// S1S0이 1이면 subtract
    {
        ret = X - Y;
    }

    return ret;
}

int logicOperation (int X, int Y, int S)
{
    if (S < 0 || S > 3)
    {
        printf("error in logic\n");
        exit(1);
    }

    if (S == 0)
    {
        return X & Y;
    }
    else if (S == 1)
    {
        return X | Y;
    }
    else if (S == 2)
    {
        return X ^ Y;
    }
    else
    {
        return ~(X | Y);
    }

}

int shiftOperation(int V, int Y, int C)
{
    int ret;

    if (C < 0 || C > 3)
    {
        printf("error in shift operation\n");
        exit(1);
    }

    if (C == 0) //No shift
        ret = V;
    else if (C == 1) //Shift left logical
        ret = V << Y;
    else if (C == 2) //Shift right logical
        ret = (unsigned int)V >> Y;
    else  //Shift right arithmetic
        ret = V >> Y;

    return ret;
}

int checkSetLess (int X, int Y)
{
    int LT;
    LT = addSubtract(X, Y, 1);

    if(LT >= 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

int checkZero (int Oa)
{
    return Oa==0 ? 1:0;		// if Oa == 0 return 1, else return 0
}



int ALU(int X, int Y, int S) {
    int s32, s10;	// S3S2, S1S0의 값 선언
    int ret;

    s32 = (S>>2) & 0x3;		// S에서 S3S2 값 추출
    s10 = S & 0x3;		// S에서 S1S0 값 추출

    if (s32 == 0)		// Shift
    {
        ret = shiftOperation(X, Y, s10);

    }
    else if (s32 == 1)		// Set Less
    {
        ret = checkSetLess(X, Y);

    }
    else if (s32 == 2)		// addSubtract
    {
        ret = addSubtract(X, Y, s10);
    }
    else if (s32 == 3)		// logic
    {
        ret = logicOperation(X, Y, s10);

    }


    return ret;

}

//
//int addSubtract( int x, int y, int s){
//int ret;
//if(s<0||s>1){
//printf("error in addSubtract\n");
//exit(1);
//}
//if(s==0){
//ret = x+y;
//}else{
//ret = x-y;
//}
//return ret;
//}
//
//int logicOperation(int x, int y, int s1s0){
//    if(s1s0 <0 || s1s0 >3){
//        printf("error in logic\n");
//        exit(1);
//    }
//    if(s1s0 == 0){
//        return x&y;
//    }else if(s1s0 == 1){
//        return x|y;
//    }else if(s1s0 == 2){
//        return x^y;
//    }else{
//        return ~(x|y);
//    }
//}
//
//int shiftOperation(int v, int y, int s1s0){
//    int ret;
//    if(s1s0 < 0|| s1s0 > 3){
//        printf("error in shift\n");
//        exit(1);
//    }
//    if(s1s0 == 0){
//        ret = v;
//    }else if(s1s0 ==1){
//        ret = v << y;
//    }else if(s1s0 == 2){
//        ret = v >> y;
//        int a = 0;
//        for(int i=0;i<y;i++){
//            a |= 1<<i;
//            ret = (v >> y) & ~(a << (32-y));
//        }
//    }else{
//        int sign = y & (1 << 31);
//        if(sign == 1 << 31){
//            int a = 0;
//            for(int i=0;i<y;i++){
//                a |= 1<<i;
//            }
//            ret = (v >> y ) | (a << (32-y));
//        }
//        else{
//            ret = v >> y;
//        }
//    }
//    return ret;
//}
//
//int checkSetLess(int x, int y){
//    int ret;
//    if(x>y){
//        ret = 0;
//    }else{
//        ret = 1;
//    }
//    return ret;
//}
//
//int checkZero(int oa){
//    int ret;
//    if(oa == 0){
//        ret = 1;
//    }else{
//        ret = 0;
//    }
//    return ret;
//}
//
//int ALU(int x, int y, int s) {
//    int s32, s10;
//    int ret;
//
//    s32 = (s >> 2) & 0x3;
//    s10 = s & 0x3;
//    if (s32 == 0) {
//        ret = shiftOperation(x, y, s10);
//    } else if (s32 == 1) {
//        ret = checkSetLess(x, y);
//    } else if (s32 == 2) {
//        s10 = s10 & 0x1;
//        ret = addSubtract(x, y, s10);
//    } else if (s32 == 3){
//        ret = logicOperation(x, y, s10);
//    }
//    return ret;
//}
//
