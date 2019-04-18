#include "regression.hpp"

void error_message()
    {
        std::cout<<"Regression error\n";
        std::cout<<"TEST FROM https://www.displayr.com/what-is-linear-regression\n";
    }

int regression_test()
{
    std::vector<double> y = {52.21,53.12,54.48,55.84,57.20,58.57,59.93,61.29,63.11,64.47,66.28,68.10,69.92,72.19,74.46};
    std::vector<double> x = {1.47,1.5,1.52,1.55,1.57,1.60,1.63, 1.65,1.68,1.7,1.73,1.75,1.78,1.80,1.83};

    std::array<double,3> res = regression(x,y);

    double exact_m = 61.27218654211063;
    double exact_b = -39.061955918843935;
    double exact_r2 = 0.9945837935768896*0.9945837935768896;


    double m = res[0];
    double b = res[1];
    double r2= res[2];

    

    if(std::abs(m-exact_m) > 1e-7){ error_message(); return -1; }
    if(std::abs(b-exact_b) > 1e-7){ error_message(); return -1; }
    if(std::abs(r2-exact_r2) > 1e-2){ error_message(); return -1; }

    return 0;
}

int main(int, char**) 
{

    regression_test();

    std::vector<double> x = {1.0, 2.0};
    std::vector<double> y = {1.0, 2.0};
    std::array<double,3> res = regression(x,y);



    std::cout << "f(x)=" << res[0] <<"x+"<<res[1] << std::endl;
    std::cout << "R2=" << res[2];
    
}
