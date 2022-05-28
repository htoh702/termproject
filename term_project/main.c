#include "MIPS.h"

extern int *reg;

int main(int argc, char* argv[]) {
    FILE *file = NULL;

    errno_t err;
    int temp, target, result, start, end, location, value;
    unsigned char data;
    char address[200];
    char cmd[10];
    char sum1[100];
    char sum2[100];
    int check = 0;
    printf("command List\nl : Load program\nj : jump program\ng : Go program\ns : step\nm : View memory\nr : View register\nb : Set break point\nx : program exit\nsr : set register\nsm : set memory\n");
    while(1){
        printf("command : ");
        fflush(stdout);
        scanf("%s", cmd);

        if((check==0)&&(strcmp(cmd, "l") != 0)){
            if(strcmp(cmd, "x") == 0){
                printf("Program exit\n");
                break;
            }
            printf("Load binary file first\n");
            continue;
        }

        switch(decoding(cmd)){
            case 1:     // load program
                printf("load file : ");
                scanf("%s", sum1);
                file = fopen(sum1, "rb+");
                if(file == NULL){
                    printf("\ncan't open FILE\n");
                    check = 0;
                    break;
                }
                setPc(0x00400000);
                int i_size = n_instruction(file);
                int d_size = n_data(file);
                fflush(stdout);
                fseek(file, 8, SEEK_SET);

                for(int i=0;i<i_size*4;i++){
                    fread(&data, 1, 1, file);
                    MEM(0x00400000+i, data, 1, 0);
                }
                for(int i=0;i<d_size*4;i++){
                    fread(&data, 1, 1,file);
                    MEM(0x10000000 + i, data, 1, 0);
                }
                fclose(file);
                check++;
                break;
//            case 2:     // jump
//                printf("destination address : ");
//                scanf("%x", &target);
//                setPc(target);
//                break;
//            case 3:     // go
//                result =0;
//                while(result != 500){
//                    printf("\n");
//                    result = step();
//                    if(result == 100){
//                        printf("breakpoint\n");
//                        break;
//                    }
//                }
//                if(result == 500){
//                    printf("\nprogram exit by systemcall\n");
//                    setPc(0x00400000);
//                }
//            case 4:     // step
//                result = step();
//                if(result == 500){
//                    printf("\nprogram exit by systemcall\n");
//                    setPc(0x00400000);
//                }else if(result == 100){
//                    printf("break point\n");
//                }
//                break;
//            case 5:     // view memory
//                scanf("start address : %s", sum1);
//                scanf("end address : %s", sum2);
//
//                start = (unsigned)strtoul(sum1, NULL, 16);
//                end = (unsigned)strtoul(sum2, NULL, 16);
//
//                if(!(start && end)){
//                    printf("failed\n");
//                }else{
//                    getMemory(start, end);
//                }
//                break;
//            case 6:     // view register
//                getRegister();
//                break;
//            case 7:     // quit program
//                printf("quit program\n");
//                return 0;
//            case 8:     // set register
//                scanf("%s", sum1);
//                scanf("%s", sum2);
//                location = (unsigned)strtoul(sum1, NULL, 16);
//                value = atoi(sum2);
//
//                if(setMemory(location, value)==0){
//                    printf("memory %0x is set to be %d", location, value);
//                }else {
//                    printf("failed\n");
//                }
//                break;
//            case 9:     // set memory
//                scanf("%s", sum1);
//                scanf("%s", sum2);
//                location = (unsigned)strtoul(sum1, NULL, 16);
//                value = atoi(sum2);
//
//                if(setMemory(location, value)==0){
//                    printf("memory %0x is set to be %d\n", location, value);
//                }else{
//                    printf("failed\n");
//                }
//
//            case 10:     // set break point
//                scanf("%s", sum1);
//                if(strcmp(sum1, "off")){
//                    printf("break point cancel");
//                    setBreakPoint(0);
//                }else{
//                    temp = (unsigned)strtoul(sum1, NULL, 16);
//                    setBreakPoint(temp);
//                }
//                break;
            default:
                printf("error(no command)\n");
        }
    }
    free(reg);

    return 0;
}
