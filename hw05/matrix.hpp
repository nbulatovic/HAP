#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>
#include <vector>

namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_Matrix1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_Matrix2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}

inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };
inline auto sq = [](auto const& x){ return x*x  ; };

/*
Mathemathical matrix class:
Assumptions:
Implements a heap allocated mathematical vector
Elements are copyable and need not to be move-aware
No exceptional cases are not handled (yet)
Square matrix
*/

template<typename T>
class Matrix
{
private:
    std::vector<T> data;
    int N;
public:
    
    //Constructors
    Matrix(): data{},N{0}{};
    Matrix( std::initializer_list<T> const& il ) :  data{il}, 
                                                    N{static_cast<int>(std::sqrt(static_cast<int>(data.size())))}{}
    Matrix( Matrix const& ) = default;
    Matrix( Matrix && ) = default;
    

	//Copy and Move assignment operators implemented by the compiler:
    Matrix<T>& operator=(Matrix const&) = default;
    Matrix<T>& operator=(Matrix &&) = default;

    //Iterators
	auto begin(){return data.begin();}
	auto cbegin() const{return data.cbegin();}
	auto end(){return data.end();}
	auto cend() const{return data.cend();}

    //Indexing
    T& operator[]( int i ){ return data[i]; }
    T const& operator[]( int i ) const { return data[i]; }

    T& operator()(int i, int j){ return data[N*i+j]; }
    T const& operator()(int i, int j) const{ return data[N*i+j]; }

    //Other
    int size()const
	{
		return static_cast<int>(data.size());
    }
};


