/*
Во програмскиот јазик C да се креира структура Pacient и истата треба да содржи: (5 поени)

Име и презиме на пациентот ( низа од макс. 100 знаци)
Дали е здраствено осигуран (1-да, 0-не)
Број на прегледи во текот на последниот месец (цел број)
Да се креира структура MaticenDoktor, која во себе содржи: (5 поени)

Име на докторот (низа од 100 знаци)
Број на пациенти (цел број)
Листа од пациенти (низа од максимум 200 елементи од структурата Pacient)
Цена на преглед (децимален број)
Да се креираат метода najuspesen_doktor, која прима низа од променливи од типот MaticenDoktor и нивниот број; и го печати името, заработената сума и бројот на прегледи на оној доктор кој заработил најголема сума од пациенти кои ги прегледувал приватно (не се здраствено осигурани) (10 поени). Доколку два или повеќе доктори имаат иста сума, тогаш се печати оној доктор кој има направено најголем број на прегледи вкупно во текот на последниот месец. (20 поени)

Функционалност (5 поени).
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Pacient
{
    char ime[100];
    int zdrastveno;
    int pregledi;
}Pacient;

typedef struct doktor
{
    char ime[100];
    int br_pac;
    Pacient niza[100];
    float cena;
}doktor;

void najuspesen_doktor(doktor *md,int n)
{
    float sum=0;
    float max=0;
    int index=0;
    int pregledi=0;
    int najpregledi=0;
    for(int i=0;i<n;i++)
    {
        sum=0;
        pregledi=0;
        for(int j=0;j<md[i].br_pac;j++)
        {
            pregledi+=md[i].niza[j].pregledi;
            if(md[i].niza[j].zdrastveno==0)
                sum+=md[i].cena*md[i].niza[j].pregledi;
        }
        if(max<=sum)
        {
            if(max==sum)
            {
                if(pregledi>najpregledi)
                {
                    najpregledi=pregledi;
                    max=sum;
                    index=i;
                }
                else
                {
                    max=sum;
                    index=index;
                    najpregledi=najpregledi;
                }
            }
            else
            {
                najpregledi=pregledi;
                max=sum;
                index=i;
            }
        }
    }
    printf("%s",md[index].ime);
    printf(" %.2f",max);
    printf(" %d",najpregledi);

}
#include<stdio.h>

int main()
{
	int i, j, n, broj;
	doktor md[200];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		//ime na doktor
		scanf("%s", &md[i].ime);
		//broj na pacienti
		scanf("%d", &md[i].br_pac);
		//cena na pregled
		scanf("%f", &md[i].cena);

		for (j = 0; j < md[i].br_pac; j++){
			scanf("%s", &md[i].niza[j].ime);
			scanf("%d", &md[i].niza[j].zdrastveno);
			scanf("%d", &md[i].niza[j].pregledi);
		}
	}
	najuspesen_doktor(md, n);

	return 0;
}
