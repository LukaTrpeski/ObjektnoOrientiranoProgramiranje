/*
Да се дефинира класа Film, во која ќе се чуваат информации за:

име низа од 100 знаци
режисер низа од 50 знаци
жанр низа од 50 знаци
година цел број
Сите променливи треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

default конструктор и конструктор со аргументи
метод за печатење на информациите за филмот
Дополнително да се реализира надворешна функција:

void pecati_po_godina(Film *f, int n, int godina) која ќе прима аргумент низа од филмови, вкупниот број на филмови и година, а треба да ги отпечати само филмовите кои се направени во дадената година.
*/
#include <iostream>
#include <cstring>
using namespace std;
class Film{

private:
char ime[100];
char reziser[50];
char zanr[50];
int godina;
public:
Film(){};
Film(char i[100],char rez[50],char z[50],int god)
{
	strcpy(ime,i);
	strcpy(reziser,rez);
    strcpy(zanr,z);
	godina=god;
}
int getgodina()
{
    return godina;}
void print()
{
	cout<<"Ime: "<<ime<<endl;
	cout<<"Reziser: "<<reziser<<endl;
	cout<<"Zanr: "<<zanr<<endl;
	cout<<"Godina: "<<godina<<endl;
}
};
void pecati_po_godina(Film *f, int n, int godina)
{
    int i,k;
    for(i=0;i<n;i++)
    {
    k=f[i].getgodina();
    if(k==godina)
    f[i].print();
}}
int main() {
 	int n;
 	cin >> n;
    Film f[n];
 	for(int i = 0; i < n; ++i) {
 		char ime[100];
 		char reziser[50];
 		char zanr[50];
 		int godina;
 		cin >> ime;
 		cin >> reziser;
 		cin >> zanr;
 		cin >> godina;
 		f[i]=Film(ime,reziser,zanr,godina);
 	}
 	int godina;
 	cin >> godina;
    pecati_po_godina(f,n,godina);
 	return 0;
 }