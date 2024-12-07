/*
Да се развие класа Nediviznina за коjа се чуваат следниве информации:

адреса (динамички алоцирана низа од знаци)
квадратура (цел боj)
цена за квадрат (цел боj)
За оваа класа да се имплементираат соодветните конструктори и следните методи:

cena() коj ќе jа враќа цената на недвижнината (квадратура * цена-за-квадрат)
pecati() коj ќе ги испечати сите информации за истата
danokNaImot() коj го ваќа данокот што се плаќа за недвижнината, а истиот се пресметува како 5% од цената на недвижнината.
Од оваа класа да се изведе класа Vila за коjа дополнително се чува данок на луксуз (цел боj, пр. 10%). За оваа класа да се преоптоварат методите:

pecati()
danokNaImot() со тоа што пресметаниот данок се зголемува процентуално за данокот на луксуз.
И за двете класи треба да се преоптовари operator >>.
*/
#include <iostream>
#include <string.h>
using namespace std;

class Nedviznina{
protected:
    char *adresa;
    int kvadratura;
    int c;
public:
    Nedviznina(char *adresa="",int kvadratura=0,int c=0)
    {
        this->adresa=new char[strlen(adresa)+1];
        strcpy(this->adresa,adresa);
        this->kvadratura=kvadratura;
        this->c=c;
    }
    Nedviznina(const Nedviznina &ned)
    {
        this->adresa=new char[strlen(ned.adresa)+1];
        strcpy(this->adresa,ned.adresa);
        this->kvadratura=ned.kvadratura;
        this->c=ned.c;
    }
    Nedviznina &operator=(const Nedviznina &ned)
    {
        if(this!=&ned){
        delete [] adresa;
        this->adresa=new char[strlen(ned.adresa)+1];
        strcpy(this->adresa,ned.adresa);
        this->kvadratura=ned.kvadratura;
        this->c=ned.c;
        }
        return *this;
    }
    double cena()
    {
        return kvadratura*c;
    }
    void pecati()
    {
        cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<c<<endl;
    }
    double danokNaImot()
    {
        return cena()*0.05;
    }
    char* getAdresa()
    {
        return adresa;
    }
    friend istream &operator>>(istream &in,Nedviznina &n)
    {
        in>>n.adresa;
        in>>n.kvadratura;
        in>>n.c;
        return in;
    }

};
class Vila:public Nedviznina
{
private:
    int danok;
public:
    Vila(){
    danok=0;
    }
    void pecati()
    {
        cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<c<<", Danok na luksuz: "<<danok<<endl;
    }
    double danokNaImot()
    {
        return cena()*(0.05+danok/100.0);
    }
    friend istream &operator>>(istream &in,Vila &v)
    {
        in>>v.adresa;
        in>>v.kvadratura;
        in>>v.c;
        in>>v.danok;
        return in;
    }
};
int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}