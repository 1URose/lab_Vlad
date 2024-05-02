#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    double real;
    double imaginary;
    double magnitude;
    double phase;

    void updatePolar() {
        magnitude = sqrt(real * real + imaginary * imaginary);
        phase = atan2(imaginary, real);
    }

    void updateRectangular() {
        real = magnitude * cos(phase);
        imaginary = magnitude * sin(phase);
    }

public:
    // Конструктор
    Complex(double real_part, double imaginary_part) {
        real = real_part;
        imaginary = imaginary_part;
        updatePolar();
    }

    // Методы для получения значений
    double getReal() const {
        return real;
    }

    double getImaginary() const {
        return imaginary;
    }

    double getMagnitude() const {
        return magnitude;
    }

    double getPhase() const {
        return phase;
    }

    // Методы для установки значений
    void setRectangular(double real_part, double imaginary_part) {
        real = real_part;
        imaginary = imaginary_part;
        updatePolar();
    }

    void setPolar(double magnitude_val, double phase_val) {
        magnitude = magnitude_val;
        phase = phase_val;
        updateRectangular();
    }

    // Операции
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    Complex operator*(const Complex& other) const {
        double new_magnitude = magnitude * other.magnitude;
        double new_phase = phase + other.phase;
        return Complex(new_magnitude * cos(new_phase), new_magnitude * sin(new_phase));
    }

    Complex operator/(const Complex& other) const {
        double new_magnitude = magnitude / other.magnitude;
        double new_phase = phase - other.phase;
        return Complex(new_magnitude * cos(new_phase), new_magnitude * sin(new_phase));
    }

    friend ostream& operator<< (ostream &out, const Complex &complex)
    {
        out << "Rectangular: " << complex.getReal() << " + " << complex.getImaginary() << "*i,\n"
            "Polar:" << complex.getMagnitude() << " * e^(" << complex.getPhase() << "*i)\n";
        return out;
    }
};


int main() {
    // Пример использования класса
    Complex z1(3, -4); // Декартовы координаты
    std::cout << z1;

    Complex z2(2, -1); // Декартовы координаты
    std::cout << "z2: Rectangular - " << z2.getReal() << " + " << z2.getImaginary() << "i, Polar - "
              << z2.getMagnitude() << " * e^(i" << z2.getPhase() << ")\n";

    Complex sum = z1 + z2;
    std::cout << "Sum: Rectangular - " << sum.getReal() << " + " << sum.getImaginary() << "i, Polar - "
              << sum.getMagnitude() << " * e^(i" << sum.getPhase() << ")\n";
}