#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Shape {
public:
    virtual void move(double x, double y) = 0;
    virtual double perimeter() = 0;
    virtual double area() = 0;
    virtual bool contains(double x, double y) = 0;
};

class Point : public Shape {
private:
    double x, y;

public:
    Point(double _x, double _y) : x(_x), y(_y) {
        cout << "Point added at (" << getX() << ", " << getY() << ")" << endl;
    }

    double getX() const {
        return x;
    }
    double getY() const {
        return y;
    }
    void setX(double _x) {
        this->x = _x;
    }
    void setY(double _y) {
        this->y = _y;
    }

    void move(double newX, double newY) override {
        setX(newX);
        setY(newY);
        cout << "Point moved to (" << getX() << ", " << getY() << ")" << endl;
    }

    double perimeter() override {
        return 0;
    }

    double area() override {
        return 0;
    }

    bool contains(double x, double y) override {
        return (getX() == x && getY() == y);
    }

    virtual ~Point() {
        cout << "Point at (" << getX() << ", " << getY() << ") removed" << endl;
    }
};

class Ellipse : public Point {
private:
    double directA, directB;

public:
    Ellipse(double _x, double _y, double _directA, double _directB) : Point(_x, _y), directA(_directA), directB(_directB) {
        cout << "Ellipse added at (" << getX() << ", " << getY() << ") with axes directA = " << getDirectA() << ", directB = " << getDirectB() << endl;
    }

    double getDirectA() const {
        return directA;
    }

    double getDirectB() const {
        return directB;
    }

    void setDirectA(double _directA) {
        this->directA = _directA;
    }

    void setDirectB(double _directB) {
        this->directB = _directB;
    }

    void move(double newX, double newY) override {
        setX(newX);
        setY(newY);
        cout << "Ellipse moved to (" << getX() << ", " << getY() << ")" << endl;
    }

    double perimeter() override {
        return M_PI * (3 * (getDirectA() + getDirectB()) - sqrt((3 * getDirectA() + getDirectB()) * (getDirectA() + 3 * getDirectB())));
    }

    double area() override {
        return M_PI * getDirectA() * getDirectB();
    }

    bool contains(double x, double y) override {
        double dx = (x - this->getX()) / getDirectA();
        double dy = (y - this->getY()) / getDirectB();
        return (dx * dx + dy * dy) <= 1;
    }

    ~Ellipse() override {
        cout << "Ellipse at (" << getX() << ", " << getY() << ") with axes directA = " << getDirectA() << ", directB = " << getDirectB() << " removed" << endl;
    }
};

class Circle : public Ellipse {
public:
    Circle(double _x, double _y, double _r) : Ellipse(_x, _y, _r, _r) {
        cout << "Circle added at (" << getX() << ", " << getY() << ") with radius " << getDirectA() << endl;
    }

    double perimeter() override {
        return 2 * M_PI * getDirectA();
    }

    double area() override {
        return M_PI * getDirectA() * getDirectA();
    }

    bool contains(double x, double y) override {
        // Проверка, содержится ли точка внутри окружности
        double dx = x - getX();
        double dy = y - getY();
        double distance = sqrt(dx * dx + dy * dy);
        return distance <= getDirectA();
    }

    ~Circle() override {}
};

class LineSegment : public Point {
private:
    double endX, endY;

public:
    LineSegment(double _startX, double _startY, double _endX, double _endY) : Point(_startX, _startY), endX(_endX), endY(_endY) {
        cout << "Line segment added from (" << getX() << ", " << getY() << ") to (" << getEndX() << ", " << getEndY() << ")" << endl;
    }

    double getEndX() const {
        return endX;
    }

    double getEndY() const {
        return endY;
    }

    void setEndX(double endX) {
        this->endX = endX;
    }

    void setEndY(double endY) {
        this->endY = endY;
    }

    void move(double newX, double newY) override {
        double deltaX = newX - getX();
        double deltaY = newY - getY();
        setX(getX()+deltaX);
        setY(getY()+deltaX);
        setEndY(getEndX() + deltaX);
        setEndY(getEndY() + deltaY);
        cout << "Line segment moved to (" << getX() << ", " << getY() << ") and (" << getEndX() << ", " << getEndY() << ")" << endl;
    }

    double perimeter() override {
        return sqrt(pow(getEndX() - getX(), 2) + pow(getEndY() - getY(), 2));
    }

