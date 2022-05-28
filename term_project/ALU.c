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

int shiftOperation (int X, int Y, int S)
{
    int ret;
    if (S < 0 || S > 3)
    {
        printf("error in shift\n");
        exit(1);
    }
    if (S == 0)		// no shift
    {
        ret = X;
    }
    else if (S == 1)		// Shift Left Logical
    {
        ret = X << Y;
    }
    else if (S == 2)		// Shift Right Logical
    {
        int sign = (X >> 31) & 1;
        if(sign == 1)		// MSB(최상위 비트) 값이 1이면 Shift Right 해준만큼 0로 채워준다.
        {
            int a = 0;
            for (int i=31; i>=(32-Y); i--)
            {
                a |= (1 << i);
            }
            ret = (X >> Y) ^ a;
        }
        else
            ret = X >> Y;
    }
    else					// Shift Right Arithmetic
    {
        int sign = (X >> 31) & 1;
        if (sign == 1)		// MSB(최상위 비트) 값이 1이면 Shift Right 해준만큼 1로 채워준다.
        {
            int a = 0;
            for (int i=31; i>=(32-Y); i--)
            {
                a |= (1 << i);
            }
            ret = (X >> Y) | a;
        }
        else
            ret = X >> Y;
    }

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