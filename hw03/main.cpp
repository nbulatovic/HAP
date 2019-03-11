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
                                             
        return x_size;
    };

    template <typename T, typename F>
    auto regression(T const& x, F const& y)
    {
        
        size_t size = check_size(x,y);
        std::vector<double> numerator(size);
        std::vector<double> denominator(size);
        std::vector<std::array<double,5>> results(size);

        const double len = static_cast<double>(size);

        const double x_avg = average(x, len);
        const double y_avg = average(y, len);


        std::transform (y.begin(),
                        y.end(),
                        x.begin(),
                        numerator.begin(),
                        [y_avg,x_avg](auto const y, auto const x){return (x-x_avg)*(y-y_avg);});

        std::transform (x.begin(),
                        x.end(),
                        denominator.begin(),
                        [x_avg](auto const x){double diff = x-x_avg; return diff*diff;});

        const double sum_numerator = std::accumulate(numerator.begin(), numerator.end(), 0.0);
        const double sum_denominator = std::accumulate(denominator.begin(), denominator.end(), 0.0);

        const double m = sum_numerator/sum_denominator;
        const double b = y_avg - m*x_avg;

        std::vector<double> xy(size);
        std::transform (y.begin(),
                        y.end(),
                        x.begin(),
                        xy.begin(),
                        std::multiplies<double>() );
        const double xy_avg = average(xy,len);

    
        std::vector<double> x2(size);
        std::transform (x.begin(),
                        x.end(),
                        x.begin(),
                        x2.begin(),
                        std::multiplies<double>() );
        const double x2_avg = average(x2,len);

        std::vector<double> y2(size);
        std::transform (y.begin(),
                        y.end(),
                        y.begin(),
                        y2.begin(),
                        std::multiplies<double>() );
        const double y2_avg = average(y2,len);

        const double r = (xy_avg-x_avg*y_avg)/(std::sqrt((x2_avg-(x_avg*x_avg))*(y2_avg-(y_avg*y_avg))));


        std::array<double,3> result = {m, b, r*r};

        return result;
    }

    void test()
    {
        std::vector<int> y = {651, 762, 858, 1063,1190,1298,1421,1440,1519};
        std::vector<int> x = {23,26,30,34,43,48,52,57,58};

        std::array<double,3> res = regression(x,y);

        double exact_m = 23.42;
        double exact_b = 167.68;
        double exact_r2 = 0.9767;

        double m = res[0];
        double b = res[1];
        double r2= res[2];
        std::cout<<"TEST FROM https://www.displayr.com/what-is-linear-regression\n";
        std::cout <<  "diff_m: " << m-exact_m << "\ndiff_b: " << b-exact_b << "\ndiff_r2: " << r2-exact_r2;
    }
    int main(int, char**) {

     
        std::vector<double> x = {1.0, 2.0};
        std::vector<double> y = {1.0, 2.0};
        test();
    }
