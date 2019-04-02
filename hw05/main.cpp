#include "matrix.hpp"

void MatrixTest()
{
    auto Error = [](auto str){ std::cout << "matrix.hpp error in: " << str << "\n"; std::exit(-1); };

    //Default constructor test and indexing:
    {
    Matrix<double> u;
    if(u.size() != 0)         { Error("default contructor test [size]");           }
	if(u.begin() != u.end())  { Error("default contructor test [begin == end]");   }
    if(u.cbegin() != u.cend()){ Error("default contructor test [cbegin == cend]"); }
    }
    //Test list initialization and indexing:
	{
		Matrix<double> a = {3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99};

		if(a.size() != 9)                            { Error("initializer list constructor test [size]");               }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99)   { Error("initializer list constructor test [indexing with []]");   }
		if(a(0,0) != 3.5 || a(0,1) != 5.2 || a(0,2) != 9.3 || a(1,0) != 6.6 ||
           a(1,1) != 1.2 || a(1,2) != 0.0 || a(2,0) != 10.0 || a(2,1) != 24.0 || 
           a(2,2) != 99.99)   { Error("initializer list constructor test [indexing with ()]");   }
        
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.begin()) != a.end()) {Error("initializer list constructor test [begin + 9 == end]");   }
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(a.cbegin()) != a.cend()) {Error("initializer list constructor test [cbegin + 9 == cend]"); }
     }
     //Test copy constructor and indexing:
	{
		Matrix<double> a = {3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99};
		Matrix<double> b{a};

        if(b.size() != 9)   { Error("copy constructor test [size]");}
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)   { Error("copy constructor test [elements]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.begin()) != b.end()) { Error("copy constructor test [begin + 9 == end]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.cbegin()) != b.cend()) { Error("copy constructor test [cbegin + 3 == cend]");}
		if(a.size() != 9)   { Error("copy constructor test [src size]");}
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99)   { Error("copy constructor test [src elements]");}
    }
    //Test move constructor and indexing:
	{
		Matrix<double> a = {3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99};
		Matrix<double> b{ std::move(a) };

		if(a.size() != 0)                            { Error("move constructor test [src size]");             }
		if(a.begin() != a.end())                     { Error("move constructor test [src begin == src end]"); }
		if(b.size() != 9)                            { Error("move constructor test [size]");                 }
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)   { Error("move constructor test [elements]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.begin()) != b.end()) { Error("move constructor test [begin + 9 == end]");}
		if(++ ++ ++ ++ ++ ++ ++ ++ ++(b.cbegin()) != b.cend()) { Error("move constructor test [cbegin + 9 == cend]");}
	}
    //Test assignment:
	{
		Matrix<double> a = {3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99};
		Matrix<double> b;

		b = a;
		if(b.size() != 9)   { Error("assignment test [size]");         }
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)   { Error("assignment test [elements]");     }
		if(a.size() != 9)   { Error("assignment test [src size]");     }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99)   { Error("assignment test [src elements]"); }
    }
    //Test self assignment:
	{
		Matrix<double> a = {3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99};

		a = a;
		if(a.size() != 9) { Error("self assignment test [size]");     }
		if(a[0] != 3.5 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 6.6 ||
           a[4] != 1.2 || a[5] != 0.0 || a[6] != 10.0 || a[7] != 24.0 || 
           a[8] != 99.99) { Error("self assignment test [elements]"); }
	}
	//Test move assignment:
	{
		Matrix<double> a = {3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99};
		Matrix<double> b;

		b = std::move(a);
		if(a.begin() != a.end()) { Error("assignment test [src begin == src end]"); }
		if(a.size() != 0)        { Error("assignment test [src size]");             }
		if(b.size() != 9)        { Error("assignment test [size]");                 }
		if(b[0] != 3.5 || b[1] != 5.2 || b[2] != 9.3 || b[3] != 6.6 ||
           b[4] != 1.2 || b[5] != 0.0 || b[6] != 10.0 || b[7] != 24.0 || 
           b[8] != 99.99)        { Error("assignment test [elements]");             }
}


    std::cout << "All tests are successful!\n";
};
int main(int, char**)
{
    MatrixTest();
    /* Matrix<double> a = {3.5, 5.2, 9.3, 6.6, 1.2, 0.0, 10.0, 24.0, 99.99};
    for(int i=0;i<3;i++)
    {for(int j=0;j<3;j++)
        {std::cout<<a(i,j)<<std::endl;}
    }

    std::cout<<(a(2,1) == 24.0); */
}
