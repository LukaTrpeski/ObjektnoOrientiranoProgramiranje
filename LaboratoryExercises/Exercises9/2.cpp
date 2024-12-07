/*
Да се креира класа PositiveIntegers во која што ќе се чуваат информации за:

низа од позитивни броеви (>0) (динамички алоцирана низа од цели броеви)
број на елементи во низата
максимален капацитет на низата
За класата да се имплементираат:

потребниот конструктор (погледнете во главната функција како се креира објект од оваа класа)
метод void increaseCapacity(int c) којшто го зголемува максималниот капацитет на низата за бројот с
оператор за додавање на нов број во низата од позитивни броеви +=
број се додава ако и само ако
оператор за множење * за множење на низата со друг цел број
Пример, низата има објекти (1 2 3 4 5) и истата се множи со 2, резултатот ќе биде (1 2 3 4 5)*2 = (2 3 6 8 10)
оператор за делење \ за делење на низата до друг цел број
потребно е секој елемент од низата да биде делив со тој број, како и делителот не смее да биде нула.
оператор [] за пристап до елемент од низата
Потребно е да се дефинираат класи за исклучоци и секој од нив да има метод void message() којшто ќе принта соодветна порака кога исклучокот ќе биде фатен. Можните исклучоци се следните:

ArithmeticException (се фрла ако се проба да се дели со нула)
принта порака Division by zero is not allowed
NumbersNotDivisibleException (се фрла ако се проба да се дели низата со некој број, а барем еден елемент од низата не е делив со тој број)
принта порака Division by number [делителот] is not supported
ArrayFullException (се фрла ако се проба да се додади елемент во низа која и е исполнет максималниот капацитет)
принта порака The array is full. Increase the capacity
IndexOutOfBoundsException (се фрла доколку се проба да се пристапи до елемент од низата со несоодветен индекс)
принта порака Index [индексот] is out of bounds
NumberIsNotPositiveException (се фрла доколку се проба да се внесе во низата број што не е позитивен или е нула)
принта порака Number [бројот] is not positive integer.
*/
#include <iostream>
#include <cstring>

using namespace std;

class ArithmeticException
{
private:
    char text[40];
public:
    ArithmeticException(char *text)
    {
        strcpy(this->text,text);
    }
    void message()
    {
        cout<<text<<endl;
    }
};
class ArrayFullException
{
private:
    char text[40];
public:
    ArrayFullException (char *text)
    {
        strcpy(this->text,text);
    }
    void message()
    {
        cout<<text<<endl;
    }
};
class NumbersNotDivisibleException
{
private:
    int n;
public:
    NumbersNotDivisibleException (int n)
    {
        this->n=n;
    }
    void message()
    {
        cout<<"Division by "<<n<<" is not supported"<<endl;
    }
};
class IndexOutOfBoundsException
{
private:
    int index;
public:
    IndexOutOfBoundsException(int index)
    {
        this->index=index;
    }
    void message()
    {
        cout<<"Index "<<index<<" is out of bounds"<<endl;
    }
};
class NumberIsNotPositiveException
{
private:
    int n;
public:
    NumberIsNotPositiveException(int n)
    {
        this->n=n;
    }
    void message()
    {
        cout<<"Number "<<n<<" is not positive integer"<<endl;
    }
};

