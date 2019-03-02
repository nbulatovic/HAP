#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm> 

double f(double x, double a){return x*x-a;}
double fprime(double x){return 2*x;}


double sqrt_newton(double num, double x0)
{
    double tolerance = 1e-7;
    double epsilon = 1e-14;
    int maxIterations = 20;
    double x1;
    bool haveWeFoundSolution = false;
    
    for(int i = 1;i <= maxIterations;i++)
    {
        double y = f(x0,num);
        double yprime = fprime(x0);
        
        if(std::abs(yprime) < epsilon) {break;}
        
        x1 = x0 - y/yprime;

        if(std::abs(x1 - x0) <= tolerance * std::abs(x1))
        {
            haveWeFoundSolution = true;
            break;
        }
        x0 = x1;
    }
    if (haveWeFoundSolution){std::cout << "Got solution\n" ;return x1;}
    else {std::cout << "Did not converged\n";return -1;}

} 



int main(int, char**) 
{
    std::cout.precision(16);
    std::cout << sqrt_newton(612, 1);   
}