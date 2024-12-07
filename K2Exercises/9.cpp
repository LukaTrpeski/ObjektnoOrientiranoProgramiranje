/*
Да се имплементира класа Trud во која се чуваат информации за: (5 поени)

вид на труд (еден знак и тоа C за конференциски труд, J за труд во списание)
година на издавање (цел број).
Да се имплементира класа Student во која се чува: (5 поени)

името на студентот (низа од најмногу 30 карактери)
индекс (цел број)
година на упис (цел број)
листа на оцени од положени предмети (низа од цели броеви)
број на положени предмети (цел број)
За оваа класа да се имплементираат следните методи:

функција rang() што пресметува просек од положените испити на студентот (5 поени)
оператор << за печатење на студентот во формат: (5 поени)

Индекс Име Година на упис ранг

Да се имплементира класа PhDStudent во која покрај основните информации за студентот дополнително се чува: (5 поени)

листа од објавени трудови (динамички резервирана низа од објекти од класата Trud)
бројот на трудови (цел број)
Во оваа класа да се препокрие соодветно функцијата rang() така што на просекот од положените испити ќе се додаде и збирот од поените од објавените трудови на PhD студентот. Во зависност од видот на трудот, секој универзитет има посебен начин на бодување на трудовите. Начинот на бодување е ист за сите PhD студенти. Иницијално да се смета дека конференциски труд се бодува со 1 поен, а труд во списание со 3 поени. Универзитетот има можност да ги менува вредностите на бодовите. (5 поени + 5 поени)

За оваа класа да се обезбеди:

оператор += за додавање нов објект од класата Trud во листата (5 поени). Ако се направи обид да се внесе труд што е издаден порано од годината на упис на студентот да се фрли исклучок (објект од класата Exception). Справувањето со исклучокот треба да се реализира во главната функција main каде што е потребно, но и во конструктор ако е потребно. Ако бил генериран исклучок треба да се отпечати соодветна порака за грешка "Ne moze da se vnese dadeniot trud", а новиот труд нема да се внесе во листата на трудови од студентот. (10 поени)
Напомена: Сите променливи на класите се чуваат како приватни.

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
*/
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <cstring>
using namespace std;

