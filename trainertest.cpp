#include <iostream>
#include <chrono>
#include "ml.h"

using namespace ml;
using namespace std::chrono;

int main()
{
	auto start = high_resolution_clock::now();




	NeuralNetwork ellipseboi(3);

	InputLayer il(2);
	DenseLayer dl(4, 2);
	DenseLayer ol(2, 4);

	ellipseboi << il;
	ellipseboi << dl;
	ellipseboi << ol;



	Trainer tr(ellipseboi, "test2.td", 1000);
	tr.partition();

	std::cout << tr.calculatecost() << std::endl;


	int k = 100;
	for (int i = 0; i < k; ++i)
	{
		NeuralNetwork grad = tr.getgradient();
		//grad.print();
		grad = (grad * OFFSHOOT);

		tr.nn = tr.nn - grad;

		std::cout << std::endl << tr.calculatecost() << std::endl;
	}




	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;
}