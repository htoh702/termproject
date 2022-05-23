#include <stdio.h>
#define M_SIZE 1024

unsigned int MEM[M_SIZE];

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

void mempryRead(unsigned int addr){
    int opcode, function;
    char *inst;
    function = MEM[addr] & 0x3f;
    opcode = (MEM[addr] >> 24) & 0xfc;
    if((opcode >> 2) == 0x00){
        if(function == 0x00){
            inst = "sll";
        }else if(function == 0x02){
            inst = "srl";
        }else if(function == 0x03){
            inst = "sra";
        }else if(function == 0x08){
            inst = "jr";
        }else if(function == 0x0c){
            inst = "svscall";
        }else if(function == 0x10){
            inst = "mfhi";
        }else if(function == 0x12){
            inst = "mflo";
        }else if(function == 0x18){
            inst = "mul";
        }else if(function == 0x20){
            inst = "add";
        }else if(function == 0x22){
            inst = "sub";
        }else if(function == 0x24){
            inst = "and";
        }else if(function == 0x25){
            inst = "or";
        }else if(function == 0x26){
            inst = "xor";
        }else if(function == 0x27){
            inst = "nor";
        }else if(function == 0x2b){
            inst = "slt";
        }
    }
    else{
        if((opcode >> 2) == 0x01){
            inst = "bltz";
        }else if((opcode >> 2) == 0x02){
            inst = "j";
        }else if((opcode >> 2) == 0x03){
            inst = "jal";
        }else if((opcode >> 2) == 0x04){
            inst = "beq";
        }else if((opcode >> 2) == 0x05){
            inst = "bne";
        }else if((opcode >> 2) == 0x08){
            inst = "addi";
        }else if((opcode >> 2) == 0x0a){
            inst = "slti";
        }else if((opcode >> 2) == 0x0c){
            inst = "andi";
        }else if((opcode >> 2) == 0x0d){
            inst = "ori";
        }else if((opcode >> 2) == 0x0e){
            inst = "xori";
        }else if((opcode >> 2) == 0x0f){
            inst = "lui";
        }else if((opcode >> 2) == 0x20){
            inst = "lb";
        }else if((opcode >> 2) == 0x23){
            inst = "lw";
        }else if((opcode >> 2) == 0x24){
            inst = "lbu";
        }else if((opcode >> 2) == 0x28){
            inst = "sb";
        }else if((opcode >> 2) == 0x2b){
            inst = "sw";
        }
    }
    printf("Opc:\t%x,\tFct:\t%x,\tInst:\t%s\n", opcode >> 2, function, inst);
}

void memoryWrite(){
    printf("Number of Instructions: %d, Number of Data: %d\n", MEM[0], MEM[1]);
    for(int i=2;i<(int)MEM[0]+2;i++){
        mempryRead(i);
    }
}

int main() {
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    FILE *fp3 = NULL;
    FILE *fp4 = NULL;
    errno_t err;
    int count, data;

    err = fopen_s(&fp1, "C:\\Users\\htoh7\\CLionProjects\\untitled1\\as_ex01_arith.bin", "rb");
    if(err){
        printf("Cannot open file\n");
        return 1;
    }
    int i=0;
    while(1){
        count = fread(&data, sizeof(data), 1, fp1);
        if(count!=1){
            break;
        }
        MEM[i] = endian(data);
        i++;
    }
    memoryWrite();

    fclose(fp1);

    printf("\n");
    err = fopen_s(&fp2, "C:\\Users\\htoh7\\CLionProjects\\untitled1\\as_ex02_logic.bin", "rb");
    if(err){
        printf("Cannot open file\n");
        return 1;
    }
    i=0;
    while(1){
        count = fread(&data, sizeof(data), 1, fp2);
        if(count!=1){
            break;
        }
        MEM[i] = endian(data);
        i++;
    }
    memoryWrite();

    fclose(fp2);

    printf("\n");
    err = fopen_s(&fp3, "C:\\Users\\htoh7\\CLionProjects\\untitled1\\as_ex03_ifelse.bin", "rb");
    if(err){
        printf("Cannot open file\n");
        return 1;
    }
    i=0;
    while(1){
        count = fread(&data, sizeof(data), 1, fp3);
        if(count!=1){
            break;
        }
        MEM[i] = endian(data);
        i++;
    }
    memoryWrite();

    fclose(fp3);

    printf("\n");
    err = fopen_s(&fp4, "C:\\Users\\htoh7\\CLionProjects\\untitled1\\as_ex04_fct.bin", "rb");
    if(err){
        printf("Cannot open file\n");
        return 1;
    }
    i=0;
    while(1){
        count = fread(&data, sizeof(data), 1, fp4);
        if(count!=1){
            break;
        }
        MEM[i] = endian(data);
        i++;
    }
    memoryWrite();

    fclose(fp4);
    return 0;
}
