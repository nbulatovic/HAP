#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <iterator>
#include <vector>
#include <fstream>
#include <random>
#include <future>
#include <thread> 

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

template<typename T>
class Matrix
{
private:
    std::vector<T> data;
    int dimension;
public:
    struct Idx1{};
    struct Idx2{};

    //Constructors
    //TESTED
    Matrix(): data{},dimension{0}{}
    //TESTED
    Matrix(int _dim, std::initializer_list<T> const& il):    data{il}, 
                                                             dimension{_dim}
    {
        if (sq(dimension) != data.size())
        {
        std::cout<<"Linear size doesn't match with the data size! Default constructor called.\n";
        data = {};
        dimension = 0;
        }
    }
    //TESTED
    Matrix(int n)
	{
		data.resize(sq(n));
        dimension = n;
    }
    //TESTED
    template<typename F>
	Matrix(Idx1,int _dim, F f)
	{
        int n = sq(_dim);
		data.resize(n);
		for(int i=0; i<n; ++i){ data[i] = f(i); }
        dimension = _dim;
    }
    //TESTED
    template<typename F>
	Matrix(Idx2, int _dim, F f)
	{
        int n = sq(_dim);
		data.resize(n);
		for(int i=0; i<_dim; i++)
            { 
                for(int j=0; j<_dim ; j++)
                {
                    data[i*_dim+j] = f(i,j);
                }
            }
        dimension = _dim;
    }
    //TESTED
    Matrix( Matrix const& ) = default;
    //TESTED
    Matrix( Matrix && m):   data{std::move(m.data)}, 
                            dimension{m.dimension}                     
    {
        m.dimension = 0; 
    }
    //TESTED
    template<typename F>
    Matrix(Matrix<T>  const& m1, Matrix<T>  const& m2,F f)
    {   
        data.resize(m1.size());
        detail::transform_Matrix2(m1, m2, data, f);
        dimension = m1.dim();
    }
    //TESTED
    template<typename F>
    Matrix(Matrix<T>  const& m1,F f)
    {   
        data.resize(m1.size());
        detail::transform_Matrix1(m1, data, f);
        dimension = m1.dim();
    }

    //Iterators
    //TESTED
	auto begin(){return data.begin();}
    //TESTED
	auto cbegin() const{return data.cbegin();}
    //TESTED
	auto end(){return data.end();}
    //TESTED
	auto cend() const{return data.cend();}


	//Copy and Move assignment operators:
    //TESTED
    Matrix<T>& operator=(Matrix<T> const& m) 
    {
        if (this != &m)
        {
            data = m.data;
            dimension = m.dimension;
        }
        return *this;
    }
    //TESTED
    Matrix<T>& operator=(Matrix<T> && m) 
    {
        if (this != &m)
        {
            data = std::move(m.data);
            dimension = m.dimension;
            m.dimension = 0;
        }
        return *this;
    }
    //Indexing
    //TESTED
    T& operator[]( int i ){ return data[i]; }
    //TESTED
    T const& operator[]( int i ) const { return data[i]; }
    //TESTED
    T& operator()(int i, int j){return data[dimension*i+j]; }
    //TESTED
    T const& operator()(int i, int j) const{return data[dimension*i+j]; }


    //Add assignment operators:
    //TESTED
	Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, add);
		return *this;
    }
    //Subtract assignment operators:
    //TESTED
	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_Matrix2(*this, cpy, *this, sub);
		return *this;
    }
    //Multiplication by scalar:
    //TESTED
    Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x * scl;} );
		return *this;
    }
    //Division by scalar:
    //TESTED
	Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_Matrix1(*this, *this, [=](T const& x){ return x / scl;} );
		return *this;
	}
    //Others

    //TESTED
    int dim()const
	{
		return dimension;
    }
    //TESTED
    int size()const
	{
		return sq(dimension);
    }
    //TESTED
    void set_to_default()
    {
        data = {};
        dimension = 0;
    }
    auto set_size(int new_dim)
    {
        int new_size = sq(new_dim);
        if(dimension !=0)
        {
            std::cout<<"Matrix already has a size!" << std::endl;
        }
        else
        {
            data.resize(new_size);
            dimension = new_dim;
        }
        return *this;
    }
};

