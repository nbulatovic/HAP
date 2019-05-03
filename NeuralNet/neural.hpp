#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>


//Activation function

auto RELU = [](double const& x)
{
    if(x > 0) {return x;}
    else {return 0.0;}
};
auto RELU_Derivative = [](double const& x)
{
    if(x > 0) {return 1.0;}
    else {return 0.0;}
};

//One-hot encoding

auto OneHotEncoding(std::vector<int> & Labels, int NumberOfExamples)
{
    int UniqueLabels = 10;

    std::vector<double> Encoded(NumberOfExamples * UniqueLabels);
    int k = 0;

    for(int i = 0; i < NumberOfExamples;i++)
    {
        for(int j = 0; j < UniqueLabels; j++)
        {
            if( j == Labels[i]) {Encoded[k * UniqueLabels + j] = 1;}
            else { Encoded[k * UniqueLabels + j] = 0;}
        }
        k++;
    }

    return Encoded;
}

//Initializing a layer
auto InitializeLayer(const int & InputDimension,const int & OutputDimension)
{
    //std::random_device rd{};
    //std::mt19937 gen(rd());
    std::mt19937 gen(42);
    std::normal_distribution<double> distr(0,1./InputDimension);

    std::vector<double>  W;
    const int _size =  InputDimension * OutputDimension;
    W.reserve(_size);

    for(int i = 0; i < _size; i++) {W.push_back(distr(gen));}

    return W;
}

void MatrixMultiplication(std::vector<double>  const& right, 
                       std::vector<double>  const& left, 
                       std::vector<double>  & Result,
                       std::vector<int> RightDimension,
                       std::vector<int> LeftDimension,
                       std::vector<int> ResultDimension,
                       std::vector<double>  const& b = {},
                       int bDimension = 0)
{   
    bool PlusVector = bDimension != 0;
    if(LeftDimension[1] != RightDimension[0]) {std::cout<<"error: col(left) != row(right)\n";std::exit(-1);}
    if(ResultDimension[0] != LeftDimension[0]) {std::cout<<"error: row(result) != row(left)\n";std::exit(-1);}
    if(ResultDimension[1] != RightDimension[1]) {std::cout<<"error: col(result) != col(right)\n";std::exit(-1);}
    if(PlusVector && bDimension != ResultDimension[0]) {std::cout<<"error: row(result) != row(b)\n";std::exit(-1);}
    

    double sum = 0.0;
    int N = LeftDimension[0];
    int K = LeftDimension[1];
    int L = RightDimension[1];

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < L; j++)
        {
            for(int k = 0; k < K; k++)
            {
            sum += left[i * K + k] * right[k * L + j];
            }
            if(PlusVector){Result[i * L + j] = sum + b[i];}
            else {Result[i * L + j] = sum;}
            sum = 0.0;
        }
    }
}


// Transpose matrix
void Transpose(std::vector<double> & Matrix, std::vector<int> & MatrixDimension)
{
    int _dim1 = MatrixDimension[0];
    int _dim2 = MatrixDimension[1];
    std::vector<double> TranposedMatrix;
    
    for(int i = 0; i < _dim2; i++)
    {
        for (int j = 0; j < _dim1; j++)
        {
            TranposedMatrix.push_back(Matrix[j * _dim2 + i]);
        }
    }
    std::copy(TranposedMatrix.begin(),TranposedMatrix.end(),Matrix.begin());
    std::rotate(MatrixDimension.begin(),MatrixDimension.begin()+1,MatrixDimension.end());
}

// Normalize
void Normalize(std::vector<double> & InputDataset)
{
    std::transform(InputDataset.begin(),InputDataset.end(),InputDataset.begin(), [](auto const& x){return x/255;});
}

// Linear step ->
void LinearForwardStep(std::vector<double>  const& x, 
                       std::vector<double>  const& W, 
                       std::vector<double>  & StepResult,
                       std::vector<int> x_Dimension,
                       std::vector<int> W_Dimension,
                       std::vector<int> StepResult_Dimension,
                       std::vector<double>  const& b,
                       int b_Dimension)
{   
    MatrixMultiplication(x,W,StepResult,x_Dimension,W_Dimension,StepResult_Dimension,b,b_Dimension);
}

// Non-linear step  ->
template <typename F>
void NonLinearStep(std::vector<double> const& State,
                   std::vector<double>  & Activated, 
                   F f)
{
    std::transform(State.begin(), State.end(), Activated.begin(), f);
}

// Softmax step ->
void Softmax(std::vector<double> const& State,
             std::vector<int> State_Dimension,
             std::vector<double> & SoftedState)
{
    int dim1 = State_Dimension[0];
    int dim2 = State_Dimension[1];
    double Nominator = 0.0;
    double MaxZ = -9999;
    double Dummy = 0.0;

    for(int i = 0; i < dim1; i++)
    {
        for(int k = 0; k< dim2; k++)
        {
            Dummy = State[i * dim2 + k];
            if(Dummy > MaxZ) {MaxZ = Dummy;}
        }
        for(int l = 0; l< dim2; l++) {Nominator += std::exp(State[i * dim2 + l] - MaxZ);}
        for(int j = 0; j < dim2; j++)
        {
            SoftedState[i * dim2 + j] = std::exp(State[i * dim2 + j] - MaxZ - std::log(Nominator));
        }
        Nominator = 0.0;
    }
}



