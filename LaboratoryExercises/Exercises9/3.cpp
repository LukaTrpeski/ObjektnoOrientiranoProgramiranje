/*
Сите елементи кои ги превезуваат камионите имаат одредена маса. Имплементирајте апстрактна класа ImaMasa од која што ќе наследуваат сите класи кои имаат маса. Во оваа класа треба да се дефинираат методите:

double vratiMasa() враќа маса изразена во kg
void pecati() печати информации за соодветниот објект
Нека еден камион превезува пијалоци и тоа: пакет сокови и пакет вина. Да се дефинираат класите PaketSok и PaketVino кои ги имплементираат методите од апстрактната класа ImaMasa. При тоа да се земе предвид дека класите PaketSok и PaketVino се изведени од класата PaketPijalok. Притоа да се земат дадените податоци:

Класа PaketPijalok:

членови:
volumenEden double
kolicina int
методи:
double vratiMasa()
void pecati()
int getKolicina()
Класа PaketSok:

членови:
volumenEden double
kolicina int
daliGaziran bool
методи:
double vratiMasa()
void pecati()
Класа PaketVino:

членови:
volumenEden double
kolicina int
procentAlkohol double
методи:
double vratiMasa()
double getProcentAlkohol()
void pecati()
Еден пијалок има маса пресметана како производ на волуменот и густината (0.8kg/dm3) и масата на амбалажата (0.2kg). Овие податоци за густината и за масата на амбалажата да се стават како статички податоци за класата PaketPijalok. Масата на пакетот е производ на масата на еден пијалок и количината на пијалоци која ја има во пакетот. Соковите кои не се газирани имаат дополнителна маса од 0.1kg по пијалок. За вината, масата се добива како производ од масата на пакетот пресметан по правилата за секој пијалок помножен со коефициентот: (0.9+procentAlkohol).

Покрај овие класи, да се имплементира класата Kamion. За еден камион се чуваат информации за:

регистрацијата char*
возачот char*
елементите кои ги превезува камионот (низа од покажувачи од ImaMasa)
Во класата Kamion покрај методите set и get дефинирајте ги и следните методи:

Kamion(char* ) конструктор со кој се генерира празен камион (без товар) и само возач
void registriraj(char*) се додава регистрацијата на камионот
void dodadiElement(ImaMasa) се додава нов елемент во камионот
double vratiVkupnaMasa() се враќа вкупната маса на товарот кој го пренесува камионот
void pecati() се печатат сите елементи во камионот заедно со регистрацијата и името на возачот
Kamion pretovar(char* , char* ) се врши претовар во нов камион, но во новиот покрај тоа што се менуваат регистрацијата и името на возачот (аргументи), се отстранува пакетот со најголема маса.
Со помош на правилата за справување со исклучоци да се модифицира програмата така што ќе се запазат следните правила: - Регистрацијата има 8 карактери, така што првите два и последните два мора да бидат букви. Да се определи каде ќе се фрли соодветниот исклучок. Онаму каде што ќе се фати исклучокот, ќе се отпечати "Pogresno vnesena registracija!".
*/
#include <iostream>
#include <cstring>

using namespace std;

class Exception
{
private:
    char text[40];
public:
    Exception(char *text)
    {
        strcpy(this->text,text);
    }
    void message()
    {
        cout<<text<<endl;
    }
};

