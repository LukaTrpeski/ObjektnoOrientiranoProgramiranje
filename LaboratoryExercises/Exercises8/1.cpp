#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};
class Rectangle:public Shape
{
public:
    void draw()
    {
        cout<<"Drawing a rectangle.\n";
    }
};
// креирајте класа Rectangle која наследува од Shape 

    // во неа препокријте ја функцијата draw() така што ќе се испечати: "Drawing a rectangle.\n"


int main() {
    Shape* shape;
    Shape sh;
    shape=&sh;
    // тука инстанцирајте објект од класата Shape и покажувачот shape нека покажува кон него
    
    shape->draw();
    Rectangle rec;
    shape=&rec;
    shape->draw();
    // сега инстанцирајте објект од класата Rectangle и покажувачот shape нека покажува кон него
    // повторно повикајте ја функцијата draw() на shape

    return 0;
}