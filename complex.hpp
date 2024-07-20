#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

namespace ariel
{
    class Complex
    {
    private:
        double real;
        double imaginary;

    public:
        Complex(double real = 0.0, double imaginary = 0.0) : real(real), imaginary(imaginary) {}

        friend std::ostream &operator<<(std::ostream &out, const Complex &c) 
        {
            out << c.real << " + " << c.imaginary << "i";
            return out;
        }

        bool operator==(const Complex &other) const
        {
            if(this->imaginary==other.getImaginary()&& this->real==other.getReal()){
                return true;
            }
            return false;
        }

        bool operator!=( const Complex &other) const
        {
            if(*this==other){
                return false;
            }
            return true;
        }

      bool operator>(const Complex& other) const {
        if(*this==other){
            return false;
        }
            return this->real > other.getReal() || (this->real == other.getReal() && this->imaginary > other.getImaginary());
        }

        double getReal() const{
            return this->real;
        }

        double getImaginary()const {
            return this->imaginary;
        }
    };
}
#endif // COMPLEX_HPP
