/*
Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:

име (динамички алоцирана низа од знаци)
пол (bool)
возраст (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)

Дополнително за оваа класа да се преоптоварат:

оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)
Да се дефинира класа Maraton за кој се чуваат:

локација (низа од максимум 100 знаци)
низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
број на учесници (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени) Исто така да се имплементираат следните методи:

оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)
*/
#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

class Ucesnik{
private:
    char *ime;
    bool pol;
    int vozrast;
public:
    Ucesnik(char *ime="",bool pol=true,int vozrast=0)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->pol=pol;
        this->vozrast=vozrast;
    }
    Ucesnik(const Ucesnik &u)
    {
        this->ime=new char[strlen(u.ime)+1];
        strcpy(this->ime,u.ime);
        this->pol=u.pol;
        this->vozrast=u.vozrast;
    }
    Ucesnik &operator=(Ucesnik &u)
    {
        if(this!=&u)
        {
            delete [] ime;
            this->ime=new char[strlen(u.ime)+1];
            strcpy(this->ime,u.ime);
            this->pol=u.pol;
            this->vozrast=u.vozrast;
        }
        return *this;
    }
    int getvozrast()
    {
        return vozrast;
    }
    friend bool operator>(const Ucesnik &u,const Ucesnik &t);
    friend ostream &operator<<(ostream &out,Ucesnik &u)
    {
        out<<u.ime<<endl;
        if(u.pol)
            out<<"mashki"<<endl;
        else
            out<<"zhenski"<<endl;
        out<<u.vozrast<<endl;
    }
};
bool operator>(const Ucesnik &u,const Ucesnik &t)
{
    return u.vozrast>t.vozrast;
}
class Maraton{
private:
    char lokacija[100];
    Ucesnik *ucesnici;
    int brojucesnici;
public:
    Maraton(char *lokacija="",Ucesnik *ucesnici=NULL,int brojucesnici=0)
    {
        strcpy(this->lokacija,lokacija);
        this->brojucesnici=brojucesnici;
        this->ucesnici=new Ucesnik[brojucesnici];
        for(int i=0;i<brojucesnici;i++)
        {
            this->ucesnici[i]=ucesnici[i];
        }
    }
    Maraton(const Maraton &m){
        strcpy(this->lokacija,m.lokacija);
        this->brojucesnici=m.brojucesnici;
        this->ucesnici=new Ucesnik[brojucesnici];
        for(int i=0;i<brojucesnici;i++)
        {
            this->ucesnici[i]=m.ucesnici[i];
        }
    }
    Maraton &operator=(Maraton &m)
    {
        if(this!=&m)
        {
        strcpy(this->lokacija,m.lokacija);
        this->brojucesnici=m.brojucesnici;
        this->ucesnici=new Ucesnik[brojucesnici];
        for(int i=0;i<brojucesnici;i++)
        {
            this->ucesnici[i]=m.ucesnici[i];
        }
        }
        return *this;
    }
    ~Maraton(){delete [] ucesnici;}
    float prosecnoVozrast()
    {
        int sum=0;
        for(int i=0;i<brojucesnici;i++)
        {
            sum+=ucesnici[i].getvozrast();
        }
        return sum/(brojucesnici*1.0);
    }
    void pecatiPomladi(Ucesnik &u)
    {
        for(int i=0;i<brojucesnici;i++)
        {
            if(ucesnici[i].getvozrast()<u.getvozrast())
            {
                cout<<ucesnici[i];
            }
        }
    }
    Maraton &operator+=(Ucesnik &nov)
    {
        Ucesnik *temp=new Ucesnik[brojucesnici+1];
        for(int i=0;i<brojucesnici;i++)
        {
            temp[i]=ucesnici[i];
        }
        temp[brojucesnici++]=nov;
        delete [] ucesnici;
        ucesnici=temp;
    }


};
int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
    	u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
	m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
	return 0;
}