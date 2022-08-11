#include <iostream>
#include <sstream>
#include <exception>
#include <cmath>

using namespace std;

int gcd (int a, int b) 
{
    if (b == 0)
    {
        return a;
    }

    return gcd(b, a%b);
}

class Rational {
public:
  Rational() {
    numerator = 0;
    denominator = 1;
  }

  Rational(int new_numerator, int new_denominator) {
    if (new_denominator == 0)
    {
        throw invalid_argument("Invalid argument");
    }
    else if (new_denominator < 0)
    {
        new_numerator = -new_numerator;
        new_denominator = -new_denominator;
    }

    int nod = gcd(abs(new_numerator), abs(new_denominator));

    numerator = new_numerator/nod;
    denominator = new_denominator/nod;

  }

  int Numerator() const {
    return numerator;
  }
  int Denominator() const {
    return denominator;
  }
private:
    int numerator;
    int denominator;
    
};

Rational operator+ (const Rational& first, const Rational& second) {
   return Rational(first.Numerator()*second.Denominator() + first.Denominator()*second.Numerator(), first.Denominator()*second.Denominator()); 
}

Rational operator- (const Rational& first, const Rational& second) {
    return Rational(first.Numerator()*second.Denominator() - first.Denominator()*second.Numerator(), first.Denominator()*second.Denominator());
}

Rational operator* (const Rational& first, const Rational& second) {
    return Rational(first.Numerator()*second.Numerator(), first.Denominator()*second.Denominator());
}

Rational operator/ (const Rational& first, const Rational& second) {
    if (second.Numerator() == 0)
    {
       throw domain_error("Division by zero");
    }

    return first*Rational(second.Denominator(), second.Numerator());
}

istream& operator>> (istream& stream, Rational& rational) {

    char c;
    int n;
    int d;

    stream >> n >> c >> d;
    rational = Rational(n, d);

    return stream;
}

ostream& operator<< (ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << '/' << rational.Denominator();

    return stream;
}

int main() 
{
    Rational r1;
    Rational r2;

    char c;

    try {
        cin >> r1 >> c >> r2;

        try {

            if (c == '+')
            {
                cout << r1 + r2;
            }
            else if (c == '-')
            {
                cout << r1 - r2;
            }
            else if (c == '*')
            {
                cout << r1 * r2;
            }
            else if (c == '/')
            {
                cout << r1 / r2;
            }

            cout << endl;
        } catch (domain_error& e) {
            cout << e.what() << endl;
        }

    } catch (invalid_argument& e) {
        cout << e.what() << endl;
    }
}
    
