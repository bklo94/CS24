// rugfit1.cpp - calculates fit of rug to a floor
// cmc, 9/25/2015

#include <iostream>
using namespace std;

// utility function to calculate area of a rectangle
double area(double width, double length) {
    return width * length;
}

int main() {

    double floorWidth, floorLength, rugWidth, rugLength,
        floorArea, rugArea, leftover;

    cout << "enter width and length of floor: ";
    cin >> floorWidth >> floorLength;
    cout << "enter width and length of rug: ";

    cin >> rugWidth >> rugLength;

    floorArea = area(floorWidth, floorLength);
    rugArea = area(rugWidth, rugLength);
    leftover = rugArea - floorArea;

    cout << "floor area: " <<  floorArea << endl;
    cout << "rug area: " << rugArea << endl;
    cout << "leftover rug area: " <<
        (leftover > 0 ? leftover : 0) << endl;
    cout << "empty floor area: " <<
        (leftover < 0 ? -leftover : 0) << endl;

    return 0;
}
