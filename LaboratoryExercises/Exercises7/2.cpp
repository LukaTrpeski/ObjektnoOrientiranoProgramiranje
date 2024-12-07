/*
Да се дефинира апстрктна класа Number со следните чисто виртуелни методи:

double doubleValue() -ја враќа децималната вредност на даден број
int intValue()- ја враќа целобројната вредност на даден број
void print() - печати информации за бројот. (1 поен)
Од оваа класа да се изведат две класи:

Integer (во која што се чува еден број од тип int)
Double (во која што се чува еден број од тип double) (1 поен).
За двете изведени класи да се имплементираaт соодветен конструктори, како и да се препокријат методите од основната класа. (1 поени)

Да се преоптовари операторот == којшто ќе споредува два броеви според нивната вредност (објекти од класа Number) (1 поен)

Дополнително да се дефинира класа Numbers во која што ќе се чуваат:

динамички алоцирана низа од покажувачи кон објекти од класата Number
број на елементи во низата од покажувачи
За класата да се имплементира соодветен конструктор (default) , како и: (1 поени)

операторот += за додавање на броеви во низата од броеви (1 поен)
Бројот се додава ако и само ако сите броеви што се веќе додадени во низата се различни од него
функција void statistics() која што печати информации за броевите во низата: (2 поени)
Count of numbers: [број на броеви во низата

Sum of all numbers: [сума на сите броеви во низата]

Count of integer numbers: [број на цели броеви (Integer)]

Sum of integer numbers: [сума на сите цели броеви (Integer)]

Count of double numbers: [број на децимални броеви (Double)]

Sum of double numbers: [сума на сите децимални броеви (Double)]

функција void integersLessThan (Integer n) која што ги печати сите цели броеви помали од бројот n (1 поен)
функција void doublesBiggerThan (Double n) која што ги печати сите децимални броеви поголеми од бројот n (1 поен)
*/
#include <iostream>
#include <string.h>
using namespace std;

class Number{
public:
    virtual double doubleValue()=0;
    virtual int intValue()=0;
    virtual void print()=0;
};
class Integer:public Number
{
private:
    int broj;
public:
    Integer(int broj=0)
    {
        this->broj=broj;
    }
    double doubleValue()
    {
        return double(broj);
    }
    int intValue()
    {
        return broj;
    }
    void print()
    {
        cout<<"Integer: "<<broj<<endl;
    }
};
class Double:public Number
{
private:
    double br;
public:
    Double(double br=0)
    {
        this->br=br;
    }
    double doubleValue()
    {
        return br;
    }
    int intValue()
    {
        return int(br);
    }
    void print()
    {
        cout<<"Double: "<<br<<endl;
    }
};
bool operator==(Number *n1,Number &n2)
{
    return n1->doubleValue()==n2.doubleValue();
}
class Numbers
{
private:
    Number **niza;
    int elementi;
public:
    Numbers()
    {
        this->elementi=0;
        this->niza=new Number*[elementi];
    }
    Numbers(const Numbers &n)
    {
        this->elementi=n.elementi;
        for(int i=0;i<elementi;i++)
        {
            niza[i]=n.niza[i];
        }
    }
    Numbers &operator=(const Numbers &n)
    {
        if(this!=&n)
        {
            delete [] niza;
            this->elementi=elementi;
            for(int i=0;i<elementi;i++)
            {
                niza[i]=n.niza[i];
            }
        }
        return *this;
    }
    Numbers &operator+=(Number *n)
    {
        int flag=0;
        Number **temp=new Number*[elementi+1];
        for(int i=0;i<elementi;i++)
        {
            if(niza[i]==*n)
                flag=1;
            temp[i]=niza[i];
        }
        if(flag==0){
        temp[elementi++]=n;
        delete [] niza;
        niza=temp;
        return *this;
        }
    }
    void statistics()
    {
        int sumint=0;
        double sum=0;
        double sumdouble=0;
        int countint=0;
        int countdouble=0;
        for(int i=0;i<elementi;i++)
        {
            Integer *in = dynamic_cast<Integer*>(niza[i]);
            if(in){
                sumint+=in->intValue();
                sum+=in->intValue();
                countint++;
            }
            Double *d = dynamic_cast<Double *>(niza[i]);
            if(d){
                sumdouble+=d->doubleValue();
                sum+=d->doubleValue();
                countdouble++;
            }
        }
        cout<<"Count of numbers: "<<elementi<<endl;
        cout<<"Sum of all numbers: "<<sum<<endl;
        cout<<"Count of integer numbers: "<<countint<<endl;
        cout<<"Sum of integer numbers: "<<sumint<<endl;
        cout<<"Count of double numbers: "<<countdouble<<endl;
        cout<<"Sum of double numbers: "<<sumdouble<<endl;
    }
    void integersLessThan (Integer n)
    {
    int flag=0;
        for(int i=0;i<elementi;i++)
        {
            Integer *in = dynamic_cast<Integer*>(niza[i]);
            if(in)
            {
                if(in->intValue()<n.intValue())
                {
                    in->print();
                    flag=1;
                }
            }
        }
        if(flag==0)
        cout<<"None"<<endl;
    }
    void doublesBiggerThan (Double n)
    {
    int flag=0;
        for(int i=0;i<elementi;i++)
        {
            Double *d = dynamic_cast<Double*>(niza[i]);
            if(d)
            {
                if(d->doubleValue()>n.doubleValue())
                {
                    d->print();
                    flag=1;
                }
            }
        }
        if(flag==0)
        cout<<"None"<<endl;
    }
};

int main() {
	
	int n;
	cin>>n;
	Numbers numbers;
	for (int i=0;i<n;i++){
		int type;
		double number;
		cin>>type>>number;
		if (type==0){//Integer object
			Integer * integer = new Integer((int) number);
			numbers+=integer;
		}
		else {
			Double * doublee = new Double(number);
			numbers+=doublee;
		}
	}
	
	int lessThan;
	double biggerThan;
	
	cin>>lessThan;
	cin>>biggerThan;		
	
	cout<<"STATISTICS FOR THE NUMBERS\n";
	numbers.statistics();
	cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
	numbers.integersLessThan(Integer(lessThan));
	cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
	numbers.doublesBiggerThan(Double(biggerThan));
	
	return 0;
}