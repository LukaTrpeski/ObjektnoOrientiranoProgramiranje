/*
За програмски јазик C.

Да се напише програма во која од стандарден влез се вчитува N (бројот на производи), а потоа се вчитуваат податоците за N производи (име, цена, количина). Програмата треба на стандарден излез да ја отпечати листата на купени производи и вкупната сума која треба да се плати во следниот облик (пример):

1. Flips    10.00 x 3 = 30.00
2. CocaCola 75.00 x 2 = 150.00
3. ChokoBanana  5.00 x 10 = 50.00
Total: 230.00
*/
#include <stdio.h>

struct proivod{
    char ime[20];
    float cena;
    float kolicina;
}proizvod[100];
int main()
{
    int n;
    scanf("%d",&n);
    int i;
    float total=0;
    for(i=1;i<=n;i++)
    {
        scanf("%s",&proizvod[i].ime);
        scanf("%f",&proizvod[i].cena);
        scanf("%f",&proizvod[i].kolicina);
        printf("%d. %s\t%.2f x %.1f = %.2f\n",i,proizvod[i].ime,proizvod[i].cena,proizvod[i].kolicina,proizvod[i].cena*proizvod[i].kolicina);
        total+=proizvod[i].cena*proizvod[i].kolicina;
    }
    printf("Total: %.2f", total);
}
    