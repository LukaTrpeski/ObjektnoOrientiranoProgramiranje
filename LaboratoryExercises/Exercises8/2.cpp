/*
Во една игротека има 2 типа играчки: топки и коцки. Коцките и топките се опишани со параметри како што се:

боја (char *)
густина (int).
Дополнително за топките се знае и радиусот (int), додека за коцките целосните димензии (висина, ширина и длабочина – int).

За секоја од класите треба да се дефинираат методи getMasa() и getVolumen(). Масата на играчката се пресметува како производ од волуменот и густината на играчката. За PI користете ја вредноста 3.14.

Во функцијата main да се декларира променлива kupche што претставува динамички алоцирана низа кон Igrachka. Во зависност од првиот влезен параметар се внесуваат објекти од класите Topka или Kocka (1 - се внесува топка, 2 - се внесува коцка).

Од тастатура да се внесат податоци за коцката на Петра Kocka petra. Во главната функција во да се отпечатат:

Да се отпечати DA ако вкупната маса на сите играчки е поголема од масата на играчката на Петра, а NE во спротивно.
Разликата по апсолутна вредност на волуменот на играчката со максимален волумен во купчето и волуменот на коцката на Петра. Форматот е:

Razlikata e: {razlika}
Задачата да се реши со тоа што класите Kocka и Topka ќе наследуваат од класите Forma и Igrachka.

Дополнителни барања:

Во класата Igrachka да се додаде уште една чисто виртуелна функција float getPlostina(). Истата да се имплементира во класите Kocka и Topka
Во главната функција, дополнително да се испечати и: Разликата по апсолутна вредност на плоштината на играчката со минимална плоштина во купчето и плоштината на коцката на Петра во истиот формат како и второто барање погоре.
*/
#include <iostream>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <cmath>
using namespace std;

class Igracki
{
protected:
    char boja[100];
    int gustina;
public:
    Igracki(char *boja="",int gustina=0)
    {
        strcpy(this->boja,boja);
        this->gustina=gustina;
    }
    virtual float getMasa()=0;
    virtual float getVolumen()=0;
    virtual float getPlostina()=0;
};
class Topka:public Igracki
{
private:
    int radius;
public:
    Topka(char *boja="",int gustina=0,int radius=0):Igracki(boja,gustina)
    {
        this->radius=radius;
    }
    float getVolumen()
    {
        return (4.0/3.0)*3.14*radius*radius*radius;
    }
    float getMasa()
    {
        return getVolumen()*gustina*1.0;
    }
    float getPlostina()
    {
        return radius*radius*3.14*4;
    }
};
class Kocka:public Igracki
{
private:
    int visina;
    int sirina;
    int dlabocina;
public:
    Kocka(char *boja="",int gustina=0,int visina=0,int sirina=0,int dlabocina=0):Igracki(boja,gustina)
    {
        this->visina=visina;
        this->sirina=sirina;
        this->dlabocina=dlabocina;
    }
    float getVolumen()
    {
        return visina*sirina*dlabocina;
    }
    float getMasa()
    {
        return getVolumen()*gustina;
    }
    float getPlostina()
    {
        return 2*(visina*sirina+sirina*dlabocina+visina*dlabocina);
    }
};
int main(){
    int n,tip;
    char boja[20];
    int gustina,visina,sirina,dlabocina,radius;
    cin>>n;
    Igracki **kupche;
    kupche=new Igracki*[n];
    for(int i=0;i<n;i++)
    {
        cin>>tip;
        if(tip==1)
        {
            cin>>boja>>gustina>>radius;
            kupche[i]=new Topka(boja,gustina,radius);
        }
        if(tip==2)
        {
            cin>>boja>>gustina>>visina>>sirina>>dlabocina;
            kupche[i]=new Kocka(boja,gustina,visina,sirina,dlabocina);
        }
    }
    cin>>boja>>gustina>>visina>>sirina>>dlabocina;
    Kocka kockanapetra(boja,gustina,visina,sirina,dlabocina);
    float suma=0;
    float max=0;
    float min;
    for(int i=0;i<n;i++)
    {
        if(i==0)
            min=kupche[i]->getPlostina();
        suma+=kupche[i]->getVolumen();
        if(kupche[i]->getVolumen()>max)
            max=kupche[i]->getVolumen();
        if(kupche[i]->getPlostina()<min)
            min=kupche[i]->getPlostina();
    }
    if(suma>kockanapetra.getVolumen())
    {
        cout<<"DA"<<endl;
    }
    else
    {
        cout<<"NE"<<endl;
    }
    cout<<"Razlikata e: "<<abs(max-kockanapetra.getVolumen())<<endl;
    cout<<"Razlikata e: "<<abs(min-kockanapetra.getPlostina())<<endl;

	return 0;
}