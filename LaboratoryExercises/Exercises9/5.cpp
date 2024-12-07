/*
Да се креира класа Transakcija во која што ќе се чуваат информации за:

датумот на реализирање на банкарската трансакција:
ден (int)
месец (int)
година (int)
паричниот износ кој се однесува на трансакцијата (позитивен или негативен, тип double)
моменталната вредност на еврото во денари (static double EUR), иницијално поставен на 61
моменталната вредност на доларот во денари (static double USD), иницијално поставен на 50
За класата да се имплемтнираат соодветните конструктори, како и да се дефинираат следните четири чисто виртуелни методи:

double voDenari()
void pecati()
Трансакциите можат да бидат денарски и девизни (DenarskaTransakcija и DeviznaTransakcija). За девизните трансакции се чува дополнителна информација за валутата на трансакцијата (низа од три знаци). Дозволени валути за девизните транскации се USD и EUR.

За двете изведени класи да се напишат соодветните конструктори, деструктори и да се препокријат потребните методи.

Да се дефинира класа Smetka во која што ќе се чуваат информации за:

извршените трансакции (динамички алоцирана низа од покажувачи кон класата Transakcija)
број на извршените трансакции (int)
број на сметката (низа од 15 знаци)
почетно салдо во денари (double)
За класата Smetka да се имплементираат:

потребен конструктор (со два аргументи, видете во main), деструктор
оператор за додавање на нова трансакција во низата од трансакции +=
void izvestajVoDenari() - функција што печати информации за сметката во форматот:

Korisnikot so smetka: [број на сметката] ima momentalno saldo od [салдо на сметката пресметано во денари] MKD

void pecatiTransakcii() - функција што ги печати сите внесени трансакции
Да се креираат класи за следните исклучоци:

InvalidDateException којшто се фрла доколку при креирање на трансакција не се испочитувани правилата 1<=ден<=31 и 1<=месец<=12
NotSupportedCurrencyException којшто се фрла доколку при креирање на девизна трансакција се внесува вредност за валута што не е дозволена
Овие исклучоци да се фрлат и да се фатат таму каде што е потребно. Истите при фаќање треба да печатат пораки од следниот формат:

Invalid Date 32/12/2018
GBP is not a supported currency
*/
#include <iostream>
#include <cstring>

using namespace std;
class InvalidDateException
{
private:
    int d;
    int m;
    int g;
public:
    InvalidDateException(int d,int m,int g)
    {
        this->d=d;
        this->m=m;
        this->g=g;
    }
    void message()
    {
        cout<<"Invalid Date "<<d<<"/"<<m<<"/"<<g<<endl;
    }
};
class NotSupportedCurrencyException
{
private:
    char val[3];
public:
    NotSupportedCurrencyException(char *val)
    {
        strcpy(this->val,val);
    }
    void message()
    {
        cout<<val<<" is not a supported currency"<<endl;
    }
};
class Transakcija
{
protected:
    int den;
    int mesec;
    int godina;
    double iznos;
public:
    static double evro;
    static double dolar;
    Transakcija(int den=1,int mesec=1,int godina=1991,double iznos=0)
    {
        if(den<1||den>31||mesec<1||mesec>12)
        {
            throw InvalidDateException(den,mesec,godina);
        }
        this->den=den;
        this->mesec=mesec;
        this->godina=godina;
        this->iznos=iznos;
    }
    static void setUSD(double usd)
    {
        dolar=usd;
    }
    static void setEUR(double eur)
    {
        evro=eur;
    }
    virtual double voDenari()=0;
    virtual void pecati()=0;
};
double Transakcija::evro=61;
double Transakcija::dolar=50;
class DenarskaTransakcija:public Transakcija
{
public:
    DenarskaTransakcija(int den=1,int mesec=1,int godina=1991,double iznos=0):Transakcija(den,mesec,godina,iznos)
    {}
    ~DenarskaTransakcija(){}
    double voDenari()
    {
        return iznos;
    }

    void pecati()
    {
        cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<iznos<<" MKD"<<endl;
    }
};
class DeviznaTransakcija:public Transakcija
{
private:
    char valuta[3];
public:
    DeviznaTransakcija(int den=1,int mesec=1,int godina=1991,double iznos=0,char *valuta="USD"):Transakcija(den,mesec,godina,iznos)
    {
        if(strcmp(valuta,"USD")!=0&&strcmp(valuta,"EUR")!=0)
        {
            throw NotSupportedCurrencyException(valuta);
        }
        strcpy(this->valuta,valuta);
    }
    double voDenari()
    {
        if(strcmp(valuta,"USD")==0)
            return iznos*dolar;
        if(strcmp(valuta,"EUR")==0)
            return iznos*evro;
    }

    void pecati()
    {
        cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<iznos<<" "<<valuta<<endl;
    }
    ~DeviznaTransakcija(){}
};

class Smetka
{
private:
    Transakcija **niza;
    int n;
    char id[15];
    double saldo;
public:
    Smetka(char *id="",double saldo=0)
    {
        this->n=0;
        this->niza=new Transakcija*[n];
        strcpy(this->id,id);
        this->saldo=saldo;
    }
    ~Smetka(){delete [] niza;}
    Smetka(const Smetka &sm)
    {
        this->n=sm.n;
        this->niza=new Transakcija*[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=sm.niza[i];
        }
        strcpy(this->id,sm.id);
        this->saldo=sm.saldo;
    }
    Smetka &operator=(const Smetka &sm)
    {
        if(this!=&sm){
        delete [] niza;
        this->n=sm.n;
        this->niza=new Transakcija*[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=sm.niza[i];
        }
        strcpy(this->id,sm.id);
        this->saldo=sm.saldo;
        }
        return *this;
    }
    Smetka &operator+=(Transakcija *t)
    {
        Transakcija **temp=new Transakcija*[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=niza[i];
        }
        temp[n++]=t;
        delete [] niza;
        niza=temp;
        return *this;
    }
    void izvestajVoDenari()
    {
        double s=saldo;
        for(int i=0;i<n;i++)
        {
            s+=niza[i]->voDenari();
        }
        cout<<"Korisnikot so smetka: "<<id<<" ima momentalno saldo od ";
        if((float)s==s)
        {
            cout<<(unsigned long long int)s<<" MKD"<<endl;
        }
        else
            cout<<s<<" MKD"<<endl;

    }
    void pecatiTransakcii()
    {
        for(int i=0;i<n;i++)
        {
            niza[i]->pecati();
        }
    }
};


int main () {

	Smetka s ("300047024112789",1500);

	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];

	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
		cin>>tip>>den>>mesec>>godina>>iznos;
		if (tip==2){
			cin>>valuta;
			try{
            Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
			s+=t;
			}
			catch(InvalidDateException &ide)
			{
			    ide.message();
			}
			catch(NotSupportedCurrencyException &nsce)
			{
			    nsce.message();
			}
            //delete t;
		}
		else {
			try{
            Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
			s+=t;
			}
			catch(InvalidDateException &ide)
			{
			    ide.message();
			}
			catch(NotSupportedCurrencyException &nsce)
			{
			    nsce.message();
			}
            //delete t;
		}

	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;
    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
	return 0;
}
