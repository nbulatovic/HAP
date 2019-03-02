#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm> 


void solve(double a, double b, double c)
{
    double D = b*b-4*a*c;
    
    if (D == 0)
    {
        std::cout << "1 solution: " << -b/(2*a)<< "\n"; 
    }
    
    else if (D > 0)
    {
        std::cout << "2 solution: " << (-b+std::sqrt(D))/(2*a) << "\tand\t" << (-b-std::sqrt(D))/(2*a) << "\n"; 
    }
    
    else if (D < 0)
    {
        std::cout << "No real solutions" << "\n";
    }
} 



int main(int, char**) 
{
    std::cout.precision(16);
    solve(2,0,-1);
    solve(2,0,1);
    solve(2,0,0);
    
}