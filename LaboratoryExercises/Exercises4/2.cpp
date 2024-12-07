/*
Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен датотечен систем.

Во класата File треба да се чуваат следниве податоци:

Име на датотеката (динамички алоцирана низа од знаци)
Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
Големина на датотеката (цел број на мегабајти)
Дополнително, во класата потребно е да се напишат и:

Конструктор без параметри
Конструктор со параметри
Конструктор за копирање
Деструктор
Преоптоварување на операторот =
Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
Во класата Folder треба да се чуваат следниве податоци:

Име на директориумот (динамички алоцирана низа од знаци)
Број на датотеки во него (на почеток директориумот е празен)
Динамички алоцирана низа од датотеки, објекти од класата File
Дополнително, во класата потребно е да се напишат и:

Конструктор со потпис Folder(const char* name)
Деструктор
Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот
Не го менувајте почетниот код.
*/
#include<iostream>
#include<cstring>

using namespace std;
#include <iostream>
#include <ctype.h>
#include <string.h>
using namespace std;

enum Extension{pdf=0,txt=1,exe=2};

class File{
private:
    char *imed;
    Extension ex;
    char *imes;
    int golemina;
public:
    File(){}
    File(char *imed,char *imes,int golemina,Extension ex)
    {
        this->imed=new char[strlen(imed)+1];
        strcpy(this->imed,imed);
        this->ex=ex;
        this->imes=new char[strlen(imes)+1];
        strcpy(this->imes,imes);
        this->golemina=golemina;
    }
    File(const File &f)
    {
        this->imed=new char[strlen(f.imed)+1];
        strcpy(this->imed,f.imed);
        this->ex=f.ex;
        this->imes=new char[strlen(f.imes)+1];
        strcpy(this->imes,f.imes);
        this->golemina=f.golemina;
    }
    File& operator=(const File &f)
    {
        if(this!=&f){
            delete [] imed;
            delete [] imes;
            this->imed=new char[strlen(f.imed)+1];
            strcpy(this->imed,f.imed);
            this->ex=f.ex;
            this->imes=new char[strlen(f.imes)+1];
            strcpy(this->imes,f.imes);
            this->golemina=f.golemina;
        }
        return *this;
    }
    ~File(){delete [] imes;
    delete [] imed;}
    void print()
    {
        cout<<"File name: "<<imed;
        if(ex==1)
        cout<<".txt"<<endl;
        else if(ex==0)
        cout<<".pdf"<<endl;
        else if(ex==2)
        cout<<".exe"<<endl;
        cout<<"File owner: "<<imes<<endl;
        cout<<"File size: "<<golemina<<endl;
        
    }
    bool equals(const File & that)
    {
        if(strcmp(imed,that.imed)==0&&strcmp(imes,that.imes)==0&&ex==that.ex)
            return true;
        else
            return false;
    }
    bool equalsType(const File & that)
    {
        if(strcmp(imed,that.imed)==0&&ex==that.ex)
            return true;
        else
            return false;
    }
    };

class Folder{
private:
    char *imef;
    int datoteki;
    File *file;
public:
    Folder(const char* imef)
    {
        this->imef=new char[strlen(imef)+1];
        strcpy(this->imef,imef);
        datoteki=0;
        this->file=new File[0];
    }
    Folder(const Folder &f)
    {
        this->imef=new char[strlen(f.imef)+1];
        strcpy(this->imef,f.imef);
        datoteki=f.datoteki;
        this->file=new File[0];
    }
    Folder& operator=(Folder &f)
    {
        if(this!=&f){
        delete [] imef;
        delete [] file;
        this->imef=new char[strlen(f.imef)+1];
        strcpy(this->imef,f.imef);
        datoteki=f.datoteki;
        this->file=new File[0];
        }
        return *this;
    }
    ~Folder(){delete [] imef;
    delete [] file;}
    void print()
    {
        cout<<"Folder name: "<<imef<<endl;
        for(int i=0;i<datoteki;i++)
        {
            file[i].print();
        }
    }
    void add(const File &f)
    {
        File *temp=new File[datoteki+1];
        for(int i=0;i<datoteki;i++)
        {
            temp[i]=file[i];
        }
        temp[datoteki++]=f;
        delete [] file;
        file=temp;
    }
    void remove(const File & f)
    {
        int n=0;
        for(int i=0;i<datoteki;i++)
        {
            if(!file[i].equals(f))
            {
                n++;
            }
        }
        File *temp=new File[n];
        n=0;
        for(int i=0;i<datoteki;i++)
        {
            if(!file[i].equals(f))
            {
                temp[n++]=file[i];
            }
        }
        delete [] file;
        file=temp;
        datoteki=n;
        
    }
    };
int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;	

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}