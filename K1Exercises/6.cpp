/*
Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.

Забелешка: Задачата да се реши во програмскиот јазик C++
*/
#include <iostream>
#include <string.h>
using namespace std;

struct Voz{
char relacija[50];
float kilometri;
int brojpatnici;
};
struct ZeleznickaStanica{
char grad[20];
Voz v[30];
int brojvozovi;
};
void najkratkaRelacija(ZeleznickaStanica* z,int n,char *grad)
{
    int index=0;
    int kindex=0;
    int mini;
    for(int i=0;i<n;i++)
    {
        if(strcmp(grad,z[i].grad)==0)
        {
            mini=z[i].v[0].kilometri;
            for(int j=0;j<z[i].brojvozovi;j++)
            {
                if(z[i].v[j].kilometri<=mini)
                {
                    mini=z[i].v[j].kilometri;
                    index=j;
                    kindex=i;
                }
            }
        }
        
    }
    cout<<"Najkratka relacija: "<<z[kindex].v[index].relacija<<" ("<<z[kindex].v[index].kilometri<<" km)"<<endl;

}


int main()
{
    int n;
	cin>>n;
    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
            cin>>zStanica[i].grad;
            cin>>zStanica[i].brojvozovi;
            for(int j=0;j<zStanica[i].brojvozovi;j++)
            {
                cin>>zStanica[i].v[j].relacija;
                cin>>zStanica[i].v[j].kilometri;
                cin>>zStanica[i].v[j].brojpatnici;
            }
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
    }

    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}