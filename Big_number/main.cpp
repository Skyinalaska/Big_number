#include <iostream>
#include "big_number.h"
//#include <ctime>

int main()
{
    //test for big number
/*
//    Big_number a,b,c,d,result_1, result_2, result_3;
//    int T = 1000, M =1000;
//    do{
//        int n = 1 + rand() % M;
//        int m = 1 + rand() % M;
//        a.Rand(n);
//        b.Rand(m);
//        c = a/b;
//        d = a%b;
//        result_1 = b*c;
//        result_2 = result_1 + d;
//        result_3 = a - d;
//        std::cout << T << std::endl;
//    }
//    while(a==result_2 && result_3==result_1 && d<b && --T);
//    if (T) std::cout<< a << b << c << d <<std::endl;
    */

    //test for Pow
/*
    Big_number x,y,m;
    x.Rand(10);
    std::cin >> y >> m;
    std::cout << "x = " << x << " y = " << y << " m = " << m <<std::endl;
    x.Pow(y, m);
    std::cout << "x = " << x;*/

    //test for Mul by Karacuba

    /*Big_number a,b, just, kar;
    a.Rand(10), b.Rand(10);
    std::cout << "a = " << a << "b = " << b << std::endl;
    just = a*b;
    kar = a.Mul_by_Karacuba(a, b);
    std::cout << just << std::endl << kar;*/
	
    /*Big_number a;
	a.Rand(3);
	std::cout << a << std::endl;
    a.right_shift(1);
    std::cout << "a = " << a;*/

	//test for mod by Barret
	Big_number tmp;
	tmp.Rand(5);
	tmp.Mod_by_Barret(tmp, tmp);
	system("pause");
}
