#include <iostream>
#include "ml.h"
#include <thread>
#include <quadmath.h>
#include <chrono>

using namespace std::chrono;



int main(int argc, char const *argv[])
{
	auto start = high_resolution_clock::now();

	NeuralNetwork nn = NeuralNetwork::extract(argv[1]);

	Trainer tr(nn, argv[2], 1000);

	ml::Vector input(tr.ninps, tr.datasets[std::stoi(argv[3])].inputs);
	ml::Vector output(tr.nouts, tr.datasets[std::stoi(argv[3])].outputs);

	ml::Vector modeloutput = nn * input;

	modeloutput.print();
	output.print();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;
}