class Exception
{
public:
    Exception(){}
    void message()
    {
        cout<< "Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud
{
protected:
    char vid;
    int godinaizdavanje;
public:
    Trud(char vid='a',int godinaizdavanje=0)
    {
        this->vid=vid;
        this->godinaizdavanje=godinaizdavanje;
    }
    void setVid(char v)
    {
        vid=v;
    }
    char getVid()
    {
        return tolower(vid);
    }
    void setGodina(int god)
    {
        godinaizdavanje=god;
    }
    int getGodina()
    {
        return godinaizdavanje;
    }
    friend istream &operator>>(istream &in,Trud &t)
    {
        in>>t.vid;
        in>>t.godinaizdavanje;
        return in;
    }
};
class Student
{
protected:
    char imestudent[30];
    int indeks;
    int godinaupis;
    int ocenki[100];
    int brojpolozeni;
public:
    Student(const char *imestudent="", int indeks=0,int godinaupis=2000,int *ocenki=NULL,int brojpolozeni=0)
    {
        strcpy(this->imestudent,imestudent);
        this->indeks=indeks;
        this->godinaupis=godinaupis;
        this->brojpolozeni=brojpolozeni;
        for(int i=0;i<brojpolozeni;i++)
            this->ocenki[i]=ocenki[i];
    }
    virtual float rang()
    {
        float prosek=0;
        for(int i=0;i<brojpolozeni;i++)
        {
            prosek+=ocenki[i];
        }
        return prosek/brojpolozeni;
    }
    friend ostream &operator<<(ostream &out, Student &s)
    {
        out<<s.indeks<<" "<<s.imestudent<<" "<<s.godinaupis<<" "<<s.rang()<<endl;
        return out;
    }
    int getIndeks()
    {
        return indeks;
    }
};
class PhDStudent:public Student
{
private:
    Trud *trudovi;
    int n;
    static int coefC;
    static int coefJ;
public:
    PhDStudent(const char *imestudent="", int indeks=0,int godinaupis=2000,int *ocenki=NULL,int brojpolozeni=0,Trud *trudovi=NULL,int n=0):Student(imestudent,indeks,godinaupis,ocenki,brojpolozeni)
    {
        this->n=n;
        this->trudovi=new Trud[n];
        for(int i=0;i<n;i++)
        {
            try{
            if(trudovi[i].getGodina()<godinaupis){
                throw Exception();
                n--;
                break;}
                else
                this->trudovi[i]=trudovi[i];

            }
            catch(Exception &e)
            {
                e.message();

            }
        }
    }
    PhDStudent(const PhDStudent &phs)
    {
        this->n=phs.n;
        this->trudovi=new Trud[n];
        for(int i=0;i<n;i++)
        {
            this->trudovi[i]=phs.trudovi[i];
        }
    }
    PhDStudent &operator=(const PhDStudent &phs)
    {
        if(this!=&phs){
                delete [] trudovi;
        this->n=phs.n;
        this->trudovi=new Trud[n];
        for(int i=0;i<n;i++)
        {
            this->trudovi[i]=phs.trudovi[i];
        }
        }
        return *this;
    }
    ~PhDStudent(){delete [] trudovi;}
    float rang()
    {
        float rangs=0;
        for(int i=0;i<n;i++)
        {
            if(trudovi[i].getVid()=='c'||trudovi[i].getVid()=='C')
            {

                rangs+=coefC;
            }
            if(trudovi[i].getVid()=='j'||trudovi[i].getVid()=='J')
            {

                rangs+=coefJ;
            }
        }
        return Student::rang()+rangs;
    }
    PhDStudent &operator+=(Trud &t)
    {
        if(t.getGodina()<godinaupis)
            throw Exception();
        else
        {
            Trud *temp=new Trud[n+1];
            for(int i=0;i<n;i++)
            {
                temp[i]=trudovi[i];
            }
            temp[n++]=t;
            delete [] trudovi;
            trudovi=temp;
            return *this;
        }
    }
    static void setKonf(int k)
    {
        coefC=k;
    }
    static void setSpis(int p)
    {
        coefJ=p;
    }

};
int PhDStudent::coefC=1;
int PhDStudent::coefJ=3;

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;

				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
		int l;
		PhDStudent *p;
		int f=0;
		for(int i=0;i<m;i++){
                if(niza[i]->getIndeks()==indeks)
        {   p=dynamic_cast<PhDStudent*>(niza[i]);
            if(p!=0){
                f=1;
                l=i;
            }
		}}
		if(f==1){
		try{
		    *p+=t;}
		catch(Exception e){
		e.message();}
        niza[l]=p;}
        else cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
        int l;
		PhDStudent *p;
		int f=0;
		for(int i=0;i<m;i++){
                if(niza[i]->getIndeks()==indeks)
        {   p=dynamic_cast<PhDStudent*>(niza[i]);
            if(p!=0){
                f=1;
                l=i;
            }
		}}
		if(f==1){
		try{
		    *p+=t;}
		catch(Exception e){
		e.message();}
        niza[l]=p;}
        else cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);

		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		int l;
		PhDStudent *p;
		int f=0;
		for(int i=0;i<m;i++){
                if(niza[i]->getIndeks()==indeks)
        {   p=dynamic_cast<PhDStudent*>(niza[i]);
            if(p!=0){
                f=1;
                l=i;
            }
		}}
		if(f==1){
		try{
		    *p+=t;}
		catch(Exception e){
		e.message();}
        niza[l]=p;}
        else cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;
		PhDStudent *p1=dynamic_cast<PhDStudent*>(niza[0]);
        p1->setKonf(conf);
        p1->setSpis(journal);


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}
