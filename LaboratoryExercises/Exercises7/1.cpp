/*
Да се дефинира апстрактна класа Employee којашто ќе содржи име на вработениот, години и работно искуство во години (integer). Да се дефинираат чисти виртуелни функции plata() и bonus() (double).

Од класата Employee да се изведе класа SalaryEmployee која покрај основните информации содржи и информација за основната плата. Бонусот на овие работници се пресметува како процент од основната плата, а процентот е бројот на години со работно искуство. На пример ако работеле 10 години, бонусот е 10 проценти од основната плата. Вкупната плата се пресметува како основната плата плус бонусот.

Од класата Employee исто така да се изведе класа HourlyEmployee која покрај основните информации содржи информација и за вкупниот број на часови кои ги одработил работникот и платата по час. Вкупната плата се пресметува како бројот на часови помножен со платата по час плус бонусот, додека бонусот се пресметува на следниот начин: За секој час над 320-тиот се добива 50 проценти од платата по час.

Од класата Employee на крај се изведува класата Freelancer која покрај основните информации содржи и број на проекти на кои работел вработениет и низа со суми кои ги добил за тие проекти (double). По направени 5 проекти, за секој нареден вработените добиваат бонус од 1000 денари. Вкупната плата на овој тип на вработени изнесува вкупната сума добиена од сите проекти плус бонусот.

Да се преоптовари операторот == кој ќе прима два објекти од класата Employee и ќе ги споредува според тоа дали имаат ист број на години и дали добиваат ист бонус.

Да се дефинира класа Company која ќе содржи информации за името на компанијата, бројот на вработени, и динамична низа од покажувачи од класата Employee или Employee **. За потребите на оваа класа треба да се дефинира конструктор кој прима само еден аргумент - името на компанијата, да се преоптовари операторот += и да се дефинираат следните методи:

double vkupnaPlata() - метод којшто ја враќа вкупната плата на сите вработени во компанијата
double filtriranaPlata(Employee * emp) - метод којшто ја враќа платата само на работниците кои се еднакви со дадениот вработен (според оператор ==)
void pecatiRabotnici() - метод којшто печати по колку вработени има од секој тип на работници во компанијата, а форматот на печатење можете да го видите од тест примерите
Hint: За потребите на последниот метод можете да искористите статички членови и статички функции во секоја од класата, dynamic_cast, виртуелна функција која ќе ја преоптоварите во секоја од класите или нешто друго по ваша желба.
*/
    #include <iostream>
    #include <string.h>
    using namespace std;

    class Employee
    {
    protected:
        char ime[100];
        int godini;
        int iskustvo;
    public:
        Employee(char *ime="",int godini=0,int iskustvo=0)
        {
            strcpy(this->ime,ime);
            this->godini=godini;
            this->iskustvo=iskustvo;
        }
        virtual double plata()=0;
        virtual double bonus()=0;
        friend bool operator==(Employee &e1,Employee &e2);
    };
    class SalaryEmployee:public Employee
    {
    private:
        double osnovna;
    public:
        SalaryEmployee(char *ime="",int godini=0,int iskustvo=0,double osnovna=0):Employee(ime,godini,iskustvo)
        {
            this->osnovna=osnovna;
        }
        double bonus()
        {
            return osnovna*iskustvo/100.0;
        }
        double plata()
        {
            return osnovna+bonus();
        }
    };
    class HourlyEmployee:public Employee
    {
    private:
        int casovi;
        double platapocas;
    public:
        HourlyEmployee(char *ime="",int godini=0,int iskustvo=0,int casovi=0,double platapocas=0):Employee(ime,godini,iskustvo)
        {
            this->casovi=casovi;
            this->platapocas=platapocas;
        }
        double bonus()
        {
            if(casovi>320)
                return platapocas*(casovi-320)*0.5;
            else
                return 0;
        }
        double plata()
        {
            return casovi*platapocas+bonus();
        }
    };
    class Freelancer:public Employee
    {
    private:
        int proekti;
        double sumi[100];
    public:
        Freelancer(char *ime="",int godini=0,int iskustvo=0,int proekti=0,double *sumi=NULL):Employee(ime,godini,iskustvo)
        {
            this->proekti=proekti;
            for(int i=0;i<proekti;i++)
            {
                this->sumi[i]=sumi[i];
            }
        }
        double bonus()
        {
            if(proekti>5)
                return (proekti-5)*1000.0;
            else
                return 0;
        }
        double plata()
        {
            double s=0;
            for(int i=0;i<proekti;i++)
            {
                s+=sumi[i];
            }
            return s+bonus();
        }
    };
    bool operator==(Employee &e1,Employee &e2)
    {
        return e1.godini==e2.godini&&e1.bonus()==e2.bonus();
    }
    class Company
    {
    private:
        char ime[100];
        int n;
        Employee **niza;
    public:
        Company(char *ime="")
        {
            strcpy(this->ime,ime);
            this->n=0;
            this->niza=new Employee*[n];
        }
        Company &operator+=(Employee *e)
        {
            Employee **temp=new Employee*[n+1];
            for(int i=0;i<n;i++)
                temp[i]=niza[i];
            temp[n++]=e;
            delete [] niza;
            niza=temp;
            return *this;
        }
        ~Company(){delete [] niza;}
        double vkupnaPlata()
        {
            double suma=0;
            for(int i=0;i<n;i++)
                suma+=niza[i]->plata();
            return suma;
        }
        double filtriranaPlata(Employee *emp)
        {
            double suma=0;
            for(int i=0;i<n;i++)
            {
                if(*niza[i]==*emp)
                {
                    suma+=niza[i]->plata();
                }
            }
            return suma;
        }
        void pecatiRabotnici()
        {
            int h=0;
            int s=0;
            int f=0;
            cout<<"Vo kompanijata "<<ime<<" rabotat:"<<endl;
            for(int i=0;i<n;i++)
            {
                HourlyEmployee *he=dynamic_cast<HourlyEmployee*>(niza[i]);
                if(he)
                    h++;
                SalaryEmployee *se=dynamic_cast<SalaryEmployee*>(niza[i]);
                if(se)
                    s++;
                Freelancer *fr=dynamic_cast<Freelancer*>(niza[i]);
                if(fr)
                    f++;
            }
            cout<<"Salary employees: "<<s<<endl;
            cout<<"Hourly employees: "<<h<<endl;
            cout<<"Freelancers: "<<f<<endl;
        }
    };
    int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
      cin >> type;
      cin >> employeeName >> age >> experience;

      if (type == 1) {
        int basicSalary;
        cin >> basicSalary;
        c += new SalaryEmployee(employeeName, age, experience, basicSalary);
      }

      else if (type == 2) {
        int hoursWorked;
        int hourlyPay;
        cin >> hoursWorked >> hourlyPay;
        c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
      }

      else {
        int numProjects;
        cin >> numProjects;
        double projects[10];
        for (int i=0; i < numProjects; ++i) {
          cin >> projects[i];
        }
        c += new Freelancer(employeeName, age, experience, numProjects, projects);
      }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
    }
