/*
Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)
*/
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <string.h>
using namespace std;
#define MAX 50
enum typeC
{
    standard,loyal,vip
};
class UserExistsException
{
public:
    UserExistsException()
    {
    }
    void print()
    {
        cout<<"The user already exists in the list!"<<endl;
    }
};
class Customer
{
protected:
    char ime[50];
    char eadresa[50];
    typeC tip;
    static int osnoven;
    static const int dopolnitelen;
    int brojkupeni;
public:
    Customer(const char *ime="",const char *eadresa="",typeC tip=(typeC)0,int brojkupeni=0)
    {
        strcpy(this->ime,ime);
        strcpy(this->eadresa,eadresa);
        this->tip=tip;
        this->brojkupeni=brojkupeni;
    }
    int getBroj()
    {
        return brojkupeni;
    }
    static void setDiscount1(int osn)
    {
        osnoven=osn;
    }
    const char *getTip()
    {
        if(tip==(typeC)0)
        {
            return "standard";
        }
        else if(tip==(typeC)1)
        {
            return "loyal";
        }
        else if(tip==(typeC)2)
        {
            return "vip";
        }
    }
    char *getAdresa()
    {
        return eadresa;
    }
    int getPopust()
    {
        if(tip==(typeC)0)
        {
            return 0;
        }
        else if(tip==(typeC)1)
        {
            return osnoven;
        }
        else if(tip==(typeC)2)
        {
            return osnoven+dopolnitelen;
        }
    }
    void setTip(typeC t)
    {
        tip=t;
    }
    friend ostream &operator<<(ostream &out,Customer &cs)
    {
        out<<cs.ime<<endl;
        out<<cs.eadresa<<endl;
        out<<cs.brojkupeni<<endl;
        out<<cs.getTip()<<" "<<cs.getPopust()<<endl;
        return out;
    }
};
int Customer::osnoven=10;
const int Customer::dopolnitelen=20;
class FINKI_bookstore
{
private:
    Customer *kupuvaci;
    int n;
public:
    FINKI_bookstore(Customer *kupuvaci=NULL,int n=0)
    {
        this->n=n;
        this->kupuvaci=new Customer[n];
        for(int i=0;i<n;i++)
        {
            this->kupuvaci[i]=kupuvaci[i];
        }
    }
    FINKI_bookstore(const FINKI_bookstore &finki)
    {
        this->n=finki.n;
        this->kupuvaci=new Customer[n];
        for(int i=0;i<n;i++)
        {
            this->kupuvaci[i]=finki.kupuvaci[i];
        }
    }
    FINKI_bookstore &operator=(const FINKI_bookstore &finki)
    {
        if(this!=&finki){
            delete [] kupuvaci;
            this->n=finki.n;
            this->kupuvaci=new Customer[n];
            for(int i=0;i<n;i++)
            {
                this->kupuvaci[i]=finki.kupuvaci[i];
            }
        }
        return *this;
    }
    ~FINKI_bookstore(){delete [] kupuvaci;}
    FINKI_bookstore &operator+=(Customer &c)
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(kupuvaci[i].getAdresa(),c.getAdresa())==0)
                throw UserExistsException();
        }
        Customer *temp=new Customer[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=kupuvaci[i];
        }
        temp[n++]=c;
        delete [] kupuvaci;
        kupuvaci=temp;
        return *this;
    }
    void setCustomers(Customer *kup,int b)
    {
        this->n=b;
        this->kupuvaci=new Customer[n];
        for(int i=0;i<n;i++)
        {
            kupuvaci[i]=kup[i];
        }
    }
    void update()
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(kupuvaci[i].getTip(),"standard")==0 && kupuvaci[i].getBroj()>5)
            {
                kupuvaci[i].setTip((typeC)1);
            }
            else if(strcmp(kupuvaci[i].getTip(),"loyal")==0 && kupuvaci[i].getBroj()>10)
            {
                kupuvaci[i].setTip((typeC)2);
            }
        }
    }
    friend ostream &operator<<(ostream &out,FINKI_bookstore &finki)
    {
        for(int i=0;i<finki.n;i++)
        {
            out<<finki.kupuvaci[i];
        }
        return out;
    }

};

int main(){
  int testCase;
  cin >> testCase;

  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;


  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

  }

  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;

    c.setDiscount1(5);

    cout << c;
  }

  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);

    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    try{
    fc+=c;
    }
    catch(UserExistsException &uee)
    {
        uee.print();
    }

    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    try{
    fc+=c;
    }
    catch(UserExistsException &uee)
    {
        uee.print();
    }

    cout << fc;
  }

  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "Update:" << endl;
    fc.update();
    cout << fc;
  }
  return 0;

}