class ImaMasa
{
public:
    virtual double vratiMasa()=0;
    virtual void pecati()=0;
};
class PaketPijalok
{
protected:
    double volumenEden;
    int kolicina;
    const static double gustina;
    const static double masa;
public:
    PaketPijalok(double volumenEden=0,int kolicina=0)
    {
        this->volumenEden=volumenEden;
        this->kolicina=kolicina;
    }
    double vratiMasa()
    {
        return (volumenEden*gustina+masa)*kolicina;
    }
    void pecati()
    {
        cout<<"kolicina "<<kolicina<<endl;
    }
    int getKolicina()
    {
        return kolicina;
    }
};
const double PaketPijalok::gustina=0.8;
const double PaketPijalok::masa=0.2;
class PaketSok:public PaketPijalok,public ImaMasa
{
protected:
    bool daliGaziran;
public:
    PaketSok(double volumenEden=0,int kolicina=0,bool daliGaziran=false):PaketPijalok(volumenEden,kolicina)
    {
        this->daliGaziran=daliGaziran;
    }
    double vratiMasa()
    {
        if(daliGaziran)
            return PaketPijalok::vratiMasa();
        else
        {
            return PaketPijalok::vratiMasa()+(0.1*kolicina);
        }
    }
    void pecati()
    {
        cout<<"Paket sok"<<endl;
        cout<<"kolicina "<<kolicina<<", so po "<<volumenEden*gustina<<" l(dm3)"<<endl;
    }
};
class PaketVino:public PaketPijalok,public ImaMasa
{
protected:
    double procentAlkohol;
public:
    PaketVino(double volumenEden=0,int kolicina=0,double procentAlkohol=0):PaketPijalok(volumenEden,kolicina)
    {
        this->procentAlkohol=procentAlkohol;
    }
    double vratiMasa()
    {
        return (0.9+procentAlkohol)*PaketPijalok::vratiMasa();
    }
    void pecati()
    {
        cout<<"Paket vino"<<endl;
        cout<<"kolicina "<<kolicina<<", "<<procentAlkohol*100<<"% alkohol od po "<<volumenEden*gustina<<" l(dm3)"<<endl;
    }
    double getProcentAlkohol()
    {
        return procentAlkohol;
    }
};
class Kamion
{
private:
    char registracija[50];
    char vozac[50];
    ImaMasa **niza;
    int n;
public:
    Kamion(char *registracija="",char* vozac="")
    {
        strcpy(this->vozac,vozac);
        bool is=false;
        if(isalpha(registracija[0])&&isalpha(registracija[1])&&isalpha(registracija[6])&&isalpha(registracija[7]))
                is=true;
        if(!is)
        {
            throw Exception("Pogresno vnesena registracija");
        }
        strcpy(this->registracija,registracija);
        this->niza=new ImaMasa*[0];
        this->n=0;
    }
    void registriraj(char *registracija)
    {
        strcpy(this->registracija,registracija);
    }
    void setvozac(char *vozac)
    {
        strcpy(this->vozac,vozac);
    }
    void setn(int n)
    {
        this->n=n;
    }
    void dodadiElement(ImaMasa *im)
    {
        ImaMasa **temp=new ImaMasa*[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=niza[i];
        }
        temp[n++]=im;
        niza=new ImaMasa*[n];
        for(int i=0;i<n;i++)
        {
            niza[i]=temp[i];
        }
    }
    double vratiVkupnaMasa()
    {
        double suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=niza[i]->vratiMasa();
        }
        return suma;
    }
    void pecati()
    {
        cout<<"Kamion so registracija "<<registracija<<" i vozac "<<vozac<<" prenesuva:"<<endl;
        for(int i=0;i<n;i++)
        {
            niza[i]->pecati();
        }
    }
    Kamion pretovar(char *registracija,char *vozac)
    {
        Kamion nov(registracija,vozac);
        int maxindex=0;
        for(int i=0;i<n;i++)
        {
            if(niza[i]->vratiMasa()>niza[maxindex]->vratiMasa())
            {
                maxindex=i;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(i!=maxindex)
                nov.dodadiElement(niza[i]);
        }
        return nov;
    }

};
int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;
    try{
            cin>>reg;
            cin>>ime;
            Kamion A(reg, ime);
            ImaMasa **d = new ImaMasa*[5];
            cin>>vol>>kol;
            cin>>g;
            d[0] = new PaketSok(vol, kol, g);
            cin>>vol>>kol;
            cin>>proc;
            d[1] = new PaketVino(vol, kol, proc);
            cin>>vol>>kol;
            cin>>proc;
            d[2] = new PaketVino(vol, kol, proc);
            cin>>vol>>kol;
            cin>>g;
            d[3] = new PaketSok(vol, kol, g);
            cin>>vol>>kol;
            cin>>proc;
            d[4] = new PaketVino(vol, kol, proc);

            A.dodadiElement(d[0]);
            A.dodadiElement(d[1]);
            A.dodadiElement(d[2]);
            A.dodadiElement(d[3]);
            A.dodadiElement(d[4]);
            A.pecati();
            cout<<"Vkupna masa: "<<A.vratiVkupnaMasa()<<endl;
            cin>>reg;
            cin>>ime;
            Kamion B = A.pretovar(reg, ime);
            B.pecati();
            cout<<"Vkupna masa: "<<B.vratiVkupnaMasa()<<endl;
    }
    catch(Exception &e)
    {
        e.message();
    }

}
