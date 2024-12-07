/*
Да се дефинира класа Pica за која ќе се чуваат податоци за:

име на пицата (низа од 15 знаци)
цена (цел број)
состојки (динамички алоцирана низа од знаци)
намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
istiSe(Pica p) - функција за споредба на две пици според состојките :
Да се дефинира класа Picerija во која се чуваат:

име (низа од максимум 15 знаци)
динмички алоцирана низа од објекти од класата Pica
број на пици (цел број)
За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

dodadi (Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.
*/
#include <iostream>
#include <string.h>
#include <ctype.h>

using namespace std;
class Picerija;
class Pica{
private:
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje;
public:
    Pica(){
    strcpy(ime,"");
    sostojki=NULL;
    cena=0;
    namaluvanje=0;
    }
    Pica(char *ime,int cena,char *sostojki,int namaluvanje){
    strcpy(this->ime,ime);
    this->cena=cena;
    this->namaluvanje=namaluvanje;
    this->sostojki=new char[strlen(sostojki)+1];
    strcpy(this->sostojki,sostojki);
    }
    Pica(const Pica &p){
    strcpy(this->ime,p.ime);
    this->cena=p.cena;
    this->namaluvanje=p.namaluvanje;
    this->sostojki=new char[strlen(p.sostojki)+1];
    strcpy(this->sostojki,p.sostojki);
    }
    Pica& operator=(const Pica &p){
    if(this!=&p){
    delete [] sostojki;
    strcpy(this->ime,p.ime);
    this->cena=p.cena;
    this->namaluvanje=p.namaluvanje;
    this->sostojki=new char[strlen(p.sostojki)+1];
    strcpy(this->sostojki,p.sostojki);
    }
    return *this;
    }
    ~Pica(){delete [] sostojki;}
    void pecati()
    {
        cout<<ime<<" - "<<sostojki<<", "<<cena<<endl;
    }
    bool istiSe(Pica p)
    {
        if(strcmp(sostojki,p.sostojki)==0)
            return true;
        else
            return false;
    }
    friend class Picerija;
};
class Picerija{
private:
    char ime[15];
    Pica *pica;
    int broj;
public:
    Picerija(char *i=""){
    strcpy(ime,i);
    pica=NULL;
    broj=0;
    }
    Picerija(const Picerija &p){
    strcpy(this->ime,p.ime);
    this->broj=p.broj;
    this->pica=new Pica[broj];
    for(int i=0;i<broj;i++)
    {
        this->pica[i]=p.pica[i];
    }
    }
    Picerija& operator=(const Picerija &p){
    if(this!=&p){
    delete [] pica;
    strcpy(this->ime,p.ime);
    this->broj=p.broj;
    this->pica=new Pica[broj];
    for(int i=0;i<broj;i++)
    {
        this->pica[i]=p.pica[i];
    }
    }
    return *this;
    }
    ~Picerija(){delete [] pica;}
    void setIme(char *i)
    {strcpy(ime,i);}
    char *getIme()
    {
        return ime;
    }
    void dodadi(Pica p)
    {
        for(int i=0;i<broj;i++)
        {
            if(pica[i].istiSe(p))
                return;
        }
        Pica *temp=new Pica[broj+1];
        for(int i=0;i<broj;i++)
        {
            temp[i]=pica[i];
        }
        temp[broj++]=p;
        delete [] pica;
        pica=new Pica[broj];
        pica=temp;

        }
    void piciNaPromocija()
    {
        for(int i=0;i<broj;i++)
        {
            if(pica[i].namaluvanje!=0)
            cout<<pica[i].ime<<" - "<<pica[i].sostojki<<", "<<pica[i].cena<<" "<<(pica[i].cena-(pica[i].cena*pica[i].namaluvanje/100))<<endl;
        }
    }

};


int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

	return 0;
}
