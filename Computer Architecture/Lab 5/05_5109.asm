\Устройства ввода-вывода
ACCEPT DEV[1] : I, 52h, 53h, 3, 2   \ Устройство ввода
ACCEPT DEV_BUF[1] : 0F001h, 0F001h  \ Буфер ввода (X ДК, Y ДК, Z ДК)
ACCEPT DEV[2] : O, 0D2h, 0D3h, 3, 2 \ Устройство вывода
ACCEPT DEV[3] : O, 0D5h, 0D6h, 3, 2 \ Устройство вывода

DW 0CAh : 0C0h \ адрес X*
DW 0CCh : 0C2h \ адрес Y*
DW 0CEH : 0C4h \ адрес Z*

\Область загрузки регистров
ACCEPT R5 : 0D6h
ACCEPT R6 : 0D3h \ РД устройства вывода
ACCEPT R7 : 000h \ Точка входа в программу
ACCEPT R9 : 053h \ РД устройства ввода

\Область загрузки программы
dw 00h: 0000100011000000% \ Считывание X по адресу 0C0h
dw 02h: 0000100011000010% \ Считывание Y по адресу 0C2h
dw 04h: 0000100011000100% \ Считывание Z по адресу 0C4h
dw 06h: 0001010011001010% \ загрузка X по адресу X*
dw 08h: 0001110011001100% \ загрузка Y по адресу Y*
dw 0Ah: 0001110011001110% \ загрузка Z по адресу Z*
dw 0Ch: 0010000000000000% \ умножение
dw 0Eh: 0010100000000000% \ Запись результата в устройство вывода
dw 10h: 0011000000000000% \ Конец программы

\Настройка связей
LINK L1 : CT
LINK L2 : RDM
LINK L3 : RDD
LINK EWH : 16
LINK M : 14,13,12,11,Z,Z,Z,Z,Z,Z,Z,Z

\Готовность устройств ввода-вывода
DW 022H : 80h
DW 0A2h : 80h

\Программа
BEGIN
 {CJP NZ, RPAK1;} \на распаковку

\Переходы по коду операций
org 000100000000% {CJP NZ, INPUT;}
org 001000000000% {CJP NZ, LOAD_A;}
org 001100000000% {CJP NZ, LOAD_B;}
org 010000000000% {CJP NZ, CALC;}
org 010100000000% {CJP NZ, OUTPUT;}
org 011000000000% {CJP NZ, END;}

INPUT
 {AND R8, R8, 03FFh;}
 {CJS NZ, MMP_I; } \ Считывание в R10
 {OR NIL, R8, Z; OEY; EWL; }
  WRITE {W; CJP RDM, WRITE; OR NIL, R10, Z; OEY;} \Запись по адресу из R8
 {CJP NZ, FALC;}

MMP_I
 {XOR R10, R10, R10; }
 {OR NIL, R9, Z; OEY; EWL;}
 READIN {I; CJP RDD, READIN; OR R10, BUS_D, Z; }
 {CRTN NZ;}

RPAK2
 {CJP NZ, END;} \ TODO

RPAK1
 {ADD NIL, R7, Z, Z; OEY; EWL; }
 {XOR R8, R8, R8; }
 SS1
 {R; CJP RDM, SS1; ADD R8, BUS_D, Z;}
 {ADD NIL, R8, Z, Z; CJP NO, RPAK2; } \Условный переход на двуадресную команду
 {XOR R10, R10, R10;}
 {ADD R10, R10, 0400h; }
 {AND NIL, R8, R10; CJP NOT ZO, KA; } \Условный переход на косвенную адресацию

PA
 {XOR R10, R10, R10;}
 {ADD R10, Z, 03FFh;} \ Mask
 {AND NIL, R10, R8; OEY; EWL;}
 SS2
 {R; CJP RDM, SS2; ADD R15, BUS_D, Z;}
 {CJP NZ, KOP;} \Переход по коду операции

KA
 {XOR R10, R10, R10;}
 {ADD R10, Z, 03FFh;} \ Mask
 {AND NIL, R10, R8; OEY; EWL;}
 {XOR R8, R8, R8;}
 SS3
 {R; CJP RDM, SS3; ADD R8, BUS_D, Z;}
 {XOR R10, R10, R10;}
 {ADD R10, Z, 0FFFFh;} \ Mask
 {AND NIL, R8, R10; OEY; EWL;}
 SS4
 {R; CJP RDM, SS4; ADD R15, BUS_D, Z;}

 {XOR R8, R8, R8; }
 {ADD NIL, R7, Z, Z; OEY; EWL; }
 SS5
 {R; CJP RDM, SS5; ADD R8, BUS_D, Z;}
 {CJP NZ, KOP;} \Переход по коду операции

KOP
 {ADD NIL,R8,z,z; OEY; EWL; JMAP; }

LOAD_A
 {XOR R11, R11, R11;}
 {ADD R11, R11,R15;}
 {XOR R15, R15, R15;}
 {CJP NZ, FALC;}

LOAD_B
 {XOR R12, R12, R12;}
 {ADD R12, R12,R15;}
 {XOR R15, R15, R15;}
 {CJP NZ, FALC;}

FALC
 {ADD R7,R7,02h;}
 {CJP NZ,BEGIN;}

CALC

  {XOR R15, R15, R15;}
\ Формуэмо знак результату
 {XOR R14, R14, R11; }
 {XOR R14, R14, R12; LOAD RM, FLAGS;}
 {XOR R14, R14, R14; }

\ Переводимо відємнине число Х в додатнє (за необхідності)
 {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, PROV_Y; }
 {SUB R11, Z, R11, NZ; }

 PROV_Y
 {AND NIL, R12, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, SHIT; }
 {SUB R12, Z, R12, NZ;}

 SHIT
  {OR SRL, R12, R12, Z;}
  {OR SR.9, R15, R15, Z;}

 \ Множення
 MULT
  {ADD NIL, R11, 0FFFFh, Z; LOAD RN, FLAGS; }
  {CJP NOT RN_C, RESULT;}
  {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
  {CJP NOT RN_N, SHIFT;}

  {ADD R14, R14, R15, Z; LOAD RN, FLAGS; }
  {ADD R13, R13, R12, RN_C;}

 SHIFT
  {OR SRL, R12, R12, Z;}
  {OR SR.9, R15, R15, Z;}
  {OR SLL, R11, R11, Z;}
  {CJP NZ, MULT; }

RESULT
 {CJP NOT RM_N, FALC;}
 {XOR R14, R14, 0FFFFh;}
 {XOR R13, R13, 0FFFFh;}
 {ADD R14, R14, Z, NZ; LOAD RN, FLAGS; }
 {ADD R13, R13, Z, RN_C; }
 {CJP NZ, FALC;}

 OUTPUT
 {XOR R15, R15, R15;}
 {OR nil, R6, R6; OEY; EWL;}
 OUTX  {O; CJP RDD, OUTX; OR nil, R13, R15; OEY;}
 {OR nil, R5, R5; OEY; EWL;}
 OUTY  {O; CJP RDD, OUTY; OR nil, R14, R15; OEY;}
 {CJP NZ, FALC;}

END {}
