/*
Во програмскиот јазик C да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер. Структурата треба да содржи: (5 поени)

Фирма која го произведува ( низа од 100 знаци)
Големина на монитор во инчи (реален број)
Дали е со touch или не (булова променлива)
Цена (цел број)
Да се креира структура ITStore, што содржи: (5 поени)

Име на продавницата (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)

[Ime na prodavnicata] [Lokacija]
[Marka1] [dim_monitor1] [Cena1]
[Marka2] [dim_monitor2] [Cena2]
[Marka3] [dim_monitor3] [Cena3]
...
Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*

Да се дополни функцијата main (10 поени).

Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Laptop
{
    char firma[100];
    float monitor;
    int touch;
    int cena;
}Laptop;
typedef struct ITStore
{
    char prodavnica[100];
    char lokacija[100];
    Laptop laptopi[100];
    int brojlaptopi;
}ITStore;
void najeftina_ponuda(ITStore *sp,int n)
{
    int mini[n];
    int index=0;
    int k=0;
    int minimum=0;
    for(int i=0;i<n;i++)
    {
        int f=0;
        mini[i]=0;
        for(int j=0;j<sp[i].brojlaptopi;j++)
        {

            if(sp[i].laptopi[j].touch&&f==0)
            {
                mini[i]=sp[i].laptopi[j].cena;
                f=1;
            }
            if(sp[i].laptopi[j].touch&&f==1)
            {
                if(sp[i].laptopi[j].cena<mini[i])
                {
                    mini[i]=sp[i].laptopi[j].cena;
                }
            }

        }
        if(k==0){
        minimum=mini[0];
        k=1;}
        if(mini[i]<minimum&&k==1&&mini[i]!=0)
        {minimum=mini[i];
        index=i;}
    }
    printf("Najeftina ponuda ima prodavnicata:\n");
    printf("%s",sp[index].prodavnica);
    printf(" ");
    printf("%s",sp[index].lokacija);
    printf("\n");
    printf("Najniskata cena iznesuva: %d",minimum);
    printf("\n");
}
void print(ITStore *sp,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%s",sp[i].prodavnica);
        printf(" ");
        printf("%s",sp[i].lokacija);
        printf("\n");
        for(int j=0;j<sp[i].brojlaptopi;j++)
        {
            printf("%s",sp[i].laptopi[j].firma);
            printf(" ");
            printf("%g",sp[i].laptopi[j].monitor);
            printf(" ");
            printf("%d",sp[i].laptopi[j].cena);
            printf("\n");
        }
    }
}

int main()
{
    ITStore s[100];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",s[i].prodavnica);
        scanf("%s",s[i].lokacija);
        scanf("%d",&s[i].brojlaptopi);
        for(int j=0;j<s[i].brojlaptopi;j++)
        {
            scanf("%s",s[i].laptopi[j].firma);
            scanf("%f",&s[i].laptopi[j].monitor);
            scanf("%d",&s[i].laptopi[j].touch);
            scanf("%d",&s[i].laptopi[j].cena);
        }
    }
        print(s,n);
    najeftina_ponuda(s,n);
}
