#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "ReadMNIST.hpp"
#include "neural.hpp"
#include "test.hpp"

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


int main(int, char**) {

   NNtest(1e-15);


   const std::string TrainingFile  = "mnist/t10k-images.idx3-ubyte";
   const std::string TrainingLabelFile = "mnist/t10k-labels.idx1-ubyte";

   //Parameters 

   const int BatchSize = 100;  
   const int Epoch = 20;
   const double LearningRate = 0.01;
   const int NumberOfImages = 10000;
   const int Iteration = NumberOfImages / BatchSize;
   const int InputLayerDimension = 784; //28*28
   const int HiddenLayerDimension = 100;
   const int OutputLayerDimension = 10;

   const int NumberOfBatchElement = BatchSize *  InputLayerDimension;
   const int NumberOfBatchElementLabel = BatchSize *  OutputLayerDimension;

   
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
   std::vector<double> W1 = InitializeLayer(HiddenLayerDimension,InputLayerDimension,1.0);
   std::vector<double> W2 = InitializeLayer(OutputLayerDimension,HiddenLayerDimension,1.0);
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
   std::vector<double> dLdb1(HiddenLayerDimension);
   
   //Dimensions

   std::vector<int> X_Dimension =  {BatchSize, InputLayerDimension};
   std::vector<int> Y_Dimension =  {BatchSize, OutputLayerDimension};

   std::vector<int> Z1_Dimension = {HiddenLayerDimension, BatchSize};
   std::vector<int> a1_Dimension = {HiddenLayerDimension, BatchSize};
   std::vector<int> Z2_Dimension = {OutputLayerDimension, BatchSize};
   std::vector<int> a2_Dimension = {OutputLayerDimension, BatchSize};

   


   std::vector<int> W1_Dimension = {HiddenLayerDimension, InputLayerDimension};
   std::vector<int> W2_Dimension = {OutputLayerDimension, HiddenLayerDimension};
   int b1_Dimension = HiddenLayerDimension;
   int b2_Dimension = OutputLayerDimension;

   std::vector<int> P_Dimension =  {BatchSize,OutputLayerDimension};

   std::vector<int> dLdZ2_Dimension = {BatchSize, OutputLayerDimension};
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
  
   

   read_Mnist(TrainingFile, Input);
   Normalize(Input);
   read_Mnist_Label(TrainingLabelFile, TrainingLabels);
   Encoded = OneHotEncoding(TrainingLabels,NumberOfImages);

   std::vector<double> tmp(10);


   for(int k = 0; k < Epoch; k++)
   {
      std::cout<<"Epoch "<< k+1 << "/" << Epoch << std::endl;
      for(int i = 0; i< Iteration; i++)
      {   
         if(i % 50 == 0){std::cout<<"Iteration "<< i+1 << "/" << Iteration << std::endl;}
         
         for(int j = 0; j < NumberOfBatchElement; j++)
         {
            X[j] = Input[i * NumberOfBatchElement + j];
         }
         

         for(int l = 0; l < NumberOfBatchElementLabel; l++)
         {
            Y[l] = Encoded[i * NumberOfBatchElementLabel + l];
         }

              
        Transpose(X,X_Dimension);
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
                          dLdZ1,dLdZ1_Dimension,
                          RELU_Derivative);
        
        LinearBackward(dLda1,dLda1_Dimension,
                        dLdZ1,dLdZ1_Dimension,
                        dLdW1,dLdW1_Dimension,
                        dLdb1,dLdb1_Dimension,
                        W1,W1_Dimension,
                        X,X_Dimension,
                        true);

         GradientDescent(W1,W2,dLdW1,dLdW2,b1,b2,dLdb1,dLdb2,LearningRate);
         X_Dimension = {BatchSize , InputLayerDimension};
         dLdZ2_Dimension = {BatchSize, OutputLayerDimension};
      }
      
   }

   
   

std::ofstream output_file;
output_file.open("Losses_acc.dat");
for(int i=0;i<Losses.size();i++) { output_file << std::setprecision(std::numeric_limits<long double>::digits10)  << Losses[i]  << std::endl;}  
output_file.close();



std::vector<double> Result(NumberOfImages * OutputLayerDimension);

Z1.clear();
Z1.resize(HiddenLayerDimension * NumberOfImages);
a1.clear();
a1.resize(HiddenLayerDimension * NumberOfImages);
Z2.clear();
Z2.resize(OutputLayerDimension * NumberOfImages);
a2.clear();
a2.resize(OutputLayerDimension * NumberOfImages);

std::vector<int> Input_Dimension = {NumberOfImages, InputLayerDimension};


Z1_Dimension = {HiddenLayerDimension, NumberOfImages};
a1_Dimension = {HiddenLayerDimension, NumberOfImages};
Z2_Dimension = {OutputLayerDimension, NumberOfImages};
a2_Dimension = {OutputLayerDimension, NumberOfImages};


Transpose(Input,Input_Dimension);
LinearForwardStep(Input,W1,Z1,Input_Dimension,W1_Dimension,Z1_Dimension,b1,b1_Dimension);
NonLinearStep(Z1,a1,RELU);
LinearForwardStep(a1,W2,Z2,a1_Dimension,W2_Dimension,Z2_Dimension,b2,b2_Dimension);
Transpose(Z2,Z2_Dimension);
Softmax(Z2,Z2_Dimension,Result);


double Acc =  Accuracy(TrainingLabels,Result,tmp,NumberOfImages);

std::cout << "Acc:\t"<< Acc << "\nDONE\n";
return 0;
}