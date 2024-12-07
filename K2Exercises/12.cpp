/*
Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер), потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)

Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот. Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка, лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).

За оваа класа да се имплементира оператор << за печатење на уред во формат:

[modelnauredotl]
[tipnaured] [casovizaproverka]

Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)

Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)

За класата да се обезбедат:

operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде поголема од 2019 или помала од 2000. Ако се направи обид за додавање на уред со невалидна година, треба да се генерира исклучок InvalidProductionDate. (10 поени)

Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).

Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)
*/
#include <iostream>
#include <cstring>
#include <ctype.h>
#include <string.h>
#include <cmath>
#include <math.h>

using namespace std;

class InvalidProductionDate
{
private:
    char text[100];
public:
    InvalidProductionDate(const char* text="")
    {
        strcpy(this->text,text);
    }
    void print()
    {
        cout<<text<<endl;
    }
};
enum tip
{
    Mobilen,Laptop
};
class Device
{
protected:
    char model[100];
    static float proverka;
    int godina;
    tip t;
public:
    Device(const char *model="",tip t=(tip)0,int godina=0)
    {
        strcpy(this->model,model);
        this->t=t;
        this->godina=godina;
    }
    float getProverka()
    {
        float temp=proverka;
        if(godina>2015){
            temp+=2;
        }
        if((tip)t==1){
            temp+=2;
        }
        return temp;
    }
    static void setPocetniCasovi(float p)
    {
        proverka=p;
    }
    int getGodina()
    {
        return godina;
    }
    char *getTip()
    {
        if((tip)t==0)
        {
            return "Mobilen";
        }
        else
            return "Laptop";
    }
    friend ostream &operator<<(ostream &out, Device &dev)
    {
       out<<dev.model<<endl<<dev.getTip()<<" "<<dev.getProverka()<<endl;
       return out;
    }
};
float Device::proverka=1;
class MobileServis
{
private:
    char adresa[100];
    Device *niza;
    int n;
public:
    MobileServis(const char* adresa="",Device *niza=NULL,int n=0)
    {
        strcpy(this->adresa,adresa);
        this->n=n;
        this->niza=new Device[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=niza[i];
        }
    }
    MobileServis(const MobileServis &ms)
    {
        strcpy(this->adresa,ms.adresa);
        this->n=ms.n;
        this->niza=new Device[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=ms.niza[i];
        }
    }
    MobileServis &operator=(const MobileServis &ms)
    {
        if(this!=&ms)
        {
            delete [] niza;
            strcpy(this->adresa,ms.adresa);
            this->n=ms.n;
            this->niza=new Device[n];
            for(int i=0;i<n;i++)
            {
                this->niza[i]=ms.niza[i];
            }
        }
        return *this;
    }
    MobileServis &operator+=(Device &d)
    {
        if(d.getGodina()>2019||d.getGodina()<2000)
            throw InvalidProductionDate("Невалидна година на производство");
        else
        {
            Device *temp=new Device[n+1];
            for(int i=0;i<n;i++)
            {
                temp[i]=niza[i];
            }
            temp[n++]=d;
            delete [] niza;
            niza=temp;
            return *this;
        }
    }
    void pecatiCasovi()
    {
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0;i<n;i++)
        {

            cout<<niza[i];
        }
    }
    ~MobileServis(){delete [] niza;}

};
int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch(InvalidProductionDate &ipd)
            {
                ipd.print();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch(InvalidProductionDate &ipd)
            {
                ipd.print();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch(InvalidProductionDate &ipd)
            {
                ipd.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
            t+=tmp;
            }
            catch(InvalidProductionDate &ipd)
            {
                ipd.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
            t+=tmp;
            }
            catch(InvalidProductionDate &ipd)
            {
                ipd.print();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}

