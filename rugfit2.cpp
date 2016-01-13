// rugfit2.cpp - calculates fit of rug to a floor
// Brandon Lo 1/12/16
/*In the definition of class Rectangle: declare a function named area that will take no arguments
and will return a double value. Make the function const - meaning it promises not to change the
object on which it is called - just like the getWidth and getLength functions that are already
 declared in the skeleton.
Scroll down past the end of the class definition and past the existing
definitions of the constructor and four standard get and set methods, and
then define the area method you declared above. Look at the other method
definitions as examples for how to do it - notice they use the scope resolution
operator to identify their connection to a particular class, as in Rectangle::setLength
 which identifies it as pertaining to class Rectangle. Return the value of length times width.
In the main function: prompt the user for the width and length of the rug,
read those two values from the user, and then reset the width and length of
the Rectangle object named rug with the user's dimensions (using the rug's setWidth
and setLength methods, of course). As a reminder, you use the object's name, the dot
operator, and the name of the method to do such things. For example, if we wanted to
find the value of the floor's width, we could do so by using the getWidth method
as follows:*/


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

/*In the main function: prompt the user for the width and length of the rug,
read those two values from the user, and then reset the width and length of
the Rectangle object named rug with the user's dimensions (using the rug's setWidth
and setLength methods, of course). As a reminder, you use the object's name, the dot
operator, and the name of the method to do such things. For example, if we wanted to
find the value of the floor's width, we could do so by using the getWidth method
as follows:
Also in main: change the two assignment statements for floorArea and rugArea to use the area method for each of the floor and rug
 objects.Also in main: change the two assignment statements for floorArea and rugArea to use the area method for each of the floor and rug objects.
*/

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
