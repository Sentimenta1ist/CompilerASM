#include "Base.h"

int DispMain = 0;

vector<vector<lexeme>> AllTokens;

vector<struct_of_sentence> AllStruct;

vector<User> MassOfUser;

vector<OneSegment> AllSegments;

vector <ElementOfDisp> MassOfDisp;

/*
 * Dictionary of token
 * If u wanna add instruction to "compi":
 *      1) add to DictionaryOfTokens
 *      2) add to MachineCodeInstruction with another data
 *      3) add to Accessed vector with operands that you want
 */
vector<pair<string, vector<string>>> DictionaryOfTokens ={
         {reg,
                 {"eax", "ebx", "ecx",  "edx",  "esi", "edi", "ebp", "al", "bl", "dl",  "cl","ax","bx","cx","dx","di","si"}},

         {instruction,
                 {"mov", "dec", "test", "push", "bts", "jz", "stosd", "add", "cmp","and", "das", "lods", "or", "rol", "jg"}},

         {JumpInstr,
                 {"jz"}},

         {directive,
                 {"db", "dd", "equ"}},

         {directiveIf,
                 {"if", "endif"}},

         {labelSeg,
                 {"data", "code"}},

         {segmentWord,
                 {"segment", "ends", "end"}},

         {registerSeg,
                 {"ds", "cs", "gs", "fs", "bs", "ss"}}};

    vector<registerValue> RegistersTable = {
        {"eax", "ax", "al", 0b000},
        {"ecx", "cx", "cl", 0b001},
        {"edx", "dx", "dl", 0b010},
        {"ebx", "bx", "bl", 0b011},
        {"esp", "sp", "ah", 0b100},
        {"ebp", "bp", "ch", 0b101},
        {"esi", "si", "dh", 0b110},
        {"edi", "di", "bh", 0b111}};

vector<pair<int , char>> ScaleTable = {
        {0b00,'1'},
        {0b01,'2'},
        {0b10,'4'},
        {0b11,'8'},
};

vector <PrefixSegments> TableOfPrefixesSegment{
        {"ds","DATA",0x3E},
        {"cs","CODE",0x2E},
        {"ss","NOTHING",0x36},
        {"es","NOTHING",0x26},
        {"gs","NOTHING",0x65},
        {"fs","NOTHING",0x64}
};

//vector<ModRMLine> ModTable= {
//        {0b11,REG32,REG32},
//        {0b11,REG8,REG8},
//        {0b00,REG},
//        {0b10},
//        {0b11},
//};
//


/*
 * 80 /0 ib     ADD r/m8, imm8
 * 81 /0 id     ADD r/m32, imm32
 * 83 /0 ib     ADD r/m32, imm8
 *
 * 6A   PUSH imm8
 * 68   PUSH imm32
 *
 * 3A /r    CMP r8, r/m8
 * 3B /r    CMP r32, r/m32
 *
 * B0+rb    MOV reg8, imm8
 * B8+rw    MOV reg16, imm16
 * B8+rd    MOV reg32, imm32
 *
 * 84 /r    TEST r/m8, r8
 * 85 /r    TEST r/m32, r32
 *
 * 48+rd    DEC r32
 * FE /1    DEC r/m8
 *
 * 0FAB     BTS r/m32, r32
 *
 * AB   STOSD
 *
 * 74 cb    JZ rel8     Якщо нуль (ZF = 1)
 */

/*
 * /r – сигналізує про те, що команда має байт mod r/m, в якому поле reg містить номер регістра даних;
 *
 * /цифра (від 0 до 7) – сигналізує про те, що команда має байт mod r/m, в якому поле reg містить частину коду операції;
 *
 * r/m8 r/m16 r/m32 – сигналізує про те, що команда має байт mod r/m, в якому поле r/m може містити або номер
 * регістра даних відповідної розрядності, або команда формує ефективну адресу (зміщення в сегменті) пам’яті
 * для даних відповідної розрядності;
 *
 * ea16, ea32 – створювана процесором ефективна адреса (зміщення в сегменті)
 * на основі байту\байтів режиму адресації (modR\m або modR\m і Sib) та зміщення в команді (displacement);
 *
 * r8, r16, r32 – операнд в одному з регістрів розміром байт, слово чи подвійне слово;
 *
 * ib, iw, id (або іmm8, іmm16, іmm32) – безпосередній операнд розміром байт, слово чи подвійне слово;
 *
 * cb, cw, cd – зміщення в команді;
 *
 * +rb, +rw, +rd – байт коду операції команди в молодших трьох бітах містить
 * номер регістра даних відповідної розрядності.
 *
 * ptr16:16 – логічна адреса – сегментна складова : зміщення всегменті
 */


vector<MachineCodeInstructionStruct> MachineCodeInstruction{  //create for 32 bit operands
        {"add",MEM32,IMM8, 0x83,1},
        {"add",MEM32,IMM32, 0x81,1 },
        {"add",MEM8,IMM8, 0x80,1 },

        {"push",IMM32,NoOperand,0x68,0 },
        {"push",IMM8,NoOperand,0x6A,0 },

        {"cmp",REG32,REG32,0x3B,1},
        {"cmp",REG8,REG8,0x3A,1},

        {"test",REG32,MEM32,0x85,1},
        {"test",REG8,MEM8,0x84,1},
        {"test",MEM32,REG32,0x85,1},
        {"test",MEM8,REG8,0x84,1},

        {"stosd",NoOperand, NoOperand,0xAB},

        {"mov", REG32,IMM32,0xB8,0,1},
        {"mov", REG8,IMM8,0xB0,0,1},

        {"dec",REG8,NoOperand,0xFE,1,0},
        {"dec",REG32,NoOperand,0x48,0,1},

        {"bts",MEM32,REG32,0x0FAB},

        {"and",REG32,REG32,0x21,1},
        {"and",REG8,REG8,0x20,1},
};

vector<MachineCodeDirectiveStruct> MachineCodeDirective{
        {"db",0,1},
        {"dd",0,4},
        {"equ",0,0}
};