template<typename T>
bool check_size(Matrix<T> const& m1, Matrix<T> const& m2)
{
    if(m1.size() == m2.size() && m1.dim() == m2.dim()) {return true;}
    else    {return false;}
}
//TESTED
template<typename T>
Matrix<T> operator+( Matrix<T>  const& m1, Matrix<T>  const& m2 )
{
    
	if(check_size(m1,m2))  { Matrix<T> result(m1,m2,add); return result;}
    else {Matrix<T> result; return result;}
    
}
//TESTED
template<typename T>
Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T> const& m2 )
{
	detail::transform_Matrix2(m1, m2, m1, add );
	return std::move(m1);
}
//TESTED
template<typename T>
Matrix<T>&& operator+( Matrix<T>const& m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m2, add ); 
	return std::move(m2);
}
//TESTED
template<typename T>
Matrix<T>&& operator+( Matrix<T> && m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m1, add );
    m2.set_to_default();
	return std::move(m1);
}
//TESTED
template<typename T>
Matrix<T> operator-( Matrix<T>  const& m1, Matrix<T>  const& m2 )
{
	if(check_size(m1,m2))  {Matrix<T> result(m1,m2,sub); return result;}
    else {Matrix<T> result;return result;}
}
//TESTED
template<typename T>
Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T> const& m2 )
{
	detail::transform_Matrix2(m1, m2, m1, sub );
	return std::move(m1);
}
//TESTED
template<typename T>
Matrix<T>&& operator-( Matrix<T>const& m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m2, sub );
	return std::move(m2);
}
//TESTED
template<typename T>
Matrix<T>&& operator-( Matrix<T> && m1, Matrix<T> && m2 )
{
	detail::transform_Matrix2(m1, m2, m1, sub );
    m2.set_to_default();
	return std::move(m1);
}
//TESTED
template<typename T>
Matrix<T> operator*( Matrix<T>  const& m1,  T const& scl)
{
    Matrix<T> result(m1,[scl](auto const& x){ return x * scl; });
    return result;
}
//TESTED
template<typename T>
Matrix<T> operator*( T const& scl, Matrix<T>  const& m1)
{
    Matrix<T> result(m1,[scl](auto const& x){ return scl * x; }); 
    return result;
}
//TESTED
template<typename T>
Matrix<T>&& operator*( Matrix<T>&& m1,  T const& scl)
{
    detail::transform_Matrix1(m1, m1, [=](T const& x){ return x * scl; });
    return std::move(m1);   
}
//TESTED
template<typename T>
Matrix<T>&& operator*(T const& scl, Matrix<T>&& m1 )
{
    detail::transform_Matrix1(m1, m1, [=](T const& x){ return  scl*x; });
    return std::move(m1);   
}
//TESTED
template<typename T>
Matrix<T> operator/( Matrix<T>  const& m1,  T const& scl)
{
    Matrix<T> result(m1,[scl](auto const& x){ return x / scl; });
    return result;
}
//TESTED
template<typename T>
Matrix<T>&& operator/( Matrix<T>&& m1,  T const& scl)
{
    detail::transform_Matrix1(m1, m1, [=](T const& x){ return x / scl; });
    return std::move(m1);   
}
//TESTED
template<typename T>
Matrix<T> operator*( Matrix<T>  const& m1, Matrix<T>  const& m2 )
{
    
	if(check_size(m1,m2))
    {
        int _dim = m1.dim();

        return Matrix<T>(Matrix<T>::Idx2{},
                         _dim,
                         [&](int i, int j)
                         {
                            T sum = static_cast<T>(0.0);
                            for(int k = 0; k<_dim; ++k)
                            {
                                sum += m1(i, k) * m2(k, j);
                            }
                            return sum;
                         });
    }
    else
    {
        std::cout<< "ERROR: Sizes don't match. Return default.\n";
        return Matrix<T>();
    }
}
//TESTED
template<typename T>
Matrix<T>&& operator*( Matrix<T>  && m1, Matrix<T>  const& m2 )
{

    
	if(check_size(m1,m2))
    {
        T sum = static_cast<T>(0.0);
        int _dim = m1.dim();
        std::vector<T> tmp(_dim);


        for(int i=0;i<_dim;i++)
        {
            for(int j=0;j<_dim;j++)
            {
                sum = static_cast<T>(0.0);
                for(int k=0;k<_dim;k++)
                {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[j] = sum;
            }
            for(int l =0; l<_dim; l++)
	        {
		        m1(i, l) = tmp[l];
	        }
        }
        
    }
    return std::move(m1);
}
//TESTED
template<typename T>
Matrix<T>&& operator*(  Matrix<T>  const& m1, Matrix<T>  && m2 )
{

    
	if(check_size(m1,m2))
    {
        T sum = static_cast<T>(0.0);
        int _dim = m1.dim();
        std::vector<T> tmp(_dim);


        for(int j=0;j<_dim;j++)
        {
            for(int i=0;i<_dim;i++)
            {
                sum = static_cast<T>(0.0);
                for(int k=0;k<_dim;k++)
                {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[i] = sum;
            }
            for(int l =0; l<_dim; l++)
	        {
		        m2(l, j) = tmp[l];
	        }
        }
        
    }
    return std::move(m2);
}
//TESTED
template<typename T>
Matrix<T>&& operator*( Matrix<T>  && m1, Matrix<T>  && m2 )
{

    
	if(check_size(m1,m2))
    {
        T sum = static_cast<T>(0.0);
        int _dim = m1.dim();
        std::vector<T> tmp(_dim);


        for(int i=0;i<_dim;i++)
        {
            for(int j=0;j<_dim;j++)
            {
                sum = static_cast<T>(0.0);
                for(int k=0;k<_dim;k++)
                {
                    sum += m1(i,k)*m2(k,j);
                }
                tmp[j] = sum;
            }
            for(int l =0; l<_dim; l++)
	        {
		        m1(i, l) = tmp[l];
	        }
        }  
    }
    m2.set_to_default();
    return std::move(m1);
}

template<typename T>
std::ostream& operator<<( std::ostream& s, Matrix<T> const& m )
{
    int _dim = m.dim();
    for(int i=0;i<_dim;i++)
    {
        for(int j=0;j<_dim;j++)
        {
            s << m(i,j) << "\t";
        }
    s << "\n";
    }
    s << "\n";
    return s;
}

//Assuming default matrix
template<typename T>
std::istream& operator>>( std::istream& s, Matrix<T>& m )
{
    auto restore_stream = [state = s.rdstate(), pos = s.tellg(), &s]()
                          {
                              s.seekg(pos);
                              s.setstate(state);
                              s.clear(); 
                          };

    std::string tmp;
    std::getline(s, tmp);
    if(s.fail() == 1){ restore_stream(); return s; }
    
    int _dim = std::stoi(tmp);
    int _size = sq(_dim);
    std::vector<T> temp_vec;
    temp_vec.reserve(_size); 

    T element;

    while(std::getline(s, tmp))
	{   
        if(s.fail() == 1){ restore_stream(); return s; }
        std::stringstream row(tmp);
        while(std::getline(row, tmp, '\t'))
        {
            if(s.fail() == 1){ restore_stream(); return s; }
            std::stringstream value(tmp);
            value >> element;
            if(s.fail() == 1){ restore_stream(); return s; }
            temp_vec.push_back(element);
        }
	}

    m.set_size(_dim);
    std::transform( temp_vec.begin(),
                    temp_vec.end(),
                    m.begin(),
                    [](auto const& x){return x;});

    return s;
}


template<typename T>
Matrix<T> parallel_matmul(int number_of_threads, Matrix<T>  const& m1, Matrix<T>  const& m2 )
{

	if(check_size(m1,m2))
    {

        const int _dim = m1.dim();
        int dim_from = 0;
        const int dim_delta = _dim / number_of_threads;
        int dim_to = dim_delta;

        Matrix<T> Result(_dim);

        auto thread_function = [&](int row_from,int row_to)
        {

            T value = static_cast<T>(0.0);

            for(int i = row_from ; i < row_to; ++i)
            {
                for(int j = 0; j < _dim; ++j)
                {
                    for(int k=0; k < _dim; k++) {value += m1(i,k)*m2(k,j);}
                    Result(i, j) = value;
                    value = 0.0;
                }
            }
        };

        std::vector<std::future<void>> futures;
        futures.reserve(number_of_threads);

        for(int t = 0; t < number_of_threads; t++)
        {
            if(t == number_of_threads -1){dim_to = _dim; }
            auto tmp = std::async(std::launch::async, thread_function, dim_from, dim_to);
            futures.push_back(move(tmp));
            dim_from = dim_to;
            dim_to += dim_delta; 
        }

        for(auto& future: futures) {future.get();}

        return Result;
    }

    
}







