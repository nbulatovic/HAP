#include "matrix.hpp"
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <iomanip>



auto measure_matmul(int N)
{

	std::mt19937 gen(42);
	std::normal_distribution<double> distr(0,1);
	Matrix<double> mat1(Matrix<double>::Idx1{}, N, [&](int){return distr(gen);});
	Matrix<double> mat2(Matrix<double>::Idx1{}, N, [&](int){return distr(gen);});
	std::vector<double> t;
	std::vector<double> t_parallel2;


	int number_of_measure = 10;
	t.reserve(number_of_measure);
	t_parallel2.reserve(number_of_measure);


	for(int j=0;j<number_of_measure;j++)
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		Matrix<double> mat3 = mat1*mat2;
		auto t2 = std::chrono::high_resolution_clock::now();

		t.push_back((static_cast<std::chrono::duration<double, std::micro>>(t2-t1)).count());

		auto t3 = std::chrono::high_resolution_clock::now();
		Matrix<double> mat4 = parallel_matmul(2,mat1,mat2);
		auto t4 = std::chrono::high_resolution_clock::now();
		
		t_parallel2.push_back((static_cast<std::chrono::duration<double, std::micro>>(t4-t3)).count());

	}
	std::vector<double> res = {*std::min_element(t.begin(), t.end()),
							   *std::min_element(t_parallel2.begin(), t_parallel2.end())};


	return res;

}

int main(int, char**)
{

	std::vector<int> T = {2,4,8,16,32,64,128,256,512,1024,2048};
	std::vector<double> sizes;
	std::vector<std::vector<double>>times;

	for(auto& t: T)
	{
		std::cout << t << std::endl;
		times.push_back(measure_matmul(t));
		sizes.push_back(sq(static_cast<double>(t)));
	}

	std::ofstream output_file;
  	output_file.open("N_vs_time_parallel.dat");
  	for(int i=0;i<times.size();i++)
	{
		output_file << sizes[i] << "\t" << std::setprecision(std::numeric_limits<long double>::digits10)
		<< times[i][0] << '\t' << times[i][1] << std::endl;
	}  
	output_file.close();

}
