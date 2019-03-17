#include <iostream>
#include <string>
#include <cmath>

template<typename T>
struct Vector2d
{
    T x,y;

    auto operator+=( Vector2d<T> const& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    };

    auto operator-=( Vector2d<T> const& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    };

    auto operator*=( T lambda)
    {
        x *= lambda;
        y *= lambda;
        return *this;
    };

    auto operator/=( T lambda)
    {   
        if(lambda != static_cast<T>(0))
        {
            x /= lambda;
            y /= lambda;
        }
        else {std::cout << "zero division error\n";}
        return *this;
    };

};
template<typename T>
auto operator+( Vector2d<T> const& a, Vector2d<T> const& b)
{
    return Vector2d<T>{ a.x+ b.x, a.y+ b.y};
};

template<typename T>
auto operator*( Vector2d<T> const& a, const T& lambda)
{
    return Vector2d<T>{ lambda*a.x, lambda*a.y};
};
template<typename T>
auto operator*( const T& lambda,Vector2d<T> const& a)
{
    return Vector2d<T>{ lambda*a.x, lambda*a.y};
};

template<typename T>
auto operator/( Vector2d<T> const& a, const T lambda)
{
    if(lambda != static_cast<T>(0)) {return Vector2d<T>{ a.x/lambda, a.y/lambda};}
    else {std::cout << "zero division error\n"; return a;}
};

template<typename T>
auto dot(Vector2d<T> const& a, Vector2d<T> const& b)
{
    return a.x*b.x+a.y*b.y;
};

template<typename T>
auto lenght(Vector2d<T> const& a)
{
    return std::sqrt(a.x*a.x+a.y*a.y);
};

template<typename T>
auto sqlenght(Vector2d<T> const& a)
{
    return a.x*a.x+a.y*a.y;
};

template<typename T>
auto normalize(Vector2d<T> const& a)
{   
    double len = lenght(a);
    return Vector2d<T>{a.x/len,a.y/len};
};




template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2d<T> const& v)
{
    o << "(" << v.x << "," << v.y <<")\n";
    return o;
};

template<typename T>
std::istream& operator>>( std::istream& i, Vector2d<T> & v)
{
    i >> v.x;
    i >> v.y;
    return i;
};
