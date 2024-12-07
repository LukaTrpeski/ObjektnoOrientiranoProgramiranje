/*
Дадена е дел од дефиницијата на класата Karticka. За секоја картичка се чуваат информации за трансакциска сметка (низа од 15 знаци) , пин код (цел број) и дали има повеќе пин кодови (булова променлива).

За секој картичка може да се пресмета тежината за пробивање на картичката. Тежината на пробивање е бројот на цифрите на пин кодот.

Специјалните картички покрај еден задолжителен имаат уште неколку пин кодови . За овие корисници да се моделира соодветна класа SpecijalnaKaricka во која покрај дополнителните пин кодови (динамичко алоцирана низа од цели броеви) се чува и бројот на пин кодовите (цел број). Со дополнителните пин кодови се менува и тежината на пробивање на картичката и таа се зголемува за бројот на дополнителни пин кодови.

Максималниот број на дополнителни пин кодови кој може да има било која картичка е P. P има фиксна вредност 4 за сите картички и оваа вредност не може да се промени.

Во класите Karticka и SpecijalnaKarticka треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за картичката во формат: smetka: tezina (5 поени)
tezinaProbivanje() – ја пресметува тежината за пробивање на картичката (5 поени)
Во класата SpecijalnaKarticka дефинирај ја функцијата:

преоптоварен оператор += за додавање на нов пин код (5 поени)
Ако се направи обид да се внесат повеќе од дозволениот број на пин кодови во безбедносниот код да се фрли исклучок (објект од класата OutOfBoundException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Brojot na pin kodovi ne moze da go nadmine dozvolenoto) и справете се со исклучокот така да додадениот пин код не се зема предвид (10 поени)

Дадена е дел од дефиницијата на класата Banka во која се чуваат информаци за името на банката (низа од 30 знаци) и за картичките издадени од банката (низа од 20 покажувачи кон класата Karticka) како и бројот на такви картички.

Велиме дека картичката издадена од банката може да се пробие ако тежината за пробивање е најмногуLIMIT. Вредноста LIMIT е членка на класата Banka, има почетна вредност 7 и истата може да се промени со функцијата setLimit(). За сите банки оваа вредност е иста. (5 поени)

Во класата Banka имплементирај ги функциите:

функција pecatiKarticki() во која се печатат сите картички кои можат да се пробијат, секој во посебен ред. Претходно во првиот ред се печати: Vo bankata XXXXX moze da se probijat kartickite: (5 поени).

функција dodadiDopolnitelenPin(char * smetka, int novPin) во која на картичката со дадена трансакциона сметка се додава нов дополнителен пин код. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

class OutOfBoundException{
private:
    char text[100];
public:
    OutOfBoundException(char *text="")
    {
        strcpy(this->text,text);
    }
    void message()
    {
        cout<<text<<endl;
    }
};
class Karticka
{
protected:
    char transakciska[16];
    int pin;
    bool pinovi;
public:
    Karticka(char *transakciska="",int pin=0,bool pinovi=false)
    {
        strcpy(this->transakciska,transakciska);
        this->pin=pin;
        this->pinovi=pinovi;
    }
    virtual int tezinaProbivanje()
    {
        int temp,br=0;
        temp=pin;
        while(temp)
        {
            br++;
            temp/=10;
        }
        return br;
    }
    char *getID()
    {
        return transakciska;
    }
    friend ostream &operator<<(ostream &out,Karticka &k)
    {
        out<<k.transakciska<<": "<<k.tezinaProbivanje()<<endl;
        return out;
    }
    bool getDopolnitelenPin()
    {
        return pinovi;
    }
};
class SpecijalnaKarticka:public Karticka
{
private:
    int *niza;
    int n;
    const int P=4;
public:
    SpecijalnaKarticka(char *transakciska="",int pin=0,bool pinovi=true):Karticka(transakciska,pin,pinovi)
    {
        n=0;
        niza=new int[0];
    }
    SpecijalnaKarticka(const SpecijalnaKarticka &sk)
    {
        strcpy(this->transakciska,sk.transakciska);
        this->pin=sk.pin;
        this->pinovi=sk.pinovi;
        this->n=sk.n;
        for(int i=0;i<n;i++)
        {
            this->niza[i]=sk.niza[i];
        }
    }
    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &sk)
    {
        if(this!=&sk)
        {
            delete [] niza;
            strcpy(this->transakciska,sk.transakciska);
            this->pin=sk.pin;
            this->pinovi=sk.pinovi;
            this->n=sk.n;
            for(int i=0;i<n;i++)
            {
                this->niza[i]=sk.niza[i];
            }
        }
        return *this;
    }
    int tezinaProbivanje()
    {
        return Karticka::tezinaProbivanje()+n;
    }
    SpecijalnaKarticka &operator+=(int nov)
    {
        if(n==P)
        {
            throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");
        }
        else{
        int *temp=new int[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=niza[i];
        }
        temp[n++]=nov;
        delete [] niza;
        niza=temp;
        return *this;
        }
    }
};
class Banka
{
private:
    char ime[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *ime="",Karticka **karticki=NULL,int broj=0)
    {
        strcpy(this->ime,ime);
        this->broj=broj;
        for(int i=0;i<broj;i++)
        {
            if(karticki[i]->getDopolnitelenPin())
            {
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else
            {
                this->karticki[i]=new Karticka(*karticki[i]);
            }
        }
    }
    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }
    static void setLIMIT(int lim)
    {
        LIMIT=lim;
    }
    void pecatiKarticki()
    {
        cout<<"Vo bankata "<<ime<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(karticki[i]->tezinaProbivanje()<=LIMIT)
            {
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char *smetka,int novPin)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(karticki[i]->getID(),smetka)==0)
            {
                
                SpecijalnaKarticka *sk=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(sk!=0)
                    *sk+=novPin;
            }
        }
    }
};
int Banka::LIMIT=7;
int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;
   try{
   komercijalna.dodadiDopolnitelenPin(smetka,pin);
   }
   catch(OutOfBoundException &oobe)
   {
       oobe.message();
   }

}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}

