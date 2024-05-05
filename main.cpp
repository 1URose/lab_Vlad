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
        magnitude = getModule();
        phase = getArgument();
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

    double getModule() const{
        return sqrt(real * real + imaginary * imaginary);
    }
    double getArgument() const{
        return atan2(imaginary, real);
    }
    Complex getAdjoined() const {
        return Complex(real, -imaginary);
    }
    Complex getSQRT() const {
        double new_magnitude = sqrt(magnitude);
        double new_phase = phase / 2.0;
        return Complex(new_magnitude * cos(new_phase), new_magnitude * sin(new_phase));
    }
    Complex power(double exponent) const {
        if (exponent == 0) {
            return Complex(1, 0);
        } else if (exponent == 1) {
            return *this;
        } else {
            Complex result = power(exponent / 2);
            result *= result;
            if ((int)exponent % 2 == 1) {
                result *= *this;
            }
            return result;
        }
    }

    Complex operator~() const{
        return this->getAdjoined();
    }
    Complex operator-() const{
        return Complex(-real, -imaginary);
    }
    Complex operator^(int exponent) const {

        return this->power(exponent);
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

    Complex& operator=(double value){
        Complex new_complex(value, 0);
        *this = new_complex;
        return *this;
    }
    friend Complex operator+(const Complex& complex, double value) {
        return Complex(complex.real + value, complex.imaginary);
    }
    friend Complex operator+(double value, const Complex& complex) {
        return complex + value;
    }
    Complex operator+=(double value){
        real += value;
        updatePolar();
        return *this;
    }

    friend ostream& operator<< (ostream &out, const Complex& complex)
    {
        out << "Rectangular: "<< complex.getReal() << " + i * " << complex.getImaginary() << "\n"
            "Polar:" << complex.getMagnitude() << " * e^(i * " << complex.getPhase() << ")\n\n";
        return out;
    }
    friend istream& operator>>(istream& in, Complex& complex) {
        double real_part, imaginary_part;
        in >> real_part >> imaginary_part;
        complex.real = real_part;
        complex.imaginary = imaginary_part;
        complex.updatePolar();
        return in;
    }

    bool isNull() const{
        if(real == 0 and imaginary == 0){
            cout << "it cannot be divided by a number of the form 0+i*0\n\n";
            return true;
        }
        return false;
    }
};


int main() {

}
