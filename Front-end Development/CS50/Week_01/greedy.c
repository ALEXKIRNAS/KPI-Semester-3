#include <cs50.h>
#include <stdio.h>

int main (void){
    
    float money;
    do {
        printf("O hai! How much change is owed?\n");
        money = GetFloat();
    } while (money < 0.0);
    
    int tMoney = money * 100;
    
    int x25 = tMoney / 25; tMoney-= x25*25;
    int x10 = tMoney / 10; tMoney-= x10*10;
    int x5  = tMoney / 5; tMoney-= x5*5;
    int x1 = tMoney;
    printf("%d\n", x25 + x10 + x5 + x1);
}