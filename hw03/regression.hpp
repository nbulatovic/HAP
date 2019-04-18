#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <numeric>
#include <typeinfo>
#include <cmath>
#include <functional>

auto sq = [](auto const x){return x*x;};
auto average = [&](auto const& x, double const& size) {return std::accumulate( x.begin(), x.end(), 0.0)/size;};
auto check_size = [&](auto const& x, auto const& y)
{
    const size_t x_size = x.size();
    const size_t y_size = y.size();

    if(x_size != y_size) {std::cout<< "x_size != y_size, exit"; std::exit(EXIT_FAILURE);}
                                            
    return static_cast<double>(x_size);
};

template <typename T>
auto regression(const T& x, const T& y)
{
    
    const double len = check_size(x,y);
    double numerator = 0.0;
    double denominator = 0.0;
    double r2_denominator = 0.0;

    const double x_avg = average(x, len);
    const double y_avg = average(y, len);


    numerator = std::inner_product (x.begin(),
                    x.end(),
                    y.begin(),
                    0.0,
                    std::plus<double>(),
                    [x_avg,y_avg](auto const x, auto const y){return (x-x_avg)*(y-y_avg);});

    denominator = std::accumulate(  x.begin(),
                                    x.end(),
                                    0.0,
                                    [x_avg](auto const a, auto const x){ return a + sq(x-x_avg);});
    
    
    r2_denominator = std::sqrt(std::accumulate(x.begin(),
                        x.end(),
                        0.0,
                        [x_avg](auto a, auto const x){double diff = x-x_avg; return a+diff*diff;})
                    *
                    std::accumulate(y.begin(),
                        y.end(),
                        0.0,
                        [y_avg](auto a, auto const x){double diff = x-y_avg; return a+diff*diff;}));

    const double m = numerator/denominator;
    const double b = y_avg-m*x_avg;
    const double r2 = numerator/r2_denominator;

    std::array<double,3> result = {m,b,r2};        
    return result;
}