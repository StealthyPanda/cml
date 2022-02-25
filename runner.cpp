#include <iostream>
#include <chrono>
#include "ml.h"

#include <quadmath.h>

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

/*int main()
{
	auto start = high_resolution_clock::now();



	NeuralNetwork jarvis = NeuralNetwork(3);

	InputLayer il = InputLayer(2);
	DenseLayer dl1 = DenseLayer(4, 2);
	//DenseLayer dl2 = DenseLayer(2000, 2000);
	DenseLayer ol = DenseLayer(2, 4);


	jarvis << il << dl1 << ol;

	
	

	Trainer obadiah = Trainer(jarvis, "test2.td", 400);

	

	obadiah.partition();
	
	

	//for (int i = 0; i < 10000; ++i)
	//{
	//	__float128 cost = obadiah.calculatecost();
	//	if (i == 9999) std::cout << cost << std::endl;
	//}
	//__float128 cost = obadiah.calculatecost();
	
	//std::cout << cost << std::endl;


	//std::cout << "Size of obadiah: " << sizeof obadiah << ", jarvis: " << sizeof (NeuralNetwork) << ", __float128: " << sizeof(__float128) << ", cost: " << sizeof(cost) << ", il: " << sizeof(il) << std::endl;

	



	__float128 cost = obadiah.calculatecost();
	std::cout << "Cost of jarvis: " << cost << std::endl;

	//std::cout << expq(1) << std::endl;
	//std::cout << actsigmoid(-0.93) << std::endl;
	//std::cout << actrelu(26) << std::endl;
	//std::cout << actleakyrelu(-0.1) << std::endl;



	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;	
}*/

int main()
{
	auto start = high_resolution_clock::now();

	NeuralNetwork epicbruhmoment = NeuralNetwork(3);
	InputLayer il(2);
	DenseLayer dl(4, 2);
	DenseLayer al(4, 4);
	DenseLayer ol(2, 4);

	epicbruhmoment << il;
	epicbruhmoment << dl;
	//epicbruhmoment << al;
	epicbruhmoment << ol;

	//epicbruhmoment.print();

	Trainer tr(epicbruhmoment, "test2.td", 500);
	tr.partition();

	//ml::Vector firstinp(2, tr.trainingdatasets[1].inputs), firstout(2, tr.trainingdatasets[1].outputs);
	//firstinp.print();
	//firstout.print();

	//int k = 200;

	/*for (int i = 0; i < k; ++i)
	{
		ml::Vector nout = (epicbruhmoment * firstinp);
		if (i == (k-1)) nout.print();
	}*/

	//OutputCache oc(epicbruhmoment, firstinp);
	//oc.outputs[2].print();

	/*for (int i = 0; i < k; ++i)
	{
		ml::Vector nout = output(epicbruhmoment, firstinp, oc, 2, 0);
		if (i == (k-1)) nout.print();
	}*/
	//OutputCache *ocs = OutputCache::getoutputcaches(epicbruhmoment, tr.trainingdatasets, tr.ntraining, tr.ninps);
	//ocs[0][2].print();

	std::cout << tr.calculatecost() << std::endl;
	///std::cout << tr.getcost(epicbruhmoment, tr.ninps, tr.nouts, tr.trainingdatasets, tr.ntraining, ocs, 3, 0) << std::endl;
	//std::cout << tr.getcost(epicbruhmoment, tr.ninps, tr.nouts, tr.trainingdatasets, tr.ntraining, ocs, 3, 0) << std::endl;
	//std::cout << tr.getcost(epicbruhmoment, tr.ninps, tr.nouts, tr.trainingdatasets, tr.ntraining, ocs, 3, 0) << std::endl;

	/*std::cout << "omae wa" << std::endl;
	ml::Vector buffinput(2, tr.trainingdatasets[0].inputs), idealoutput(2, tr.trainingdatasets[0].outputs);
	std::cout << "mou" << std::endl;
	ml::Vector buffoutput = output(epicbruhmoment, buffinput, ocs[0], 0, 0);
	std::cout << "shindeiru" << std::endl;*/
	//std::cout << tr.getcost(epicbruhmoment, tr.ninps, tr.nouts, tr.trainingdatasets, tr.ntraining, ocs, 3, 0) << std::endl;


	NeuralNetwork grad = tr.getgradient();
	grad.print();
	//grad = (grad * -1.0q);

	NeuralNetwork newnn = (epicbruhmoment - grad);

	Trainer tr2(newnn, "test2.td", 500);
	tr2.partition();

	std::cout << std::endl << tr2.calculatecost() << std::endl;


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << std::endl << "Time taken: " << duration.count() << "micros or " << (duration.count()/1000000.) << "s" << std::endl;
	return 0;
}

/*int main()
{
	NeuralNetwork n1(3), n2(3);

	InputLayer il1(2), il2(2);
	DenseLayer dl1(4, 2), dl2(4, 2);
	DenseLayer ol1(2, 4), ol2(2, 4);

	n1 << il1;
	n1 << dl1;
	n1 << ol1;
	n1[1][0][0] = 69420.0q;

	n2 << il2;
	n2 << dl2;
	n2 << ol2;
	n2[2][0].bias = -3.141592q;

	std::cout << "N1: " << n1.nlayers << std::endl;
	n1.print();

	std::cout << std::endl << "N2: " << n2.nlayers << std::endl;
	n2.print();

	std::cout << std::endl << "\nN2 ends here fam\n" << std::endl;

	NeuralNetwork n3 = (n1 + n2);
	std::cout << std::endl << "N3: " << n3.nlayers <<std::endl;
	n3.print();

	return 0;
}*/