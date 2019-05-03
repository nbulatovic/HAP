#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "ReadMNIST.hpp"
#include "neural.hpp"

/*
Simple two layer neural net for MNIST's digit classification.
Unit test isn't complete, only the most crucial parts are tested.
The program uses std::vector containers, but no dynamic allocations.
The notation and the variables are the following:

Forward direction:

X -> Z1 = W1*X'+ b1 -> a1 = RELU(Z1) -> Z2 = W2*a1 + b2 -> P = Softmax(Z') -> Loss

Dimensions:

Examples x InputLayer -> Hiddenlayer x Examples -> ... -> OutputLayer x Examples -> Examples x Outputlayer
 

Backward direction:

dL/dZ2 = 1/Examples*(P-Y)' -> dL/da1 = W2'*dL/dZ2     ->  dL/dZ1 = dL/da1 * RELU'(Z1) ->  -----
                              dL/W2  = dL/dZ2 * a1'                                       dL/W1  = dL/dZ1 * X'
                              (dL/db2)_i=SUM((dL/dZ2)_i)                                  (dL/db1)_i=SUM((dL/dZ1)_i) 

Dimensions:

OutputLayer x Examples -> HiddenLayer x Examples      -> HiddenLayer x Examples -> -----
                          OutputLayer x HiddenLayer                                HiddenLayer x InputLayer
                          OutputLayer x 1                                          HiddenLayer x 1

*/

void NNtest(double precision)
{

    
    auto error = [](auto str){ std::cout << "NNtest error in: " << str << "\n"; std::exit(-1); };
    auto check_values = [](auto const& x, auto const& y, double prec, bool exact = false)
						{
							bool check = true;
							for(int i=0;i<(int)x.size();i++)
							{
                        if(exact == false) {check = check && (std::abs(x[0]-y[0]) > prec);}
                        else {check = check && (x[0] == y[0]);}
							}
							return check;
						};
    //Transpose  
    {
        std::vector<double> v = {0.0,1.0,9.0,1.0,16.0,15.0};
        std::vector<int> dims = {2,3};


        if(v[0] != 0.0 || v[1] != 1.0 || v[2] != 9.0 || v[3] != 1.0 ||
           v[4] != 16.0 || v[5] != 15.0){error("Transpose test: src element");}

        Transpose(v,dims);

        if(v[0] != 0.0 || v[1] != 1.0 || v[2] != 1.0 || v[3] != 16.0 ||
           v[4] != 9.0 || v[5] != 15.0){error("Transpose test: element");}
        if(dims[0] != 3 || dims[1] != 2){error("Transpose test: dims");}

        Transpose(v,dims);

        if(v[0] != 0.0 || v[1] != 1.0 || v[2] != 9.0 || v[3] != 1.0 ||
           v[4] != 16.0 || v[5] != 15.0){error("Transpose back test: element");}
        if(dims[0] != 2 || dims[1] != 3){error("Transpose back test: dims");}


    }

    //One-hot encoding test
    {
        std::vector<int> x = {0,1,1,9};
        auto v = OneHotEncoding(x,4);
        std::vector<double> Reference = {1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                                         0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                                         0.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                                         1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0};
        check_values(x,v,true);
        
      
    }

    //Matmul + vector
    {
        std::vector<double> W = {3.57000000000000e+00,3.27000000000000e+01,1.12140000000000e+03,
                                 0.00000000000000e+00,3.59000000000000e+01,7.70000000000000e-01,
                                 1.00000000000000e+00,4.55600000000000e+01,2.24760000000000e+01};

        std::vector<double> b = {23.3455,
                                 9384.2000200000002,
                                 283.1};

        std::vector<double> x = {890.54999999999995,
                                 6.872,
                                 467.10000000000002,
                                 9.99913300000000e+04,
                                 5.69000132300000e+02,
                                 5.30100000000000e-04};

        std::vector<double> Result(6);

        int b_Dimension = 3;
        std::vector<int> W_Dimension = {3,3};
        std::vector<int> x_Dimension{3,2};
        std::vector<int> Result_Dimension{3,2};

         MatrixMultiplication(x,W,Result,x_Dimension,W_Dimension,Result_Dimension,b,b_Dimension);
 
        std::vector<double> Reference = {656553.5273612202,3269764.9639941403,
                                         26591.2201218710,3599072.9474281766,
                                         35243.5729735748,4555894.9787145285};

        if(check_values(Reference,Result,precision)){ error("Matmul + vec error"); }
    }
    //Matmul
    {
        std::vector<double> W = {3.57000000000000e+00,3.27000000000000e+01,1.12140000000000e+03,
                                 0.00000000000000e+00,3.59000000000000e+01,7.70000000000000e-01,
                                 1.00000000000000e+00,4.55600000000000e+01,2.24760000000000e+01};

        std::vector<double> x = {890.54999999999995,
                                 6.872,
                                 467.10000000000002,
                                 9.99913300000000e+04,
                                 5.69000132300000e+02,
                                 5.30100000000000e-04};

        std::vector<double> Result(6);

        std::vector<int> W_Dimension = {3,3};
        std::vector<int> x_Dimension{3,2};
        std::vector<int> Result_Dimension{3,2};

        MatrixMultiplication(x,W,Result,x_Dimension,W_Dimension,Result_Dimension); 

        std::vector<double> Reference = {656530.1818612202,3269741.6184941404,
                                         17207.0201018710,3589688.7474081768,
                                         34960.4729735748,4555611.8787145289};

        if(check_values(Reference,Result,precision)){ error("Matmul error"); }
    }
    //Softmax
    {
       std::vector<double> v = {0.496714153011233,-0.138264301171185,0.647688538100692,
                                1.523029856408025, -0.234153374723336, -0.234136956949181};
       std::vector<int> v_Dim = {2,3};
       std::vector<double> Result(6);
       std::vector<double> Reference = {0.371344975609489,0.196793121006899,0.431861903383611,
                                        0.743459518349729, 0.128269187869213,0.128271293781058};
       Softmax(v,v_Dim,Result);

       if(check_values(Reference,Result,precision)){ error("Softmax error"); }


    }
   //CrossEntropy
   {
       std::vector<double> x = {0.4,0.3,0.05,0.05,0.2};
       std::vector<double> y = {1.0,0.0,0.0,0.0,0.0};
       double ref = 0.183258146374831;
       double res = CrossEntropy(x,y);

       if(std::abs(ref-res) > precision){error("Loss test");}
   }

    //Softmaxback
   {
      std::vector<double> Prediction = {0.49967587, 0.50032413,0.49966831, 0.50033169,0.49970124, 0.50029876};
      std::vector<int> PredictionDimension = {3,2};
      std::vector<double> TrueValues = {0.0,1.0,1.0,0.0,1.0,0.0};
      std::vector<int> TrueValuesDimension = {3,2};
      std::vector<double> Result = {0.0,0.0,0.0,0.0,0.0,0.0};
      std::vector<int> ResultDimension = {2,3};

      std::vector<double> Reference = {0.16655862,-0.16677723,-0.16676625,-0.16655862,0.16677723,0.16676625};

      SoftmaxBackward(Prediction,PredictionDimension,TrueValues,TrueValuesDimension,Result,ResultDimension);
      if(check_values(Reference,Result,1e-8)){ error("Softmaxback error"); }
   }


    std::cout << "Tests are succesfull!\n";
}


