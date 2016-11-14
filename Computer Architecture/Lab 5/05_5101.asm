\Устройства ввода-вывода
ACCEPT DEV[1] : I, 52h, 53h, 3, 2   \ Устройство ввода
ACCEPT DEV_BUF[1] : 0FFFh, 0FFFh  \ Буфер ввода (A ДК,B ПК)
ACCEPT DEV[2] : O, 0D2h, 0D3h, 3, 2 \ Устройство вывода
ACCEPT DEV[3] : O, 0D5h, 0D6h, 3, 2 \ Устройство вывода

DW 0CAh : 0C0h \ адрес А*
DW 0CCh : 0C2h \ адрес В*

\Область загрузки регистров
ACCEPT R5 : 0D6h
ACCEPT R6 : 0D3h \ РД устройства вывода
ACCEPT R7 : 030h \ Точка входа в программу
ACCEPT R9 : 053h \ РД устройства ввода

\Область загрузки программы
dw 30h: 0000100011000000% \ Считывание A по адресу 0C0h
dw 32h: 0000100011000010% \ Считывание B по адресу 0C2h
dw 34h: 0001010011001010% \ загрузка А по адресу А*
dw 36h: 0001110011001100% \ загрузка В по адресу В*
dw 38h: 0010000000000000% \ умножение
dw 3Ah: 0010100000000000% \ Запись результата в устройство вывода
dw 3Ch: 0011000000000000% \ Конец программы

\Настройка связей
LINK L1 : CT
LINK L2 : RDM
LINK L3 : RDD
LINK EWH : 16
LINK M : Z,Z,Z,Z,14,13,12,11,Z,Z,Z,Z

\Готовность устройств ввода-вывода
DW 022H : 80h
DW 0A2h : 80h

\Программа
BEGIN
 {CJP NZ, RPAK1;} \на распаковку

\Переходы по коду операций
org 000000010000% {CJP NZ, INPUT;}
org 000000100000% {CJP NZ, LOAD_A;}
org 000000110000% {CJP NZ, LOAD_B;}
org 000001000000% {CJP NZ, CALC;}
org 000001010000% {CJP NZ, OUTPUT;}
org 000001100000% {CJP NZ, END;}

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
 {ADD NIL, R7, Z, Z; OEY; EWL; }
 {XOR R8, R8, R8; }
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
 {XOR R15, R15, 10h; } \ CT

\ Формуэмо знак результату
 {XOR R14, R14, R11; }
 {XOR R14, R14, R12; LOAD RM, FLAGS;}

\Переводимо відємнине число Х в додатнє (за необхідності)
 {AND NIL, R12, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, PROV_Y; }
 {SUB R12, Z, R12, NZ; }

PROV_Y
 {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, MULT; }
 {SUB R11, Z, R11, NZ; }

 \ Множення
MULT
  {ADD NIL, R15, Z, Z; LOAD RN, FLAGS; }
  {CJP RN_Z, RESULT;}

  {AND NIL, R12, 08000h; LOAD RN, FLAGS; }
  {CJP NOT RN_N, SHIFT;}

  {ADD R13, R13, R11, Z;}

SHIFT
  {OR SLL, R13, R13, Z;}
  {OR SL.25, R12, R12, Z;}
  {SUB R15, R15, Z; }
  {CJP NZ, MULT; }

RESULT
 {OR SRL, R12, R12, R12; }
 {OR SR.9, R13, R13, R13; }
 {CJP NOT RM_N, FALC;}
 {XOR R12, R12, 8000h; }
 {CJP NZ, FALC;}

 OUTPUT
 {XOR R15, R15, R15;}
 {OR nil, R6, R6; OEY; EWL;}
 OUTX  {O; CJP RDD, OUTX; OR nil, R12, R15; OEY;}
 {OR nil, R5, R5; OEY; EWL;}
 OUTY  {O; CJP RDD, OUTY; OR nil, R13, R15; OEY;}
 {CJP NZ, FALC;}
END {}
