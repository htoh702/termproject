#include "MIPS.h"

int is_immed = False;
int is_sign = False;


char bin[40] = "";
char *convertBinary(int IR) { // convert IR to 32bit binary
    //32bit binary character

    char temp_zero[40]="";
    itoa(IR, bin, 2);
    while (strlen(bin) +strlen(temp_zero) < 32) // be filled with "0" at lack of bits(32-length).
        strcat(temp_zero, "0");
    strcat(temp_zero, bin);
    strcpy(bin,temp_zero);

    return bin;
}

int convertDecimal(char * binString) {
    return (int) strtol(binString, NULL, 2);
    // binary string to integer
}

char *splitIR(char *input, int start, int len){
    //split binaryIR for encoding
    // start: start bit
    // len: bit length

    int i;
    int length;
    char *output;

    output = (char*)malloc(sizeof(char)*len+1);
    // last indexing is null;
    length= strlen(input);

    if(length> start + len)
        length = start + len;

    if(start==16&& is_immed==True && input[start]=='1')
        is_sign=True;
    else
        is_sign=False;

    if(is_sign==True){
        for(i=start;i<length;i++)
            if(input[i]=='1')
                output[i-start]='0';
            else if(input[i]=='0')
                output[i-start]='1';
    }else{
        for(i= start; i<length; i++)
            output[i-start]=input[i];
    }

    output[i-start] ='\0';

    return output;
}

void convertIR(char * bin, int *op, int * rs, int *rt, int* rd, int *sh, int *fn, int *operand, int *jta){
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
    int tmp_operand;

    *op=convertDecimal(splitIR(bin,0,6));
    if(*op==0x001000||*op==0x001010||*op==0x001111)
        is_immed=True;
    else
        is_immed=False;
    *rs=convertDecimal(splitIR(bin,6,5));
    *rt=convertDecimal(splitIR(bin,11,5));
    *rd=convertDecimal(splitIR(bin,16,5));
    *sh=convertDecimal(splitIR(bin,21,5));
    *fn=convertDecimal(splitIR(bin,26,6));
    tmp_operand=convertDecimal(splitIR(bin,16,16));
    if(is_immed==True&&is_sign==True){
        tmp_operand+=1;
        tmp_operand=-tmp_operand;
    }
    *operand= tmp_operand;

    *jta=convertDecimal(splitIR(bin,6,26));
}
