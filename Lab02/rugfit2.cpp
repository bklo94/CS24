// rugfit2.cpp - calculates fit of rug to a floor
// Brandon Lo 1/12/16

#include <iostream>
using namespace std;

// definition of class Rectangle
// (usually would be in a separate file named rectangle.h)
class Rectangle {

public:
    // declare constructor and get/set methods (already done)
    Rectangle(double w, double l);  // constructor
    double getWidth() const;        // accessor for width
    double getLength() const;       // accessor for length
    void setWidth(double);          // mutator for width
    void setLength(double);         // mutator for length
    double area ( ) const;
    // DECLARE (const) METHOD TO RETURN AREA OF RECTANGLE


private:
    double width, length;

}; // end of class definition

// implementation of class Rectangle here to main function
// (usually would be in a separate file named rectangle.cpp,
// and this separate file would #include "rectangle.h")

// implement constructor
Rectangle::Rectangle(double w, double l) : width(w), length(l) {
} // no constructor body: uses initialization list

// implement accessors and mutators for width and length
double Rectangle::getWidth() const {
    return width;
}
double Rectangle::getLength() const {
    return length;
}
void Rectangle::setWidth(double w) {
    width = w;
}
void Rectangle::setLength(double l) {
    length = l;
}

// IMPLEMENT THE AREA METHOD HERE

double Rectangle::area () const{
  return length * width;
}

// change main where instructed in UPPER CASE below
// (usually would #include "rectangle.h" before main)
int main() {

    double width, length;
    Rectangle rug(0,0); // will be updated below

    // create Rectangle named "floor" for sizes input by user
    cout << "enter width and length of floor: ";
    cin >> width >> length;
    const Rectangle floor(width, length); // note: const object

    // RESET Rectangle NAMED "rug" FOR SIZES INPUT BY USER
    cout << "enter width and length of rug: ";
    cin >> width >> length;
    rug.setWidth(width);
    rug.setLength(length);


    // DO NOT CHANGE ANYTHING BELOW (if you do, you will earn 0 points,
    // no matter what submit.cs says is your "tentative" score)

    // print results
    cout << "floor area: " << floor.area() << endl;
    cout << "rug area: " << rug.area() << endl;
    double leftover = rug.area() - floor.area();
    cout << "leftover rug area: " <<
        (leftover > 0 ? leftover : 0) << endl;
    cout << "empty floor area: " <<
        (leftover < 0 ? -leftover : 0) << endl;

    return 0;
}
