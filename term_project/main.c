#include "MIPS.h"

extern int *reg;

int main(int argc, char* argv[]) {
    FILE *file = NULL;


    int temp, target, result, start, end, location, value, n_register;
    unsigned char data;
    char address[200];
    char cmd[10];
    char sum1[100];
    char sum2[100];
    int check = 0;

    allocate_register();

    printf("command List\nl : Load program\nj : jump program\ng : Go program\ns : step\nm : View memory\nr : View register\nb : Set break point\nx : program exit\nsr : set register\nsm : set memory\nlist : show list\n");
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

        if(strcmp(cmd, "l")==0){
            printf("load file : ");
            scanf("%s", sum1);
            file = fopen(sum1, "rb+");
            if(file == NULL){
                printf("\ncan't open FILE\n");
                check = 0;
                continue;
            }
            check++;
            setPc(0x00400000);
            int i_size = n_instruction(file);
            int d_size = n_data(file);

            printf("number of instruction : %d, number of data : %d\n", i_size, d_size);

            fflush(stdout);
            fseek(file, 8, SEEK_SET);

            for(int i=0;i<i_size*4;i++){
                fread(&data, 1, 1, file);
                MEM(0x00400000 + i, data, 1, 0);
            }
            for(int i=0;i<d_size*4;i++){
                fread(&data, 1, 1,file);
                MEM(0x10000000 + i, data, 1, 0);
            }

            fclose(file);

        }else if(strcmp(cmd, "j")==0){
            printf("destination address : ");
            scanf("%x", &target);
            setPc(target);

        }else if(strcmp(cmd, "g")==0){
            result =0;
            while(result != syscall){
                printf("\n");
                result = step();
                if(result == b_point){
                    printf("breakpoint\n");
                    break;
                }
            }
            if(result == syscall){
                printf("\nprogram exit by systemcall\n");
            }
        }else if(strcmp(cmd, "s")==0){
            result = step();
            if(result == syscall){
                printf("\nprogram exit by systemcall\n");
            }else if(result == b_point){
                printf("break point\n");
            }

        }else if(strcmp(cmd, "m")==0){
            printf("start address : ");
            scanf("%s", sum1);
            printf("end address : ");
            scanf("%s", sum2);

            start = (unsigned)strtoul(sum1, NULL, 16);
            end = (unsigned)strtoul(sum2, NULL, 16);

            if(!(start && end)){
                printf("failed\n");
            }else{
                getMemory(start, end);
            }

        }else if(strcmp(cmd, "r")==0){
            getRegister();

        }else if(strcmp(cmd, "b")==0){
            printf("set break point :");
            scanf("%s", sum1);
            if(strcmp(sum1, "cancel")==0){
                printf("break point cancel\n");
                setBreakPoint(0);
            }else{
                temp = (unsigned)strtoul(sum1, NULL, 16);
                setBreakPoint(temp);
            }

        }else if(strcmp(cmd, "x")==0){
            printf("exit program\n");
            return 0;
        }else if(strcmp(cmd, "sr")==0){
            printf("register number : ");
            scanf("%s", sum1);
            printf("value : ");
            scanf("%s", sum2);
            n_register = atoi(sum1);
            value = (unsigned int)strtoul(sum2, NULL, 16);

            if(!value){
                printf("wrong value\n");
            }else if(n_register > 31 || n_register < 0){
                printf("wrong value\n");
            }else{
                Reg(n_register, value, 1);
            }

        }else if(strcmp(cmd, "sm")==0){
            printf("memory's location : ");
            scanf("%s", sum1);
            printf("value : ");
            scanf("%s", sum2);
            location = (unsigned)strtoul(sum1, NULL, 16);
            value = atoi(sum2);

            if(setMemory(location, value)==0){
                printf("memory %0x is set to be %d\n", location, value);
            }else{
                printf("failed\n");
            }
        }else if(strcmp(cmd, "list")==0) {
            printf("command List\nl : Load program\nj : jump program\ng : Go program\ns : step\nm : View memory\nr : View register\nb : Set break point\nx : program exit\nsr : set register\nsm : set memory\nlist : show list\n");
        }else{
                printf("error(no command)\n");
        }
    }
    free(reg);

    return 0;
}
