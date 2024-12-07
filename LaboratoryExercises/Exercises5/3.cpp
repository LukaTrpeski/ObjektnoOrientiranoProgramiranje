/*
Да се напише класа за матрица. Во класата се чуваат елементите од матрицата од тип float (матрица со максимална димензија [10]x[10]) и големината на матрицата (број на редици и колони). За оваа класа да се преоптоварат следните оператори:

оператор + за собирање матрица со број
оператор - за одземање на матрици
оператор * за множење на матрици
операторот >> за внесување на елементите на матрицата
операторот << за печатење на елементите на матрицата
Во главната функција да се креираат објекти A, B и C со подразбирливиот конструктор на класата Matrica. Од стандарден влез да се прочитаат нивните вредности. Да се отпечати вредноста на изразот A-(B*C)+2 на стандарден излез.

Да се претпостави дека секогаш матриците ќе бидат квадратни со ист број на редици и колони.
*/
#include <iostream>

using namespace std;

class Matrica{
private:
    float matrica[10][10];
    int broj;
public:
    Matrica()
    {
        broj=0;
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                matrica[i][j]=0;
    }
    ~Matrica(){}
    Matrica& operator+(int n)
    {
        for(int i=0;i<broj;i++)
            for(int j=0;j<broj;j++)
                matrica[i][j]+=n;
        return *this;
    }
    Matrica& operator-(Matrica &m)
    {
        for(int i=0;i<broj;i++)
        {
            for(int j=0;j<broj;j++)
            matrica[i][j]-=m.matrica[i][j];
        }
        return *this;
    }
    Matrica operator*(Matrica const &m)
    {
        Matrica temp;
        for(int i=0;i<broj;i++)
        {
            for(int j=0;j<broj;j++)
            {
                for(int k=0;k<broj;k++)
                    temp.matrica[i][j]+=matrica[i][k]*m.matrica[k][j];
            }
        }
        return temp;
    }
    friend istream &operator>>(istream &in,Matrica &m)
    {
        int k,j;
        in>>k;
        in>>j;
        m.broj=k;
        for(int i=0;i<m.broj;i++){
            for(int j=0;j<m.broj;j++){
                in>>m.matrica[i][j];
            }
        }
        return in;
    }
    friend ostream &operator<<(ostream &out,const Matrica &m)
    {
        for(int i=0;i<m.broj;i++){
            for(int j=0;j<m.broj;j++){
                out<<m.matrica[i][j];
                out<<" ";
            }
            out<<endl;
        }
        return out;
    }

};

int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D;
    Matrica K=R+2;
    cout<<K;
}