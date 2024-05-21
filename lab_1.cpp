#include <iostream>
#include <cmath>

using namespace std;

class Complex {
private:
    double real;
    double imaginary;
    double magnitude;
    double phase;

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
        return ::sqrt(real * real + imaginary * imaginary);
    }
    double getArgument() const{
        return atan2(imaginary, real);
    }
    Complex getAdjoined() const {
        return {real, -imaginary};
    }
    Complex sqrt() const {
        double new_magnitude = ::sqrt(magnitude);
        double new_phase = phase / 2.0;
        return {new_magnitude * cos(new_phase), new_magnitude * sin(new_phase)};
    }
    Complex power(int exponent) const {
        if (exponent == 0) {
            return {1, 0};
        } else if (exponent == 1) {
            return *this;
        } else {
            Complex result = power(exponent / 2);
            result *= result;
            if (exponent % 2 == 1) {
                result *= *this;
            }
            return result;
        }
    }

    Complex operator~() const{
        return this->getAdjoined();
    }
    Complex operator-() const{
        return {-real, -imaginary};
    }
    Complex operator^(int exponent) const {
        return this->power(exponent);
    }

    Complex operator+(const Complex& other) const {
        return {real + other.real, imaginary + other.imaginary};
    }
    Complex operator-(const Complex& other) const {
        return {real - other.real, imaginary - other.imaginary};
    }
    Complex operator*(const Complex& other) const {
        double real_part = real * other.real - imaginary * other.imaginary;
        double imaginary_part = real * other.imaginary + imaginary * other.real;
        return {real_part, imaginary_part};
    }
    Complex operator/(const Complex& other) const {
        if(other.isNull()){
            return *this;
        }
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double real_part = (real * other.real + imaginary * other.imaginary) / denominator;
        double imaginary_part = (imaginary * other.real - real * other.imaginary) / denominator;
        return {real_part, imaginary_part};
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
        return {complex.real + value, complex.imaginary};
    }
    friend Complex operator+(double value, const Complex& complex) {
        return complex + value;
    }
    Complex operator+=(double value){
        real += value;
        updatePolar();
        return *this;
    }

    friend ostream& operator<<(ostream &out, const Complex& complex)
    {
        out << "Rectangular: "<< complex.getReal();
        if(complex.getImaginary() < 0){
            out << " - i * " << -complex.getImaginary() << "\n";
        }
        else if(complex.getImaginary() == 0){
            out << "\n";
        }
        else{
                out << " + i * " << complex.getImaginary() << "\n";
        }

        out << "Polar: " << complex.getMagnitude();
        if(complex.getPhase() < 0){
            out << " * e^(- i * " << -complex.getPhase() << ")\n";
        }
        else if(complex.getPhase() == 0){
            out << "\n";
        }
        else{
            out << " * e^(i * " << complex.getPhase() << ")\n";
        }
        out << "\n";
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
    void updatePolar() {
        magnitude = getModule();
        phase = getArgument();
    }
    ~Complex() = default;
};

int main() {

}