\-----------nastroiyka shemy---------------------
LINK L1 : CT
LINK L2 : RDM
LINK L3 : RDD
LINK EWH : 16
LINK M : Z, Z, Z, Z, Z, Z, Z, Z, 14, 13, 12, 11

\-----------------I/O devices--------------------
ACCEPT DEV[1] : I,  \ INPUT DEVICE
    02h, \ PC
    03h, \ PD
    3, \ RDD DELAY
    2 \ DELAY RDD
ACCEPT DEV_BUF[1] : 0F001h, 0F001h \ all DK

ACCEPT DEV[2] : O, 082h, 083h, 3, 2


DW 02h : 80h \ Force seting ready mode for input device
DW 082h : 80h \ Force seting ready mode for output device

\----------------Data------------------------------
ACCEPT R5 : 03h \ RD of INPUT device
ACCEPT R6 : 083h \ RD of OUTPUT device
ACCEPT R7 : 030h \ RC

\-----------------Commands-------------------------
DW 30h : 0000100000000100% \ Read X from input device and write to 04h
DW 32h : 0000100000000101% \ Read Y from input device and write to 05h
DW 34h : 0000100000000110% \ Read Z from input device and write to 06h
DW 36h : 0001100000000101% \ Mult (04h and 05 address)
DW 38h : 0010000000000100% \ Write Result to output device
DW 3Ah : 0010100000000000% \ end

\-----------------Microprogrammi-----------------
ORG 00h {CJP NZ, BEGIN; } \ Begin of program
ORG 01h {CJP NZ, INPUTING; } \ Input data from input device
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
 {CJP not RM_Z, END; }
 
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
 {OR NIL, R5, Z; OEY; EWL;}
 READIN {I; CJP RDD, READIN; OR R10, BUS_D, Z; }
 {CRTN NZ;}

\----------LOAD X and Y to registers----------------------
 LOADOP
 {AND R8, R8, 03FFh;}
 {XOR R11, R11, R11;}
 {XOR NIL, R15, R8; OEY; EWL; }
 READX {R; CJP RDM, READX; ADD R11, R11, BUS_D, Z; }

 {ADD R8, R8, 01h, Z;}
 {XOR R12, R12, R12; }
 {XOR NIL, R15, R8; OEY; EWL;}
 READY {R; CJP RDM, READY; ADD R12, R12, BUS_D, Z; }

 {CRTN NZ; }


\-----------MULT-----------------------------------------
 CALC
 {CJS NZ, LOADOP; } \ Loading operands
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
 {SUB R11, Z, R11, NZ; }

 PROV_Y
 {AND NIL, R12, 08000h; LOAD RN, FLAGS; }
 {CJP not RN_N, MULT; }
 {SUB R12, Z, R12, NZ; }

 MULT
 {AND NIL, R12, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, SHIFTL; }

 {ADD R13, R13, R11, Z; LOAD RN, FLAGS; }

 SHIFTL
 {OR SLL, R13, R13, Z;  }
 {OR SL.25, R12, R12, Z; }
 {SUB R10, R10, Z; LOAD RN, FLAGS;}
 {CJP NOT RN_Z, MULT; }

 \Result
 {OR SRL, R12, R12, Z; }
 {OR SR.9, R13, R13, Z; }

 {CJP NOT RM_N, NEXTCOMAND; }
 {XOR R12, R12, 08000h;}
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
 {ADD R7, R7, 02h, Z; }
 {CJP NZ, BEGIN;}

END {}
