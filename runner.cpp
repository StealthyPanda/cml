#include <iostream>
#include <chrono>
#include "ml.h"

using namespace ml;
using namespace std::chrono;

//g++ runner.cpp ml.cpp -o builds/runner -std=gnu++11 -lquadmath
/*int main()
{
	NeuralNetwork nn = NeuralNetwork(4);

	InputLayer input = InputLayer(2);
	DenseLayer middle1 = DenseLayer(4, 2);
	DenseLayer middle2 = DenseLayer(4, 4);
	DenseLayer output = DenseLayer(2, 4);

	nn << input << middle1 << middle2 << output;

	nn.print();

	__float128 inp[2] = {3.0q, -1.0q};

	Vector inpvect = Vector(2, inp);

	(nn*inpvect).print();

	return 0;
}*/

/*int main()
{
	NeuralNetwork  jarvis = NeuralNetwork(2);

	InputLayer il = InputLayer(2);
	DenseLayer dl = DenseLayer(4);
	DenseLayer ol = DenseLayer(2);

	jarvis << il << dl << ol;

	Trainer obadiah = Trainer(jarvis, "test.td", 50);

	obadiah.partition(0.5);

	std::cout << "Training: " << std::endl;
	for(int i = 0; i < obadiah.ntraining; i++)
	{
		std::cout << i << " " << obadiah.trainingdatasets[i].inputs[0] << std::endl;
	}

	std::cout << "Testing: " << std::endl;
	for(int i = 0; i < obadiah.ntesting; i++)
	{
		std::cout << i << " " << obadiah.testingdatasets[i].inputs[0] << std::endl;
	}

	std::cout << obadiah.datasets[obadiah.ndatasets-1].inputs[0] << std::endl;

	return 0;
}
*/

int main()
{

	auto start = high_resolution_clock::now();



	NeuralNetwork jarvis = NeuralNetwork(3);

	InputLayer il = InputLayer(2);
	DenseLayer dl = DenseLayer(4, 2);
	DenseLayer ol = DenseLayer(2, 4);


	jarvis << il << dl << ol;




	Trainer obadiah = Trainer(jarvis, "test.td", 50);

	obadiah.partition();
	
	/*Vector bruhbruh = Vector(2, obadiah.trainingdatasets[0].outputs);

	std::cout << bruhbruh << std::endl;

	Vector bruhbruh2 = Vector(2, obadiah.trainingdatasets[1].outputs);

	std::cout << bruhbruh2 << std::endl;*/

	

	/*for (int i = 0; i < 10000; ++i)
	{
		__float128 cost = obadiah.calculatecost();
		if (i == 9999) std::cout << cost << std::endl;
	}*/
	__float128 cost = obadiah.calculatecost();
	
	std::cout << cost << std::endl;

	





	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;	
}