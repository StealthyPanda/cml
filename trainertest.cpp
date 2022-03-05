#include <iostream>
#include <chrono>
#include <quadmath.h>
#include "ml.h"

//using namespace ml;
using namespace std::chrono;

//IMPORTANT NOTE:
//IMPLEMENT ~ClassName() (destructor) for all the classes to make sure memory is managed tight and stuff

int main()
{
	
	auto start = high_resolution_clock::now();

	//std::cout << RAND_MAX << std::endl;


	NeuralNetwork ellipseboi = NeuralNetwork::extract("ellipseboi19.nn");

	Trainer somethingelse(ellipseboi, "test2.td", 1000);
	somethingelse.partition();

	std::cout << "EPIC BRUH MOMENT" << std::endl;
	std::cout << somethingelse.calculatecost() << std::endl;

	int nnn = 20;
	__float128 factor = powq(10.0q, -8.0q);
	srand(time(0));
	__float128 costs[nnn];

	__float128 lowest = 1.0q;
	NeuralNetwork lowestnn;


	for(int j = 0; j < nnn; j++)
	{
		NeuralNetwork changed = (1.0q * ellipseboi);

		Trainer tr(changed, "test2.td", 1000);
		tr.partition();


		if (j == 0)
		{
			Trainer bufferer(ellipseboi, "test2.td", 1000);
			bufferer.partition();
			costs[0] = bufferer.calculatecost();
		}
		else
		{
			for (int x = 1; x < changed.nlayers; ++x)
			{
				for (int y = 0; y < changed[x].ncells; ++y)
				{
					for (int z = 0; z < changed[x][y].nweights; ++z)
					{
						changed[x][y][z] += (rand() * factor * powq(-1, (rand() % 2)));
					}
					changed[x][y].bias += (rand() * factor * powq(-1, (rand() % 2)));
				}
			}
			tr.nn = changed;
		}


		//tr.nn.print();


		int k = 10;
		for (int i = 0; i < k; ++i)
		{
			NeuralNetwork grad = tr.getgradient();
			//grad.print();
			grad = (grad * OFFSHOOT);

			tr.nn = tr.nn - grad;

			if (i == (k-1))
			{
				__float128 cost = tr.calculatecost();
				costs[j] = cost;
				std::cout << std::endl << cost << std::endl;
				/*if (cost < 0.4)
				{
					std::string name = "networks/ellipseboi" + std::to_string(j) + ".nn";
					tr.nn.save(name.c_str());
				}*/
				if (cost < lowest)
				{
					lowest = cost;
					lowestnn = (tr.nn * 1.0q);
				}
			}
		}

		//NeuralNetwork *cp = &changed;

		//delete cp;
	}

	lowestnn.save("ellipseboi19.nn");

	ml::Vector cv(nnn, costs);

	cv.print();




	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;
}
