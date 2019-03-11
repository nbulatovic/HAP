#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm> 

auto f = [](auto x){return x*x - 612.0;};
auto fp = [](auto x){return 2.0*x;};
auto continueiter = [](auto x0, auto x1)
    {
        double tolerance = 1e-7;
        if(std::abs(x1 - x0) <= tolerance * std::abs(x1))
        {
            return false;   
        }
        else
        {
            return true; 
        }
    };


template<typename F, typename P, typename T, typename E>
double Newton(F f, P fprime,T check, E x0)
{
    
    double epsilon = 1e-14;
    int maxIterations = 20;
    double x1 = 0.0;
    
    double y = f(x0);
    double yprime = fprime(x0);
    
    for(int i = 1;i <= maxIterations;i++)
    {
        if(std::abs(yprime) < epsilon) {break;}
        
        x1 = x0 - y/yprime;

        if(check(x0,x1))
        {
            x0 = x1;
            y = f(x0);
            yprime = fprime(x0);
        }
        else {std::cout << "Got solution\n" ;return x1;}
    }
    std::cout << "Didn't get solution\n";
    return -9999;
} 



int main(int, char**) 
{
    double e = 24.738633753705963298928; 
    double sol = Newton(f,fp,continueiter,10.0);
    std::cout.precision(16);
    std::cout << sol << "\t difference: " << sol-e << "\n" ;   
}