\-----------nastroiyka shemy---------------------
LINK L1 : CT
LINK L2 : RDM
LINK L3 : RDD
LINK EWH : 16
LINK M : Z, Z, Z, Z, Z, Z, Z, Z, 14, 13, 12, 11

\-----------------I/O devices--------------------
ACCEPT DEV[1] : I,  \ INPUT DEVICE
    22h, \ PC
    23h, \ PD
    3, \ RDD DELAY
    2 \ DELAY RDD    
ACCEPT DEV_BUF[1] : 03Fh, 03Fh \ DK and PK     
    
ACCEPT DEV[2] : O, 0A2h, 0A3h, 3, 2


DW 22H : 80h \ Force seting ready mode for input device
DW 0A2h : 80h \ Force seting ready mode for output device

\----------------Data------------------------------
ACCEPT R6 : 0A3h \ RD of OUTPUT device
ACCEPT R7 : 030h \ RC
ACCEPT R9 : 023h \ RD of INPUT device

\-----------------Commands-------------------------
DW 30h : 0000100011000000% \ Read X from input device and write to 0C0h
DW 32h : 0000100011000010% \ Read Y from input device and write to 0C2h
DW 34h : 0001000000000000% \ Read X and Y to RG11 and RG12
DW 36h : 0001100000000000% \ Mult
DW 38h : 0010000000000000% \ Write Result to output device
DW 3Ah : 0010100000000000% \ end

\-----------------Microprogrammi-----------------
ORG 00h {CJP NZ, BEGIN; } \ Begin of program
ORG 01h {CJP NZ, INPUTING; } \ Input data from input device
ORG 02h {CJP NZ, LOADOP; } \ LOAD X and Y from memory
ORG 03h {CJP NZ, CALC; } \ MULT of X and Y
ORG 04h {CJP NZ, OUTPUTING;} \ OUTPUT data
ORG 05h {CJP NZ, END;} \ Ending program

\----------------Reading of command--------------
BEGIN
 {OR NIL, R7, R7; OEY; EWL;}
 READCOMAND {R; CJP RDM, READCOMAND; OR R8, Z, BUS_D; }
 
 {AND NIL, R8, 08000h; LOAD RM, FLAGS; }
 {CJP RM_N, END;} \ If command have two operands
 
 {AND nil, R8, 400h; LOAD RM, FLAGS;}
 {OR NIL, R8, Z; OEY; JMAP; }
 
\------------READ AND WRITE-------------------------------
INPUTING
 {AND R8, R8, 03FFh;}
 {CJS NZ, MMP_I; } \ Microprogram
 {OR NIL, R8, Z; OEY; EWL; }
  WRITING {W; CJP RDM, WRITING; OR NIL, R10, Z; OEY;}
 {CJP NZ, NEXTCOMAND;}
 
\-----------READ FROM INPUT DEVICE------------------------
MMP_I 
 {XOR R10, R10, R10; }
 {OR NIL, R9, Z; OEY; EWL;}
 READIN {I; CJP RDD, READIN; OR R10, BUS_D, Z; }
 {CRTN NZ;}
 
\----------LOAD X and Y to registers----------------------
LOADOP
 {XOR R14, R14, 0C0h; }
 {XOR R11, R11, R11; }
 {XOR NIL, R15, R14; OEY; EWL; }
 READX {R; CJP RDM, READX; ADD R11, R11, BUS_D, Z; }
  
 {ADD R14, R14, 02h, Z;}
 {XOR R12, R12, R12; }
 {XOR NIL, R15, R14; OEY; EWL;}
 READY {R; CJP RDM, READY; ADD R12, R12, BUS_D, Z; }
 
 {CJP NZ, NEXTCOMAND; }
 
\-----------MULT-----------------------------------------
CALC
  {XOR R10, R10, R10; }
  {ADD R10, R10, 10h, Z; }
  {XOR R13, R13, R13; }
 \ Result sign
 {OR R14, R11, Z;}
 {XOR R14, R14, R12; LOAD RM, FLAGS; }
 {XOR R14, R14, R14; }
 

\PROV_X
 {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, PROV_Y; }
 {XOR R11, R11, 08000h; }
 
 PROV_Y
 {AND NIL, R12, 08000h; LOAD RN, FLAGS; }
 {CJP not RN_N, MULT; }
 {SUB R12, Z, R12, NZ;}
 {XOR R12, R12, 08000h; }
 
 MULT
 {AND NIL, R12, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, SHIFTL; }
 
 {ADD R13, R13, R11, Z; LOAD RN, FLAGS; }
 {ADD R12, R12, Z, RN_C; }

SHIFTL
 {OR @SLL, R13, R13, Z;  }
 {OR @SL.25, R12, R12, Z; }
 {SUB R10, R10, Z; LOAD RN, FLAGS;}
 {CJP NOT RN_Z, MULT; }
 
\Result 
 {OR SRL, R12, R12, Z; }
 {OR SR.9, R13, R13, Z; }
 
 {CJP NOT RM_N, NEXTCOMAND; }
 {XOR R13, R13, 0FFFFh;}
 {XOR R12, R12, 0FFFFh;}
 {ADD R13, R13, Z, NZ; LOAD RN, FLAGS; }
 {ADD R12, R12, Z, RN_C; }
 {CJP NZ, NEXTCOMAND;}
 
\-----------WRITING TO OUTPUT DEVICE---------------------
OUTPUTING
 {XOR R15, R15, R15;}
 {OR nil, R6, R6; OEY; EWL;}
OUTX  {O; CJP RDD, OUTX; OR nil, R12, R15; OEY;}
 {OR nil, R6, R6; OEY; EWL;}
OUTY  {O; CJP RDD, OUTY; OR nil, R13, R15; OEY;}
 {CJP NZ, NEXTCOMAND;}

 
\-----------INC RC---------------------------------------
NEXTCOMAND
 {ADD R7, R7, 02H, Z; }
 {CJP NZ, BEGIN;}
 
END {}
