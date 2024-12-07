/*
Потребно е да се напише класа за работа со комплексни броеви ComplexNumber. Во неа се чуваат две променливи кои можат да бидат децимални броеви. Едната го претставува реалниот дел од комплексниот број - real, а другата имагинарниот дел - imaginary. За класата да се напише:

конструктор со параметри и со предодредени вредности - нули
метод со потпис double module() кој го враќа модулот на комплексниот број. Модул се пресметува според следната формула:

sqrt(pow(real, 2) + pow(imaginary, 2))

Дополнително, потребно е да се преоптоварат следниве оператори:

оператор за доделување вредност =
оператор за печатење на стандарден излез << кој ќе го печати бројот во формат [real]+[imaginary]i. Доколку реалниот дел е 0, се печати само [imaginary]i, a доколку имагинарниот дел е 0, се печати само [real].
оператор за собирање на комплексни броеви +. Резултатот е нов комплексен број, чиј реален и имагинарен дел се збир од соодветните делови од собироците
оператор за одземање на комплексни броеви -. Резултатот е нов комплексен број, чиј реален и имагинарен дел се разлика од соодветните делови од собироците
оператор за множење на комплексни броеви *. Резултатот е нов комплексен број, чиј реален и имагинарен дел се производ од соодветните делови од множителите
оператор за делење на комплексни броеви /. Резултатот е нов комплексен број, чиј реален и имагинарен дел се количник од соодветните делови од делителите
оператор за еднаквост на комплексни броеви ==. Два комплексни броеви се еднакви ако и само ако се еднакви нивните реални и имагинарни делови
оператори за споредба на комплексни броеви > и <. Комплексните броеви се споредуваат според вредноста на нивниот реален дел. Ако тој е еднаков, тогаш се споредуваат според вредноста на имагинарниот дел
Целосна функционалност на класата носи (5 поени).

Потоа, потребно е да се напише класа за работа со равенки од комплексни броеви Equation. Во неа ќе се чуваат динамички алоцирана низа од комплексни броеви (објекти од класата ComplexNumber) и динамички алоцирана низа од знаци char - аритметички оператори за операции меѓу броевите.

Следно, треба да се преоптовари операторот за читање од стандарден влез >> кој ќе чита податоци за равенката. Прво се вчитуваат податоци за еден комплексен број (прво реален па имагинарен дел), па оператор, па повторно комплексен број, повторно оператор итн. сѐ додека не се прочита знакот =. Со вчитување на знакот = (на местото за оператор) читањето од влез завршува (2 поени).

За класата да се напишат и следниве методи:

ComplexNumber result() кој ќе го врати резултатот од равенката. При пресметувањето на резултатот сите аритметички оператори (+, -, *, /) имаат еднаква предност, т.е. не треба да внимавате да извршувате множење пред собирање или слично, туку ги извршувате операциите во оној редослед во кој сте ги добиле при вчитување од стандарден влез. (2 поени)
double sumModules() кој ќе врати збир од модулите на сите комплексни броеви во равенката. (1 поен)
Забелешка: Не го менувајте почетниот код!
*/
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
class Equation;
class ComplexNumber{
private:
    float real;
    float imaginary;
public:
    ComplexNumber(float real=0,float imaginary=0)
    {
        this->real=real;
        this->imaginary=imaginary;
    }
    double module()
    {
        return sqrt(pow(real,2)+pow(imaginary,2));
    }
    ComplexNumber& operator=(const ComplexNumber &c)
    {
        if(this!=&c){
        real=c.real;
        imaginary=c.imaginary;
        }
        return *this;
    }
    ComplexNumber operator+(const ComplexNumber &c)
    {
        return ComplexNumber(real+c.real,imaginary+c.imaginary);
    }
    ComplexNumber operator-(const ComplexNumber &c)
    {
        return ComplexNumber(real-c.real,imaginary-c.imaginary);
    }
    ComplexNumber operator*(const ComplexNumber &c)
    {
        return ComplexNumber(real*c.real,imaginary*c.imaginary);
    }
    ComplexNumber operator/(const ComplexNumber &c)
    {
        return ComplexNumber(real/c.real,imaginary/c.imaginary);
    }
    bool operator==(const ComplexNumber &c)
    {
        if(real==c.real&&imaginary==c.imaginary)
            return true;
        else
            return false;
    }
    friend ostream& operator<<(ostream &out,const ComplexNumber &c)
    {
        if(c.real==0)
            out<<c.imaginary<<"i"<<endl;
        else if(c.imaginary==0)
            out<<c.real<<endl;
        else
        {
            if(c.imaginary>0)
            {
                out<<c.real<<"+"<<c.imaginary<<"i"<<endl;
            }
            else
            {
                out<<c.real<<c.imaginary<<"i"<<endl;
            }
        }
        return out;
    }
    friend bool operator<(const ComplexNumber &c,const ComplexNumber &d);
    friend bool operator>(const ComplexNumber &c,const ComplexNumber &d);
    friend class Equation;
    friend istream& operator>>(istream &in,Equation &e);
};
    bool operator>(const ComplexNumber &c,const ComplexNumber &d)
    {
        if(c.real==d.real)
        {
            if(c.imaginary>d.imaginary)
                return true;
            else
                return false;
        }
        else if(c.real>d.real)
            return true;
        else
            return false;
    }
    bool operator<(const ComplexNumber &c,const ComplexNumber &d)
    {
        if(c.real==d.real)
        {
            if(c.imaginary<d.imaginary)
                return true;
            else
                return false;
        }
        else if(c.real<d.real)
            return true;
        else
            return false;

    }
