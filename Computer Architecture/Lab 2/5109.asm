LINK L1 : CT
ACCEPT R10 : 0f001h \ A = 7 ДК
ACCEPT R11 : 0f001h \ B = 5 ДК
ACCEPT R15 : 00000h

\ Result
ACCEPT R12 : 00000h
ACCEPT R13 : 00000h
ACCEPT R14 : 00000h \ sign


\ Формуэмо знак результату
 {XOR R14, R14, R11; }
 {XOR R14, R14, R10; LOAD RM, FLAGS;}

\ Переводимо відємнине число Х в додатнє (за необхідності)
 {AND NIL, R10, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, PROV_Y; }
 {SUB R10, Z, R10, NZ; }

 PROV_Y
 {AND NIL, R11, 08000h; LOAD RN, FLAGS; }
 {CJP NOT RN_N, SHIT; }
 {SUB R11, Z, R11, NZ;}

 SHIT
  {OR @SRL, R11, R11, Z;}
  {OR @SR.9, R15, R15, Z;}

 \ Множення
 MULT
  {ADD NIL, R10, 0FFFFh, Z; LOAD RN, FLAGS; }
  {CJP NOT RN_C, RESULT;}
  {AND NIL, R10, 08000h; LOAD RN, FLAGS; }
  {CJP NOT RN_N, SHIFT;}

  {ADD R13, R13, R15, Z; LOAD RN, FLAGS; }
  {ADD R12, R12, R11, RN_C;}

 SHIFT
  {OR @SRL, R11, R11, Z;}
  {OR @SR.9, R15, R15, Z;}
  {OR @SLL, R10, R10, Z;}
  {CJP NZ, MULT; }

 RESULT
  {CJP NOT RM_N, END;}
  {XOR R13, R13, 0FFFFh;}
  {XOR R12, R12, 0FFFFh;}
  {ADD R13, R13, Z, NZ; LOAD RN, FLAGS; }
  {ADD R12, R12, Z, RN_C; }

  END {}
