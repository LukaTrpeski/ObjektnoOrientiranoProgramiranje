/*
Да се креира генеричка класа Array за работа со низи. Класата треба во себе да ги вклучи:

покажувач кон елементи од соодветниот тип
број на елементи во рамките на низата
Елементите во рамките на објектот треба динамички да се алоцираат. Класата треба да ги поддржува следниве методи:

void Erase() - ги брише сите елементи од низата
Т operator[](int i) - за пристап до соодветниот елемент во низата (вклучувајќи и проверка дали индексот е во границите)
int GetLength() - го враќа бројот на елементите во низата
Да се преоптовари operator<< (ostream) за работа со класата (да се претпостави дека елементите од низата го имаат преоптоварено операторот <<).

Надвор од класата да се напишат следниве функции:

void BubbleSort(Array<T> t&)  - ги сорира елементите користејќи го BubbleSort алгоритмот (да се претпостави дека операторот > e преоптоварен за елементите од класата).

Т Sum(Array<T> &) - ги сумира елементите (да се претпостави дека операторот += e преоптоварен за елементите од класата).

Т Average(Array<T>&) - користејќи ја функцијата за сума пресметува просечна вредност на елементите ( операторот / е преоптоварен за елементите)

bool Equal (Array<T>&, Array<M>&) - проверува дали низите се еднакви (се претпоставува дека операторот == е преоптоварен за соодветните класи)

bool Equal (Array <T>&, Array<double>& ) - која ќе изврши пацијална специјализација и ќе смета дека:
 - два елементи се исти ако и само ако се разликуваат за помалку од 0.1
 - разликата од просечната вредност на низите мора да е помала од 0.5.
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

template <typename T>
class Array
{
public:
    T *pointer;
    int n;
    Array<T>(int n)
    {
        pointer=new T[n];
        this->n=n;
    }
    void Erase()
    {
        for(int i=0;i<n;i++)
            delete pointer[i];
        delete [] pointer;
    }
    T &operator[](int i)
    {
        if(i>=0&&i<n)
        return pointer[i];
    }
    int GetLenght()
    {
        return n;
    }
    friend ostream &operator<<(ostream &out,Array<T>&a)
    {
        for(int i=0;i<a.n;i++)
        {
            if(i==a.n-1)
            out<<"Array["<<i<<"] = "<<a[i]<<endl;
            else
            out<<"Array["<<i<<"] = "<<a[i]<<", ";
        }
        return out;
    }
};
template <typename T>
void BubbleSort(Array<T> &t)
{
    for(int i=0;i<t.n;i++)
    {
        for(int j=0;j<t.n-i-1;j++)
        {
            if(t[j]>t[j+1]){
                T temp=t[j];
                t[j]=t[j+1];
                t[j+1]=temp;
            }
        }
    }
}
template <typename T>
T Sum(Array<T> &t)
{
    T suma=0;
    for(int i=0;i<t.n;i++)
    {
        suma+=t[i];
    }
    return suma;
}
template <typename T>
T Average(Array<T> &t)
{
    return Sum(t)/t.n;
}
template <typename T,typename M>
bool Equal (Array<T> &t, Array<M> &m)
{
    bool eq=false;
    if(t.n!=m.n)
        return false;
    for(int i=0;i<t.n;i++)
    {
        if(t[i]==m[i])
            eq=true;
        else{
            eq=false;
            break;
        }
    }
    return eq;
}
template <typename T>
bool Equal (Array <T>&t, Array<double>&m )
{
    bool eq=false;
    if(t.n!=m.n)
        return false;
    for(int i=0;i<t.n;i++)
    {
        if(abs(t[i]-m[i])<=0.1)
            eq=true;
        else{
            eq=false;
            break;
        }
        if(abs(Average(t)-Average(m))<=0.5)
            eq=true;
        else{
            eq=false;
            break;
        }
    }
    return eq;
}

int main()
{

  int n;
  double r;

  cin>>r;
  cin>>n;
  Array<int> anArray(n);
  Array<double> adArray(n);
  Array<int> intArray2(n);

  for (int nCount = 0; nCount < n; nCount++)
  {
      cin>>anArray[nCount];
      adArray[nCount] = anArray[nCount] + r;
  }

  BubbleSort(anArray);

  intArray2 = anArray;

  cout<<"The arrays: "<<endl;
  cout<<anArray;
  cout<<"and "<<endl;
  cout<<intArray2;
  cout<<((Equal(anArray,intArray2))?" ARE":" ARE NOT")<<" same!"<<endl;
  cout<<"The Average of the array adArray is: "<<Average(adArray)<<endl;

  cout<<"The arrays: "<<endl;
  cout<<anArray;
  cout<<"and "<<endl;
  cout<<adArray;
  cout<<((Equal(anArray,adArray))?" ARE":" ARE NOT")<<" same!";


return 0;
}