// Loss function
auto CrossEntropy(std::vector<double> const& predicted, std::vector<double> const& y)
{
    int _size = static_cast<int>(y.size());
    double sum = 0.0;
    double PredictedValue = 0.0;
    double TrueValue = 0.0;

    for(int i = 0; i<_size; i++) 
    {
        TrueValue = y[i];
        if(TrueValue != 0.0)
        {
            PredictedValue = predicted[i];
            if(PredictedValue < 1e-15) {PredictedValue = 1e-15;}
            sum += TrueValue*std::log(PredictedValue);
        }
    }
    
    return -1./_size*sum;
}


void SoftmaxBackward(std::vector<double> const& Prediction,
                     std::vector<int> const& Prediction_Dimension,
                     std::vector<double> const& TrueLabels,
                     std::vector<int> const& TrueLabels_Dimension,
                     std::vector<double> & dLdz,
                     std::vector<int>& dLdz_Dimension)
{
    int M = Prediction_Dimension[0];
    if(M != TrueLabels_Dimension[0]) {std::cout<<"error: row(P) != col(Y) \n";std::exit(-1);}
    if(Prediction_Dimension[1] != TrueLabels_Dimension[1]) {std::cout<<"error: col(P) != rows(Y) \n";std::exit(-1);}
    if(dLdz_Dimension[0] != TrueLabels_Dimension[1]) {std::cout<<"error: rows(dLdz) != cols(x) \n";std::exit(-1);}
    if(dLdz_Dimension[1] != M) {std::cout<<"error: rows(dLdz) != rows(x) \n";std::exit(-1);}

    std::transform (Prediction.begin(),
                    Prediction.end(),
                    TrueLabels.begin(),
                    dLdz.begin(),
                    [&](auto const& x ,auto const& y){return (x-y)/M;});
}

void NonLinearBackward( std::vector<double> const& dLda,
                        std::vector<int> const& dLda_Dimension,
                        std::vector<double> const& Z,
                        std::vector<int> const& Z_Dimension,
                        std::vector<double> & dLdZ,
                        std::vector<int> const& dLdZ_Dimension)
{
    if(dLda_Dimension[0] != Z_Dimension[0]) {std::cout<<"error: row(dlDa) != cols(Z) \n";std::exit(-1);}
    if(dLda_Dimension[1] != Z_Dimension[1]) {std::cout<<"error: col(dlDa) != cosl(Z) \n";std::exit(-1);}
    if(dLda_Dimension[0] != dLdZ_Dimension[0]) {std::cout<<"error: row(dlDa) != cols(dLdZ) \n";std::exit(-1);}
    if(dLda_Dimension[1] != dLdZ_Dimension[1]) {std::cout<<"error: col(dlDa) != cosl(dLdZ) \n";std::exit(-1);}
    
    
    std::transform(dLda.begin(),
                   dLda.end(),
                   Z.begin(),
                   dLdZ.begin(),
                   [](auto const& x,auto const& y){return x*RELU_Derivative(y);}); 
}

void LinearBackward(std::vector<double>& dLda,
                    std::vector<int> const& dLda_Dimension,
                    std::vector<double> const& dLdZ,
                    std::vector<int> const& dLdZ_Dimension,
                    std::vector<double>& dLdW,
                    std::vector<int> const& dLdW_Dimension,
                    std::vector<double> & dLdb,
                    std::vector<int> const& dLdb_Dimension,
                    std::vector<double> & W,
                    std::vector<int> & W_Dimension,
                    std::vector<double> & a,
                    std::vector<int> & a_Dimension,
                    bool LastStep = false)
{
    //check dims
    if(LastStep == false)
    {
        Transpose(W,W_Dimension);
        MatrixMultiplication(dLdZ, W, dLda,dLdZ_Dimension,W_Dimension,dLda_Dimension);
        Transpose(W,W_Dimension);
    }
    Transpose(a,a_Dimension);
    MatrixMultiplication(a, dLdZ, dLdW,a_Dimension,dLdZ_Dimension,dLdW_Dimension);
    Transpose(a,a_Dimension);

    double sum = 0.0;
    int dim1 = dLdZ_Dimension[0];
    int dim2 = dLdZ_Dimension[1];

    for(int i = 0; i < dim1; i++ )
    {
        for(int j = 0; j < dim2; j++ )
        { 
            for(int k = 0; k < dim2; k++ ) {sum += dLdZ[ i * dim2 + k];}
            dLdb[i] = sum;
            sum = 0.0;
        }
    }
}

void GradientDescent(std::vector<double> & W1,
                    std::vector<double> & W2,
                    std::vector<double> const& dLdW1,
                    std::vector<double> const& dLdW2,
                    std::vector<double>& b1,
                    std::vector<double>& b2,
                    std::vector<double> const& dLdb1,
                    std::vector<double> const& dLdb2,
                    const double& LearningRate)
{
    auto DescentMove = [&](auto const& x, auto const& y){ return x - LearningRate * y;};

    std::transform(W1.begin(),
                   W1.end(),
                   dLdW1.begin(),
                   W1.begin(),
                   DescentMove);
    
    std::transform(W2.begin(),
                   W2.end(),
                   dLdW2.begin(),
                   W2.begin(),
                   DescentMove);

    std::transform(b1.begin(),
                   b1.end(),
                   dLdb1.begin(),
                   b1.begin(),
                   DescentMove);
    
    std::transform(b2.begin(),
                   b2.end(),
                   dLdb2.begin(),
                   b2.begin(),
                   DescentMove);
    
}