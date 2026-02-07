#include <iostream>
using namespace std;

typedef struct{
    float x;
    float y;
}coord;

float absolute(float num){
    return (num < 0)? (num - 2*num) : num;
}

class Rectangle{
    private:
    coord lowerLeft, upperRight;
     
    public:
    Rectangle(coord lL, coord uR){
        lowerLeft = lL;
        upperRight = uR;
        cout << "Rectangle created." << endl;
    }
    
    void calculateArea(){
        float width = absolute(upperRight.x - lowerLeft.x);
        float height = absolute(upperRight.y - lowerLeft.y);

        double area = width * height;
        cout << "Area of the Rectangle: " << area << endl;
    }

    ~Rectangle(){
        cout << "Rectangle destroyed." << endl;
    }
};

int main(){
    coord lowerLeft, upperRight;
    cin >> lowerLeft.x >> lowerLeft.y 
        >> upperRight.x >> upperRight.y;

    Rectangle obj(lowerLeft, upperRight);
    obj.calculateArea();

    return 0;
}
