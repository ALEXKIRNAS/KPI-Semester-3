\-----------nastroiyka shemy---------------------
LINK L1 : CT
LINK L2 : RDM
LINK EWH : 16
LINK M : Z, Z, Z, Z, Z, Z, Z, Z, 14, 13, 12, 11

\----------------Data------------------------------
ACCEPT R7 : 020h \ RC

\ Operands
DW 5Eh : 8FFFh
DW 5Fh : 8FFFh

\-----------------Commands-------------------------
DW 20h : 0000100001011110% \ Mult (30h and 31 address)
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
 READY {R; CJP RDM, READY; ADD R11, R11, BUS_D, Z; }

 {CRTN NZ; }

\-----------MULT-----------------------------------------
 CALC
 {CJS NZ, LOADOP; } \ Loading operands
 {XOR R15, R15, 10h; } \ CT

\ Формуэмо знак результату
 {XOR nil, R10, R11; LOAD RM, FLAGS;}

\Переводимо відємнине число Х в додатнє (за необхідності)
 {AND NIL, R10, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, PROV_Y; }
 {XOR R10, R10, 08000h; }

PROV_Y
 {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, MULT; }
 {XOR R11, R11, 08000h; }

 \ Множення
MULT
  {ADD NIL, R15, Z, Z; LOAD RN, FLAGS; }
  {CJP RN_Z, RESULT;}

  {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
  {CJP NOT RN_N, SHIFT;}

  {ADD R12, R12, R10, Z;}

SHIFT
  {OR SLL, R12, R12, Z;}
  {OR SL.25, R11, R11, Z;}
  {SUB R15, R15, Z; }
  {CJP NZ, MULT; }

RESULT
 {OR SRL, R11, R11, R11; }
 {OR SR.9, R12, R12, R12; }
 {CJP NOT RM_N, NEXTCOMAND;}
 {XOR R11, R11, 0FFFFh; }
 {XOR R12, R12, 0FFFFh; }
 {ADD R12, R12, Z, NZ; LOAD RN, FLAGS; }
 {ADD R11, R11, Z, RN_C;}
 {CJP NZ, NEXTCOMAND;}

\-----------INC RC---------------------------------------
NEXTCOMAND
 {ADD R7, R7, 02h, Z; }
 {CJP NZ, BEGIN;}

END {}
