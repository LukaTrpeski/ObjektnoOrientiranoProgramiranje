/*
За програмски јазик C.

Да се напише структура која ќе опишува отсечка во дводимензионален простор (две точки). Потоа да се напише функција која ќе проверува дали две отсечки се сечат.
*/
#include <stdio.h>

typedef struct tocka
{
    float x;
    float y;
}tocka;
typedef struct otsecka
{
     tocka t1;
     tocka t2;
}otsecka;
int se_secat(otsecka o1,otsecka o2)
{
    int i=0,j=0,k=0;
    int x = (o1.t2.y - o1.t1.y) * (o2.t1.x - o1.t2.x) - 
              (o1.t2.x - o1.t1.x) * (o2.t1.y - o1.t2.y); 
    if (x == 0) i++;
    if (x < 0)  j++;
    if (x > 0)  k++;
    int y = (o1.t2.y - o1.t1.y) * (o2.t2.x - o1.t2.x) - 
              (o1.t2.x - o1.t1.x) * (o2.t2.y - o1.t2.y); 
    if (y == 0) i++;
    if (y < 0)  j++;
    if (y > 0)  k++;
    if(i!=2 && j!=2 && k!=2)
    return 1;
    else
    return 0;
    
}
int main() {
    float x1, y1, x2, y2;
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t1 = { x1, y1 };
    tocka t2 = { x2, y2 };
    otsecka o1 = { t1, t2 };
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t3 = { x1, y1 };
    tocka t4 = { x2, y2 };
    otsecka o2 = { t3, t4 };
    printf("%d\n", se_secat(o1, o2));
    return 0;
}