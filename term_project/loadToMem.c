#include "MIPS.h"

int endian(unsigned int value , int s){
    if(s == 2){ // word 단위로 변환
        value = (value>>24) | ((value << 8) & 0x00ff0000) | ((value >> 8) & 0x0000ff00) | (value << 24);
    }else if(s == 1){   // Half word 단위로 변환
        value = (value>>8) | (value<<8);
    }

    return value;
}


unsigned int n_instruction(FILE * file){    // 명령어 개수
    unsigned int num;
    fseek(file, 0, SEEK_SET);
    fread(&num, sizeof(int), 1, file);
    fseek(file, 0, SEEK_SET);
    num = endian(num, 2);
    return num;
}

unsigned int n_data(FILE* file){        // 데이터 개수
    unsigned num;
    fseek(file, 4, SEEK_SET);
    fread(&num, sizeof(int), 1, file);
    fseek(file, 0, SEEK_SET);
    num = endian(num, 2);
    return num;
}

