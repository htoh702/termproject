#include "MIPS.h"

extern int pc;

int break_point = 0;

int step(){
    unsigned int ir = MEM(pc, 0, 0, 2);

    int op, rt, rs, rd, sh, fn, offset, jta;
    convertIR(convertBinary(ir), &op, &rs, &rt, &rd, &sh, &fn, &offset, &jta);
    //split 32bits
//	printf(
//			"op = %d rs =%d rt = %d rd = %d sh = %d fn = %d, offset = %d, jta = %d \n",
//			op, rs, rt, rd, sh, fn, offset, jta);
    printf("현재 PC : %x\n", pc);
//	printf("IR : %x\n", IR);
    if (op == 0) {
        //R-format
        if (fn == 32) { // add
            Reg(rd, ALU(ADD, Reg(rs, 0, 0), Reg(rt, 0, 0)), 1);
            printf("ADD\t$%d\t$%d\t$%d\n",rd,rs,rt);
        } else if (fn == 34) { // sub
            Reg(rd, ALU(SUB, Reg(rs, 0, 0), Reg(rt, 0, 0)), 1);
            printf("SUB\t$%d\t$%d\t$%d\n",rd,rs,rt);
        } else if (fn == 0) { // sll
            Reg(rd, ALU(SLL, Reg(rt, 0, 0), sh), 1);
            printf("SLL\t$%d\t$%d\t%d\n",rd,rt,sh);
        } else if (fn == 2) { // srl
            Reg(rd, ALU(SRL, Reg(rt, 0, 0), sh), 1);
            printf("SRL\t$%d\t$%d\t%d\n",rd,rt,sh);
        } else if (fn == 3) { // sra
            Reg(rd, ALU(SRA, Reg(rt, 0, 0), sh), 1);
            printf("SRA\t$%d\t$%d\t%d\n",rd,rt,sh);
        } else if (fn == 42) { // set less
            Reg(rd, ALU(SL, Reg(rt, 0, 0), sh), 1);
            printf("SL\t$%d\t$%d\t%d\n",rd,rt,sh);
        } else if (fn == 36) { // and
            Reg(rd, ALU(AND, Reg(rs, 0, 0), Reg(rt, 0, 0)), 1);
            printf("AND\t$%d\t$%d\t$%d\n",rd,rs,rt);
        } else if (fn == 37) { //or
            Reg(rd, ALU(OR, Reg(rs, 0, 0), Reg(rt, 0, 0)), 1);
            printf("OR\t$%d\t$%d\t$%d\n",rd,rs,rt);
        } else if (fn == 38) { //xor
            Reg(rd, ALU(XOR, Reg(rs, 0, 0), Reg(rt, 0, 0)), 1);
            printf("XOR\t$%d\t$%d\t$%d\n",rd,rs,rt);
        } else if (fn == 39) { //Nor
            Reg(rd, ALU(NOR, Reg(rs, 0, 0), Reg(rt, 0, 0)), 1);
            printf("NOR\t$%d\t$%d\t$%d\n",rd,rs,rt);
        } else if (fn == 12) {
            if (Reg(v0, 0, 0) == 10) {
                printf("\n SystemCall 10 \n");
                // v0 is 10 -> return
                return 500;
                // syscall 10 -> return 500
            }
        } else if (fn == 8) { //setPC
            setPc(Reg(ra, 0, 0)-4);
            printf("JR\t$%x\n",Reg(ra, 0, 0));
        } else {
            printf("not defined command");
        }
    } else {

        if (op == 1) {
            // I-format. bltz
            // REG(ra, PC, 1);
            if(Reg(rs, 0, 1) < 0) {
                pc = pc + 4 * offset - 4;
            }
            printf("bltz\t$%d\t$%d\n",rs,offset);

        } else if (op == 2) {
            // j-format. j
            pc = jta*4 - 4;
            printf("J\t$%x\n",jta*4 - 4);

        } else if (op == 3) {
            Reg(ra, pc + 4, 1);

            //setPC(PC + (jta & 0x000FFFFF));
            pc = jta*4 - 4;
            //printf("\n jump target adr : %x\n", jta);
            printf("jal\t$%x\n",jta*4 - 4);
        } else if (op == 4) {
            //beq
            if (Reg(rs, 0, 0) == Reg(rt, 0, 0)) {
                // REG(ra, PC, 1);
                pc = pc + 4 * offset - 4;
            }
            printf("beq\t$%d\t$%d\t$%d\n",rs,rt,offset);
        } else if (op == 5) {
            //bne
            if (Reg(rs, 0, 0) != Reg(rt, 0, 0)) {
                // REG(ra, PC, 1);
                pc = pc + 4 * offset - 4;
            }
            printf("bne\t$%d\t$%d\t$%d\n",rs,rt,offset);
        } else if (op == 8) {
            //addi
            Reg(rt, (int)Reg(rs, 0, 0) + offset, 1);
            printf("\n operand is %d, %x\n", offset, Reg(sp, 0, 0));
            printf("addi\t$%d\t$%d\t%d\n",rt,rs,offset);

        } else if (op == 10) {
            //slti
            Reg(rt, Reg(rs, 0, 0) < offset, 1);
            printf("slti\t$%d\t$%d\t$%d\n",rt,rs,offset);

        } else if (op == 12) {
            //andi
            Reg(rt, Reg(rs, 0, 0) & offset, 1);
            printf("andi\t$%d\t$%d\t$%d\n",rt,rs,offset);

        } else if (op == 13) {
            //ori
            Reg(rt, Reg(rs, 0, 0) | offset, 1);
            printf("ori\t$%d\t$%d\t%d\n",rt,rs,offset);

        } else if (op == 14) {
            //xori
            Reg(rt, Reg(rs, 0, 0) ^ offset, 1);
            printf("xori\t$%d\t$%d\t%d\n",rt,rs,offset);

        } else if (op == 15) {

            Reg(rt, ALU(SLL, offset, 16),1);
            printf("lui\t$%d\t$%d\n",rt,offset);

        } else if (op == 32) {			//lb
            Reg(rs, MEM(rt + offset, 0, 0, 2), 1);
            printf("lb\t$%d\t%d($%d)\n",rt,offset,rs);

        } else if (op == 35) {			//lw
            int value = MEM(Reg(rs, 0, 0) + offset, 0, 0, 2);
            Reg(rt, value, 1);
            printf("lw\t$%d\t%d($%d)\n",rt,offset,rs);

        } else if (op == 36) {			//lbu
            Reg(rs, MEM(rt + offset, 0, 0, 2), 1);
            printf("lbu\t$%d\t%d($%d)\n",rt,offset,rs);

        } else if (op == 40) {			//sb

            MEM(Reg(rs,0,0) + offset*4, Reg(rt, 0, 0), 1, 2);
            printf("sb\t$%d\t%d($%d)\n",rt,offset,rs);

        } else if (op == 43) {				//sw
            MEM(Reg(rs, 0, 0)+ offset, Reg(rt, 0, 0), 1, 2);
            printf("sw\t$%d\t%d($%d)\n",rt,offset,rs);
            //printf("메모리 저장된거 확인하기 :%d\n", MEM(REG(rs, 0, R)+ offset, 0, 0, WORD));
        } else {
            printf("not defined command");
        }
    }

    if (break_point == pc) {
        pc += 4;
        return 100;
    }

    pc += 4; // PC increase
    return 0;
}

void setBreakPoint(unsigned int argv1){
    break_point = argv1;
    printf("set break point : %x\n", break_point);
}