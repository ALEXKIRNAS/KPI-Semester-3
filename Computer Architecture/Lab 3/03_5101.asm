\-----------nastroiyka shemy---------------------
LINK L1 : CT
LINK L2 : RDM
LINK EWH : 16
LINK M : Z, Z, Z, Z, Z, Z, Z, Z, 14, 13, 12, 11

\----------------Data------------------------------
ACCEPT R7 : 020h \ RC
\ Addresses of operands
DW 5Eh : 54h
DW 5Fh : 55h

\ Operands
DW 54h : 0FFFh
DW 55h : 0F001h

\-----------------Commands-------------------------
DW 20h : 0000110001011110% \ Mult (30h and 31 address)
DW 22h : 0001010000000000% \ end

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
 {CJP RM_Z, END; }
 {OR NIL, R8, Z; OEY; JMAP; }

\----------LOAD X and Y to registers----------------------
LOADOP
 {AND R8, R8, 03FFh;}
 {XOR R10, R10, R10;}
 {XOR NIL, R15, R8; OEY; EWL; }
 READAX {R; CJP RDM, READAX; ADD R10, R10, BUS_D, Z; }
 {XOR NIL, R15, R10; OEY; EWL; }
 {XOR R10, R10, R10; }
 READX {R; CJP RDM, READX; ADD R10, R10, BUS_D, Z; }

 {ADD R8, R8, 01h, Z;}
 {XOR R11, R11, R11; }
 {XOR NIL, R15, R8; OEY; EWL;}
 READAY {R; CJP RDM, READAY; ADD R11, R11, BUS_D, Z; }
 {XOR NIL, R15, R11; OEY; EWL;}
 {XOR R11, R11, R11; }
 READY {R; CJP RDM, READY; ADD R11, R11, BUS_D, Z; }

 {CRTN NZ; }

\-----------MULT-----------------------------------------
 CALC
 {CJS NZ, LOADOP; } \ Loading operands
 {XOR R15, R15, 10h; } \ CT

\ Формуэмо знак результату
 {XOR R14, R14, R11; }
 {XOR R14, R14, R10; LOAD RM, FLAGS;}

\Переводимо відємнине число Х в додатнє (за необхідності)
 {AND NIL, R10, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, PROV_Y; }
 {SUB R10, Z, R10, NZ; }

PROV_Y
 {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, MULT; }
 {SUB R11, Z, R11, NZ; }

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
 {XOR R11, R11, 8000h; }
 {CJP NZ, NEXTCOMAND;}

\-----------INC RC---------------------------------------
NEXTCOMAND
 {ADD R7, R7, 02h, Z; }
 {CJP NZ, BEGIN;}

END {}
