#include "matrix.hpp"
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <iomanip>


auto measure_matmul(int N)
{

    std::mt19937 gen(42);
	Matrix<double> mat1(Matrix<double>::Idx1{}, N, [&](int i){return gen();});
	//Matrix<double> mat2(Matrix<double>::Idx1{}, N, [&](int i){return gen();});
	std::vector<double> t;
	int number_of_measure = 60;
	t.reserve(number_of_measure);


	for(int j=0;j<number_of_measure + 1;j++)
	{
		//Matrix<double> mat1(Matrix<double>::Idx1{}, N, [&](int i){return gen();});
		Matrix<double> mat2(Matrix<double>::Idx1{}, N, [&](int i){return gen();});
		auto t1 = std::chrono::high_resolution_clock::now();
		Matrix<double> mat3 = mat1*std::move(mat2);
		auto t2 = std::chrono::high_resolution_clock::now();

		t.push_back((static_cast<std::chrono::duration<double, std::micro>>(t2-t1)).count());
	}


	return *std::min_element(t.begin(), t.end());

}

inline auto cube = [](auto const& x){ return x*x*x  ; };

int main(int, char**)
{

	int dim_min = 2;
	int dim_max = 256;
	int steps = (dim_max-dim_min)/2;
	std::vector<int> sizes;
	std::vector<double>times;
	
	sizes.reserve(steps);
	times.reserve(steps);
	
	for(int i=dim_min; i <= dim_max; i+=4)
	{
		times.push_back(measure_matmul(sq(i)));
		sizes.push_back(cube(i));
	}

	std::ofstream output_file;
  	output_file.open("N_vs_time_lr.dat");
  	for(int i=0;i<times.size();i++){output_file << sizes[i] << "\t" <<std::setprecision(std::numeric_limits<long double>::digits10)<< times[i] << std::endl;}  
	output_file.close();
	
}
