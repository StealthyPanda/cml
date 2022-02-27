#include <iostream>
#include <chrono>
#include "ml.h"

#include <quadmath.h>

//using namespace ml;
using namespace std::chrono;

int main()
{



	for (int i = 0; i < 10; ++i)
	{
		ml::Vector bruh(3);
		ml::Vector moment(3);

		moment[0] = 3;
		moment[1] = 4;
		moment[2] = 12;

		//bruh.print();
		moment.print();

		__float128 fi = __float128(i);

		ml::Vector epic = moment * fi;

		epic.print();

		std::cout << std::endl;
	}
	

	return 0;
}