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
    int dimension;
public:
    
    //Constructors
    Matrix(): data{},N{0},dimension{0}{};
    Matrix(int element, std::initializer_list<T> const& il):    data{il}, 
                                                                dimension{element},
                                                                N{static_cast<int>(data.size())}
    {
        if (N != sq(dimension))
        {
        std::cout<<"Linear size doesn't match with the data size! Default constructor called.\n";
        data = {};
        N = 0;
        dimension = 0;
        }
    }
    Matrix( Matrix const& ) = default;
    Matrix( Matrix && m):   N{std::move(m.N)}, 
                            data{std::move(m.data)},
                            dimension{std::move(m.dimension)}
    {
        if (this != &m)
        {
        m.N = 0;
        m.dimension = 0;
        }
    }
    //Matrix( Matrix && ) = default;
    
    //Iterators
	auto begin(){return data.begin();}
	auto cbegin() const{return data.cbegin();}
	auto end(){return data.end();}
	auto cend() const{return data.cend();}


	//Copy and Move assignment operators:
    Matrix<T>& operator=(Matrix const&) = default;
    Matrix<T>& operator=(Matrix && m)
    {
        if (this != &m)
        {
            data = std::move(m.data);
            N = m.N;
            dimension = m.dimension;

            m.N = 0;
            m.dimension =0;
        }
        return *this;
    }
    //Matrix<T>& operator=(Matrix &&) = default;

    //Indexing
    T& operator[]( int i ){ return data[i]; }
    T const& operator[]( int i ) const { return data[i]; }

    T& operator()(int i, int j){ return data[dimension*i+j]; }
    T const& operator()(int i, int j) const{ return data[dimension*i+j]; }


    //Add assignment operators:
	Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, add);
		return *this;
    }
    //Subtract assignment operators:
	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, sub);
		return *this;
    }
    //Multiplication by scalar:
    Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x * scl;} );
		return *this;
    }
    //Division by scalar:
	Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x / scl;} );
		return *this;
	}
    //Others
    int dim()const
	{
		return dimension;
    }

    int size()const
	{
		return N;
    }

    auto set_to_default()
    {
        data = {};
        N = 0;
        dimension = 0;

        return *this;
    }

    auto set_size(int new_size)
    {
        if(N !=0)
        {
            std::cout<<"Matrix already has a size!" << std::endl;
        }
        else
        {
            data.resize(new_size);
            N = new_size;
        }
        return *this;
    }

    auto set_dim(int new_dim)
    {
        if(dimension !=0)
        {
            std::cout<<"Matrix already has a dimension!" << std::endl;
        }
        else
        {
            dimension = new_dim;
        }
        
        return *this;
    }

    auto set_element(int i, int j, T value)
    {
        data[i*dimension+j] = value;
        return *this;
    }
};

template<typename T>
bool check_size(Matrix<T> const& m1, Matrix<T> const& m2)
{
    if(m1.size() == m2.size() && m1.dim() == m2.dim()) {return true;}
    else    {return false;}
}

template<typename T>
Matrix<T> operator+( Matrix<T>  const& m1, Matrix<T>  const& m2 )
{
    Matrix<T> result;
	if(check_size(m1,m2))
    {
        result.set_size(m1.size());
        detail::transform_Matrix2(m1, m2, result, add);
        result.set_dim(m1.dim());
    }
    return result;
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T> const& m2 )
{
	detail::transform_Matrix2(m1, m2, m1, add );
	return std::move(m1);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>const& m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m2, add ); 
	return std::move(m2);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T> && m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m1, add );
    m2.set_to_default();
	return std::move(m1);
}


template<typename T>
Matrix<T> operator-( Matrix<T>  const& m1, Matrix<T>  const& m2 )
{
    Matrix<T> result;
	if(check_size(m1,m2))
    {
        result.set_size(m1.size());
        detail::transform_Matrix2(m1, m2, result, sub);
        result.set_dim(m1.dim());
    }
    return result;
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T> const& m2 )
{
	detail::transform_Matrix2(m1, m2, m1, sub );
	return std::move(m1);
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>const& m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m2, sub );
	return std::move(m2);
}

template<typename T>
Matrix<T>&& operator-( Matrix<T> && m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m1, sub );
    m2.set_to_default();
	return std::move(m1);
}

