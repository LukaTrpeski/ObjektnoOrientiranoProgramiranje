/*
Да се креира структура Igrac во која се чуваат податоци за еден играч на компјутерската игра. За играчот се чуваат информации за корисничкото име на играчот (низа од 15 знаци), број на ниво до кој играчот е стигнат (цел број) и број на освоени поени (цел број) (10 поени).

Потоа да се креирa структура KompjuterskaIgra во која се чуваат податоци за името на играта (низа од 20 знаци), низа од играчи кои ја играат играта (најмногу 30) и бројот на играчи. (10 поени)

Треба да се направи функција со потпис (15 поени)

void najdobarIgrac(KompjuterskaIgra *lista, int n)
Оваа функција треба да го испечати името на најдобриот играч на онаа игра која има најголема популарност (ја играат наjголем број на играчи). Најдобар играч е играчот кој има најголем број на освоени поени. Ако има повеќе играчи со ист максимален број на освоени поени, најдобар е играчот кој има достигнато најголемо ниво.

Печатењето е во форматот: "Najdobar igrac e igracot so korisnicko ime XXXXX koj ja igra igrata YYYYYY". (XXXXXX е корисничкото име на најдобриот играч,а YYYYY е името на играта која ја играат најголем број на играчи)

(Забелешка: секогаш ќе има точно еден најдобар играч)

Функционалност на задачата и дополнување на main функцијата (10 поени)

Забелешка: Задачата да се реши во програмскиот јазик C+
*/
#include <iostream>
#include <string.h>
using namespace std;

struct Igrac
{
    char ime[15];
    int nivo;
    int poeni;
};
struct KompjuterskaIgra
{
    char ime[20];
    Igrac igraci[30];
    int brojigraci;
};
void najdobarIgrac(KompjuterskaIgra *lista,int n)
{
    int najdobra=lista[0].brojigraci;
    int index=0;
    int kindex=0;
    for(int i=0;i<n;i++)
    {
        if(lista[i].brojigraci>najdobra)
            {
                najdobra=lista[i].brojigraci;
                index=i;
            }
    }
    int najdobar=lista[index].igraci[0].poeni;
    for(int i=0;i<lista[index].brojigraci;i++)
    {
        if(lista[index].igraci[i].poeni>najdobar)
        {
            najdobar=lista[index].igraci[i].poeni;
            kindex=i;
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<lista[index].igraci[kindex].ime<<" koj ja igra igrata "<<lista[index].ime<<endl;
}

int main()
{
    int n;
    cin>>n;
    KompjuterskaIgra igra[100];
    for(int i=0;i<n;i++)
    {
        cin>>igra[i].ime;
        cin>>igra[i].brojigraci;
        for(int j=0;j<igra[i].brojigraci;j++)
        {
            cin>>igra[i].igraci[j].ime;
            cin>>igra[i].igraci[j].nivo;
            cin>>igra[i].igraci[j].poeni;
        }
    }
    najdobarIgrac(igra,n);
}

/*#include<iostream>
using namespace std;
struct Igrac {
    char korisnickoIme[15];
    int nivo;
    int poeni;

};
struct KompjuterskaIgra {
    char ime[20];
    Igrac lista[30];
    int n;
};
void najdobarIgrac(KompjuterskaIgra *igri,int n) {
    int indeksNajmnoguIgraci=0;
    for (int i=1; i<n; i++) {
        if (igri[i].n>igri[indeksNajmnoguIgraci].n)
            indeksNajmnoguIgraci=i;
    }

    KompjuterskaIgra najpopularna=igri[indeksNajmnoguIgraci];
    int indeksmax=0;
    for (int i=1; i<najpopularna.n; i++) {
        if (najpopularna.lista[i].poeni>najpopularna.lista[indeksmax].poeni)
            indeksmax=i;
        else if (najpopularna.lista[i].poeni==najpopularna.lista[indeksmax].poeni) {
            if (najpopularna.lista[i].nivo>najpopularna.lista[indeksmax].nivo)
                indeksmax=i;
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime ";
    cout<<najpopularna.lista[indeksmax].korisnickoIme;
    cout<<" koj ja igra igrata ";
    cout<<najpopularna.ime;
}
int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}*/
