#include "MIPS.h"

int is_immed = 0;
int is_sign = 0;


char bin[40] = "";
char *convertBinary(int IR) { // convert IR to 32bit binary
    //32bit binary character

    char temp_zero[40]="";
    itoa(IR, bin, 2);   // change int to alphabet
    while (strlen(bin) +strlen(temp_zero) < 32) // be filled with "0" at lack of bits(32-length).
        strcat(temp_zero, "0");
    strcat(temp_zero, bin);
    strcpy(bin,temp_zero);

    return bin;
}

int convertDecimal(char * binString) {
    return (int) strtol(binString, NULL, 2);    // 문자열을 long값으로 변환

}

char *splitIR(char *code, int start, int len){     // 특정 범위의 bin값을 반환

    int i;
    int length;
    char *output;

    output = (char*)malloc(sizeof(char)*len+1); // return memory address
    // last indexing is null;
    length= strlen(code);

    if(length> start + len)
        length = start + len;

    if(start==16&& is_immed==1 && code[start]=='1')
        is_sign=1;
    else
        is_sign=0;

    if(is_sign==1){
        for(i=start;i<length;i++)
            if(code[i]=='1')
                output[i-start]='0';
            else if(code[i]=='0')
                output[i-start]='1';
    }else{
        for(i= start; i<length; i++)
            output[i-start]=code[i];
    }

    output[i-start] ='\0';

    return output;
}

void convertIR(char * bin, int *op, int * rs, int *rt, int* rd, int *sh, int *fn, int *offset, int *jta){
    /*
     op: 0~5
     rs: 6~10
     rt: 11~15
     rd: 16~20
     sh: 21~25
     fn: 26~31
     operand: 16~31
     jta: 6~31
     */
    int tmp_offset;

    *op=convertDecimal(splitIR(bin,0,6));
    if(*op==0x001000||*op==0x001010||*op==0x001111)
        is_immed=1;
    else
        is_immed=0;
    *rs=convertDecimal(splitIR(bin,6,5));
    *rt=convertDecimal(splitIR(bin,11,5));
    *rd=convertDecimal(splitIR(bin,16,5));
    *sh=convertDecimal(splitIR(bin,21,5));
    *fn=convertDecimal(splitIR(bin,26,6));
    tmp_offset=convertDecimal(splitIR(bin,16,16));
    if(is_immed==1&&is_sign==1){
        tmp_offset += 1;
        tmp_offset = -tmp_offset;
    }
    *offset= tmp_offset;

    *jta=convertDecimal(splitIR(bin,6,26));
}