#include <iostream>
#include "big_number.h"
#include <ctime>

#define T 3

int main()
{
	//test for big number
	 /*   Big_number a,b,c,d,result_1, result_2, result_3;
	    int T = 1000, M =1000;
	    do{
	        int n = 1 + rand() % M;
	        int m = 1 + rand() % M;
	        a.Rand(n);
	        b.Rand(m);
	        c = a/b;
	        d = a%b;
	        result_1 = b*c;
	        result_2 = result_1 + d;
	        result_3 = a - d;
	        std::cout << T << std::endl;
	    }
	    while(a==result_2 && result_3==result_1 && d<b && --T);
	    if (T) std::cout<< a << b << c << d <<std::endl;
	*/

	//test for Pow
	/*
	Big_number x,y,m;
	x.Rand(10);
	std::cin >> y >> m;
	std::cout << "x = " << x << " y = " << y << " m = " << m <<std::endl;
	x.Pow(y, m);
	std::cout << "x = " << x;*/

	//tests for Karacuba
	/*Big_number a, b, just, kar;
	a.Rand(10000), b.Rand(10000);
	unsigned int time = clock();
	for (int i = 0; i < T; i++)
	{
		just = a * b;
	}

	std::cout << (clock() - time) / 1000.0 << std::endl;
	time = clock();
	for (int i = 0; i < T; i++)
	{
		kar = a.Karacuba(a, b);
		//std::cout << i << std::endl;
	}

	std::cout << (clock() - time) / 1000.0 << std::endl;*/
	/*Big_number a, b, just, kar;
	for (int i = 0; i < 10; i++)
	{
		a.Rand(1+rand()%100), b.Rand(1 + rand() % 100);
		kar = a.Karacuba(a, b);
		just = a * b;
		if (just != kar)
		{
			std::cout << std::endl << "Karacuba isn't right" << std::endl;
		}
	}*/

	//test for Barrett

	Big_number x, mod, z, r_bur, r_std;
	mod.Rand(rand() % 50);
	z.z_for_Barret(mod);
	for (int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		x.Rand((rand() % 50)+50);
		r_bur = x.Mod_by_Barret(mod, z);
		r_std = x % mod;
		if (r_bur != r_std)
		{
			std::cout << "shit :c" << std::endl;
		}
		else
			std::cout << i << std::endl;
	}

	system("pause");

}
