/*
Да се дефинира класата Film во која се чуваат информации за:

име на филмот (динамички алоцирано поле од знаци)
мемориската зафатнина на филмот изразена во MB
жанр на филмот кој може да биде: акција, комедија или драма (енумерација zanr)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат одделени со цртичка(-): мемориска зафатнина на филмот со постфикс MB и името на филмот во наводници.
Да се креира класата DVD во која се чуваат информации за :

низа од филмови снимени на DVD-то (Поле од најмногу 5 објекти од класата Film )
број на филмови снимени на DVD-то
меморискиот капацитет на DVD-то (во MB)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинираат методите:

dodadiFilm (Film f) - со кој се додава филмот f на DVDто, но само ако има доволно преостанато место (земајќи го предвид меморискиот капацитет на DVD-то и мемориската зафатнина на снимените филмови) и притоа да има помалку од 5 филмови на DVD-то.
pecatiFilmoviDrugZanr(zanr z) – со кој се печатат информациите за сите филмови кои НЕ се од жанрот zanr (акција, комедија или драма).
(дополнително барање):float procentNaMemorijaOdZanr(zanr z)- со кој се пресметува процентот на меморијата која ја зафаќаат филмовите од жанр z на DVD-то.
*/
#include <iostream>
#include <string.h>
#include <ctype.h>

using namespace std;

enum zanr{akcija,komedija,drama};

class Film{
private:
    char *ime;
    int mb;
    zanr zr;
public:
    Film(){
    ime=new char[1];
    strcpy(ime,"");
    mb=0;
    }
    Film(char *ime,int mb,zanr zr)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->mb=mb;
        this->zr=zr;
    }
    Film(const Film &f)
    {
        this->ime=new char[strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->mb=f.mb;
        this->zr=f.zr;
    }
    Film& operator=(Film &f)
    {
        if(this!=&f)
        {
            delete [] ime;
            this->ime=new char[strlen(f.ime)+1];
            strcpy(this->ime,f.ime);
            this->mb=f.mb;
            this->zr=f.zr;
        }
        return *this;
    }
    void pecati()
    {
        cout<<mb<<"MB-"<<"\""<<ime<<"\""<<endl;
    }
    int getmb()
    {
        return mb;
    }
    zanr getzanr()
    {
        return zr;
    }
};
class DVD{
private:
    Film snimeni[5];
    int broj;
    int kapacitet;
public:
    DVD(){}
    DVD(int kapacitet)
    {
        this->kapacitet=kapacitet;
        broj=0;
    }
    DVD(Film *snimeni,int broj, int kapacitet)
    {
        this->broj=broj;
        this->kapacitet=kapacitet;
        for(int i=0;i<broj;i++)
        {
            this->snimeni[i]=snimeni[i];
        }
    }
    DVD(DVD &d)
    {
        this->broj=d.broj;
        this->kapacitet=d.kapacitet;
        for(int i=0;i<broj;i++)
        {
            this->snimeni[i]=d.snimeni[i];
        }
    }
    void dodadiFilm(Film f)
    {
        int sum=0;
        for(int i=0;i<broj;i++)
        {
            sum+=snimeni[i].getmb();
        }

        if(broj<5&&kapacitet-sum>=f.getmb())
        {
            snimeni[broj]=f;
            broj++;
        }
    }
    int getBroj()
    {return broj;}
    Film getFilm(int i)
    {
        return snimeni[i];
    }
    void pecatiFilmoviDrugZanr(zanr z)
    {
        for(int i=0;i<broj;i++)
        {
            if(snimeni[i].getzanr()!=(zanr)z)
            {
                snimeni[i].pecati();
            }
        }
    }
    float procentNaMemorijaOdZanr(zanr z)
    {
        float sum = 0.0;
        for (int i=0;i<broj;i++)
            if (snimeni[i].getzanr()==z)
                sum+=snimeni[i].getmb();
            
        return sum / broj*10.0;
    }

};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
		cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
		DVD omileno(40);
		cin >> n;
		for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";
		
	}

    return 0;
}