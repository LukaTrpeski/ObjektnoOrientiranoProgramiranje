/*
Дадена е дел од дефиниција на класата StudentKurs. За секој студент кој слуша некој курс се чуваат информации за неговото име (низа од знаци), оценка од писмен дел (цел број) и дали студентот сака да биде испрашуван и усно (булова променлива).

Оцената за писмениот дел е вредност од 1 до МАX. MAX има почетна вредност 10 која е иста е за сите и може да се промени со соодветна функција setMAX(). (5 поени)

Кај оние студенти кои сакаат да бидат испрашувани усно и добиваат и описна оценка. Имплементирај соодветна класа StudentKursUsno во која се чуваат дополнителни информации за описна оценка на усното испрашување (динамичко алоцирана низа од знаци). Описни оценки може да бидат: odlicen, dobro, losho.... Ако описната оценка е odlicen тогаш оцената ќе биде најмногу за оценки 2 повисока од оценката од писмениот дел, ако е dobro оценката ќе биде најмногу за 1 повисока, а ако е losho за 1 пониска. Ако студентот добие некоја друга описна оценка, неговата оценка ќе остане иста со оценката од писмениот дел.

Во класите StudentKurs и StudentKursUsno треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за студентот на курсот во формат: Ime --- ocenka (5 поени)
оcenka() – ја враќа оценката на студентот на курсот (5 поени)
Во класата StudentKursUsno дефинирај ја функцијата:

преоптоварен оператор += за поставување на описна оценка на студентот(5 поени)
Ако се направи обид да се внесе описна оценка во која покрај букви има и други знаци треба да се фрли исклучок (објект од класата BadInputException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Greshna opisna ocenka) и справете се со исклучокот така што тие знаци ќе отстранат од стрингот со описната оценка (ако описната оценка била dо1ba0r ќе се промени во dоbar). (10 поени)

Дадена е дел од дефиницијата на класата KursFakultet во која се чуваат информаци за името на курсот (низа од 30 знаци) и за студентите запишани на курсот (низа од 20 покажувачи кон класата StudentKurs) како и бројот на студенти запишани на курсот.

Еден студент кој запишал некој курс ќе го положи курсот ако има барем MINOCENKA. Вредноста MINOCENKA е членка на класата StudentKurs и има фиксна вредност 6 која не може да се промени. (5 поени)

Во класата KursFakultet имплементирај ги функциите:

функција pecatiStudenti() во која се печатат сите студенти кои го положиле курсот, секој во посебен ред. Претходно во првиот ред се печати: Kursot XXXXX go polozile: (5 поени).

функција postaviOpisnaOcenka(char * ime, char* opisnaOcenka) во која на студентот на курсот со даденото име му се поствува описна оценка. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)
*/
#include <iostream>
#include <ctype.h>
#include <math.h>
#include <cstring>
#include <string.h>
using namespace std;

class BadInputException
{
public:
    char *nova;
    BadInputException(char *a=""){
        int k=0;
        for(int i=0;i<strlen(a);i++)
        {
            if(isalpha(a[i]))
            {
                k++;
            }
        }
        nova=new char[k+1];
        k=0;
        for(int i=0;i<strlen(a);i++)
        {
            if(isalpha(a[i]))
            {
                nova[k]=a[i];
                k++;
            }
        }
        nova[k]='\0';
    }
    void print()
    {
        cout<<"Greshna opisna ocenka"<<endl;
    }
};
class StudentKurs
{
protected:
    char ime[30];
    int ocena;
    bool daliUsno;
public:
    static int MAX;
    const static int MINOCENKA;
    StudentKurs(const char *ime="",int ocena=0,bool daliUsno=false)
    {
        strcpy(this->ime,ime);
        this->ocena=ocena;
        this->daliUsno=daliUsno;
    }
    char* getIme()
    {
        return ime;
    }
    void setIme(const char *i)
    {
        strcpy(ime,i);
    }
    void setOcenka(int o)
    {
        ocena=o;
    }
    void setdaliUsno(bool u)
    {
        daliUsno=u;
    }
    bool getDaliUsno()
    {
        return daliUsno;
    }
    static void setMAX(int m)
    {
        MAX=m;
    }
    virtual int ocenka()
    {
        return ocena;
    }
    friend ostream &operator<<(ostream &out,StudentKurs &sk)
    {
        out<<sk.ime<<" --- "<<sk.ocenka()<<endl;
        return out;
    }
};
int StudentKurs::MAX=10;
const int StudentKurs::MINOCENKA=6;
class StudentKursUsno:public StudentKurs
{
private:
    char *opisna;
public:
    StudentKursUsno(const char *ime="",int ocena=0,bool daliUsno=true, char *opisna=""):StudentKurs(ime,ocena,daliUsno)
    {
        this->opisna=new char[strlen(opisna)+1];
        strcpy(this->opisna,opisna);

    }
    void setOpisna(char *o)
    {
        opisna=new char[strlen(o)+1];
        strcpy(opisna,o);

    }
    StudentKursUsno &operator+=(char *op)
    {
        for(int i=0;i<strlen(op);i++)
        {
            if(!isalpha(op[i]))
                throw BadInputException(op);
        }
        this->daliUsno=true;
        this->opisna=new char[strlen(op)+1];
        strcpy(this->opisna,op);
        return *this;
    }
    int ocenka()
    {
        if(strcmp(opisna,"odlicen")==0&&(ocena+2)<=StudentKurs::MAX)
            return this->ocena+2;
        else if(strcmp(opisna,"dobro")==0&&(ocena+1)<=StudentKurs::MAX)
            return this->ocena+1;
        else if(strcmp(opisna,"losho")==0)
            return this->ocena-1;
        else
            return this->ocena;
        
    }
};
class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        if (studenti[i]->getDaliUsno()){
            this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
        }
        else this->studenti[i]=new StudentKurs(*studenti[i]);
      }
      this->broj=broj;
    }
    ~KursFakultet(){
    for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti()
    {
        cout<<"Kursot "<<naziv<<" go polozile: "<<endl;
        for(int i=0;i<broj;i++)
        {
            if(studenti[i]->ocenka()>=StudentKurs::MINOCENKA)
                cout<<*studenti[i];
        }
    }
    void postaviOpisnaOcenka(char *ime,char *opisnaOcenka)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(ime,studenti[i]->getIme())==0)
            {
                StudentKursUsno* sku=dynamic_cast<StudentKursUsno*>(studenti[i]);
                if(sku)
                    *sku+=opisnaOcenka;
            }

        }
    }

};
int main(){

StudentKurs **niza;
int n,m,ocenka;
char ime[30],opisna[10];
bool daliUsno;
cin>>n;
niza=new StudentKurs*[n];
for (int i=0;i<n;i++){
   cin>>ime;
   cin>>ocenka;
   cin>>daliUsno;
   if (!daliUsno)
    niza[i]=new StudentKurs(ime,ocenka);
   else
   {
    niza[i]=new StudentKursUsno(ime,ocenka);
   }
}

KursFakultet programiranje("OOP",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;

for (int i=0;i<m;i++){
   cin>>ime>>opisna;
   try{
        programiranje.postaviOpisnaOcenka(ime,opisna);
    }
    catch(BadInputException bie)
    {
        bie.print();
        programiranje.postaviOpisnaOcenka(ime,bie.nova);
    }
}

StudentKurs::setMAX(9);

programiranje.pecatiStudenti();

}
