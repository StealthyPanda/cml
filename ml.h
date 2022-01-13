

int testfunc();


class Cell
{
public:
	long double* weights;
	long double bias;
	int nweights;

	Cell();
	Cell(int size);
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
	DenseLayer(int numberofcells, int prevoutputn);

};


class NeuralNetwork
{
public:
	Layer *layers;
	int nlayers, index;
	NeuralNetwork(int nlayers);
	NeuralNetwork(int nlayers, InputLayer il);
};

NeuralNetwork operator << (NeuralNetwork &nn, Layer layer);