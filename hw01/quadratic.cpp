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
        std::cout << "1 solution: " << (-b+std::sqrt(b*b-4*a*c))/(2*a); 
    }
    
    if (D > 0)
    {
        std::cout << "2 solution: " << (-b+std::sqrt(b*b-4*a*c))/(2*a) << "\tand\t" << (-b-std::sqrt(b*b-4*a*c))/(2*a); 
    }
    
    if (D < 0)
    {
        std::cout << "No real solutions ";
    }
} 



int main(int, char**) 
{
    std::cout.precision(16);
    solve(2,0,-1);
    
}