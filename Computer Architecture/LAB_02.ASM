\ Лабороторна робота #2
\ Множення 2-й спосіб
\ Роботу виконав Зарічковий Олександр


\ Підоготовка до роботи, загрузка початкових даних
LINK L1 : CT
ACCEPT R3 : 00007h \X = -7
ACCEPT R4 : 0FFFBh \Y = -5

ACCEPT R5 : 0 \Z
ACCEPT R6 : 0 \Знак Z

\ Формуэмо знак результату
 {OR R6, R3, Z;}
 {XOR R6, R6, R4;}

\ Переводимо відємнине число Х в додатнє (за необхідності)
 {ADD NIL, R3, 1000000000000000%; LOAD RM, FLAGS; }
 {CJP NOT RM_C, PROV_Y;}
 {SUB R3, 0, R3, NZ;}

PROV_Y
\ Переводимо відємнине число Y в додатнє (за необхідності)
 {ADD NIL, R4, 1000000000000000%; LOAD RM, FLAGS; }
 {CJP NOT RM_C, MULT; }
 {SUB R4, 0, R4, NZ;}

MULT
\ Множення
 {OR R2, R4, Z;}
 
SHIFT_R
 {OR R2, R2, Z; CJP ZO, RES;} \Якщо у Р2 0, то завершуємо виконання
 {XOR R0, R0; }
 {AND R0, R2, 000000000000001%; }
 {ADD R0, R0, 111111111111111%, Z; LOAD RM, FLAGS; }
 {OR @SRL, R2, Z; } \Здигаємо Р2
 {CJP NOT RM_V, SHIFT_L;} \ Якщо старший біт 1, то виконуємо суму
 {ADD R1, R1, R3, Z;}
 
SHIFT_L
 {OR @SLL, R3, Z;}
 {CJP NZ, SHIFT_R; } \ Повтор циклу
 
\ Запис результату
RES
 {ADD R6, R6, 1000000000000000%, Z; LOAD RM, FLAGS; }
 {OR R5, R1, Z;}
 {CJP NOT RM_V, END;}
 {SUB R5, Z, R5, NZ;}
END {}
