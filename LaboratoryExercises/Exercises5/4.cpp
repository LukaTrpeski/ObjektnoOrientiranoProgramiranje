/*
Да се креира класа за претставување на планинарско друштво во која ќе се чуваат информации за името на друштвото (динамички алоцирана низа од знаци), број на поминати тури (цел број) и број на членови во планинарското друштво (цел број). За оваа класа да се напише:

оператор + за собирање на две друштва што како резултат враќа друштво со број на членови еднаков на збирот од членовите од двете друштва, а останатите атрибути на резултантното друштво ги добиваат вредностите на соодветните атрибути од друштвото со поголем број на членови

оператори >, < за споредба во однос на бројот на членови во планинарските друштва

оператор << за печатење на информациите за планинарското друштво

Да се напише функција што на влез прима низа од планинарски друштва и вкупен број на друштва во низата и го печати планинарското друштво што има најголем број на членови .
*/
#include <iostream>
#include <string.h>
using namespace std;

class PlDrustvo{
private:
    char *ime;
    int brojturi;
    int brojchlenovi;
public:
    PlDrustvo(){
    ime = new char[1];
    strcpy(ime,"");
    brojturi=0;
    brojchlenovi=0;
    }
    PlDrustvo(char *ime,int brojturi,int brojchlenovi){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->brojturi=brojturi;
        this->brojchlenovi=brojchlenovi;
    }
    PlDrustvo(const PlDrustvo &p){
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->brojturi=p.brojturi;
        this->brojchlenovi=p.brojchlenovi;
    }
    PlDrustvo& operator=(PlDrustvo &p)
    {
        if(this!=&p)
        {
            delete [] ime;
            this->ime=new char[strlen(p.ime)+1];
            strcpy(this->ime,p.ime);
            this->brojturi=p.brojturi;
            this->brojchlenovi=p.brojchlenovi;
        }
        return *this;
    }
    PlDrustvo& operator+(const PlDrustvo &p)
    {
        PlDrustvo *temp;

        if(brojchlenovi>p.brojchlenovi)
        {
            temp = new PlDrustvo(ime,brojturi,brojchlenovi+p.brojchlenovi);
        }
        else
        {
            temp = new PlDrustvo(p.ime,p.brojturi,brojchlenovi+p.brojchlenovi);
        }
        return *temp;
    }
    friend ostream& operator<<(ostream &out,PlDrustvo &p)
    {
        out<<"Ime: "<<p.ime<<" Turi: "<<p.brojturi<<" Clenovi: "<<p.brojchlenovi<<endl;
        return out;
    }
    friend bool operator>(const PlDrustvo &p,const PlDrustvo &q);
    friend bool operator<(const PlDrustvo &p,const PlDrustvo &q);
};
bool operator>(const PlDrustvo &p,const PlDrustvo &q)
    {
        return p.brojchlenovi>q.brojchlenovi;
    }
bool operator<(const PlDrustvo &p,const PlDrustvo &q)
    {
        return p.brojchlenovi<q.brojchlenovi;
    }
void najmnoguClenovi(PlDrustvo *p,int n)
{
    int k=0;
    for(int i=0;i<n-1;i++)
    {
        if(p[i+1]>p[i])
            k=i+1;
    }
    cout<<"Najmnogu clenovi ima planinarskoto drustvo: "<<p[k]<<endl;
}
int main()
{        		
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
   	{
    	char ime[100];
    	int brTuri;
    	int brClenovi;
    	cin>>ime;
    	cin>>brTuri;
    	cin>>brClenovi;
    	PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;
    	
   	}
    
    pl = drustva[0] + drustva[1];
    cout<<pl;
    
    najmnoguClenovi(drustva, 3);
    
    return 0;
}
