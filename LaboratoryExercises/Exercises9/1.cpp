/*
Да се дефинира апстрактна класа User за која ќе се чуваат:

username (char[50])
password (char[50])
email (char[50])
Класата треба да содржи еден чист виртуелен метод double popularity().

Од оваа класа да се изведат две класи и тоа FacebookUser и TwitterUser.

За класата FacebookUser уште се чуваат и:

број на пријатели
број на лајкови и
број на коментари
Популарноста се пресметува така што се собираат бројот на пријатели, бројот на лајкови и бројот на коментари, но притоа бројот на лајкови се множи со коефициент на вредност на лајкот кој е ист за секој корисник и изнесува 0.1, а исто така и бројот на коментари се множи со ист таков коефициент кој е 0.5.

За класата TwitterUser уште се чуваат и:

број на следачи и
број на твитови
Популарноста се пресметува така што се собираат бројот на следачи и бројот на твитови, но притоа бројот на твитови се множи со коефициент на вредност на твитот кој е ист за секој корисник и изнесува 0.5.

Да се креира класа SocialNetwork која ќе содржи:

динамичка низа од покажувачи од класата User
број на тековни корисници и
максимален број на корисници кој може да го содржи мрежата и кој е ист за сите мрежи и иницијално е поставен на 5
Да се преоптовари операторот += со кој ќе се додава нов корисник.

Да се дефинира метод avgPopularity() кој ќе ја враќа просечната популарност на корисниците во мрежата.

Исто така да се овозможи промена на максималната големина на низата преку методот changeMaximumSize(int number).

Потребно е да се справите со следните исклучоци:

Доколку лозинката на корисникот не содржи барем 1 голема буква, 1 мала буква и 1 број да се фрли исклучок од класа InvalidPassword така што како параметар ќе се прати пораката Password is too weak.
Доколку емаилот на корисникот не содржи точно еднаш @ да се фрли исклучок од класа InvalidEmail така што како параметар ќе се прати пораката Mail is not valid.
Доколку проба да се додаде корисник во социјалната мрежа, а веќе максималниот број на корисници е пополнет да се фрли исклучок од класа MaximumSizeLimit така што како параметар ќе се прати максималниот број на корисници во мрежата.
Сите класи кои се справуваат со исклучоци треба да го имаат имплементирано методот void message() така што за првите две класи ќе ја печати пораката којашто е испратена како параметар, а за последната класа ќе печати You can't add more than N users, каде што N е параметарот кој е пратен. Исто така со try-catch блокови справете се со исклучоците на соодветните места во main(), каде што во catch ќе го повикате методот message() од соодветниот исклучок.
*/
#include <iostream>
#include <cstring>

using namespace std;

class InvalidPassword{
private:
    char text[40];
public:
    InvalidPassword(char *text)
    {
    	strcpy(this->text,text);
    }
    void message()
    {
    	cout<<text<<endl;
    }
};

class InvalidEmail{
private:
    char text[40];
public:
    InvalidEmail(char *text)
    {
    	strcpy(this->text,text);
    }
    void message(){
    	cout<<text<<endl;
    }
};

class MaximumSizeLimit{
private:
    int n;
public:
    MaximumSizeLimit(int n)
    {
		this->n=n;
    }
    void message()
    {
    	cout<<"You can't add more than "<<n<<" users."<<endl;
    }
};

class User
{
protected:
    char username[50];
    char password[50];
    char email[50];
public:
    User(char *username="",char *password="",char *email="")
    {
        strcpy(this->username,username);
        int count1=0;
        int count2=0;
        int count3=0;
        int count4=0;
        for(int i=0;i<strlen(password);i++)
        {
            if(isupper(password[i]))
                count1++;
            if(islower(password[i]))
                count2++;
            if(isdigit(password[i]))
                count3++;
        }
        if(!count1||!count2||!count3)
            throw InvalidPassword("Password is too weak.");
        strcpy(this->password,password);
        for(int i=0;i<strlen(email);i++)
        {
            if(email[i]=='@')
                count4++;
        }
        if(count4!=1)
        {
            throw InvalidEmail("Mail is not valid.");
        }
        strcpy(this->email,email);
    }
    virtual double popularity()=0;
};
class FacebookUser:public User
{
private:
    int friends;
    int comments;
    int likes;
    const static double like;
    const static double comment;
public:
    FacebookUser(char *username="",char *password="",char *email="",int friends=0,int likes=0,int comments=0):User(username,password,email)
    {
        this->friends=friends;
        this->comments=comments;
        this->likes=likes;
    }
    double popularity()
    {
        return likes*like+comments*comment+friends;
    }
};
const double FacebookUser::like=0.1;
const double FacebookUser::comment=0.5;
class TwitterUser:public User
{
private:
    int followers;
    int tweets;
    const static double tweet;
public:
    TwitterUser(char *username="",char *password="",char *email="",int followers=0,int tweets=0):User(username,password,email)
    {
        this->followers=followers;
        this->tweets=tweets;
    }
    double popularity()
    {
        return followers+tweets*tweet;
    }
};
const double TwitterUser::tweet=0.5;
class SocialNetwork
{
private:
    User **niza;
    int n;
    int maxKorisnici;
public:
    SocialNetwork()
    {
        niza=NULL;
        n=0;
        maxKorisnici=5;
    }
    SocialNetwork(const SocialNetwork &sn)
    {
        this->n=sn.n;
        this->maxKorisnici=sn.maxKorisnici;
        this->niza=new User*[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=sn.niza[i];
        }
    }
    SocialNetwork &operator=(const SocialNetwork &sn)
    {
        if(this!=&sn)
        {
            delete [] niza;
            this->n=sn.n;
            this->maxKorisnici=sn.maxKorisnici;
            this->niza=new User*[n];
            for(int i=0;i<n;i++)
            {
                this->niza[i]=sn.niza[i];
            }
        }
        return *this;
    }
    SocialNetwork &operator+=(User *user)
    {
        if(n==maxKorisnici)
        {
            throw MaximumSizeLimit(maxKorisnici);
        }
        User **temp=new User*[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=niza[i];
        }
        temp[n++]=user;
        delete [] niza;
        niza=temp;
    }
    double avgPopularity()
    {
        double suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=niza[i]->popularity();
        }
        return suma/n;
    }
    void changeMaximumSize(int number)
    {
        maxKorisnici=number;
    }

};
int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;
        // TODO: Try-catch
        try{
        User * u = new FacebookUser(username,password,email,friends,likes,comments);
        network += u;
        }
        catch(InvalidPassword &ip)
        {
            ip.message();
        }
        catch(InvalidEmail &ie)
        {
            ie.message();
        }
        catch(MaximumSizeLimit &msl)
        {
            msl.message();
        }
      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;

        // TODO: Try-catch
        try{
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
        }
        catch(InvalidPassword &ip)
        {
            ip.message();
        }
        catch(InvalidEmail &ie)
        {
            ie.message();
        }
        catch(MaximumSizeLimit &msl)
        {
            msl.message();
        }
      }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    // TODO: Try-catch
    try{
    User * u= new TwitterUser(username,password,email,followers,tweets);
    network += u;
    }
    catch(InvalidPassword &ip)
        {
            ip.message();
        }
    catch(InvalidEmail &ie)
        {
            ie.message();
        }
    catch(MaximumSizeLimit &msl)
        {
            msl.message();
        }
    cout << network.avgPopularity();

}
