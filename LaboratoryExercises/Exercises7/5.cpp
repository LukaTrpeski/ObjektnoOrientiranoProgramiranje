/*
Да се креира хиерархиjа на класи за репрезентациjа на жичани инструменти. За потребите на оваа хиерархиjа да се дефинира класа ZicanInstrument од коjа ќе бидат изведени двете класи Mandolina и Violina.

Во класата ZicanInstrument се чуваат податоци за:

името на инструментот (низа од 20 знаци)
броjот на жици
основната цена на инструментот.
За класата Mandolina дополнително се чува неjзината форма (низа од 20 знаци).

За класата Violina дополнително се чува неjзината големина (децимален броj).

За секоjа изведените класи треба да се дефинираат соодветните конструктори и следните методи:

cena() за пресметување на цената на инструментот
основната цена на мандолината се зголемува за 15% доколку таа има форма во Неаполитански стил (вредноста на променливата форма е “Neapolitan”)
основната цена на виолината се зголемува за 10% ако неjзината големина има вредност 1/4 (0.25), односно за 20% ако неjзината големина има вредност 1 (1.00)
проптоварување на операторот ==, коj ги споредува жичаните инструменти според броjот на жици што го имаат
преоптоварување на операторот << за печатење на сите податоци за жичаните инструменти.
Да се напише функциjа pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n) коjа на влез прима жичан инструмент, низа од покажувачи кон жичани инструменти и броj на елементи во низата. Функциjата jа печати цената на сите жичани инструменти од низата кои имаат ист броj на жици како и инструментот проследен како прв аргумент на функциjата.
*/
#include <iostream>
#include <string.h>
using namespace std;
class ZicanInstrument
{
protected:
    char ime[20];
    int broj;
    float osnovna;
public:
    ZicanInstrument(char *ime="",int broj=0,float osnovna=0)
    {
        strcpy(this->ime,ime);
        this->broj=broj;
        this->osnovna=osnovna;
    }
    virtual float cena()
    {
        return osnovna;
    }
    bool operator==(ZicanInstrument &z)
    {
        return broj==z.broj;
    }
    friend ostream &operator<<(ostream &out,ZicanInstrument &z)
    {
        out<<z.ime<<" "<<z.broj<<" "<<z.osnovna<<endl;
        return out;
    }
};
class Mandolina:public ZicanInstrument
{
private:
    char forma[20];
public:
    Mandolina(char *ime="",int broj=0,float osnovna=0,char *forma=""):ZicanInstrument(ime,broj,osnovna)
    {
        strcpy(this->forma,forma);
    }
    float cena()
    {
        if(strcmp(forma,"Neapolitan")==0)
            return osnovna*1.15;
        else
            return osnovna;
    }

};
class Violina:public ZicanInstrument
{
private:
    float golemina;
public:
    Violina(char *ime="",int broj=0,float osnovna=0,float golemina=0.0):ZicanInstrument(ime,broj,osnovna)
    {
        this->golemina=golemina;
    }
    float cena()
    {
        if(golemina==0.25)
            return osnovna*1.10;
        else if(golemina==1)
            return osnovna*1.20;
        else
            return osnovna;
    }

};
void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **niza, int n)
{
    for(int i=0;i<n;i++)
    {
        if(*niza[i]==zi)
            cout<<niza[i]->cena()<<endl;
    }
}
int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument **zi = new ZicanInstrument*[2 * n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for(int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for(int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete [] zi;
	return 0;
}