\ ����������� ������ #2
\ �������� 2-� �����
\ ������ ������� ��������� ���������


\ ϳ��������� �� ������, �������� ���������� �����
LINK L1 : CT
ACCEPT R3 : 00007h \X = -7
ACCEPT R4 : 0FFFBh \Y = -5

ACCEPT R5 : 0 \Z
ACCEPT R6 : 0 \���� Z

\ �������� ���� ����������
 {OR R6, R3, Z;}
 {XOR R6, R6, R4;}

\ ���������� ������� ����� � � ������� (�� �����������)
 {ADD NIL, R3, 1000000000000000%; LOAD RM, FLAGS; }
 {CJP NOT RM_C, PROV_Y;}
 {SUB R3, 0, R3, NZ;}

PROV_Y
\ ���������� ������� ����� Y � ������� (�� �����������)
 {ADD NIL, R4, 1000000000000000%; LOAD RM, FLAGS; }
 {CJP NOT RM_C, MULT; }
 {SUB R4, 0, R4, NZ;}

MULT
\ ��������
 {OR R2, R4, Z;}
 
SHIFT_R
 {OR R2, R2, Z; CJP ZO, RES;} \���� � �2 0, �� ��������� ���������
 {XOR R0, R0; }
 {AND R0, R2, 000000000000001%; }
 {ADD R0, R0, 111111111111111%, Z; LOAD RM, FLAGS; }
 {OR @SRL, R2, Z; } \������� �2
 {CJP NOT RM_V, SHIFT_L;} \ ���� ������� �� 1, �� �������� ����
 {ADD R1, R1, R3, Z;}
 
SHIFT_L
 {OR @SLL, R3, Z;}
 {CJP NZ, SHIFT_R; } \ ������ �����
 
\ ����� ����������
RES
 {ADD R6, R6, 1000000000000000%, Z; LOAD RM, FLAGS; }
 {OR R5, R1, Z;}
 {CJP NOT RM_V, END;}
 {SUB R5, Z, R5, NZ;}
END {}