    double area() override {
        return 0;
    }

    bool contains(double x, double y) override {
        // Check if the point is collinear with the line segment and within the bounding box of the segment
        double minX = min(getX(), getEndX());
        double maxX = max(getX(), getEndX());
        double minY = min(getY(), getEndY());
        double maxY = max(getY(), getEndY());

        if (x < minX || x > maxX || y < minY || y > maxY)
            return false;

        // Check if the point is on the line defined by the segment
        return ((y - getY()) * (getEndX() - getX()) == (getEndY() - getY()) * (x - getX()));
    }

    ~LineSegment() override {
        cout << "Line segment from (" << getX() << ", " << getY() << ") to (" << getEndX() << ", " << getEndY() << ") removed" << endl;
    }
};


#include <vector>

class Polyline : public LineSegment {
protected:
    vector<Point> points;

    void removeLastPoint() {
        if (!points.empty()) {
            points.pop_back();
            cout << "Last point removed from Polyline" << endl;
        } else {
            cout << "Polyline is empty. Cannot remove point." << endl;
        }
    }

public:
    Polyline(double startX, double startY, double endX, double endY) : LineSegment(startX, startY, endX, endY) {}

    void addPoint(double _x, double _y) {
        points.emplace_back(_x, _y);
        cout << "Point added to Polyline at (" << _x << ", " << _y << ")" << endl;
    }

    void move(double newX, double newY) override {
        double deltaX = newX - getX();
        double deltaY = newY - getY();
        setX(getX() +deltaX);
        setY(getY() + deltaY);
        setEndX(getEndX()+ deltaX);
        setEndY(getEndY() + deltaY);
        for (auto &point : points) {
            point.move(point.getX() + deltaX, point.getY() + deltaY);
        }
        cout << "Polyline moved to (" << getX() << ", " << getY() << ") and (" << getEndX() << ", " << getEndY() << ")" << endl;
    }

    double perimeter() override {
        double totalPerimeter = LineSegment::perimeter();
        for (size_t i = 0; i < points.size() - 1; ++i) {
            totalPerimeter += sqrt(pow(points[i + 1].getX() - points[i].getX(), 2) + pow(points[i + 1].getY() - points[i].getY(), 2));
        }
        return totalPerimeter;
    }

    double area() override {
        return 0;
    }

    bool contains(double x, double y) override {
        // Check if the point is within any of the line segments forming the polyline
        if (LineSegment::contains(x, y)) {
            return true;
        }
        for (size_t i = 0; i < points.size() - 1; ++i) {
            if (LineSegment(points[i].getX(), points[i].getY(), points[i + 1].getX(), points[i + 1].getY()).contains(x, y)) {
                return true;
            }
        }
        return false;
    }

    ~Polyline() override {
        for (auto &point : points) {
            removeLastPoint();
        }
    }
};

class Rectangle : public Polyline {
public:
    Rectangle()=default;
    Rectangle(double x1, double y1, double x2, double y2) : Polyline(x1, y1, x2, y1) {
        addPoint(x2, y2);
        addPoint(x1, y2);
        addPoint(x1, y1);
    }

    void move(double newX, double newY) override {

        double deltaX = newX - getX();
        double deltaY = newY - getY();
        setX(getX() +deltaX);
        setY(getY() + deltaY);
        setEndX(getEndX()+ deltaX);
        setEndY(getEndY() + deltaY);
        for (auto &point : points) {
            point.move(point.getX() + deltaX, point.getY() + deltaY);
        }

        cout << "Rectangle moved to (" << getX() << ", " << getY() << ") and (" << getEndX() << ", " << getEndY() << ")" << endl;
    }

    double perimeter() override {
        double totalPerimeter = Polyline::perimeter();
        // Последняя точка является начальной точкой, ее не нужно учитывать в периметре
        totalPerimeter -= LineSegment(getX(), getY(), points.back().getX(), points.back().getY()).perimeter();
        return totalPerimeter;
    }

    double area() override {
        // Площадь прямоугольника можно найти как произведение его ширины на высоту
        double width = abs(getEndX() - getX());
        double height = abs(getEndY() - getY());
        return width * height;
    }

    bool contains(double x, double y) override {
        // Проверяем, лежит ли точка внутри или на границе прямоугольника
        return (x >= this->getX() && x <= getEndX() && y >= this->getX() && y <= getEndY());
    }

    ~Rectangle() override {

    }
};

