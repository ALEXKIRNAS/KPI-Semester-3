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
 {XOR R12, R12, R12;}
 {XOR NIL, R15, R8; OEY; EWL; }
 READX {R; CJP RDM, READX; ADD R12, R12, BUS_D, Z; }

 {ADD R8, R8, 01h, Z;}
 {XOR R11, R11, R11; }
 {XOR NIL, R15, R8; OEY; EWL;}
 READY {R; CJP RDM, READY; ADD R11, R11, BUS_D, Z; }

 {CRTN NZ; }

\-----------MULT-----------------------------------------
 CALC
 {CJS NZ, LOADOP; } \ Loading operands

 {xor r10, r10, 10h; }

\defining result sign
{or r14, r11, z;}
{xor r14, r14, r12; load rm, flags;}
{xor r14, r14, r14;}

\converting in straight code
{and nil, r11, 08000h; load rn, flags;}
{cjp not rn_n, prov_y;}
{sub r11, z, r11, nz;}

prov_y
{and nil, r12, 08000h; load rn, flags;}
{cjp not rn_n, mult;}
{sub r12, z, r12, nz;}

\multiplication function
mult
{and nil, r12, 08000h; load rn, flags;}
{cjp not rn_n, shiftl;}

{add r13, r13, r11, z; load rn, flags;}
{add r12, r12, z, rn_c;}

\left shift function
shiftl
{or @sll, r13, r13, z;}
{or @sl.25, r12, r12, z;}
{sub r10, r10, z; load rn, flags;}
{cjp not rn_z, mult;}

\finall shift 
RESULT
{or srl, r12, r12, z;}
{or sr.9, r13, r13, z;}
 {CJP NOT RM_N, NEXTCOMAND;}
 {xor r13, r13, 0ffffh;}
{xor r12, r12, 0ffffh;}
{add r13, r13, z, nz; load rn, flags;}
{add r12, r12, z, rn_c;}
 {CJP NZ, NEXTCOMAND;}

\-----------INC RC---------------------------------------
NEXTCOMAND
 {ADD R7, R7, 02h, Z; }
 {CJP NZ, BEGIN;}

END {}
