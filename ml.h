#include <ostream>

void print(const __float128& afloat);

std::ostream& operator<< (std::ostream& stream, __float128 afloat);

char* strepr(__float128 afloat);



class Cell
{
public:
	__float128* weights;
	__float128 bias;
	int nweights;

	Cell();
	//weights are initialised with 0
	Cell(int nweights);
	//if default1 is true, then all weights are initialised with 1; else 0
	Cell(int nweights, bool default1);
	Cell(const __float128 weights[], const int nweights, const __float128 bias);
};




class Layer
{

public:
	int ncells = 0;
	Layer();
	Layer(int size);
	Layer(Cell cells[], int ncells);
	Cell* layer;

	//dont use this for now:
	Layer append(Cell &cell);

	void print();

};

class InputLayer : public Layer
{
public:
	InputLayer();
	InputLayer(int ninputs);

	void print();
};

class DenseLayer : public Layer
{

public:
	DenseLayer();
	DenseLayer(int numberofcells);
	DenseLayer(int numberofcells, int prevoutputn);
};


class NeuralNetwork
{
public:
	Layer *layers;
	int nlayers, index;
	NeuralNetwork(int nlayers);
	NeuralNetwork(int nlayers, InputLayer il);
	//todo this:
	//NeuralNetwork(NeuralNetwork &nn);

	void print();
	void save();
	void save(const char* savefilename);
};


class Trainer
{
public:
	Trainer();
	Trainer(const char* datafilename);

	__float128** trainingdatasets;
	__float128** traininglabels;

	__float128** testingdatasets;
	__float128** testinglabels;
};


namespace ml
{
	class Vector
	{
	public:
		__float128* list;
		int size;
		Vector(int size);
		Vector(int size, __float128 initval);
		Vector(int size, __float128* initvals);

		void print();
	};
}

NeuralNetwork& operator << (NeuralNetwork &nn, Layer &layer);

__float128 operator * (Cell cell, ml::Vector v);
__float128 operator * (ml::Vector v, Cell cell);

ml::Vector operator * (Layer layer, ml::Vector v);
ml::Vector operator * (ml::Vector v, Layer layer);

ml::Vector operator * (NeuralNetwork nn, ml::Vector v);
ml::Vector operator * (ml::Vector v, NeuralNetwork nn);