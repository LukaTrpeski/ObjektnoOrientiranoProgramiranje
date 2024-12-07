/*
Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

име на песна (динамички алоцирано поле од знаци)
времетраење на песната во минути
тип на песна кој може да биде: поп, рап или рок (енумерација tip)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

Дополнително за оваа класа да се дефинира методот:

pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
Да се креира класата CD во која се чуваат информации за (5 поени):

низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
број на песни снимени на CD-то
максимално времетраење на песните на CD-то (во минути)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

Дополнително за оваа класа да се дефинираат методите:

dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
Комплетна функционалност (5 поени).
*/
#include <iostream>
#include <string.h>
using namespace std;

enum tip{pop,rap,rok};

class Pesna{
private:
    char *ime;
    int vreme;
    tip t;
public:
    Pesna(char *ime="",int vreme=0,tip t=pop)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->vreme=vreme;
        this->t=t;
    }
    Pesna(const Pesna &p)
    {
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->vreme=p.vreme;
        this->t=p.t;
    }
    Pesna &operator=(Pesna &p)
    {
        if(this!=&p){
        delete [] ime;
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->vreme=p.vreme;
        this->t=p.t;
        }
        return *this;
    }
    ~Pesna(){delete [] ime;}
    void pecati()
    {
        cout<<"\""<<ime<<"\""<<"-"<<vreme<<"min"<<endl;
    }
    int getvreme()
    {
        return vreme;
    }
    tip gettip()
    {
        return t;
    }
};
class CD{
private:
    Pesna p[10];
    int brojpesni;
    int vremetraenje;
public:
    CD(int vremetraenje=0,int brojpesni=0,Pesna *p=0)
    {
        this->brojpesni=brojpesni;
        this->vremetraenje=vremetraenje;
        for(int i=0;i<brojpesni;i++)
        {
            this->p[i]=p[i];
        }
    }
    void dodadiPesna(Pesna q)
    {
        int site=0;
        for(int i=0;i<brojpesni;i++)
        {
            site+=p[i].getvreme();
        }
        if(brojpesni<10&&q.getvreme()<=vremetraenje-site)
        {
            p[brojpesni++]=q;
        }
    }
    void pecatiPesniPoTip(tip t)
    {
        for(int i=0;i<brojpesni;i++)
        {
            if(p[i].gettip()==t)
                p[i].pecati();
        }
    }
    Pesna getPesna(int i)
    {
        return p[i];
    }
    int getBroj()
    {
        return brojpesni;
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;
	
	int n, minuti, kojtip;
	char ime[50];
	
	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    
return 0;
}