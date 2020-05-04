#include "Base.h"

/*
 * /r – сигналізує про те, що команда має байт mod r/m, в якому поле reg містить номер регістра даних;
 * /цифра (від 0 до 7) – сигналізує про те, що команда має байт mod r/m, в якому поле reg містить частину коду операції;
 * r/m8 r/m16 r/m32 – сигналізує про те, що команда має байт mod r/m, в якому поле r/m може містити або номер
 * регістра даних відповідної розрядності, або команда формує ефективну адресу (зміщення в сегменті) пам’яті
 * для даних відповідної розрядності; ea16, ea32 – створювана процесором ефективна адреса (зміщення в сегменті)
 * на основі байту\байтів режиму адресації (modR\m або modR\m і Sib) та зміщення в команді (displacement);
 * r8, r16, r32 – операнд в одному з регістрів розміром байт, слово чи подвійне слово;
 * ib, iw, id (або іmm8, іmm16, іmm32) – безпосередній операнд розміром байт, слово чи подвійне слово;
 * cb, cw, cd – зміщення в команді; +rb, +rw, +rd – байт коду операції команди в молодших трьох бітах містить
 * номер регістра даних відповідної розрядності. ptr16:16 – логічна адреса – сегментна складова : зміщення всегменті
 */


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
                 {"mov", "dec", "test", "push", "bts", "jz", "stosd", "add", "cmp",   "das", "lods", "or", "rol", "jg"}},

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
        {"eax","al",0b000},
        {"ecx","cl",0b001},
        {"edx","dl",0b010},
        {"ebx","bl",0b011},
        {"esp","ah",0b100},
        {"ebp","ch",0b101},
        {"esi","dh",0b110},
        {"edi","bh",0b111}};

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

//vector<pair<int , string>> ModTable = {
//        {0b00,"reg32"},
//        {0b01,'2'},
//        {0b10,'4'},
//        {0b11,'8'},
//};