class PositiveIntegers
{
protected:
    int *niza;
    int n;
    int maxKapacitet;
public:
    PositiveIntegers(int maxKapacitet=0)
    {
        this->maxKapacitet=maxKapacitet;
        n=0;
        niza=new int[0];
    }
    PositiveIntegers(const PositiveIntegers &pi)
    {
        this->maxKapacitet=pi.maxKapacitet;
        this->n=pi.n;
        this->niza=new int[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=pi.niza[i];
        }
    }
    PositiveIntegers &operator=(const PositiveIntegers &pi)
    {
        if(this!=&pi)
        {

            this->maxKapacitet=pi.maxKapacitet;
            this->n=pi.n;
            this->niza=new int[n];
            for(int i=0;i<n;i++)
            {
                this->niza[i]=pi.niza[i];
            }
        }
        return *this;
    }
    void increaseCapacity(int c)
    {
        maxKapacitet+=c;
    }
    void print()
    {
        cout<<"Size: "<<n<<" Capacity: "<<maxKapacitet<<" Numbers: ";
        for(int i=0;i<n;i++)
        {
            if(i!=n-1)
            cout<<niza[i]<<" ";
            if(i==n-1)
            cout<<niza[i]<<endl;
        }

    }
    PositiveIntegers &operator+=(int number)
    { 
        if(n==maxKapacitet)
        {
            throw ArrayFullException("The array is full. Increase the capacity");
        }
        if(number<=0)
        {
            throw NumberIsNotPositiveException(number);
        }
       
        int *temp=new int[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=niza[i];
        }
        temp[n++]=number;
        delete [] niza;
        niza=temp;
        return *this;
    }
    PositiveIntegers operator*(int number)
    {
        PositiveIntegers temp(*this);
        for(int i=0;i<n;i++)
        {
            temp.niza[i]=temp.niza[i]*number;
        }
        return temp;
    }
    PositiveIntegers operator/(int number)
    {
        if(number==0)
        {
            throw ArithmeticException("Division by zero is not allowed");
        }
        int flag=0;
        for(int i=0;i<n;i++)
        {
            if(niza[i]%number!=0)
                flag=1;
        }
        if(flag)
        {
            throw NumbersNotDivisibleException(number);
        }
        PositiveIntegers temp(*this);
        for(int i=0;i<n;i++)
        {
            temp.niza[i]=temp.niza[i]/number;
        }
        return temp;
    }
    int operator[](int index)
    {
        if(index<0||index>=n)
            throw IndexOutOfBoundsException(index);
        return niza[index];
    }
};

int main() {

	int n,capacity;
	cin >> n >> capacity;
	PositiveIntegers pi (capacity);
	for (int i=0;i<n;i++){
		int number;
		cin>>number;
		try{pi+=number;}
		catch(ArrayFullException &afe)
        {
        	afe.message();
        }
        catch(NumberIsNotPositiveException &ninpe)
        {
        	ninpe.message();
        }
	}
	cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	int incCapacity;
	cin>>incCapacity;
	pi.increaseCapacity(incCapacity);
	cout<<"===INCREASING CAPACITY==="<<endl;
	pi.print();

	int n1;
	cin>>n1;
	for (int i=0;i<n1;i++){
		int number;
		cin>>number;
		try{pi+=number;}
		catch(ArrayFullException &afe)
        {
        	afe.message();
        }
        catch(NumberIsNotPositiveException &ninpe)
        {
        	ninpe.message();
        }
	}
	cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
	PositiveIntegers pi1;

	cout<<"===TESTING DIVISION==="<<endl;

	try{
        pi1 = pi/0;
        pi1.print();
	}
	catch(ArithmeticException &ae)
	{
    	ae.message();
    }
    catch(NumbersNotDivisibleException &nnde)
    {
    	nnde.message();
    }
    try{
	pi1 = pi/1;
	pi1.print();
    }
    catch(ArithmeticException &ae)
	{
    	ae.message();
    }
    catch(NumbersNotDivisibleException &nnde)
    {
    	nnde.message();
    }
	try{
	    pi1 = pi/2;
        pi1.print();
	}
	catch(ArithmeticException &ae)
	{
    	ae.message();
    }
    catch(NumbersNotDivisibleException &nnde)
    {
    	nnde.message();
    }


	cout<<"===TESTING MULTIPLICATION==="<<endl;
	pi1 = pi*3;
	pi1.print();


	cout<<"===TESTING [] ==="<<endl;
	try
	{
	    cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
	}
	catch(IndexOutOfBoundsException &ioobe)
	{
        ioobe.message();
    }
    try
	{
	    cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
	}
	catch(IndexOutOfBoundsException &ioobe)
	{
        ioobe.message();
    }
    try
	{
	    cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
	}
	catch(IndexOutOfBoundsException &ioobe)
	{
        ioobe.message();
    }
    try
	{
	    cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
	}
	catch(IndexOutOfBoundsException &ioobe)
	{
        ioobe.message();
    }

	return 0;
}
