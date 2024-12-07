/*
(40 поени)

Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).

За оваа класа да се преоптоварат:

Оператор << - за печатење на информациите за патникот во формат:
Име на патник

Бројот на класата (1 или 2)

Дали има велосипед?

Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).

За класата да се обезбедат:

Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
Оператор << - за печатење на крајната дестинација до која вози и листата на патници
Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед. Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот. На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.
*/
#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

class Patnik{
private:
    char ime[100];
    int klasa;
    bool velosiped;
public:
    Patnik(char *ime="",int klasa=1,bool velosiped=true)
    {
        strcpy(this->ime,ime);
        this->klasa=klasa;
        this->velosiped=velosiped;
    }
    friend ostream&operator<<(ostream &out,Patnik &p)
    {
        out<<p.ime<<endl<<p.klasa<<endl;
        if(p.velosiped)
            out<<1<<endl;
        else
            out<<0<<endl;
        out<<endl;
        return out;
    }
    bool imavelosiped()
    {
        return velosiped;
    }
    int getKlasa()
    {
        return klasa;
    }
};
class Voz{
private:
    char destinacija[100];
    Patnik *p;
    int broje;
    int brojv;
public:
    Voz(char *destinacija="",int brojv=0,int broje=0,Patnik *p=0)
    {
        strcpy(this->destinacija,destinacija);
        this->brojv=brojv;
        this->broje=broje;
        this->p = new Patnik[broje];
        for(int i=0;i<broje;i++)
        {
            this->p[i]=p[i];
        }
    }
    Voz(const Voz &v)
    {
        strcpy(this->destinacija,v.destinacija);
        this->brojv=v.brojv;
        this->broje=v.broje;
        p = new Patnik[broje];
        for(int i=0;i<broje;i++)
        {
            this->p[i]=v.p[i];
        }
    }
    Voz &operator=(Voz &v)
    {
        if(this!=&v)
        {
        delete [] p;
        strcpy(this->destinacija,v.destinacija);
        this->brojv=v.brojv;
        this->broje=v.broje;
        p = new Patnik[broje];
        for(int i=0;i<broje;i++)
        {
            this->p[i]=v.p[i];
        }
        }
        return *this;
    }
    ~Voz(){delete [] p;}
    Voz &operator+=(Patnik nov)
    {
        if(!(nov.imavelosiped())&&brojv==0||brojv!=0)
        {
            Patnik *temp=new Patnik[broje+1];
            for(int i=0;i<broje;i++)
            {
                temp[i]=p[i];
            }
            temp[broje++]=nov;
            delete [] p;
            p=temp;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out,Voz &v)
    {
        out<<v.destinacija<<endl;
        for(int i=0;i<v.broje;i++)
        {
            out<<v.p[i];
        }
        return out;
    }
        void patniciNemaMesto()
    {
        int prva=0;
        int vtora=0;
        for(int i=0;i<broje;i++){
        if(p[i].getKlasa()==1&&p[i].imavelosiped())
            prva++;
        else if(p[i].getKlasa()==2&&p[i].imavelosiped())
            vtora++;
            }
        if(prva>=brojv)
        {
            prva-=brojv;
        }
        else if(prva<brojv)
        {
            brojv-=prva;
            prva=0;
            if(vtora>=brojv)
            {
                vtora-=brojv;
            }
            else 
            {
                vtora=0;
            }
        }
        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<prva<<endl;
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<vtora<<endl;
    }
};

int main()
{
	Patnik p;
	char ime[100], destinacija[100];
	int n;
	bool velosiped;
	int klasa;
	int maxv;
	cin >> destinacija >> maxv;
	cin >> n;
	Voz v(destinacija, maxv);
	//cout<<v<<endl;
	for (int i = 0; i < n; i++){
		cin >> ime >> klasa >> velosiped;
		Patnik p(ime, klasa, velosiped);
		//cout<<p<<endl;
		v += p;
	}
	cout << v;
	v.patniciNemaMesto();


	return 0;
}