int main(int, char**) {


   NNtest(1e-15);

   std::string TrainingFile  = "mnist/t10k-images.idx3-ubyte";
   std::string TrainingLabelFile = "mnist/t10k-labels.idx1-ubyte";

   //Parameters 

   int BatchSize = 16;  
   int Epoch = 5;
   double LearningRate = 0.01;
   int NumberOfImages = 10000;
   int Iteration = NumberOfImages / BatchSize;
   int InputLayerDimension = 784; //28*28
   int HiddenLayerDimension = 14;
   int OutputLayerDimension = 10;

   int NumberOfBatchElement = BatchSize *  InputLayerDimension;
   int NumberOfBatchElementLabel = BatchSize *  OutputLayerDimension;

   
   //Initialize layers

   //Input, output
   std::vector<double> Input;
   std::vector<double> X(NumberOfBatchElement); 
   std::vector<double> Y(NumberOfBatchElementLabel);
   std::vector<double> Encoded;
   std::vector<int> TrainingLabels(NumberOfImages * OutputLayerDimension);

   //Inner states
   std::vector<double> Z1(HiddenLayerDimension * BatchSize);
   std::vector<double> a1(HiddenLayerDimension * BatchSize);
   std::vector<double> Z2(OutputLayerDimension * BatchSize);
   std::vector<double> a2(OutputLayerDimension * BatchSize);

   //Output
   std::vector<double> P(OutputLayerDimension * BatchSize);

    
   //Weights and bias
   std::vector<double> W1 = InitializeLayer(HiddenLayerDimension,InputLayerDimension);
   std::vector<double> W2 = InitializeLayer(OutputLayerDimension,HiddenLayerDimension);
   std::vector<double> b1(HiddenLayerDimension);
   std::vector<double> b2(OutputLayerDimension);

   

   //Derivatives
   std::vector<double> dLdZ2(OutputLayerDimension * BatchSize);
   std::vector<double> dLda2(HiddenLayerDimension * BatchSize);
   std::vector<double> dLdW2(OutputLayerDimension * HiddenLayerDimension);
   std::vector<double> dLdb2(OutputLayerDimension);
   std::vector<double> dLdZ1(HiddenLayerDimension * BatchSize);
   std::vector<double> dLda1;
   std::vector<double> dLdW1(HiddenLayerDimension * InputLayerDimension);
   std::vector<double> dLdb1(InputLayerDimension);
   
   //Dimensions

   std::vector<int> X_Dimension =  {BatchSize, InputLayerDimension};
   std::vector<int> Y_Dimension =  {BatchSize, OutputLayerDimension};

   std::vector<int> Z1_Dimension = {HiddenLayerDimension, BatchSize};
   std::vector<int> a1_Dimension = {HiddenLayerDimension, BatchSize};
   std::vector<int> Z2_Dimension = {OutputLayerDimension, BatchSize};
   std::vector<int> a2_Dimension = {OutputLayerDimension, BatchSize};

   std::vector<int> W1_Dimension = {HiddenLayerDimension, InputLayerDimension};
   int b1_Dimension = HiddenLayerDimension;
   std::vector<int> W2_Dimension = {OutputLayerDimension, HiddenLayerDimension};
   int b2_Dimension = OutputLayerDimension;

   std::vector<int> P_Dimension =  {BatchSize,OutputLayerDimension};

   std::vector<int> dLdZ2_Dimension = {OutputLayerDimension, BatchSize};
   std::vector<int> dLda2_Dimension = {HiddenLayerDimension, BatchSize};
   std::vector<int> dLdW2_Dimension = {OutputLayerDimension, HiddenLayerDimension};
   std::vector<int> dLdb2_Dimension = {OutputLayerDimension};
   std::vector<int> dLdZ1_Dimension = {HiddenLayerDimension, BatchSize};
   std::vector<int> dLda1_Dimension;
   std::vector<int> dLdW1_Dimension = {HiddenLayerDimension, InputLayerDimension};
   std::vector<int> dLdb1_Dimension = {InputLayerDimension};


   double Loss = 0;
   std::vector<double> Losses;
   Losses.reserve(Iteration);
   int dummy = 0;


   read_Mnist(TrainingFile, Input);
   Normalize(Input);
   read_Mnist_Label(TrainingLabelFile, TrainingLabels);
   Encoded = OneHotEncoding(TrainingLabels,NumberOfImages);


   for(int k = 0; k < Epoch; k++)
   {
      std::cout<<"Epoch "<< k+1 << "/" << Epoch << std::endl;
      for(int i = 0; i< Iteration; i++)
      {
         dummy += 1; 
         
         if(i % 50 == 0){std::cout<<"Iteration "<< i+1 << "/" << Iteration << std::endl;}
         
         for(int j = 0; j < NumberOfBatchElement; j++)
         {
            X[j] = Input[i * NumberOfBatchElement + j];
         }

         for(int l = 0; l < NumberOfBatchElementLabel; l++)
         {
            Y[l] = Encoded[i * NumberOfBatchElementLabel + l];
         }

              
         if(i==0 && k == 0){Transpose(X,X_Dimension);}

         LinearForwardStep(X,W1,Z1,X_Dimension,W1_Dimension,Z1_Dimension,b1,b1_Dimension);
         NonLinearStep(Z1,a1,RELU);
         LinearForwardStep(a1,W2,Z2,a1_Dimension,W2_Dimension,Z2_Dimension,b2,b2_Dimension);
         Transpose(Z2,Z2_Dimension);
         Softmax(Z2,Z2_Dimension,P);
         Transpose(Z2,Z2_Dimension); 

         

         Loss = CrossEntropy(P,Y);
         Losses.push_back(Loss);

         SoftmaxBackward(P,P_Dimension,Y,Y_Dimension,dLdZ2,dLdZ2_Dimension);
         LinearBackward(dLda2,dLda2_Dimension,
                        dLdZ2,dLdZ2_Dimension,
                        dLdW2,dLdW2_Dimension,
                        dLdb2,dLdb2_Dimension,
                        W2,W2_Dimension,
                        a1,a1_Dimension);
         NonLinearBackward(dLda2,dLda2_Dimension,
                           Z1,Z1_Dimension,
                           dLdZ1,dLdZ1_Dimension);
         LinearBackward(dLda1,dLda1_Dimension,
                        dLdZ1,dLdZ1_Dimension,
                        dLdW1,dLdW1_Dimension,
                        dLdb1,dLdb1_Dimension,
                        W1,W1_Dimension,
                        X,X_Dimension,
                        true);

         GradientDescent(W1,W2,dLdW1,dLdW2,b1,b2,dLdb1,dLdb2,LearningRate);
      }
      
   }

   
   

std::ofstream output_file;
  	output_file.open("Losses.dat");
  	for(int i=0;i<Losses.size();i++){output_file << std::setprecision(std::numeric_limits<long double>::digits10)<< Losses[i] << std::endl;}  
	output_file.close();


std::cout << "DONE\n";
return 0;
}