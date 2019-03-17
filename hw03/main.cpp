    #include <iostream>
    #include <algorithm>
    #include <vector>
    #include <array>
    #include <numeric>
    #include <typeinfo>
    #include <cmath>
    #include <functional>

    auto average = [&](auto x, double size) {return std::accumulate( x.begin(), x.end(), 0.0)/size;};
    auto check_size = [&](auto const x, auto const y)
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

        denominator = std::inner_product (x.begin(),
                        x.end(),
                        x.begin(),
                        0.0,
                        std::plus<double>(),
                        [x_avg](auto const x, auto const y){return (x-x_avg)*(y-x_avg);});

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

    void test()
    {
        std::vector<int> y = {651, 762, 858, 1063,1190,1298,1421,1440,1519};
        std::vector<int> x = {23,26,30,34,43,48,52,57,58};

        std::array<double,3> res = regression(x,y);

        

        double exact_m = 61.272;
        double exact_b = -39.062;
        double exact_r2 = 0.9945;

        double m = res[0];
        double b = res[1];
        double r2= res[2];

        
        std::cout<<"TEST FROM https://en.wikipedia.org/wiki/Simple_linear_regression#Fitting_the_regression_line\n";
        std::cout <<  "m: " << m << "\nb: " << b << "\nr2: " << r2 << "\n";
        std::cout <<  "diff_m: " << m-exact_m << "\ndiff_b: " << b-exact_b << "\ndiff_r2: " << r2-exact_r2 << "\n";
    }

    void test2()
    {
        std::vector<double> y = {52.21,53.12,54.48,55.84,57.20,58.57,59.93,61.29,63.11,64.47,66.28,68.10,69.92,72.19,74.46};
        std::vector<double> x = {1.47,1.5,1.52,1.55,1.57,1.60,1.63, 1.65,1.68,1.7,1.73,1.75,1.78,1.80,1.83};

        std::array<double,3> res = regression(x,y);

        

        double exact_m = 23.42;
        double exact_b = 167.68;
        double exact_r2 = 0.9767;

        double m = res[0];
        double b = res[1];
        double r2= res[2];

        
        std::cout<<"TEST FROM https://www.displayr.com/what-is-linear-regression\n";
        std::cout <<  "m: " << m << "\nb: " << b << "\nr2: " << r2 << "\n";
        std::cout <<  "diff_m: " << m-exact_m << "\ndiff_b: " << b-exact_b << "\ndiff_r2: " << r2-exact_r2 ;
    }

    int main(int, char**) {

     
        std::vector<double> x = {1.0, 2.0};
        std::vector<double> y = {1.0, 2.0};
        test();
        test2();
    }
