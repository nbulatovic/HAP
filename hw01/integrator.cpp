#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm> 

double integrate(int n, double x0, double x1)
{
    //auto NormalDistribution = [](double x){return (1/std::sqrt(2*3.14))*std::exp(-x*x/2);};
    auto f =  [](double x){return std::cos(x)*std::exp(-x*x);};

    double h = (x1-x0)/n;
    
    /*This attempt wasn't a luckiest choice, because of the unnecessary dynamic allocation (std::accumulate)
    and it went trough the data 2 times.
    
    std::vector<double> f_xj;
    
    for(int j = 1; j < n+2; j++)
    {
        //f_xj.push_back(NormalDistribution(x0+j*h));
        f_xj.push_back(f(x0+j*h));
    }
    double sum  = std::accumulate(f_xj.begin(), f_xj.end(), 0.0);
    */
    double sum = 0;
    
    for(int j = 1; j < n+2; j++)
    {
        //sum += NormalDistribution(x0+j*h);
        sum += f(x0+j*h);
    }
    
    //return 0.5*h*(NormalDistribution(x0)+2*sum+NormalDistribution(x1));
    return 0.5*h*(f(x0)+2*sum+f(x1));
}

void print_difference (int i, double x0, double x1) {
    double exact = 1.34638795680345037669816;
    double integral = integrate(i,x0,x1);
    double diff = exact-integral;
    
    std::cout << "N: " << i << "\tabsolute difference:" <<  diff << "\t\trelative difference:" << diff/exact << "\n";
}


int main(int, char**) {

    int n = 1000;
    double a = -1.0;
    double b = 3.0;
    
    std::cout.precision(16);
    

    std::cout << "integrate cos(x)*exp(-x^2) from " << a <<" to " << b << ": " << integrate(n,a,b) << "\n";
    
    std::vector<int> N = {1,10,50,100,250,500,1000,2000,5000};
    
    for_each ( N.begin(), N.end(), [a,b](double i){print_difference(i,a,b);});
       
    
}