#include "vector2.hpp"


int main(int, char**) {
    
    Vector2d<double> v1{}, v2{};
    double lambda = 5.0;
    
    std::cout <<"Enter vector 1:\n";
    std::cin >> v1;
    std::cout <<"Enter vector 2:\n";
    std::cin >> v2;

    std::cout<<"v1:"<<v1;
    std::cout<<"v2:"<<v2;
    std::cout<<"v1+v2:"<<v1+v2;
    std::cout<<"v1*5.0:"<<v1*lambda;
    std::cout<<"5.0*v1:"<<lambda*v1;
    std::cout<<"v1/5.0:"<<v1/lambda;
    std::cout<<"v1/0.0:"<<v1/0.0;
    std::cout<<"v1*v2:"<<dot(v1,v2) << std::endl;
    std::cout<<"len v1:"<<lenght(v1)<< std::endl;
    std::cout<<"sqlen v1:"<<sqlenght(v1)<< std::endl;
    std::cout<<"normalized v2:"<<normalize(v2)<< std::endl;
    std::cout<<"len of normalized v2:"<<lenght(normalize(v2))<< std::endl;

    v1+=v2;
    std::cout<<"v1+=v2:"<<v1;
    v1-=v2;
    std::cout<<"v1-=v2:"<<v1;
    v1*=10.0;
    std::cout<<"v1*=10.0:"<<v1;
    v1/=0.0;
    v1/=10.0;
    std::cout<<"v1/=10.0:"<<v1;






    return 0;
}
