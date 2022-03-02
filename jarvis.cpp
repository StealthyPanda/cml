#include <iostream>
#include "ml.h"
#include <chrono>

using namespace std::chrono;

int main()
{
	auto start high_resolution_clock::now();


	NeuralNetwork jarvis(3);

	InputLayer il(2);
	DenseLayer dl(4, 2);
	DenseLayer ol(2, 4);

	jarvis << il << dl << ol;

	Trainer obadiah(jarvis, "test2d.td", 1000);

	auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl
	return 0;
}
