#include "MIPS.h"

extern int pc;

int break_point = 0;

int step(){
    unsigned int ir = MEM(pc, 0, 0, 2);

    int op, rt, rs, rd, sh, fn, offset, jta;
    convertIR(convertBinary(ir), &op, &rs, &rt, &rd, &sh, &fn, &offset, &jta);

    printf("PC : %x\n", pc);
    printf("op : %d rs : %d rt :  %d rd : %d sh : %d fn : %d, offset : %d, jta : %d \n", op, rs, rt, rd, sh, fn, offset, jta);

    if(op == 0x0){
        //R-format
        if (fn == 0x0) { // sll
            Reg(rd, ALU(Reg(rt, 0, 0), sh, SLL), 1);
            printf("SLL\t$%d\t$%d\t%d\n", rd, rt, sh);
        }else if (fn == 0x2){ // srl
            Reg(rd, ALU(Reg(rt, 0, 0), sh, SRL), 1);
            printf("SRL\t$%d\t$%d\t%d\n", rd, rt, sh);
        }else if (fn == 0x3){ // sra
            Reg(rd, ALU(Reg(rt, 0, 0), sh, SRA), 1);
            printf("SRA\t$%d\t$%d\t%d\n", rd, rt, sh);
        }else if (fn == 0x8){ //setPC
            setPc(Reg(ra, 0, 0) - 4);
            printf("JR\t$%x\n", Reg(ra, 0, 0));
        }else if (fn == 0xc){
            if (Reg(v0, 0, 0) == 10) {
                printf("\n SystemCall 10 \n");
                return syscall;
            }
        }else if (fn == 0x20){ // add
            Reg(rd, ALU(Reg(rs, 0, 0), Reg(rt, 0, 0), ADD), 1);
            printf("ADD\t$%d\t$%d\t$%d\n", rd, rs, rt);
        }else if(fn == 0x22){ // sub
            Reg(rd, ALU(Reg(rs, 0, 0), Reg(rt, 0, 0), SUB), 1);
            printf("SUB\t$%d\t$%d\t$%d\n",rd,rs,rt);
        }else if (fn == 0x24){ // and
            Reg(rd, ALU(Reg(rs, 0, 0), Reg(rt, 0, 0), AND), 1);
            printf("AND\t$%d\t$%d\t$%d\n",rd,rs,rt);
        }else if (fn == 0x25){ //or
            Reg(rd, ALU(Reg(rs, 0, 0), Reg(rt, 0, 0), OR), 1);
            printf("OR\t$%d\t$%d\t$%d\n",rd,rs,rt);
        }else if (fn == 0x26){ //xor
            Reg(rd, ALU(Reg(rs, 0, 0), Reg(rt, 0, 0), XOR), 1);
            printf("XOR\t$%d\t$%d\t$%d\n",rd,rs,rt);
        }else if (fn == 0x27){ //Nor
            Reg(rd, ALU(Reg(rs, 0, 0), Reg(rt, 0, 0), NOR), 1);
            printf("NOR\t$%d\t$%d\t$%d\n",rd,rs,rt);
        }else if (fn == 0x2a){ // slt
            Reg(rd, ALU(Reg(rt, 0, 0), sh, SL), 1);
            printf("SLT\t$%d\t$%d\t%d\n",rd,rt,sh);
        }else{
            printf("not defined command");
        }
    }else{
        if(op == 0x1){  // bltz
            if(Reg(rs, 0, 1) < 0){
                pc = pc + 4 * offset - 4;
            }
            printf("BLTZ\t$%d\t$%d\n",rs,offset);

        }else if(op == 0x2){   // j
            pc = jta*4 - 4;
            printf("J\t$%x\n",jta*4 - 4);

        }else if(op == 0x3){   // jal
            Reg(ra, pc + 4, 1);
            pc = jta*4 - 4;
            printf("JAL\t$%x\n",jta*4 - 4);
        }else if(op == 0x4){   // beq
            if (Reg(rs, 0, 0) == Reg(rt, 0, 0)) {
                pc = pc + 4 * offset - 4;
            }
            printf("BEQ\t$%d\t$%d\t$%d\n",rs,rt,offset);
        }else if(op == 0x5){   // bne
            if (Reg(rs, 0, 0) != Reg(rt, 0, 0)) {
                pc = pc + 4 * offset - 4;
            }
            printf("BNE\t$%d\t$%d\t$%d\n",rs,rt,offset);
        }else if(op == 0x8) {   // addi
            Reg(rt, (int)Reg(rs, 0, 0) + offset, 1);
            printf("ADDI\t$%d\t$%d\t%d\n",rt,rs,offset);

        }else if(op == 0xa){  // slti
            Reg(rt, Reg(rs, 0, 0) < offset, 1);
            printf("SLTI\t$%d\t$%d\t$%d\n",rt,rs,offset);

        }else if(op == 0xc){  // andi
            Reg(rt, Reg(rs, 0, 0) & offset, 1);
            printf("ANDDI\t$%d\t$%d\t$%d\n",rt,rs,offset);

        }else if(op == 0xd){  // ori
            Reg(rt, Reg(rs, 0, 0) | offset, 1);
            printf("ORI\t$%d\t$%d\t%d\n",rt,rs,offset);

        }else if(op == 0xe){  // xori
            Reg(rt, Reg(rs, 0, 0) ^ offset, 1);
            printf("XORI\t$%d\t$%d\t%d\n",rt,rs,offset);

        }else if(op == 0xf){  // lui
            Reg(rt, ALU(offset, 16, SLL),1);
            printf("LUI\t$%d\t$%d\n",rt,offset);

        }else if(op == 0x20){	// lb
            Reg(rs, MEM(rt + offset, 0, 0, 2), 1);
            printf("LB\t$%d\t%d($%d)\n",rt,offset,rs);

        }else if(op == 0x23){	// lw
            int value = MEM(Reg(rs, 0, 0) + offset, 0, 0, 2);
            Reg(rt, value, 1);
            printf("LW\t$%d\t%d($%d)\n",rt,offset,rs);

        }else if(op == 0x24){	// lbu
            Reg(rs, MEM(rt + offset, 0, 0, 2), 1);
            printf("LBU\t$%d\t%d($%d)\n",rt,offset,rs);

        }else if(op == 0x28){	// sb

            MEM(Reg(rs,0,0) + offset*4, Reg(rt, 0, 0), 1, 2);
            printf("SB\t$%d\t%d($%d)\n",rt,offset,rs);

        }else if(op == 0x2b){	// sw
            MEM(Reg(rs, 0, 0)+ offset, Reg(rt, 0, 0), 1, 2);
            printf("SW\t$%d\t%d($%d)\n",rt,offset,rs);
        }else{
            printf("not defined command");
        }
    }

    if(break_point == pc){
        pc += 4;
        return b_point;
    }

    pc += 4; // PC increase
    return 0;
}

void setBreakPoint(unsigned int sum){
    break_point = sum;
    printf("set break point : %x\n", break_point);
}