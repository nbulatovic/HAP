#include "matrix.hpp"
 
void MatrixTest(double precision)
{
    auto Error = [](auto str){ std::cout << "matrix.hpp error in: " << str << "\n"; std::exit(-1); };
	auto check_values = [](auto const& x, auto const& y, double prec)
						{
							bool check = true;
							for(int i=0;i<(int)x.size();i++)
							{
								check = check && (std::abs(x[0]-y[0]) > prec);
							}
							return check;
						};

    //Default constructor test and indexing:
    {
		Matrix<double> u;
		if(u.size() != 0)         { Error("default contructor test [size]");}
		if(u.dim() != 0)         { Error("default contructor test [dim]");}
		if(u.begin() != u.end())  { Error("default contructor test [begin == end]");}
		if(u.cbegin() != u.cend()){ Error("default contructor test [cbegin == cend]");}
    }
    //Test constructor size check:
	{
		std::cout<<"Expected error: 'Linear size doesn't match with the data size! Default constructor called.'\n";
		Matrix<double> a(9,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		
		if(a.size() != 0)         { Error("contructor size check test [size]");}
		if(a.dim() != 0)         { Error("contructor size check test [dim]");}
		if(a.begin() != a.end())  { Error("contructor size check test [begin == end]");}
		if(a.cbegin() != a.cend()){ Error("contructor size check test [cbegin == cend]");}
	}
	//Test list initialization and indexing:
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});

		if(a.size() != 9)   { Error("initializer list constructor test [size]");}
		if(a.dim() != 3)   { Error("initializer list constructor test [dim]");}
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99)   { Error("initializer list constructor test [indexing with []]");   }
		if(a(0,0) != 3.5 || a(0,1) != 5.2 || a(0,2) != 9.3 || a(1,0) != 6.6 ||
           a(1,1) != 1.2 || a(1,2) != 0.0 || a(2,0) != 10.0 || a(2,1) != 24.0 || 
           a(2,2) != 99.99)   { Error("initializer list constructor test [indexing with ()]");   }
        
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.begin()) != a.end()) {Error("initializer list constructor test [begin + 9 == end]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.cbegin()) != a.cend()) {Error("initializer list constructor test [cbegin + 9 == cend]"); }
    }
	//Test empty constructor
	{
		Matrix<double> a(3);
		if(a.size() != 9)   { Error("empty constructor test [size]");}
		if(a.dim() != 3)   { Error("empty constructorr test [dim]");}

		if(a[0] != 0.0 || a[1] != 0.0 || a[2] != 0.0|| a[3] != 0.0 ||
           a[4] != 0.0 || a[5] != 0.0 || a[6] != 0.0 || a[7] != 0.0 || 
           a[8] != 0.0)   { Error("empty constructor test [indexing with []]");   }
		if(a(0,0) != 0.0 || a(0,1) != 0.0 || a(0,2) != 0.0 || a(1,0) != 0.0 ||
           a(1,1) != 0.0 || a(1,2) != 0.0 || a(2,0) != 0.0 || a(2,1) != 0.0 || 
           a(2,2) != 0.0)   { Error("empty constructor test [indexing with ()]");   }
		
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.begin()) != a.end()) {Error("empty constructor test [begin + 9 == end]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.cbegin()) != a.cend()) {Error("empty constructor test [cbegin + 9 == cend]"); }
	}
	//Test function constructor
	{
		Matrix<double> a(9,[](auto const& x){return sq(x);});

		if(a.size() != 9)   { Error("function constructor test [size]");}
		if(a.dim() != 3)   { Error("function constructorr test [dim]");}

		if(a[0] != 0.0 || a[1] != 1.0 || a[2] != 4.0|| a[3] != 9.0 ||
           a[4] != 16.0 || a[5] != 25.0 || a[6] != 36.0 || a[7] != 49.0 || 
           a[8] != 64.0)   { Error("function constructor test [indexing with []]");   }
		if(a(0,0) != 0.0 || a(0,1) != 1.0 || a(0,2) != 4.0 || a(1,0) != 9.0 ||
           a(1,1) != 16.0 || a(1,2) != 25.0 || a(2,0) != 36.0 || a(2,1) != 49.0 || 
           a(2,2) != 64.0)   { Error("function constructor test [indexing with ()]");   }
		
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.begin()) != a.end()) {Error("function constructor test [begin + 9 == end]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.cbegin()) != a.cend()) {Error("function constructor test [cbegin + 9 == cend]"); }

	}
    //Test copy constructor and indexing:
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		Matrix<double> b{a};

        if(b.size() != 9)   { Error("copy constructor test [size]");}
		if(b.dim() != 3)   { Error("copy constructor test [dim]");}
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)   { Error("copy constructor test [elements]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.begin()) != b.end()) { Error("copy constructor test [begin + 9 == end]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.cbegin()) != b.cend()) { Error("copy constructor test [cbegin + 3 == cend]");}
		if(a.size() != 9)   { Error("copy constructor test [src size]");}
		if(a.dim() != 3)   { Error("copy constructor test [src dim]");}
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99)   { Error("copy constructor test [src elements]");}
    }
    //Test move constructor and indexing:
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		Matrix<double> b{ std::move(a) };

		if(a.size() != 0)  { Error("move constructor test [src size]");}
		if(a.dim() != 0)   { Error("move constructor test [src dim]");}
		if(a.begin() != a.end())  { Error("move constructor test [src begin == src end]");}
		if(b.size() != 9)  { Error("move constructor test [size]");}
		if(b.dim() != 3)   { Error("move constructor test [dim]");}
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)   { Error("move constructor test [elements]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.begin()) != b.end()) { Error("move constructor test [begin + 9 == end]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.cbegin()) != b.cend()) { Error("move constructor test [cbegin + 9 == cend]");}
	}

	//Test matrix function constructor1
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		double scl = 5.0;
		Matrix<double> ref(3,{6.12500000000000e+01,1.35200000000000e+02,4.32450000000000e+02,
   							  2.17800000000000e+02,7.20000000000000e+00,0.00000000000000e+00,
   							  5.00000000000000e+02,2.88000000000000e+03,4.99900005000000e+04});
		Matrix<double> res(a,[=](auto const& x){return sq(x)*scl;}); 

		if(a.size() != 9)  { Error("matrix function  constructor1 test [src size]");}
		if(a.dim() != 3)   { Error("matrix function constructor1 test [src dim]");}
		if(res.size() != 9)  { Error("matrix function constructor1 test [res size]");}
		if(res.dim() != 3)   { Error("matrix function constructor1 test [res dim]");}
		if(check_values(ref,res,precision)){ Error("matrix function constructor1 test [res elements]"); }
	}
	//Test matrix function constructor2
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		double scl = 5.0;
		Matrix<double> ref(3,{95.5, 463.0000000000001,66.65,33.0,62.0,200.0,483.5,508.2,500.0});
		Matrix<double> res(a,b,[=](auto const& x,auto const& y){return (x+y)*scl;}); 

		if(a.size() != 9)  { Error("matrix function  constructor2 test [src size]");}
		if(a.dim() != 3)   { Error("matrix function constructor2 test [src dim]");}
		if(b.size() != 9)  { Error("matrix function constructor2 test [src size]");}
		if(b.dim() != 3)   { Error("matrix function constructor2 test [src dim]");}
		if(res.size() != 9)  { Error("matrix function constructor2 test [res size]");}
		if(res.dim() != 3)   { Error("matrix function constructor2 test [res dim]");}
		if(check_values(ref,res,precision)){ Error("matrix function constructor2 test [res elements]"); }
	}
    //Test assignment:
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		Matrix<double> b;

		b = a;
		if(b.size() != 9)   { Error("assignment test [size]");         }
		if(b.dim() != 3)   { Error("assignment test [dim]");         }
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)   { Error("assignment test [elements]");     }
		if(a.size() != 9)   { Error("assignment test [src size]");     }
		if(a.dim() != 3)   { Error("assignment test [src dim]");     }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99)   { Error("assignment test [src elements]"); }
    }
    //Test self assignment:
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		a = a;

		if(a.size() != 9) { Error("self assignment test2 [size]");     }
		if(a.dim() != 3) { Error("self assignment test2 [dim]");     }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99) { Error("self assignment test [elements]"); }
	}
	//Test move assignment:
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		Matrix<double> b;

		b = std::move(a);
		if(a.begin() != a.end()) { Error("assignment test [src begin == src end]"); }
		if(a.size() != 0)        { Error("assignment test [src size]");             }
		if(b.size() != 9)        { Error("assignment test [size]");                 }
		if(a.dim() != 0)        { Error("assignment test [src dim]");             }
		if(b.dim() != 3)        { Error("assignment test [dim]");                 }
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)        { Error("assignment test [elements]");}
	}
	//Test self move assignment:
	{
		Matrix<double> a(3,{3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99});
		a = std::move(a);
		if(a.size() != 9)    {Error("self assignment test [size]");     }
		if(a.dim() != 3)    {Error("self assignment test [dim]");     }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99){ Error("self assignment test [elements]"); }
	}
	//Test aritmetic += operator test
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{19.1, 92.6,13.33,6.6,12.4,40.0,96.7,101.64,100.00});
		a += b;

		if(a.size() != 9) { Error("+= test  [size]");     }
		if(a.dim() != 3) { Error("+= test [dim]");     }
		if(b.size() != 9){ Error("+= test [src size]");     }
		if(b.dim() != 3){ Error("+= test [src dim]");     }
		if(b[0] != 15.6 || b[1] != 87.4 || b[2] != 4.03 || b[3] != 0.0 ||
           b[4] != 11.2 || b[5] != 40.0 || b[6] != 86.7 || b[7] != 77.64 || 
           b[8] != 0.01)   { Error("+= test [src elements]"); }
		if(check_values(ref,a,precision)){ Error("+= test [res elements]"); }
	}
	//Test aritmetic -= operator test
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{-12.1,-82.2,5.27,6.6,-10.0,-40.0,-76.7,-53.64,99.98});
		a -= b;

		if(a.size() != 9) { Error("-= test  [size]");     }
		if(a.dim() != 3) { Error("-= test [dim]");     }
		if(b.size() != 9){ Error("-= test [src size]");     }
		if(b.dim() != 3){ Error("-= test [src dim]");     }
		if(b[0] != 15.6 || b[1] != 87.4 || b[2] != 4.03 || b[3] != 0.0 ||
           b[4] != 11.2 || b[5] != 40.0 || b[6] != 86.7 || b[7] != 77.64 || 
           b[8] != 0.01)   { Error("-= test [src elements]"); }
		if(check_values(ref,a,precision)){ Error("-= test [res elements]"); }
	}
	//Test aritmetic *= operator test
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		double scalar = 4.49876315;
		Matrix<double> ref(3,{15.745671025,23.393568380000001,41.838497295000003,
    						  29.69183679, 5.39851578,0.0,
    						  44.987631500000006,107.970315600000006,449.831327368500013});
		a *= scalar;

		if(a.size() != 9) { Error("*= test  [size]");     }
		if(a.dim() != 3) { Error("*= test [dim]");     }
		if(check_values(ref,a,precision)){ Error("*= test [res elements]"); }
	}
	//Test aritmetic /= operator test
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		double scalar = 4.49876315;
		Matrix<double> ref(3,{0.777991613094812,1.155873253740864,2.06723485765193,
    						  1.467069898978789,0.266739981632507,0.0,
    						  2.222833180270893,5.334799632650142,22.226108969528656});
		a /= scalar;

		if(a.size() != 9) { Error("/= test  [size]");     }
		if(a.dim() != 3) { Error("/= test [dim]");     }
		if(check_values(ref,a,precision)){ Error("/= test [res elements]"); }
	}
	//Test set_to_default
	{
		Matrix<double> a(2,{3.5 , 5.2 ,  9.3, 6.6});
		a.set_to_default();
		if(a.size() != 0) { Error("set_to_default test  [size]");     }
		if(a.dim() != 0) { Error("set_to_default test [dim]");     }
		if(a.begin() != a.end())  { Error("set_to_default  test [begin == end]");}
		if(a.cbegin() != a.cend()){ Error("set_to_default test [cbegin == cend]");}


	} 
	//Test operator+ (l-value, l-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{19.1, 92.6,13.33,6.6,12.4,40.0,96.7,101.64,100.00});
		Matrix<double> res = a + b;

		if(a.size() != 9) { Error("operator+ test (l-value, l-value)  [src size]");     }
		if(a.dim() != 3) { Error("operator+ test (l-value, l-value) [src dim]");     }
		if(b.size() != 9) { Error("operator+ test (l-value, l-value)  [src size]");     }
		if(b.dim() != 3) { Error("operator+ test (l-value, l-value) [src dim]");     }
		if(res.size() != 9) { Error("operator+ test (l-value, l-value)  [size]");     }
		if(res.dim() != 3) { Error("operator+ test (l-value, l-value) [dim]");     }

		if(b[0] != 15.6 || b[1] != 87.4 || b[2] != 4.03 || b[3] != 0.0 ||
           b[4] != 11.2 || b[5] != 40.0 || b[6] != 86.7 || b[7] != 77.64 || 
           b[8] != 0.01){ Error("operator+ test [src elements]"); }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99){ Error("operator+ test [src elements]"); }

		if(check_values(ref,res,precision)){ Error("operator+ test (l-value, l-value) [elements]"); }
	}
	//Test operator+ (r-value, l-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{19.1, 92.6,13.33,6.6,12.4,40.0,96.7,101.64,100.00});
		Matrix<double> res = std::move(a) + b;

		if(a.size() != 0) { Error("operator+ test (r-value, l-value)  [src size]");     }
		if(a.dim() != 0) { Error("operator+ test (r-value, l-value) [src dim]");     }
		if(b.size() != 9) { Error("operator+ test (r-value, l-value)  [src size]");     }
		if(b.dim() != 3) { Error("operator+ test (r-value, l-value) [src dim]");     }
		if(res.size() != 9) { Error("operator+ test (r-value, l-value)  [size]");     }
		if(res.dim() != 3) { Error("operator+ test (r-value, l-value) [dim]");     }

		if(b[0] != 15.6 || b[1] != 87.4 || b[2] != 4.03 || b[3] != 0.0 ||
           b[4] != 11.2 || b[5] != 40.0 || b[6] != 86.7 || b[7] != 77.64 || 
           b[8] != 0.01){ Error("operator+ test (l-value, l-value) [src elements]"); }

		if(check_values(ref,res,precision)){ Error("operator+ test (l-value, l-value) [elements]"); }
	}
	//Test operator+ (l-value, r-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{19.1, 92.6,13.33,6.6,12.4,40.0,96.7,101.64,100.00});
		Matrix<double> res = a + std::move(b);

		if(b.size() != 0) { Error("operator+ test (l-value, r-value)  [src size]");     }
		if(b.dim() != 0) { Error("operator+ test (l-value, r-value) [src dim]");     }
		if(a.size() != 9) { Error("operator+ test (l-value, r-value)  [src size]");     }
		if(a.dim() != 3) { Error("operator+ test (l-value, r-value) [src dim]");     }
		if(res.size() != 9) { Error("operator+ test (l-value, r-value)  [size]");     }
		if(res.dim() != 3) { Error("operator+ test (l-value, r-value) [dim]");     }

		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99){ Error("operator+ test (l-value, r-value) [src elements]"); }

		if(check_values(ref,res,precision)){ Error("operator+ test (l-value, r-value) [elements]"); }
	}
	//Test operator+ (r-value, r-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{19.1, 92.6,13.33,6.6,12.4,40.0,96.7,101.64,100.00});
		Matrix<double> res = std::move(a) + std::move(b);

		if(b.size() != 0) { Error("operator+ test (r-value, r-value)  [src size]");     }
		if(b.dim() != 0) { Error("operator+ test (r-value, r-value) [src dim]");     }
		if(a.size() != 0) { Error("operator+ test (r-value, r-value)  [src size]");     }
		if(a.dim() != 0) { Error("operator+ test (r-value, r-value) [src dim]");     }
		if(res.size() != 9) { Error("operator+ test (r-value, r-value)  [size]");     }
		if(res.dim() != 3) { Error("operator+ test (r-value, r-value) [dim]");     }

		if(check_values(ref,res,precision)){ Error("operator+ test (r-value, r-value) [elements]"); }
	}

	//Test operator- (l-value, l-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{-12.1,-82.2,5.27,6.6,-10.0,-40.0,-76.7,-53.64,99.98});
		Matrix<double> res = a - b;

		if(a.size() != 9) { Error("operator- test (l-value, l-value)  [src size]");     }
		if(a.dim() != 3) { Error("operator- test (l-value, l-value) [src dim]");     }
		if(b.size() != 9) { Error("operator- test (l-value, l-value)  [src size]");     }
		if(b.dim() != 3) { Error("operator- test (l-value, l-value) [src dim]");     }
		if(res.size() != 9) { Error("operator- test (l-value, l-value)  [size]");     }
		if(res.dim() != 3) { Error("operator- test (l-value, l-value) [dim]");     }

		if(b[0] != 15.6 || b[1] != 87.4 || b[2] != 4.03 || b[3] != 0.0 ||
           b[4] != 11.2 || b[5] != 40.0 || b[6] != 86.7 || b[7] != 77.64 || 
           b[8] != 0.01){ Error("operator- test [src elements]"); }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99){ Error("operator- test [src elements]"); }

		if(check_values(ref,res,precision)){ Error("operator- test (l-value, l-value) [elements]"); }
	}
	//Test operator- (r-value, l-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{-12.1,-82.2,5.27,6.6,-10.0,-40.0,-76.7,-53.64,99.98});
		Matrix<double> res = std::move(a) - b;

		if(a.size() != 0) { Error("operator- test (r-value, l-value)  [src size]");     }
		if(a.dim() != 0) { Error("operator- test (r-value, l-value) [src dim]");     }
		if(b.size() != 9) { Error("operator- test (r-value, l-value)  [src size]");     }
		if(b.dim() != 3) { Error("operator- test (r-value, l-value) [src dim]");     }
		if(res.size() != 9) { Error("operator- test (r-value, l-value)  [size]");     }
		if(res.dim() != 3) { Error("operator- test (r-value, l-value) [dim]");     }

		if(b[0] != 15.6 || b[1] != 87.4 || b[2] != 4.03 || b[3] != 0.0 ||
           b[4] != 11.2 || b[5] != 40.0 || b[6] != 86.7 || b[7] != 77.64 || 
           b[8] != 0.01){ Error("operator- test (l-value, l-value) [src elements]"); }

		if(check_values(ref,res,precision)){ Error("operator- test (l-value, l-value) [elements]"); }
	}
	//Test operator- (l-value, r-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{-12.1,-82.2,5.27,6.6,-10.0,-40.0,-76.7,-53.64,99.98});
		Matrix<double> res = a - std::move(b);

		if(b.size() != 0) { Error("operator- test (l-value, r-value)  [src size]");     }
		if(b.dim() != 0) { Error("operator- test (l-value, r-value) [src dim]");     }
		if(a.size() != 9) { Error("operator- test (l-value, r-value)  [src size]");     }
		if(a.dim() != 3) { Error("operator- test (l-value, r-value) [src dim]");     }
		if(res.size() != 9) { Error("operator- test (l-value, r-value)  [size]");     }
		if(res.dim() != 3) { Error("operator- test (l-value, r-value) [dim]");     }

		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99){ Error("operator- test (l-value, r-value) [src elements]"); }

		if(check_values(ref,res,precision)){ Error("operator- test (l-value, r-value) [elements]"); }
	}
	//Test operator- (r-value, r-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});
		Matrix<double> ref(3,{-12.1,-82.2,5.27,6.6,-10.0,-40.0,-76.7,-53.64,99.98});
		Matrix<double> res = std::move(a) - std::move(b);

		if(b.size() != 0) { Error("operator- test (r-value, r-value)  [src size]");     }
		if(b.dim() != 0) { Error("operator- test (r-value, r-value) [src dim]");     }
		if(a.size() != 0) { Error("operator- test (r-value, r-value)  [src size]");     }
		if(a.dim() != 0) { Error("operator- test (r-value, r-value) [src dim]");     }
		if(res.size() != 9) { Error("operator- test (r-value, r-value)  [size]");     }
		if(res.dim() != 3) { Error("operator- test (r-value, r-value) [dim]");     }

		if(check_values(ref,res,precision)){ Error("operator- test (r-value, r-value) [elements]"); }
	}
	//Test operator* (l-value, scalar)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		double scalar = 4.49876315;
		Matrix<double> ref(3,{15.745671025,23.393568380000001,41.838497295000003,
    						  29.69183679, 5.39851578,0.0,
    						  44.987631500000006,107.970315600000006,449.831327368500013});
		Matrix<double> res = a*scalar;

		if(a.size() != 9) { Error("operator* (l-value, scalar) test  [src size]");}
		if(a.dim() != 3) { Error(" operator* (l-value, scalar) test [src dim]");}
		if(res.size() != 9) { Error("operator* (l-value, scalar) test  [size]");}
		if(res.dim() != 3) { Error(" operator* (l-value, scalar) test [dim]");}


		if(check_values(ref,res,precision)){ Error("operator* (l-value, scalar) test [res elements]"); }
	}
	//Test operator* (r-value, scalar)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		double scalar = 4.49876315;
		Matrix<double> ref(3,{15.745671025,23.393568380000001,41.838497295000003,
    						  29.69183679, 5.39851578,0.0,
    						  44.987631500000006,107.970315600000006,449.831327368500013});
		Matrix<double> res = std::move(a)*scalar;

		if(a.size() != 0) { Error("operator* (r-value, scalar) test  [src size]");}
		if(a.dim() != 0) { Error(" operator* (r-value, scalar) test [src dim]");}
		if(res.size() != 9) { Error("operator* (r-value, scalar) test  [size]");}
		if(res.dim() != 3) { Error(" operator* (r-value, scalar) test [dim]");}


		if(check_values(ref,res,precision)){ Error("operatorr* (r-value, scalar) test [res elements]"); }
	}
	//Test operator* (scalar,l-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		double scalar = 4.49876315;
		Matrix<double> ref(3,{15.745671025,23.393568380000001,41.838497295000003,
    						  29.69183679, 5.39851578,0.0,
    						  44.987631500000006,107.970315600000006,449.831327368500013});
		Matrix<double> res = scalar*a;

		if(a.size() != 9) { Error("operator* (scalar,l-value) test  [src size]");}
		if(a.dim() != 3) { Error(" operator* (scalar,l-value) test [src dim]");}
		if(res.size() != 9) { Error("operator* (scalar,l-value) test  [size]");}
		if(res.dim() != 3) { Error(" operator* (scalar,l-value) test [dim]");}


		if(check_values(ref,res,precision)){ Error("operator* (scalar,l-value) test [res elements]"); }
	}
	//Test operator* (scalar,r-value)
	{
		Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
		double scalar = 4.49876315;
		Matrix<double> ref(3,{15.745671025,23.393568380000001,41.838497295000003,
    						  29.69183679, 5.39851578,0.0,
    						  44.987631500000006,107.970315600000006,449.831327368500013});
		Matrix<double> res = scalar*std::move(a);

		if(a.size() != 0) { Error("operator* (scalar,r-value) test  [src size]");}
		if(a.dim() != 0) { Error(" operator* (scalar,r-value) test [src dim]");}
		if(res.size() != 9) { Error("operator* (scalar,r-value) test  [size]");}
		if(res.dim() != 3) { Error(" operator* (scalar,r-value) test [dim]");}


		if(check_values(ref,res,precision)){ Error("operator* (scalar,r-value) test [res elements]"); }
	}
	//Test operator/ (l-value, scalar)
	{
	Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
	double scalar = 4.49876315;
	Matrix<double> ref(3,{0.777991613094812,1.155873253740864,2.06723485765193,
    						  1.467069898978789,0.266739981632507,0.0,
    						  2.222833180270893,5.334799632650142,22.226108969528656});
	Matrix<double> res = a/scalar;

	if(a.size() != 9) { Error("operator/ (l-value, scalar) test  [src size]");}
	if(a.dim() != 3) { Error(" operator/ (l-value, scalar) test [src dim]");}
	if(res.size() != 9) { Error("operator/ (l-value, scalar) test  [size]");}
	if(res.dim() != 3) { Error(" operator/ (l-value, scalar) test [dim]");}

	if(check_values(ref,res,precision)){ Error("operator/ (l-value, scalar) test [res elements]"); }
	}
	//Test  matmul operator* (l-value, l-value)
	{
	Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
	Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});

	Matrix<double> ref(3,{860.9100000000001,1086.192,222.198,
    					  102.96,590.2800000000001,74.598,
						  8825.1329999999998,8906.0235999999986,1001.2999});
	Matrix<double> res = a*b;

	if(res.size() != 9) { Error("matmul operator* (l-value, l-value) test  [size]");}
	if(res.dim() != 3) { Error(" matmul operator* (l-value, l-value) test [dim]");}
	if(check_values(ref,res,precision)){ Error("matmul operator* (l-value, l-value) test [res elements]"); }
	}
	//Test  matmul operator* (r-value, l-value)
	{
	Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
	Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});

	Matrix<double> ref(3,{860.9100000000001,1086.192,222.198,
    					  102.96,590.2800000000001,74.598,
						  8825.1329999999998,8906.0235999999986,1001.2999});
	Matrix<double> res = std::move(a)*b;

	if(a.size() != 0) { Error("matmul operator* (r-value, l-value) test  [src size]");}
	if(a.dim() != 0) { Error(" matmul operator* (r-value, l-value) test [src dim]");}
	if(res.size() != 9) { Error("matmul operator* (r-value, l-value) test  [size]");}
	if(res.dim() != 3) { Error(" matmul operator* (r-value, l-value) test [dim]");}
	if(check_values(ref,res,precision)){ Error("matmul operator* (r-value, l-value) test [res elements]"); }
	}
	//Test  matmul operator* (l-value, r-value)
	{
	Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
	Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});

	Matrix<double> ref(3,{860.9100000000001,1086.192,222.198,
    					  102.96,590.2800000000001,74.598,
						  8825.1329999999998,8906.0235999999986,1001.2999});
	Matrix<double> res = a*std::move(b);

	if(b.size() != 0) { Error("matmul operator* (l-value, r-value) test  [src size]");}
	if(b.dim() != 0) { Error(" matmul operator* (l-value, r-value) test [src dim]");}
	if(res.size() != 9) { Error("matmul operator* (l-value, r-value) test  [size]");}
	if(res.dim() != 3) { Error(" matmul operator* (l-value, r-value) test [dim]");}
	if(check_values(ref,res,precision)){ Error("matmul operator* (l-value, r-value) test [res elements]"); }
	}
	//Test  matmul operator* (l-value, r-value)
	{
	Matrix<double> a(3,{3.5 , 5.2 ,  9.3, 6.6,  1.2,  0.0, 10.0,  24.0, 99.99});
	Matrix<double> b(3,{15.6, 87.4, 4.03, 0.0, 11.2, 40.0, 86.7, 77.64, 0.01});

	Matrix<double> ref(3,{860.9100000000001,1086.192,222.198,
    					  102.96,590.2800000000001,74.598,
						  8825.1329999999998,8906.0235999999986,1001.2999});
	Matrix<double> res = std::move(a)*std::move(b);

	if(b.size() != 0) { Error("matmul operator* (l-value, r-value) test  [src size]");}
	if(b.dim() != 0) { Error(" matmul operator* (l-value, r-value) test [src dim]");}
	if(a.size() != 0) { Error("matmul operator* (l-value, r-value) test  [src size]");}
	if(a.dim() != 0) { Error(" matmul operator* (l-value, r-value) test [src dim]");}
	if(res.size() != 9) { Error("matmul operator* (l-value, r-value) test  [size]");}
	if(res.dim() != 3) { Error(" matmul operator* (l-value, r-value) test [dim]");}
	if(check_values(ref,res,precision)){ Error("matmul operator* (l-value, r-value) test [res elements]"); }
	}
	
		


    std::cout << "All tests are successful!\n";
}; 
int main(int, char**)
{
    MatrixTest(1e-13);

}