template<typename T>
Matrix<T> operator*( Matrix<T>  const& m1,  T const& scl)
{
    Matrix<T> result;
	result.set_size(m1.size());
    result.set_dim(m1.dim());
    detail::transform_Matrix1(m1, result, [=](T const& x){ return x * scl; });

    return result;
}

template<typename T>
Matrix<T> operator*( T const& scl, Matrix<T>  const& m1)
{
    Matrix<T> result;

    result.set_size(m1.size());
    result.set_dim(m1.dim());
    detail::transform_Matrix1(m1, result, [=](T const& x){ return scl * x; });
        
    return result;
}

template<typename T>
Matrix<T>&& operator*( Matrix<T>&& m1,  T const& scl)
{
    detail::transform_Matrix1(m1, m1, [=](T const& x){ return x * scl; });
    return std::move(m1);   
}

template<typename T>
Matrix<T>&& operator*(T const& scl, Matrix<T>&& m1 )
{
    detail::transform_Matrix1(m1, m1, [=](T const& x){ return  scl*x; });
    return std::move(m1);   
}

template<typename T>
Matrix<T> operator/( Matrix<T>  const& m1,  T const& scl)
{
    Matrix<T> result;
	result.set_size(m1.size());
    result.set_dim(m1.dim());
    detail::transform_Matrix1(m1, result, [=](T const& x){ return x / scl; });

    return result;
}

template<typename T>
Matrix<T>&& operator/( Matrix<T>&& m1,  T const& scl)
{
    detail::transform_Matrix1(m1, m1, [=](T const& x){ return x / scl; });
    return std::move(m1);   
}


template<typename T>
Matrix<T> operator*( Matrix<T>  const& m1, Matrix<T>  const& m2 )
{
    Matrix<T> result;
    double sum = 0.0;
	if(check_size(m1,m2))
    {
        int _dim = m1.dim();
        result.set_size(m1.size());
        result.set_dim(_dim);
        for(int i=0;i<_dim;i++)
        {
            for(int j=0;j<_dim;j++)
            {
                sum = 0.0;
                for(int k=0;k<_dim;k++)
                {
                    sum += m1(i,k)*m2(k,j);
                }
                result.set_element(i,j,sum);
            }
        }
        
    }
    return result;
}


template<typename T>
Matrix<T>&& operator*( Matrix<T>  && m1, Matrix<T>  const& m2 )
{

    double sum = 0.0;
	if(check_size(m1,m2))
    {

        int _dim = m1.dim();
        std::vector<T> tmp(_dim);


        for(int i=0;i<_dim;i++)
        {
            for(int j=0;j<_dim;j++)
            {
                sum = 0.0;
                for(int k=0;k<_dim;k++)
                {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[j] = sum;
            }
            for(int l =0; l<_dim; l++)
	        {
		        m1.set_element(i, l, tmp[l]);
	        }
        }
        
    }
    return std::move(m1);
}

template<typename T>
Matrix<T>&& operator*(  Matrix<T>  const& m1, Matrix<T>  && m2 )
{

    double sum = 0.0;
	if(check_size(m1,m2))
    {

        int _dim = m1.dim();
        std::vector<T> tmp(_dim);


        for(int j=0;j<_dim;j++)
        {
            for(int i=0;i<_dim;i++)
            {
                sum = 0.0;
                for(int k=0;k<_dim;k++)
                {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[i] = sum;
            }
            for(int l =0; l<_dim; l++)
	        {
		        m2.set_element(l, j, tmp[l]);
	        }
        }
        
    }
    return std::move(m2);
}

template<typename T>
Matrix<T>&& operator*( Matrix<T>  && m1, Matrix<T>  && m2 )
{

    double sum = 0.0;
	if(check_size(m1,m2))
    {

        int _dim = m1.dim();
        std::vector<T> tmp(_dim);


        for(int i=0;i<_dim;i++)
        {
            for(int j=0;j<_dim;j++)
            {
                sum = 0.0;
                for(int k=0;k<_dim;k++)
                {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[j] = sum;
            }
            for(int l =0; l<_dim; l++)
	        {
		        m1.set_element(i, l, tmp[l]);
	        }
        }
        
    }
    m2.set_to_default();
    return std::move(m1);
}

//TODO: matrix inverse for Matrix<T> operator/(Matrix<T> const& m1,Matrix<T> const& m2 )





