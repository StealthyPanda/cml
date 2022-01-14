

int testfunc();


class Cell
{
public:
	long double* weights;
	long double bias;
	int nweights;

	Cell();
	//weights are initialised with 0
	Cell(int nweights);
	//if default1 is true, then all weights are initialised with 1; else 0
	Cell(int nweights, bool default1);
	Cell(const long double weights[], const int nweights, const long double bias);
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

namespace ml
{
	class Vector
	{
	public:
		long double* list;
		int size;
		Vector(int size);
		Vector(int size, long double initval);
		Vector(int size, long double* initvals);

		void print();
	};
}

NeuralNetwork operator << (NeuralNetwork &nn, Layer &layer);

long double operator * (Cell cell, ml::Vector v);
long double operator * (ml::Vector v, Cell cell);

ml::Vector operator * (Layer layer, ml::Vector v);
ml::Vector operator * (ml::Vector v, Layer layer);

ml::Vector operator * (NeuralNetwork nn, ml::Vector v);
ml::Vector operator * (ml::Vector v, NeuralNetwork nn);