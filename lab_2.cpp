#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class Shape {
public:
    virtual void add() = 0;
    virtual void remove() = 0;
    virtual void move(double x, double y) = 0;
    virtual double perimeter() = 0;
    virtual double area() = 0;
    virtual bool contains(double x, double y) = 0;
    virtual void print() = 0;
};

class Point : public Shape {
protected:
    double x, y;

public:
    Point(double x, double y) : x(x), y(y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    void add() override {
        cout << "Point added at (" << x << ", " << y << ")" << endl;
    }

    void remove() override {
        cout << "Point at (" << x << ", " << y << ") removed" << endl;
    }

    void move(double newX, double newY) override {
        x = newX;
        y = newY;
        cout << "Point moved to (" << x << ", " << y << ")" << endl;
    }

    double perimeter() override {
        return 0;
    }

    double area() override {
        return 0;
    }

    bool contains(double x, double y) override {
        return (this->x == x && this->y == y);
    }

    void print() override {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};

class Circle : public Point {
private:
    double radius;

public:
    Circle(double x, double y, double radius) : Point(x, y), radius(radius) {}

    double perimeter() override {
        return 2 * M_PI * radius;
    }

    double area() override {
        return M_PI * radius * radius;
    }

    bool contains(double x, double y) override {
        return sqrt(pow((x - this->x), 2) + pow((y - this->y), 2)) <= radius;
    }

    void print() override {
        cout << "Circle(center: (" << x << ", " << y << "), radius: " << radius << ")" << endl;
    }
};

class Ellipse : public Point {
private:
    double radiusX, radiusY;

public:
    Ellipse(double x, double y, double radiusX, double radiusY) : Point(x, y), radiusX(radiusX), radiusY(radiusY) {}

    double perimeter() override {
        // Approximation using Ramanujan's formula
        double h = pow((radiusX - radiusY), 2) / pow((radiusX + radiusY), 2);
        return M_PI * (radiusX + radiusY) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
    }

    double area() override {
        return M_PI * radiusX * radiusY;
    }

    bool contains(double x, double y) override {
        return pow((x - this->x) / radiusX, 2) + pow((y - this->y) / radiusY, 2) <= 1;
    }

    void print() override {
        cout << "Ellipse(center: (" << x << ", " << y << "), radiusX: " << radiusX << ", radiusY: " << radiusY << ")" << endl;
    }
};

class LineSegment : public Point {
protected:
    double x2, y2;

public:
    LineSegment(double x1, double y1, double x2, double y2) : Point(x1, y1), x2(x2), y2(y2) {}

    double perimeter() override {
        return sqrt(pow((x2 - x), 2) + pow((y2 - y), 2));
    }

    double area() override {
        return 0;
    }

    bool contains(double x, double y) override {
        double d1 = sqrt(pow((x - this->x), 2) + pow((y - this->y), 2));
        double d2 = sqrt(pow((x - this->x2), 2) + pow((y - this->y2), 2));
        double lineLength = perimeter();
        return fabs((d1 + d2) - lineLength) < 1e-6;
    }

    void print() override {
        cout << "LineSegment((" << x << ", " << y << "), (" << x2 << ", " << y2 << "))" << endl;
    }
};

class Polyline : public Shape {
private:
    vector<Point> points;

public:
    Polyline(const vector<Point>& points) : points(points) {}

    void add() override {
        cout << "Polyline added with points:";
        for (Point point : points) {
            point.print();
        }
    }

    void remove() override {
        cout << "Polyline removed" << endl;
    }

    void move(double x, double y) override {
        for (auto& point : points) {
            point.move(x, y);
        }
        cout << "Polyline moved to new points:" << endl;
        for (Point point : points) {
            point.print();
        }
    }

    double perimeter() override {
        double perimeter = 0;
        for (size_t i = 1; i < points.size(); ++i) {
            perimeter += LineSegment(points[i - 1].getX(), points[i - 1].getY(), points[i].getX(), points[i].getY()).perimeter();
        }
        return perimeter;
    }

    double area() override {
        return 0;
    }

    bool contains(double x, double y) override {
        for (Point point : points) {
            if (point.contains(x, y)) {
                return true;
            }
        }
        return false;
    }

    void print() override {
        cout << "Polyline with points:" << endl;
        for (Point point : points) {
            point.print();
        }
    }
};

// Additional shapes like Triangle, Square, Rectangle, Rhombus can be implemented similarly.

int main() {
    Point p(1, 2);
    p.add();
    p.move(3, 4);
    p.print();
    cout << "Contains (3, 4): " << p.contains(3, 4) << endl;

    Circle c(5, 5, 3);
    c.add();
    c.print();
    cout << "Perimeter: " << c.perimeter() << endl;
    cout << "Area: " << c.area() << endl;
    cout << "Contains (7, 5): " << c.contains(7, 5) << endl;

    Ellipse e(0, 0, 3, 5);
    e.add();
    e.print();
    cout << "Perimeter: " << e.perimeter() << endl;
    cout << "Area: " << e.area() << endl;
    cout << "Contains (1, 1): " << e.contains(1, 1) << endl;

    LineSegment l(0, 0, 3, 4);
    l.add();
    l.print();
    cout << "Length: " << l.perimeter() << endl;
    cout << "Contains (1.5, 2): " << l.contains(1.5, 2) << endl;

    vector<Point> polylinePoints = { Point(0, 0), Point(1, 1), Point(2, 0) };
    Polyline pl(polylinePoints);
    pl.add();
    pl.print();
    cout << "Perimeter: " << pl.perimeter() << endl;
    cout << "Contains (1, 1): " << pl.contains(1, 1) << endl;

    return 0;
}
