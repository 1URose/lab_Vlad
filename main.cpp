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
        magnitude = calculatingModule();
        phase = calculatingArgument();
    }
    void updateRectangular() {
        real = magnitude * cos(phase);
        imaginary = magnitude * sin(phase);
    }

public:
    Complex() = default;
    Complex(double real_part, double imaginary_part) : real(real_part), imaginary(imaginary_part) {
        updatePolar();
    }
    Complex(const Complex& other) : real(other.real), imaginary(other.imaginary), magnitude(other.magnitude), phase(other.phase) {}
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imaginary = other.imaginary;
            magnitude = other.magnitude;
            phase = other.phase;
        }
        return *this;
    }


    ~Complex() = default;

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


    double calculatingModule() const{
        return sqrt(real * real + imaginary * imaginary);
    }
    double calculatingArgument() const{
        return atan2(imaginary, real);
    }
    Complex getAdjoined() const {
        return Complex(real, -imaginary);
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
    Complex operator~() const{
        return this->getAdjoined();
    }
    Complex operator-(){
        this->real *= -1;
        this->imaginary *= -1;
        updatePolar();
        return *this;
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    Complex operator*(const Complex& other) const {
        double real_part = real * other.real - imaginary * other.imaginary;
        double imaginary_part = real * other.imaginary + imaginary * other.real;
        return Complex(real_part, imaginary_part);
    }
    Complex operator/(const Complex& other) const {
        if(other.isNull()){
            return *this;
        }
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double real_part = (real * other.real + imaginary * other.imaginary) / denominator;
        double imaginary_part = (imaginary * other.real - real * other.imaginary) / denominator;
        return Complex(real_part, imaginary_part);
    }

    Complex& operator+=(const Complex& other) {
        real += other.real;
        imaginary += other.imaginary;
        updatePolar();
        return *this;
    }
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imaginary -= other.imaginary;
        updatePolar();
        return *this;
    }
    Complex& operator*=(const Complex& other) {
        double real_part = real * other.real - imaginary * other.imaginary;
        double imaginary_part = real * other.imaginary + imaginary * other.real;
        real = real_part;
        imaginary = imaginary_part;
        updatePolar();
        return *this;
    }
    Complex& operator/=(const Complex& other) {
        if(other.isNull()){
            return *this;
        }
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double new_real = (real * other.real + imaginary * other.imaginary) / denominator;
        double new_imaginary = (imaginary * other.real - real * other.imaginary) / denominator;
        real = new_real;
        imaginary = new_imaginary;
        updatePolar();
        return *this;
    }


    Complex operator=(double value){
        Complex new_complex(value, 0);
        *this = new_complex;
        return *this;
    }
    Complex operator+(double value) const{
        return Complex(real + value, imaginary);
    }
    Complex operator+=(double value){
        real += value;
        magnitude += value;
        return *this;
    }

    bool isNull() const{
        if(real == 0 and imaginary == 0){
            cout << "it cannot be divided by a number of the form 0+i*0\n\n";
            return true;
        }
        return false;
    }


    friend ostream& operator<< (ostream &out, const Complex& complex)
    {
        out << "Rectangular: "<< complex.getReal() << " + i * (" << complex.getImaginary() << ")\n"
            "Polar:" << complex.getMagnitude() << " * e^(i * (" << complex.getPhase() << "))\n\n";
        return out;
    }
    friend istream& operator >> (std::istream& in, Complex &complex)
    {
        double real_part, imaginary_part;
        in >> real_part >> imaginary_part;
        complex.setRectangular(real_part, imaginary_part);
        return  in;
    }
};


int main() {
    // Пример использования класса
    Complex z5{};

    z5 = 1.2232;
    cout << z5;

}