class Equation{
private:
    ComplexNumber *niza;
    char *operacija;
public:
    Equation(){
    niza=NULL;
    operacija=NULL;
    }
    Equation(ComplexNumber *niza,char *operacija)
    {
        this->niza=new ComplexNumber[strlen(operacija)+1];
        this->operacija = new char[strlen(operacija)+1];
        strcpy(this->operacija,operacija);
        for(int i=0;i<strlen(operacija);i++)
        {
            this->niza[i]=niza[i];
        }
    }
    Equation(const Equation &c)
    {
        operacija=new char[strlen(c.operacija)+1];
        strcpy(operacija,c.operacija);
        niza=new ComplexNumber[strlen(operacija)];
        for(int i=0;i<strlen(operacija);i++)
        {
            niza[i]=c.niza[i];
        }
    }
    Equation &operator=(const Equation &c)
    {
        if(this!=&c){
        delete [] operacija;
        operacija=new char[strlen(c.operacija)+1];
        strcpy(operacija,c.operacija);
        delete [] niza;
        niza=new ComplexNumber[strlen(operacija)];
        for(int i=0;i<strlen(operacija);i++)
        {
            niza[i]=c.niza[i];
        }
        }
        return *this;
    }
    friend istream& operator>>(istream &in,Equation &e)
    {
        int i=0;
        char q;
        ComplexNumber *temp=new ComplexNumber[100];
        char *tmp=new char[100];
        while(1)
        {
            in>>temp[i].real;
            in>>temp[i].imaginary;
            in>>tmp[i];
            i++;
            q=tmp[i-1];
            if(q=='=')
            {
                break;
            }
        }
        e.niza=temp;
        e.operacija=new char[strlen(tmp)+1];
        strcpy(e.operacija,tmp);

        return in;
    }
    ComplexNumber result()
    {
        ComplexNumber rez=niza[0];
        for(int i=0;i<strlen(operacija);i++)
        {
        if(operacija[i]=='+')
        {
            rez=rez+niza[i+1];
        }
            if(operacija[i]=='-')
        {
            rez=rez-niza[i+1];
        }
            if(operacija[i]=='*')
        {
            rez=rez*niza[i+1];
        }
            if(operacija[i]=='/')
        {
            rez=rez/niza[i+1];
        }
        if(operacija[i]=='=')
        {
            rez=rez;
        }
    }
    return rez;
    }
    double sumModules()
    {
        double suma=0;
        for(int i=0;i<strlen(operacija);i++)
        {
            suma+=niza[i].module();
        }
        return suma;
    }

    ~Equation(){delete [] niza;
    delete [] operacija;}
};
int main() {
	int testCase;
	double real, imaginary;
	ComplexNumber first, second, result;

	cin >> testCase;

	if (testCase <= 8) {
		cin >> real;
		cin >> imaginary;
		first = ComplexNumber(real, imaginary);
		cin >> real;
		cin >> imaginary;
		second = ComplexNumber(real, imaginary);
	}

	if (testCase == 1) {
		cout << "===== OPERATOR + =====" << endl;
		result = first + second;
		cout << result;
	}
	else if (testCase == 2) {
		cout << "===== OPERATOR - =====" << endl;
		result = first - second;
		cout << result;
	}
	else if (testCase == 3) {
		cout << "===== OPERATOR * =====" << endl;
		result = first * second;
		cout << result;
	}
	else if (testCase == 4) {
		cout << "===== OPERATOR / =====" << endl;
		result = first / second;
		cout << result;
	}
	else if (testCase == 5) {
		cout << "===== OPERATOR == =====" << endl;
		cout << first;
		cout << second;
		if (first == second)
			cout << "EQUAL" << endl;
		else
			cout << "NOT EQUAL" << endl;
	}
	else if (testCase == 6) {
		cout << "===== OPERATOR > =====" << endl;
		cout << first;
		cout << second;
		if (first > second)
			cout << "FIRST GREATER THAN SECOND" << endl;
		else
			cout << "FIRST LESSER THAN SECOND" << endl;
	}
	else if (testCase == 7) {
		cout << "===== OPERATOR < =====" << endl;
		cout << first;
		cout << second;
		if (first < second)
			cout << "FIRST LESSER THAN SECOND" << endl;
		else
			cout << "FIRST GREATER THAN SECOND" << endl;
	}
	else if (testCase == 8) {
		cout << "===== MODULE =====" << endl;
		double module = first.module();
		cout << first;
		cout << "Module: " << module << endl;
		cout << second;
		module = second.module();
		cout << "Module: " << module << endl;
	}
	else if (testCase == 9) {
		cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
		Equation equation;
		cin >> equation;
		cout << equation.sumModules();
	}
	else if (testCase == 10) {
		cout << "===== EQUATION RESULT =====" << endl;
		Equation equation;
		cin >> equation;
		result = equation.result();
		cout << result;
	}
	return 0;
}
