/*
Да се дефинира класа Vozilo која ќе содржи информација за неговата маса (децимален број), ширина и висина (цели броеви).

Од оваа класа да се изведе класата Автомобил во која како дополнителна информација се чува информацијата за бројот на врати (цел број).

Од класата возило да се изведе и класата Автобус во која се чуваат информации и за бројот на патници кои може да ги пренесува.

Од класата возило да се изведе класата Камион во која се чуваат информации и за максималната маса која може да се товари на него (децимална вредност).

За сите класи да се креираат погодни контруктори, како и set и get функции.

Да се дефинира класа ParkingPlac за која се чува динамичко алоцирано поле од покажувачи кон Vozilo, како и бројот на елементи во полето. Во оваа класа да се дефинираат:

конструктор
деструктор
операторот += за додавање на ново возило (аргументот е покажувач кон Vozilo)
функција float presmetajVkupnaMasa() со која се пресметува вкупната маса на сите возила во паркинг плацот
функција int brojVozilaPoshirokiOd(int l) со која се пресметува бројот на возила кои се пошироки од дадената вредност
функција void pecati() со која се печати: Brojot na avtomobili e X, brojot na avtobusi e Y i brojot na kamioni e Z.
функција int pogolemaNosivostOd(Vozilo& v) во која се враќа бројот на сите камиони кои имаат носивост поголема од масата на возилото предадено како аргумент.
Да се дефинира виртуелна функција int vratiDnevnaCena() во класата Vozilo и истата да се преоптовари во сите изведени класи. За секој автомобил со помалку од 5 врати дневната цена е 100, а инаку е 130 денари. За секој камион цената се пресметува со формулата: (masa+nosivost)*0.02. За секој автобус цената е 5 денари по лице кое може да се пренесува.

Во класата ParkingPlac да се додаде следната функција: - функција int vratiDnevnaZarabotka() со која се враќа дневната заработка од сите возила на паркингот.
*/
#include <iostream>
#include <string.h>
using namespace std;

class Vozilo
{
protected:
    float masa;
    int sirina;
    int visina;
public:
    Vozilo(float masa=0.0,int sirina=0,int visina=0)
    {
        this->masa=masa;
        this->sirina=sirina;
        this->visina=visina;
    }
    float getmasa()
    {
        return masa;
    }
    int getsirina()
    {
        return sirina;
    }
    int getvisina()
    {
        return visina;
    }
    virtual int vratiDnevnaCena()=0;
};
class Avtomobil:public Vozilo
{
private:
    int brvrati;
public:
    Avtomobil(float masa=0.0,int sirina=0,int visina=0,int brvrati=0):Vozilo(masa,sirina,visina)
    {
        this->brvrati=brvrati;
    }
    int vratiDnevnaCena()
    {
        if(brvrati<5)
            return 100;
        else
            return 130;
    }
};
class Avtobus:public Vozilo
{
private:
    int brpatnici;
public:
    Avtobus(float masa=0.0,int sirina=0,int visina=0,int brpatnici=0):Vozilo(masa,sirina,visina)
    {
        this->brpatnici=brpatnici;
    }
    int vratiDnevnaCena()
    {
        return 5*brpatnici;
    }
};
class Kamion:public Vozilo
{
private:
    float maksmasa;
public:
    Kamion(float masa=0.0,int sirina=0,int visina=0,float maksmasa=0.0):Vozilo(masa,sirina,visina)
    {
        this->maksmasa=maksmasa;
    }
    float getnosivost()
    {
        return maksmasa;
    }
    int vratiDnevnaCena()
    {
        return (maksmasa+masa)*0.02;
    }
};
class ParkingPlac
{
private:
    Vozilo **niza;
    int n;
public:
    ParkingPlac()
    {
        this->n=0;
        niza=new Vozilo*[n];
    }
    ParkingPlac(const ParkingPlac &pp)
    {
        this->n=pp.n;
        for(int i=0;i<n;i++)
        {
            this->niza[i]=pp.niza[i];
        }
    }
    ParkingPlac &operator=(const ParkingPlac &pp)
    {
        if(this!=&pp)
        {
        delete [] niza;
        this->n=pp.n;
        for(int i=0;i<n;i++)
        {
            this->niza[i]=pp.niza[i];
        }
        }
        return *this;
    }
    ~ParkingPlac(){}
    ParkingPlac operator+=(Vozilo *v)
    {
        Vozilo **temp=new Vozilo*[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=niza[i];
        }
        temp[n++]=v;
        delete [] niza;
        niza=temp;
    }
    float presmetajVkupnaMasa()
    {
        float sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=niza[i]->getmasa();
        }
        return sum;
    }
    int brojVozilaPoshirokiOd(int l)
    {
        int br=0;
        for(int i=0;i<n;i++)
        {
            if(niza[i]->getsirina()>l)
                br++;
        }
        return br;
    }
    int pogolemaNosivostOd(Vozilo &v)
    {
        int br=0;
        for(int i=0;i<n;i++)
        {
            Kamion *k=dynamic_cast<Kamion*>(niza[i]);
            if(k)
            {
                if(k->getnosivost()>v.getmasa())
                    br++;
            }
        }
        return br;
    }
    int vratiDnevnaZarabotka()
    {
        int zar=0;
        for(int i=0;i<n;i++)
        {
            zar+=niza[i]->vratiDnevnaCena();
        }
        return zar;
    }
    void pecati()
    {
        int av=0;
        int k=0;
        int as=0;
        for(int i=0;i<n;i++)
        {
            Avtomobil *a=dynamic_cast<Avtomobil*>(niza[i]);
            if(a)
                av++;
            Kamion *ka=dynamic_cast<Kamion*>(niza[i]);
            if(ka)
                k++;
            Avtobus *au=dynamic_cast<Avtobus*>(niza[i]);
            if(au)
                as++;
        }
        cout<<"Brojot na avtomobili e "<<av<<", brojot na avtobusi e "<<as<<" i brojot na kamioni e "<<k<<"."<<endl;
    }
};



int main(){
ParkingPlac p;

int n;
cin>>n;
int shirina,visina, broj;
float masa,nosivost;
for (int i=0;i<n;i++){
    int type;
    cin>>type;
    if(type==1){
        cin>>masa>>shirina>>visina>>broj;
        Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
        p+=a;
    }
    if(type==2){
        cin>>masa>>shirina>>visina>>broj;
        p+=new Avtobus(masa,shirina,visina,broj);
    }
    if(type==3){
        cin>>masa>>shirina>>visina>>nosivost;
        p+=new Kamion(masa,shirina,visina,nosivost);
    }
}

p.pecati();

cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
Avtomobil a(1200,4,3,5);
cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
