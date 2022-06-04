#include "MIPS.h"

int endian(unsigned int value , int s){
    if(s == 2){
        value = (value>>24) | ((value << 8) & 0x00ff0000) | ((value >> 8) & 0x0000ff00) | (value << 24);
    }else if(s == 1){
        value = (value>>8) | (value<<8);
    }

    return value;
}

unsigned int n_instruction(FILE * file){
    unsigned int num;
    fseek(file, 0, SEEK_SET);
    fread(&num, sizeof(int), 1, file);
    fseek(file, 0, SEEK_SET);
    num = endian(num, 2);
    return num;
}

unsigned int n_data(FILE* file){
    unsigned num;
    fseek(file, 4, SEEK_SET);
    fread(&num, sizeof(int), 1, file);
    fseek(file, 0, SEEK_SET);
    num = endian(num, 2);
    return num;
}



int decoding(char *cmd) {
    if (strcmp(cmd, "l")) {
        return 1;
    } else if (strcmp(cmd, "j")) {
        return 2;
    } else if (strcmp(cmd, "g")) {
        return 3;
    } else if (strcmp(cmd, "s")) {
        return 4;
    } else if (strcmp(cmd, "m")) {
        return 5;
    } else if (strcmp(cmd, "r")) {
        return 6;
    } else if (strcmp(cmd, "x")) {
        return 7;
    } else if (strcmp(cmd, "sr")) {
        return 8;
    } else if (strcmp(cmd, "sm")) {
        return 9;
    } else if (strcmp(cmd, "b")) {
        return 10;
    }
    return 0;
}
