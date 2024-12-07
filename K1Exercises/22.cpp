/*
Да се креира структура Proizvod во која се чуваат податоци за кодот напрозиводот (низа од 20 знаци), единична цена на производ (цел број), бројот на достапни производи кои ги има во еден магацин (цел број) .

Потоа да се креирa структура Narachka во која се чуваат податоци за името лицето кое ја прави нарачката (низи од 15 знаци), низа од Proizvodi (максимум 10) кои ги има во нарачката, низа од бројот на нарачани производи за секоја производ посебно (максимум10) и бројот на производи во нарачката .

Треба да се направи функција со потпис

void pecatiFaktura(Narachka n)

која што ќе ги отпечати една фактура за една нарачка (n) .

Во фактурата во првиот ред се печати: Faktura za XXXXX, каде XXXXX е името на лицето кое ја прави нарачката.

Ако сите производи може да се нарачаат печатат нарачаните производи, подредени по азбучен ред според кодот на производот. Во следните редови, во секој ред посебно се печати кодот на производот, единична цена на производот, број на нарачани производи и вкупната цена на производот (сите се одделени со едно празно место) . Исто така бројот на достапни производи од тој производ да се ажурира (да се намали за бројот на нарачани производи од тој производ). Во последниот ред да се отпечати: Vkupnata suma na fakturata e XXX, каде XXX е вкупната сума за цените за сите нарачани производи.

Ако постои производ кој не може да биде нарачан затоа што во магацинот не се достапни нарачаниот број производи тогаш не може да се изготви фактура за нарачката. На екранот да се отпечати: Fakturata ne moze da se izgotvi.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Proizvod
{
    char kod[20];
    int cena;
    int broj;
}Proizvod;

typedef struct Narachka
{
    char lice[15];
    Proizvod proizvodi[10];
    int n;
    int kolku[10];
}Narachka;


void pecatiFaktura(Narachka n)
{
    Proizvod temp;
    for(int i=0;i<n.n-1;i++)
    {
        for(int j=0;j<n.n-i-1;j++)
        {
            if(strcmp(n.proizvodi[j].kod,n.proizvodi[j+1].kod)>0)
            {
                temp=n.proizvodi[j];
                n.proizvodi[j]=n.proizvodi[j+1];
                n.proizvodi[j+1]=temp;

            }
        }
    }
    int sum=0;
    int f=0;
    printf("Faktura za %s\n",n.lice);
    for(int i=0;i<n.n;i++)
    {
        if(n.proizvodi[i].broj<n.kolku[i])
        {
            printf("Fakturata ne moze da se izgotvi");
            f=1;
            break;
        }
        else
        {
            printf("%s ",n.proizvodi[i].kod);
            printf("%d ",n.proizvodi[i].cena);
            printf("%d ",n.kolku[i]);
            printf("%d\n",n.proizvodi[i].cena*n.kolku[i]);
            sum+=n.proizvodi[i].cena*n.kolku[i];
            n.kolku[i]--;

        }

    }if(f==0)
        printf("Vkupnata suma na fakturata e %d\n",sum);

}
int main()
{
    Narachka narachka;
    scanf("%s",narachka.lice);
    scanf("%d",&narachka.n);
    int i;
    for (i = 0; i < narachka.n; ++i) {
        scanf("%s",narachka.proizvodi[i].kod);
        scanf("%d",&narachka.proizvodi[i].cena);
        scanf("%d",&narachka.proizvodi[i].broj);
    }
    int j;
    for (j = 0; j < narachka.n; ++j) {
            scanf("%d",&narachka.kolku[j]);
    }
    pecatiFaktura(narachka);
    return 0;
}
