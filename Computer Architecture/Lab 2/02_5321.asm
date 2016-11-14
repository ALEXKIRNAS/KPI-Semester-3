\-----------nastroiyka shemy---------------------
LINK L1 : CT

ACCEPT R10 : 0FFFh
ACCEPT R11 : 0FFFh


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
 {CJP NOT RM_N, END;}
 {XOR R11, R11, 0FFFFh; }
 {XOR R12, R12, 0FFFFh; }
 {ADD R12, R12, Z, NZ; LOAD RN, FLAGS; }
 {ADD R11, R11, Z, RN_C;}

END {}
