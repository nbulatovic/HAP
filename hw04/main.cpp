#include "vector2.hpp"

void Vector2dTest(double precision)
{
    auto Error = [](auto str){ std::cout << "vector2.hpp error in: " << str << "\n"; std::exit(-1); };
    
    //Initialization test
    {
        Vector2d<double> u = {3.14, 9.6};
        if(u.x != 3.14 || u.y != 9.6){ Error("initializer test"); }
    }
    //Assignment operator test
    {
        Vector2d<double> u = {3.14, 9.6};
        Vector2d<double> v = {10.15, 1.0};

        u += v;
        if(std::abs(u.x - 13.29) > precision || std::abs(u.y - 10.6) > precision){ Error("+= operator test"); }
        u -= v;
        if(std::abs(u.x - 3.14) > precision || std::abs(u.y - 9.6) > precision){ Error("-= operator test"); }
        u *= 5.0;
        if(std::abs(u.x - 15.7) > precision || std::abs(u.y - 48.0) > precision){ Error("*= operator test"); }
        std::cout<< "Expected error: Cannot divide by zero\n";
        u /= 0.0;
        if(std::abs(u.x - 15.7) > precision || std::abs(u.y - 48.0) > precision){ Error("/= operator (division by zero) test"); }
        u /= 5.0;
        if(std::abs(u.x - 3.14) > precision || std::abs(u.y - 9.6) > precision){ Error("/= operator test"); }
    }
    //Aritmetic operator test
    {
    Vector2d<double> u = {3.14, 9.6};
    Vector2d<double> v = {10.15, 1.0};
    Vector2d<double> w;

    w = u+v; 
    if(std::abs(w.x - 13.29) > precision || std::abs(w.y - 10.6) > precision){ Error("+ operator test"); }
    w = u-v; 
    if(std::abs(w.x - (-7.01)) > precision || std::abs(w.y - 8.6) > precision){ Error("- operator test"); }
    w = 5.0*u;
    if(std::abs(w.x - 15.7 > precision || std::abs(w.y - 48.0) > precision)){ Error("* (scalar*vec) operator test"); }
    w = u*5.0;
    if(std::abs(w.x - 15.7) > precision || std::abs(w.y - 48.0) > precision){ Error("* (vec*scalar) operator test"); }
    std::cout<< "Expected error: Cannot divide by zero\n";
    w = u/0.0;
    if(std::abs(w.x - 3.14) > precision || std::abs(w.y - 9.6) > precision){ Error("/ (zero division) operator test"); }
    w = v/5.0;
    if(std::abs(w.x - 2.03 )> precision || std::abs(w.y - 0.2) > precision){ Error("/ operator test"); }
    }
    //Miscellaneous operator test
    {
        Vector2d<double> u = {3.14, 9.6};
        Vector2d<double> v = {10.15, 1.0};
        double result;

        result = dot(u,v);
        if(std::abs(result - 41.471) > precision){Error("Dot product test");}
        result = sqlength(u);
        if(std::abs(result - 102.0196) > precision){Error("Square length test");}
        result = length(u);
        if(std::abs(result - 10.1004752363441) > precision){Error("Length test");}
        v = normalize(u);
        if(std::abs(length(v) - 1.0) > precision){Error("Normalize test");}
    }
    std::cout << "All tests are successful!\n";
}


int main(int, char**) {
    
    Vector2dTest(1e-13);


    return 0;
}
