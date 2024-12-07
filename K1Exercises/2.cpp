/*
Да се имплементира класа List во којашто ќе се чуваат информации за:

броеви што се дел од листата (динамички алоцирана низа од цели броеви)
бројот на броеви што се дел од листата
За класата да се дефинираат следните методи:

конструктор (со аргументи), copy-конструктор, деструктор, оператор =
void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
int sum() метод што ја враќа сумата на елементите во листата
double average() метод што ќе го враќа просекот на броевите во листата
Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

низа од листи (динамички алоцирана низа од објекти од класата List)
број на елементи во низата од листи (цел број)
број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
За класата потребно е да ги дефинирате следните методи:

конструктор (default), copy-конструктор, деструктор, оператор =
void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
доколку контејнерот е празен се печати само порака The list is empty.
void addNewList(List l) метод со којшто се додава листа во контејнерот
Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
int sum() метод што ја враќа сумата на сите елементи во сите листи
double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот
*/
#include <iostream>
using namespace std;

class List{
private:
    int* broevi;
    int n;
public:
    List(){
    	broevi=new int[0];
    	n=0;
    }
    ~List(){
    delete[] broevi;
    }
    List(int *broevi,int n){
    this->broevi=new int[n];
    for(int i=0;i<n;i++)
        this->broevi[i]=broevi[i];
    this->n=n;
    }
    List(const List& l){
    this->n=l.n;
    this->broevi=new int[n];
    for(int i=0;i<n;i++)
        this->broevi[i]=l.broevi[i];
    }
    List& operator=(List& l){
       if(this!=&l){
         delete [] broevi;
         n=l.n;
         broevi=new int[n];
         for(int i=0;i<n;i++)
            broevi[i]=l.broevi[i];
        }
        return *this;
    }
    int sum(){
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=broevi[i];
    }
        return sum;
    }
    double average(){
        return sum()*1.0/n;
    }
    void print(){
        cout<<n<<": ";
        for(int i=0;i<n;i++){
            cout<<broevi[i]<<" ";
        }
        cout<<"sum: "<<sum();
        cout<<" average: "<<average()<<endl;
    }
    friend class ListContainer;
};
class ListContainer{
private:
    List* listi;
    int elementi;
    int obidi;
public:
    ListContainer(){    
    elementi=0;
    listi=new List[0];
    obidi=0;
    }
    ~ListContainer(){
    delete [] listi;
    }
    ListContainer(const ListContainer& lc){
        this->obidi=lc.obidi;
        this->elementi=lc.elementi;
        this->listi=new List[lc.elementi];
        for(int i=0;i<lc.elementi;i++){
            this->listi[i]=lc.listi[i];
        }
    }
    ListContainer& operator=(ListContainer& lc){
        if(this!=&lc){
        delete [] listi;
        obidi=lc.obidi;
        elementi=lc.elementi;
        listi=new List[lc.elementi];
        for(int i=0;i<lc.elementi;i++){
            listi[i]=lc.listi[i];
        }
        }
        return *this;
    }
    int sum()
    {
        int sum=0;
        for(int i=0;i<elementi;i++)
        {
            sum+=listi[i].sum();
        }
        return sum;
    }
    double average()
    {
        double a=0.0;
        for(int i=0;i<elementi;i++)
        {
        a+=listi[i].n;
        }
        return sum()/a;
    }
    void addNewList(List l)
    {
        ++obidi;
        for(int i=0;i<elementi;i++){
            if(l.sum()==listi[i].sum())
                return;
        }
        List *temp=new List[elementi+1];
        int i;
        for(i=0;i<elementi;i++)
        {
            temp[i]=listi[i];
        }
        temp[elementi++]=l;
        delete [] listi;
        listi=temp;
    }
        void print()
    {
        if(elementi==0)
            {cout<<"The list is empty"<<endl;
            return;}
        else{
        for(int i=0;i<elementi;i++)
        {
            cout<<"List number: "<<(i+1)<<" List info: ";
            listi[i].print();
        }
        }
        cout<<"Sum: "<<sum();
        cout<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<elementi<< " Failed attempts: " <<obidi-elementi<<endl;
    }
    
};
int main() {
	
	ListContainer lc;
	int N;	
	cin>>N;	
    
	for (int i=0;i<N;i++) {
		int n;
		int niza[100];
		
		cin>>n;
       
		for (int j=0;j<n;j++){
			cin>>niza[j];
            
		}
       
		List l=List(niza,n);
	
		lc.addNewList(l);
	}	
	
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
        
    }
    else {
        lc.print();
    }
}