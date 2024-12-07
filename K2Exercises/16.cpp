/*
Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)
*/
#include <iostream>
#include <ctype.h>
#include <math.h>
#include <cstring>
#include <string.h>
using namespace std;

class Transport
{
protected:
    char destinacija[20];
    int osnovna;
    int rastojanie;
public:
    Transport(char *destinacija,int osnovna=0,int rastojanie=0)
    {
        strcpy(this->destinacija,destinacija);
        this->osnovna=osnovna;
        this->rastojanie=rastojanie;
    }
    Transport &operator=(const Transport &t)
    {
        strcpy(this->destinacija,t.destinacija);
        this->osnovna=t.osnovna;
        this->rastojanie=t.rastojanie;
    }
    void setDestinacija(char *d)
    {
        strcpy(destinacija,d);
    }
    void setOsnovna(int o)
    {
        osnovna=o;
    }
    void setRastojanie(int r)
    {
        rastojanie=r;
    }
    char *getDestinacija()
    {
        return destinacija;
    }
    int getOsnovna()
    {
        return osnovna;
    }
    int getRastojanie()
    {
        return rastojanie;
    }
    virtual double cenaTransport()
    {
        return osnovna;
    }
    bool operator<(const Transport &t)
    {
        return this->rastojanie<t.rastojanie;
    }
};
class AvtomobilTransport:public Transport
{
private:
    bool daliPlaten;
public:
    AvtomobilTransport(char *destinacija,int osnovna=0,int rastojanie=0,bool daliPlaten=true):Transport(destinacija,osnovna,rastojanie)
    {
        this->daliPlaten=daliPlaten;
    }
    double cenaTransport()
    {
        if(daliPlaten)
            return Transport::cenaTransport()*1.20;
        else
            return Transport::cenaTransport();
    }
};
class KombeTransport:public Transport
{
private:
    int broj;
public:
    KombeTransport(char *destinacija,int osnovna=0,int rastojanie=0,int broj=0):Transport(destinacija,osnovna,rastojanie)
    {
        this->broj=broj;
    }
    double cenaTransport()
    {
        return Transport::cenaTransport()-broj*200;
    }
};
void pecatiPoloshiPonudi(Transport **niza,int n,Transport edna)
{
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<n-i-1;j++)
       {
           if(niza[j]->getRastojanie()>niza[j+1]->getRastojanie()){
                Transport *temp=niza[j];
                niza[j]=niza[j+1];
                niza[j+1]=temp;
           }
       }
    }
    for(int i=0;i<n;i++)
    {
            if(niza[i]->cenaTransport()>edna.cenaTransport())
                cout<<niza[i]->getDestinacija()<<" "<<niza[i]->getRastojanie()<<" "<<niza[i]->cenaTransport()<<endl;
    }
}

int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
