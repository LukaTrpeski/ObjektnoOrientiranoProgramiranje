/*
Да се дефинира класа Agol, во која се чуваат информации за:

степени, минути и секунди (int)
Во класата да се реализираат:

конструктор по потреба
методи за поставување на вредности на атрибутите на класата (set методи)
метод за пресметување на вредноста на аголот во секунди
Да се дефинира и метод за проверување на тоа дали внесениот агол е валиден, односно дали се внесени соодветни вредности за атрибутите (во границите кои ги дозволуваат).
*/
#include <iostream>
using namespace std;

class Agol {
public:
int stepeni;
int minuti;
int sekundi;
Agol();
Agol(int st,int mi,int se)
{
    stepeni=st;
    minuti=mi;
    sekundi=se;
};
int getSekundi()
{
    return sekundi;
}
void set_minuti(int min)
{
    minuti=min;
}
void set_stepeni(int step)
{
    stepeni=step;
}
void set_sekundi(int sek)
{
    sekundi=sek;
}
int to_sekundi()
{
    return stepeni*3600+minuti*60+sekundi;
}
};
bool proveri(int deg, int min, int sec)
{
    return deg<180&&deg>=0&&min<60&&min>=0&&sec<60&&sec>=0;
}

bool changeOfSeconds(Agol a, int sec){
	return a.getSekundi()!=sec;
}

int main() {

    Agol a1(0,0,0);
    int deg, min, sec;
    cin >> deg >> min >> sec;
    if (proveri(deg, min, sec)) {

    	a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
			cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }
    else
    cout<<"Nevalidni vrednosti za agol"<<endl;

    return 0;
}
