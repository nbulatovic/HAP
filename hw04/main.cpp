#include "vector2.hpp"

void Vector2dTest()
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
        if(std::abs(u.x - 13.29) > 1e-7 || std::abs(u.y - 10.6) > 1e-7){ Error("+= operator test"); }
        u -= v;
        if(std::abs(u.x - 3.14) > 1e-7 || std::abs(u.y - 9.6) > 1e-7){ Error("-= operator test"); }
        u *= 5.0;
        if(std::abs(u.x - 5.0*3.14) > 1e-7 || std::abs(u.y - 9.6*5) > 1e-7){ Error("*= operator test"); }
        u /= 0.0;
        if(std::abs(u.x - 5.0*3.14) > 1e-7 || std::abs(u.y - 9.6*5) > 1e-7){ Error("/= operator (division by zero) test"); }
        u /= 5.0;
        if(std::abs(u.x - 3.14) > 1e-7 || std::abs(u.y - 9.6) > 1e-7){ Error("/= operator test"); }
    }
    //Aricmetic operator test
    {
    Vector2d<double> u = {3.14, 9.6};
    Vector2d<double> v = {10.15, 1.0};
    Vector2d<double> w;

    w = u+v; 
    if(std::abs(w.x - 13.29) > 1e-7 || std::abs(w.y - 10.6) > 1e-7){ Error("+ operator test"); }
    w = u-v; 
    if(std::abs(w.x - (3.14-10.15) > 1e-7 || std::abs(w.y - (9.6-1.0)) > 1e-7)){ Error("- operator test"); }
    w = 5.0*u;
    if(std::abs(w.x - (3.14*5.0) > 1e-7 || std::abs(w.y - (9.6*5.0)) > 1e-7)){ Error("* (scalar*vec) operator test"); }
    w = u*5.0;
    if(std::abs(w.x - (3.14*5.0) > 1e-7 || std::abs(w.y - (9.6*5.0)) > 1e-7)){ Error("* (vec*scalar) operator test"); }
    w = u/0.0;
    if(std::abs(w.x - 3.14 > 1e-7 || std::abs(w.y - 9.6) > 1e-7)){ Error("/ (zero division) operator test"); }
    w = v/5.0;
    if(std::abs(w.x - (10.15/5.0) > 1e-7 || std::abs(w.y - (1.0/5.0)) > 1e-7)){ Error("/ operator test"); }
    }
    //Miscellaneous operator test
    {
        Vector2d<double> u = {3.14, 9.6};
        Vector2d<double> v = {10.15, 1.0};
        double result;

        result = dot(u,v);
        if(result - (3.14*10.15+9.6*1.0) > 1e-7){Error("Dot product test");}
        result = sqlength(u);
        if(result - (sq(3.14)+sq(9.6)) > 1e-7){Error("Square length test");}
        result = length(u);
        if(result - (std::sqrt(sq(3.14)+sq(9.6))) > 1e-7){Error("Length test");}
        v = normalize(u);
        if(length(v) - 1.0 > 1e-7){Error("Normalize test");}
    }
    std::cout << "All tests are successful!\n";
}


int main(int, char**) {
    
    Vector2dTest();


    return 0;
}
