/*
Со цел да се подобри системот Мој Термин, со воведување функционалност за пресметување плати за лекарите за еден месец, од Министерството за здравство на Република Македонија, ги добивате следните задачи:

Да се креира класа Lekar во која што ќе се чуваат:

факсимил на докторот (цел број)
име (низа од максимум 10 знаци)
презиме (низа од максимум 10 знаци)
почетна плата (децимален број)
За класата да се имплементираат методите:

void pecati(): Печати информации за лекарот во формат Факсимил: име презиме

double plata(): ја враќа платата на лекарот

Да се креира класа MaticenLekar која што наследува од Lekar и во неа се чуваат дополнителни информации за:

број на пациенти со којшто лекарот соработувал во текот на месецот (цел број)
котизации наплатени од пациентите во текот на месецот (динамички алоцирана низа од децимални броеви)
За класата да се препокријат методитe:

void pecati() : ги печати основните информации за лекарот, а во нов ред го печати и просекот од наплатените котизации

double plata(): ја враќа платата на матичниот лекар

Платата на матичниот лекар се пресметува со зголемување на основната плата за 30% од просекот од наплатените котизации за месецот
*/
#include <iostream>
#include <string.h>
using namespace std;

class Lekar{
protected:
    int faksimil;
    char ime[15];
    char prezime[15];
    double pl;
public:
    Lekar(int faksimil=0,char *ime="",char *prezime="",double pl=0.0)
    {
        this->faksimil=faksimil;
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->pl=pl;
    }
    Lekar(const Lekar &lek)
    {
        this->faksimil=lek.faksimil;
        strcpy(this->ime,lek.ime);
        strcpy(this->prezime,lek.prezime);
        this->pl=lek.pl;
    }
    void pecati()
    {
        cout<<faksimil<<": "<<ime<<" "<<prezime<<endl;
    }
    double plata()
    {
        return pl;
    }
};
class MaticenLekar:public Lekar{
private:
    int broj;
    double *kotizacii;
public:
    MaticenLekar(){
    this->broj=0;
    this->kotizacii=new double[broj];
    }
    MaticenLekar(Lekar &lek,int broj,double *kotizacii):Lekar(lek)
    {
        this->broj=broj;
        this->kotizacii=new double[broj+1];
        for(int i=0;i<broj;i++)
        {
            this->kotizacii[i]=kotizacii[i];
        }
    }
    MaticenLekar(const MaticenLekar &mlek){
        this->broj=mlek.broj;
        this->kotizacii=new double[mlek.broj+1];
        for(int i=0;i<mlek.broj;i++)
        {
            this->kotizacii[i]=mlek.kotizacii[i];
        }
    }
    void pecati()
    {
        int sum=0;
        Lekar::pecati();
        for(int i=0;i<broj;i++)
        {
            sum+=kotizacii[i];
        }
        cout<<"Prosek na kotizacii: "<<sum/broj<<endl;
    }
    double plata()
    {
        double sum=0;
        for(int i=0;i<broj;i++)
        {
            sum+=kotizacii[i];
        }
        return pl+sum/broj*0.3;
    }
};
int main() {
	int n;
	cin>>n;
	int pacienti;
	double kotizacii[100];
	int faksimil;
	char ime [20];
	char prezime [20];
	double osnovnaPlata;

	Lekar * lekari = new Lekar [n];
	MaticenLekar * maticni = new MaticenLekar [n];

	for (int i=0;i<n;i++){
		cin >> faksimil >> ime >> prezime >> osnovnaPlata;
		lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
	}

	for (int i=0;i<n;i++){
		cin >> pacienti;
		for (int j=0;j<pacienti;j++){
			cin >> kotizacii[j];
		}
		maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
	}

	int testCase;
	cin>>testCase;

	if (testCase==1){
		cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
		for (int i=0;i<n;i++){
			lekari[i].pecati();
			cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
		}
	}
	else {
		cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
		for (int i=0;i<n;i++){
			maticni[i].pecati();
			cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
		}
	}

	delete [] lekari;
	delete [] maticni;

	return 0;
}
