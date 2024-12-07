/*
Потребно е да се имплементира класа за компјутерска игра (Game), што содржи информации за:

име на играта (низа од макс. 100 знаци)
цена на играта (децимален број)
дали е играта купена на распродажба (bool променлива).
Од класата Game да се изведе класа SubscriptionGame, што дополнително ќе чува:

месечен надоместок за играње (децимален број).
датум кога играта е купена (месец и година како позитивни цели броеви)
За класите Game и SubscriptionGame да се преоптоварат операторите за печатење (<<) и читање (>>). Да се дефинира и операторот == кој ќе споредува игри според нивното име.

Да се дефинира класа за корисник (User) во која се чуваат:

кориснично име на корисникот (низа од макс. 100 знаци)
колекција од игри кои се купени од корисникот (динамички алоцирана низа).
Да се преоптовари операторот += кој ќе овозможи додавање на нова игра во колекцијата на игри. Притоа ако корисникот ја има веќе купено играта, потребно е да се креира исклучок од типот ExistingGame. Класата за имплементација на исклучоци потребно е има соодветен конструктор и метода message за печатење на порака на екран.

Да се креира и метода total_spent() во класата User која ќе пресметува колку пари корисникот потрошил за својата колекција од игри. Доколку играта е купена на распродажба, цената на играта е 30% од стандарната цена. Доколку играта е од типот SubscriptionGame, потребно е да се вкалкулира и сумата потрошена за месечниот надоместок (број_на_изминати_месеци x цена_на_месечен_надоместок) без да се земе во предвид моменталниот месец (мај 2018).

Да се преоптовари и оператоторот за печатење на корисникот, која печати информации во сл. формат (види тест примери 7 до 12):

User: username
- Game: PUBG, regular price: $70, bought on sale
- Game: Half Life 2, regular price: $70 - Game: Warcraft 4, regular price: $40, monthly fee: $10, purchased: 1-2017

Листа на дел од методите со нивни прототипови кои се користат во main:

ЕxistingGame::message()
Game::operator==(Game&)
User::operator+=(Game&)
User::get_game(int)
User::total_spent(int)
User::get_name()
User::get_games_number()
*/
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <string.h>
using namespace std;

class ExistingGame
{
public:
    char text[50];
    ExistingGame(const char *text="")
    {
        strcpy(this->text,text);
    }
    void message()
    {
        cout<<text<<endl;
    }
};
class Game
{
protected:
    char igra[100];
    float cena;
    bool rasprodazhba;
public:
    Game(const char *igra="",float cena=0,bool rasprodazhba=true)
    {
        strcpy(this->igra,igra);
        this->cena=cena;
        this->rasprodazhba=rasprodazhba;
    }
    friend ostream &operator<<(ostream &out,Game &gam)
    {
        out<<"Game: "<<gam.igra<<", regular price: $"<<gam.cena;
        if(gam.rasprodazhba)
            out<<", bought on sale";
        
        return out;
    }
    virtual float get_price()
    {
        if(rasprodazhba)
            return cena*0.3;
        else
            return cena;
    }
    friend istream &operator>>(istream &in,Game &gam)
    {
        cin.get();
        cin.getline(gam.igra, 100);
        in>>gam.cena;
        in>>gam.rasprodazhba;
        return in;
    }
    char *getName()
    {
        return igra;
    }
    bool operator==(Game &g)
    {
        return (strcmp(this->igra,g.igra)==0);
    }
};
class SubscriptionGame:public Game
{
private:
    float nadomestok;
    int mesec;
    int godina;
public:
    SubscriptionGame(const char *igra="",float cena=0,bool rasprodazhba=true,float nadomestok=0,int mesec=0,int godina=0):Game(igra,cena,rasprodazhba)
    {
        this->nadomestok=nadomestok;
        this->mesec=mesec;
        this->godina=godina;
    }
    float get_price()
    {
        int n=0;
        if(godina<2018)
            n=(12-mesec)+(2017-godina)*12+5;
        else
            n=5-mesec;
        return n*nadomestok+Game::get_price();
    }
    friend ostream &operator<<(ostream &out,SubscriptionGame &gam)
    {
        Game * tmp = dynamic_cast<Game*>(&gam);

        out<< *tmp;

        out<<", monthly fee: $"<< gam.nadomestok<<", purchased: "<< gam.mesec << "-" << gam.godina<<endl;
        return out;
    }
    friend istream &operator>>(istream &in,SubscriptionGame &gam)
    {
        cin.get();
        cin.getline(gam.igra, 100);
        in>>gam.cena;
        in>>gam.rasprodazhba;
        in>>gam.nadomestok;
        in>>gam.mesec;
        in>>gam.godina;
        return in;
    }
};
class User
{
private:
    char korisnicko[100];
    Game **niza;
    int n;
public:
    User(const char *korisnicko="",Game **niza=NULL,int n=0)
    {
        strcpy(this->korisnicko,korisnicko);
        this->n=n;
        this->niza=new Game*[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=niza[i];
        }
    }
    User(const User &u)
    {
        strcpy(this->korisnicko,u.korisnicko);
        this->n=u.n;
        this->niza=new Game*[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=u.niza[i];
        }
    }
    User &operator=(const User &u)
    {
        if(this!=&u){
            delete [] niza;
            strcpy(this->korisnicko,u.korisnicko);
            this->n=u.n;
            this->niza=new Game*[n];
            for(int i=0;i<n;i++)
            {
                this->niza[i]=u.niza[i];
            }
        }
        return *this;
    }
    User &operator+=(Game &g)
    {
        for(int i=0;i<n;i++)
        {
            if(*niza[i]==g)
                throw ExistingGame("The game is already in the collection");
        }
        Game **temp=new Game*[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=niza[i];
        }
        SubscriptionGame * sg = dynamic_cast< SubscriptionGame* >(&g);
        if(sg)
            temp[n]=new SubscriptionGame(*sg);
        else
            temp[n]=new Game(g);
        delete [] niza;
        n++;
        niza=temp;
        return *this;
    }
    ~User(){delete [] niza;}
    float total_spent()
    {
        float suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=niza[i]->get_price();
        }
        return suma;
    }
    friend ostream &operator<<(ostream &out,User &u)
    {
        out<<endl;
        out<<"User: "<<u.korisnicko<<endl;
        for(int i=0;i<u.n;i++)
        {
            out<<"- ";
            SubscriptionGame * sg;
            sg = dynamic_cast<SubscriptionGame *> (u.niza[i]);
            if(sg)
                out<<*sg;
            else
            {
                out<<*u.niza[i];
            }
            out<<endl;
        }
        return out;
    }
    Game& get_game(int n)
    {
        return *niza[n];
    }
    const char *get_username()
    {
        return korisnicko;
    }
    int get_names_number()
    {
        return n;
    }

};

int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}