class Square : public Rectangle {
public:
    Square(double x, double y, double sideLength) : Rectangle(x, y, x + sideLength, y + sideLength) {}

    void move(double newX, double newY) override {
        double deltaX = newX - getX();
        double deltaY = newY - getY();
        setX(getX() +deltaX);
        setY(getY() + deltaY);
        setEndX(getEndX()+ deltaX);
        setEndY(getEndY() + deltaY);
        for (auto &point : points) {
            point.move(point.getX() + deltaX, point.getY() + deltaY);
        }
        cout << "Square moved to (" << getX() << ", " << getY() << ") and (" << getEndX() << ", " << getEndY() << ")" << endl;
    }

    double perimeter() override {
        // Периметр квадрата равен четырем удвоенным длинам его сторон
        return 4 * ( getEndX() - getX());
    }

    double area() override {
        // Площадь квадрата равна квадрату длины его стороны
        double sideLength = getEndX() - getX();
        return sideLength * sideLength;
    }

    bool contains(double x, double y) override {
        // Проверяем, лежит ли точка внутри или на границе квадрата
        return Rectangle::contains(x,y);
    }

    ~Square() override {}
};



class Rhombus : public Polyline {
private:
    double diagonal1, diagonal2; // Lengths of the diagonals

public:
    Rhombus(double startX, double startY, double diagonal1, double diagonal2) : Polyline(startX, startY, startX + diagonal1, startY) {
        setDiagonal1(diagonal1);
        setDiagonal2(diagonal2);
        // Add other two points
        addPoint(startX + diagonal1 / 2, startY + diagonal2 / 2);
        addPoint(startX, startY + diagonal2);
    }

    double getDiagonal1() const {
        return diagonal1;
    }

    void setDiagonal1(double _diagonal1) {
        this->diagonal1 = _diagonal1;
    }

    double getDiagonal2() const {
        return diagonal2;
    }

    void setDiagonal2(double _diagonal2) {
        this->diagonal2 = _diagonal2;
    }

    void move(double newX, double newY) override {
        double deltaX = newX - getX();
        double deltaY = newY - getY();
        setX(getX() +deltaX);
        setY(getY() + deltaY);
        setEndX(getEndX()+ deltaX);
        setEndY(getEndY() + deltaY);
        for (auto &point : points) {
            point.move(point.getX() + deltaX, point.getY() + deltaY);
        }
        cout << "Rhombus moved to (" << getX() << ", " << getY() << ") and (" << getEndX() << ", " << getEndY() << ")" << endl;
    }

    double perimeter() override {
        return 4 * sqrt(pow(getDiagonal1() / 2, 2) + pow(getDiagonal2() / 2, 2));
    }

    double area() override {
        return getDiagonal1() * getDiagonal2() / 2;
    }

    bool contains(double x, double y) override {
        // Check if the point is inside the bounding box formed by the rhombus
        if (x < getX() || x > getEndX() || y < getY()|| y > getEndY())
            return false;

        // Check if the point is inside the rhombus using its diagonal equations
        double dx1 = x - getX();
        double dy1 = y - getY();
        double dx2 = x - (getX() + getDiagonal1());
        double dy2 = y - (getY() + getDiagonal2());
        double dot1 = dx1 * (getEndX() - getX()) + dy1 * (getEndY() - getY());
        double dot2 = dx2 * (-getDiagonal1()) + dy2 * (-getDiagonal2());
        return dot1 >= 0 && dot2 >= 0;
    }

};


int main() {
    Point p(1, 2);
    p.move(3, 4);
    cout << "Contains (3, 4): " << p.contains(3, 4) << endl;

    Circle c(5, 5, 3);

    cout << "Perimeter: " << c.perimeter() << endl;
    cout << "Area: " << c.area() << endl;
    cout << "Contains (7, 5): " << c.contains(7, 5) << endl;

    Ellipse e(0, 0, 3, 5);

    cout << "Perimeter: " << e.perimeter() << endl;
    cout << "Area: " << e.area() << endl;
    cout << "Contains (1, 1): " << e.contains(1, 1) << endl;

    LineSegment l(0, 0, 3, 4);
    cout << "Length: " << l.perimeter() << endl;
    cout << "Contains (1.5, 2): " << l.contains(1.5, 2) << endl;

    vector<Point> polylinePoints = { Point(0, 0), Point(1, 1), Point(2, 0) };

    return 0;
}
