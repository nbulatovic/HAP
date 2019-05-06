#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>


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
        std::vector<double> v = {0.125296170000000,-0.125296170000000,
                                -0.124719170000000,0.124719170000000,
                                -0.124713340000000,0.124713340000000,
                                -0.124708770000000,0.124708770000000};
        std::vector<int> dims = {4,2};

        if(v[0] != 0.125296170000000 || v[1] != -0.125296170000000 || v[2] != -0.124719170000000 || 
           v[3] != 0.124719170000000 || v[4] != -0.124713340000000 || v[5] != 0.124713340000000 ||
           v[6] !=  -0.124708770000000 || v[7] != 0.124708770000000){error("Transpose test: src element");}

        Transpose(v,dims);

        if(v[0] != 0.125296170000000 || v[1] != -0.124719170000000 || v[2] != -0.124713340000000 || 
           v[3] != -0.124708770000000 || v[4] != -0.125296170000000 || v[5] != 0.124719170000000 ||
           v[6] !=  0.124713340000000 || v[7] != 0.124708770000000){error("Transpose test: element");}
        if(dims[0] != 2 || dims[1] != 4){error("Transpose test: dims");}

        Transpose(v,dims);

        if(v[0] != 0.125296170000000 || v[1] != -0.125296170000000 || v[2] != -0.124719170000000 || 
           v[3] != 0.124719170000000 || v[4] != -0.124713340000000 || v[5] != 0.124713340000000 ||
           v[6] !=  -0.124708770000000 || v[7] != 0.124708770000000){error("Transpose back test: element");}
        if(dims[0] != 4 || dims[1] != 2){error("Transpose back test: dims");}


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
    //Forward
    {
      std::vector<double> W1 = { 1.624345363663241837e-02, -6.117564136500754091e-03, -5.281717522634557169e-03,
                                 -1.072968622156170518e-02, 8.654076293246784624e-03, -2.301538696880282842e-02,
                                 1.744811764216479960e-02, -7.612069008951028240e-03, 3.190390960570985580e-03,
                                 -2.493703754774100750e-03, 1.462107937044974069e-02, -2.060140709497653919e-02};
      std::vector<double> W2 = {-3.224172040135074926e-03, -3.840543546684156359e-03, 1.133769442335437472e-02, -1.099891267314030870e-02,
                                -1.724282075504357482e-03, -8.778584179213717517e-03, 4.221374671559283078e-04, 5.828152137158222786e-03};
      std::vector<double> b1 = {0.0,0.0,0.0,0.0};
      std::vector<double> b2 = {0.0,0.0};

      std::vector<double> x = {-1.100619177212921240e+00,1.144723709839614134e+00,9.015907205927955470e-01,
                                5.024943389018682316e-01, 9.008559492644118150e-01, -6.837278591743330969e-01};

      std::vector<double> Z1(4*2);
      std::vector<double> Z2(2*2);
      std::vector<double> a1(4*2);
      std::vector<double> a2;
      
      std::vector<int> W1_Dim = {4,3};
      std::vector<int> W2_Dim = {2,4};
      std::vector<int> x_Dim = {2,3};
      std::vector<int> Z1_Dim = {4,2};
      std::vector<int> Z2_Dim = {2,2};
      std::vector<int> a1_Dim = {4,2};
      int b1_Dim = 4;
      int b2_Dim = 2;


      std::vector<double> Z1_Ref = {-2.964272479736320895e-02, 6.262456863763934088e-03,
                                    9.653654186436018110e-04, 1.814073078987974222e-02,
                                    -2.504102187360131987e-02, -2.711564946435081097e-04,
                                    9.076769256074905578e-04, 2.600417028489171792e-02};
      
      std::vector<double> a2_Ref = {-1.100619177212921240e+00, 5.024943389018682316e-01,
                                    1.144723709839614134e+00, 9.008559492644118150e-01,
                                    9.015907205927955470e-01, -6.837278591743330969e-01};

      std::vector<double> Z2_Ref = {-3.413471258038671546e-03, -3.457700743175833556e-03,
                                    -2.116949821852103213e-03, -2.130940954342790128e-03};

      std::vector<double> a1_Ref = {4.925898613946372295e-01, 5.015656090992250959e-01,
                                    5.002413413359181327e-01, 5.045350583294253566e-01,
                                    4.937400716369695353e-01, 4.999322108767544903e-01,
                                    5.002269192158224076e-01, 5.065006762531044648e-01};
      
      std::vector<double> P_Ref = {4.996758696863577431e-01,5.003241303136423124e-01,
                                   4.996683101014476880e-01, 5.003316898985523675e-01};

      std::vector<double> P(2 * 2);
                                                    
      Transpose(x,x_Dim);
      LinearForwardStep(x,W1,Z1,x_Dim,W1_Dim,Z1_Dim,b1,b1_Dim);
      NonLinearStep(Z1,a1,Sigmoid);
      LinearForwardStep(a1,W2,Z2,a1_Dim,W2_Dim,Z2_Dim,b2,b2_Dim);
      Transpose(Z2,Z2_Dim);
      Softmax(Z2,Z2_Dim,P);
      Transpose(Z2,Z2_Dim);

      if(check_values(Z1,Z1_Ref,precision)){ error("Forward z1 error"); }
      if(check_values(a1,a1_Ref,precision)){ error("Forward a1 error"); }
      if(check_values(Z2,Z2_Ref,precision)){ error("Forward z2 error"); }
      if(check_values(x,a2_Ref,precision)){ error("Forward a2 error"); }
      if(check_values(P,P_Ref,precision)){ error("Forward P error"); }
    }
    //CrossEntropy
    {
       std::vector<double> x = {4.996758696863577431e-01,5.003241303136423124e-01,
                                4.996683101014476880e-01,5.003316898985523675e-01};
       std::vector<double> y = {0.0,1.0,1.0,0.0};
       double ref = 6.931549552268021497e-01;
       double res = CrossEntropy(x,y)/2.0;

       if(std::abs(ref-res) > precision){error("Loss test");}
    }

    //Softmaxback
    {
      std::vector<double> Prediction = { 0.4667508110318858,0.5332491889681141,
                                         0.7709416657675008,0.2290583342324992,
                                         0.9809437859012410,0.0190562140987590};
      std::vector<int> PredictionDimension = {3,2};
      std::vector<double> TrueValues = {0.0,1.0,1.0,0.0,0.0,1.0};
      std::vector<int> TrueValuesDimension = {3,2};
      std::vector<double> Result(2*3);
      std::vector<int> ResultDimension = {3,2};

      std::vector<double> Reference = {0.1555836036772953,-0.0763527780774997,0.3269812619670803,
                                       -0.1555836036772953,0.0763527780774997,-0.3269812619670803};

      SoftmaxBackward(Prediction,PredictionDimension,TrueValues,TrueValuesDimension,Result,ResultDimension);
      if(check_values(Reference,Result,precision)){ error("Softmaxback error"); }
    }
    //Nonlinearback
    {
      std::vector<double> Z = {1.624345363663241670e+00, -6.117564136500753813e-01,
                               -5.281717522634556961e-01, -1.072968622156170504e+00,
                               8.654076293246785179e-01, -2.301538696880282675e+00,
                               1.744811764216479988e+00, -7.612069008951027893e-01};
      std::vector<int> Z_Dim = {4,2};

      std::vector<double> W = {3.190390960570985701e-01, -2.493703754774100889e-01, 1.462107937044974104e+00,
                               -2.060140709497654044e+00, -3.224172040135074857e-01, -3.840543546684156428e-01,
                               1.133769442335437416e+00, -1.099891267314030863e+00, -1.724282075504357525e-01,
                               -8.778584179213717587e-01, 4.221374671559283143e-02, 5.828152137158222335e-01};
      std::vector<int> W_Dim = {4,3};

      std::vector<double> a = {-1.100619177212921240e+00, 1.144723709839614134e+00,
                                9.015907205927955470e-01, 5.024943389018682316e-01,
                                9.008559492644118150e-01, -6.837278591743330969e-01};
      std::vector<int> a_Dim = {3,2};
      std::vector<double> dLda = {-1.228902255186481718e-01,-9.357694342590687775e-01,
                                  -2.678880796260159070e-01, 5.303554667381860099e-01,
                                  -6.916607517253090531e-01, -3.967535268559773676e-01,
                                  -6.871727001195994111e-01, -8.452056414987195732e-01};
      std::vector<int> dLda_Dim = {4,2};

      std::vector<double> Reference  = {-1.689877934415893318e-02, -2.133506034083587077e-01,
                                        -6.251018150511211680e-02, 1.007124118370704702e-01,
                                        -1.441904839720875853e-01, -3.281762924189310371e-02,
                                        -8.698937386744942657e-02, -1.834229232874307891e-01};
      std::vector<int> Reference_Dim = {4,2};

      std::vector<double> Result(4*2);
      std::vector<int> Result_Dim = {4,2};

      NonLinearBackward(dLda,dLda_Dim,Z,Z_Dim,Result,Result_Dim,Sigmoid_Derivative);
      if(check_values(Reference,Result,precision)){ error("Nonlinearback error"); }
    }
    //Linearback
    {
        std::vector<double> dLda(2*3);
        std::vector<int> const dLda_Dimension = {2,3};
        std::vector<double> dLda_Reference = {2.381918028873391754e-03,-2.370949202892568865e-03,-2.370838199382818094e-03,
                                             -8.550820723069382789e-04, 8.511443858136322031e-04, 8.511045367886029217e-04};

        std::vector<double> dLdW(2*2);
        std::vector<int> const dLdW_Dimension = {2,2};
        std::vector<double> dLdW_Reference = {-8.095971082773248395e-02, -8.519951994845832710e-02,
                                              8.095971082773249783e-02, 8.519951994845834098e-02};

        std::vector<double>  dLdb(2);
        std::vector<int> const dLdb_Dimension = {2,1};
        std::vector<double> dLdb_Reference = {-1.655151221581837029e-01,
                                              1.655151221581837306e-01};

        std::vector<double> const dLdZ = {1.670615577130089013e-01,-1.662922326848483290e-01,-1.662844471863442752e-01,
                                         -1.670615577130089291e-01, 1.662922326848483845e-01, 1.662844471863442752e-01};
        std::vector<int> const dLdZ_Dimension = {2,3};
        std::vector<double>  a = {5.095127624714836934e-01,4.981587679717864314e-01,5.005866408542328783e-01,
                                  4.934763658267979913e-01, 5.098104740362865428e-01, 4.983203765988029610e-01};
        std::vector<int>  a_Dimension = {2,3};
        std::vector<double>  W = {1.744811764216479960e-02, -7.612069008951028240e-03,
                                  3.190390960570985580e-03,-2.493703754774100750e-03};
        std::vector<int>  W_Dimension = {2,2};

        LinearBackward(dLda,dLda_Dimension,dLdZ,dLdZ_Dimension,dLdW,dLdW_Dimension,dLdb,dLdb_Dimension,W,W_Dimension,a,a_Dimension);

        if(check_values(dLdb_Reference,dLdb,precision)){ error("linear back test: dLdb error"); }
        if(check_values(dLdW_Reference,dLdW,precision)){ error("linear back test: dLdW error"); }
        if(check_values(dLda_Reference,dLda,precision)){ error("linear back test: dLda error"); }
    }
    //Backpropagation
    {   
        const int InputLayerDimension = 3;
        const int HiddenLayerDimension = 2;
        const int OutputLayerDimension = 2;
        const int BatchSize = 4;
        const int NumberOfBatchElement = BatchSize *  InputLayerDimension;
        const int NumberOfBatchElementLabel = BatchSize *  OutputLayerDimension;

        std::vector<double> X = {1.462107937044974104e+00,-2.060140709497654044e+00,-3.224172040135074857e-01,
                                -3.840543546684156428e-01, 1.133769442335437416e+00, -1.099891267314030863e+00,
                                -1.724282075504357525e-01, -8.778584179213717587e-01, 4.221374671559283143e-02,
                                5.828152137158222335e-01, -1.100619177212921240e+00, 1.144723709839614134e+00}; 
        std::vector<double> Y = {0.000000000000000000e+00,1.000000000000000000e+00,
                                 1.000000000000000000e+00,0.000000000000000000e+00,
                                 1.000000000000000000e+00,0.000000000000000000e+00,
                                 1.000000000000000000e+00, 0.000000000000000000e+00};
        std::vector<int> X_Dimension =  {BatchSize, InputLayerDimension};
        std::vector<int> Y_Dimension =  {BatchSize, OutputLayerDimension};
        

        std::vector<double> Z1(HiddenLayerDimension * BatchSize);
        std::vector<double> a1(HiddenLayerDimension * BatchSize);
        std::vector<double> Z2(OutputLayerDimension * BatchSize);
        std::vector<double> a2(OutputLayerDimension * BatchSize);

        std::vector<double> P(OutputLayerDimension * BatchSize);

            
        std::vector<double> W1 = {1.624345363663241837e-02, -6.117564136500754091e-03, -5.281717522634557169e-03,
                                 -1.072968622156170518e-02, 8.654076293246784624e-03, -2.301538696880282842e-02};
        std::vector<double> W2 = {1.744811764216479960e-02, -7.612069008951028240e-03,
                                  3.190390960570985580e-03, -2.493703754774100750e-03};
        std::vector<double> b1 = {0.0, 0.0};
        std::vector<double> b2 = {0.0, 0.0};

        std::vector<int> Z1_Dimension = {HiddenLayerDimension, BatchSize};
        std::vector<int> a1_Dimension = {HiddenLayerDimension, BatchSize};
        std::vector<int> Z2_Dimension = {OutputLayerDimension, BatchSize};
        std::vector<int> a2_Dimension = {OutputLayerDimension, BatchSize};

        std::vector<double> dLdZ2(OutputLayerDimension * BatchSize);
        std::vector<double> dLda2(HiddenLayerDimension * BatchSize);
        std::vector<double> dLdW2(OutputLayerDimension * HiddenLayerDimension);
        std::vector<double> dLdb2(OutputLayerDimension);
        std::vector<double> dLdZ1(HiddenLayerDimension * BatchSize);
        std::vector<double> dLda1;
        std::vector<double> dLdW1(HiddenLayerDimension * InputLayerDimension);
        std::vector<double> dLdb1(HiddenLayerDimension);


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

        
        std::vector<double> dLdW1_Reference = {6.410711558283270235e-04,-5.442935375301059852e-04,-1.825892858189856222e-04,
                                               -2.301981709027503737e-04, 1.954662034604115386e-04, 6.554625906002950356e-05};
        std::vector<double> dLdW2_Reference = {-1.233907340387447593e-01,-1.249408922583610804e-01,
                                               1.233907340387447732e-01, 1.249408922583611081e-01};
        std::vector<double> dLdb1_Reference = {-8.871349410143555565e-04,
                                                3.183133197497862456e-04};
        std::vector<double> dLdb2_Reference = {-2.488451066699052250e-01,
                                                2.488451066699052805e-01}; 
         
        Transpose(X,X_Dimension);
        LinearForwardStep(X,W1,Z1,X_Dimension,W1_Dimension,Z1_Dimension,b1,b1_Dimension);
        
        NonLinearStep(Z1,a1,Sigmoid);
        LinearForwardStep(a1,W2,Z2,a1_Dimension,W2_Dimension,Z2_Dimension,b2,b2_Dimension);
        Transpose(Z2,Z2_Dimension);
        Softmax(Z2,Z2_Dimension,P);
        Transpose(Z2,Z2_Dimension);
        

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
                          Sigmoid_Derivative);
        
        LinearBackward(dLda1,dLda1_Dimension,
                        dLdZ1,dLdZ1_Dimension,
                        dLdW1,dLdW1_Dimension,
                        dLdb1,dLdb1_Dimension,
                        W1,W1_Dimension,
                        X,X_Dimension,
                        true);

        if(check_values(dLdW1,dLdW1_Reference,precision)){ error("Backpropagation test: dLdW1 error"); }
        if(check_values(dLdW2,dLdW2_Reference,precision)){ error("Backpropagation test: dLdW2 error"); }
        if(check_values(dLdb1,dLdb1_Reference,precision)){ error("Backpropagation test: dLdb1 error"); }
        if(check_values(dLdb2,dLdb2_Reference,precision)){ error("Backpropagation test: dLdb2 error"); }
    }
    std::cout << "Tests are succesfull!\n";
}
