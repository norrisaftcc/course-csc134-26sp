// Rectangle.h

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    private:
     double width;
     double length;

    public:
     double getWidth() const {
        return width;
     }
     double getLength() const {
        return length;
     }
     double getArea() const {
        // always calculated fresh
        double area = length * width;
        return area; 
     }
     void setWidth(double w) {
        width = w;
     }
     void setLength(double l) {
        length = l;
     }
     // maybe add drawRectangle() later





};





#endif // RECTANGLE_H