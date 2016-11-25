\-----------nastroiyka shemy---------------------
LINK L1 : CT
LINK L2 : RDM
LINK EWH : 16
LINK M : Z, Z, Z, Z, Z, Z, Z, Z, 14, 13, 12, 11

\----------------Data------------------------------
ACCEPT R7 : 020h \ RC

DW 04h : 0FFFh
DW 05h : 0FFFh

\-----------------Commands-------------------------
DW 20h : 0000100000000100% \ Mult (04h and 05 address)
DW 22h : 0001000000000000% \ end

\-----------------Microprogrammi-----------------
ORG 00h {CJP NZ, BEGIN; } \ Begin of program
ORG 01h {CJP NZ, CALC; } \ MULT of X and Y
ORG 02h {CJP NZ, END;} \ Ending program

\----------------Reading of command--------------
 BEGIN
 {OR NIL, R7, R7; OEY; EWL;}
 READCOMAND {R; CJP RDM, READCOMAND; OR R8, Z, BUS_D; }

 {AND NIL, R8, 08000h; LOAD RM, FLAGS; }
 {CJP RM_N, END;} \ If command have two operands

 {AND nil, R8, 400h; LOAD RM, FLAGS;}
 {CJP not RM_Z, END; }
 {OR NIL, R8, Z; OEY; JMAP; }

\----------LOAD X and Y to registers----------------------
LOADOP
 {AND R8, R8, 03FFh;}
 {XOR R10, R10, R10;}
 {XOR NIL, R15, R8; OEY; EWL; }
 READX {R; CJP RDM, READX; ADD R10, R10, BUS_D, Z; }

 {ADD R8, R8, 01h, Z;}
 {XOR R11, R11, R11; }
 {XOR NIL, R15, R8; OEY; EWL;}
 READY {R; CJP RDM, READY; ADD R11, R11, BUS_D, Z; }

 {CRTN NZ; }

\-----------MULT-----------------------------------------
 CALC
 {CJS NZ, LOADOP; } \ Loading operands

\ Формуэмо знак результату
 {XOR R14, R14, R11; }
 {XOR R14, R14, R10; LOAD RM, FLAGS;}

\Переводимо відємнине число Х в додатнє (за необхідності)
 {AND NIL, R10, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, PROV_Y; }
 {SUB R10, Z, R10, NZ; }

PROV_Y
 {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, SHIFTR; }
 {XOR R11, R11, 08000h; }

SHIFTR
  {OR SRL, R11, R11, Z;}
  {OR SR.9, R15, R15, Z;}

 \ Множення
MULT
  {ADD NIL, R10, 0FFFFh, Z; LOAD RN, FLAGS; }
  {CJP NOT RN_C, RESULT;}

  {AND NIL, R10, 08000h; LOAD RN, FLAGS; }
  {CJP NOT RN_N, SHIFT;}

  {ADD R13, R13, R15, Z; LOAD RN, FLAGS; }
  {ADD R12, R12, R11, RN_C;}

SHIFT
  {OR SRL, R11, R11, Z;}
  {OR SR.9, R15, R15, Z;}
  {OR SLL, R10, R10, Z;}
  {CJP NZ, MULT; }

RESULT
 {CJP NOT RM_N, NEXTCOMAND;}
 {XOR R12, R12, 8000h; }
 {CJP NZ, NEXTCOMAND;}

\-----------INC RC---------------------------------------
NEXTCOMAND
 {ADD R7, R7, 02h, Z; }
 {CJP NZ, BEGIN;}

END {}
