#include <ostream>

#define DEFACTFUNC ACTSIGMOID

void print(const __float128& afloat);

std::ostream& operator<< (std::ostream& stream, __float128 afloat);

char* strepr(__float128 afloat);


struct dataset
{
public:
	__float128 *inputs;
	__float128 *outputs;
};



class Cell
{
public:
	__float128* weights;
	__float128 bias;
	int nweights;

	bool actfuncsetted = false;

	Cell();
	//weights are initialised with 0
	Cell(int nweights);
	//if default1 is true, then all weights are initialised with 1; else 0
	Cell(int nweights, bool default1);
	Cell(const __float128 weights[], const int nweights, const __float128 bias);

	__float128& operator[] (int index);

	__float128 (*actfunc)(const __float128& val);
	void setactfunc( __float128 (*actfunc)(const __float128& val) );
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

	Cell& operator[](int index);

	__float128 (*actfunc)(const __float128& val);
	void setactfunc( __float128 (*actfunc)(const __float128& val) );
};

class InputLayer : public Layer
{
public:
	//int ninputs;
	InputLayer();
	InputLayer(int ninputs);

	void print();
};

class DenseLayer : public Layer
{

public:
	//int noutputs;
	DenseLayer();
	//DenseLayer(int numberofcells);
	DenseLayer(int numberofcells, int prevoutputn);
};


class NeuralNetwork
{
public:
	Layer *layers;
	int nlayers, index;
	NeuralNetwork();
	NeuralNetwork(int nlayers);
	NeuralNetwork(int nlayers, InputLayer il);
	//todo this:
	//NeuralNetwork(NeuralNetwork &nn);

	void print();
	void save();
	void save(const char* savefilename);

	Layer& operator[] (int index);
};


class Trainer
{
public:

	dataset *datasets;
	int ninps, nouts, ndatasets, ntraining, ntesting;
	NeuralNetwork nn;

	//ratio is basically ratio of training to testing datasets; default is 1/2;
	//note: MUST manually call partition;
	void partition();
	void partition(float ratio);

	Trainer();
	Trainer(NeuralNetwork &nn, const char* datafilename, int ndatasets);
	

	dataset* trainingdatasets;
	dataset* testingdatasets;


	__float128 calculatecost();
	__float128 calculatecost(dataset* datasetgroup);


};


namespace ml
{
	class Vector
	{
	public:
		__float128* list;
		int size;

		Vector();
		Vector(int size);
		Vector(int size, __float128 initval);
		Vector(int size, __float128* initvals);

		void print();

		__float128 getMagnitude();


		__float128& operator [] (int n);
	};
}


#define LEAK 0.1q
#define ALPHA 0.1q

#define ACTTANINV acttaninv
#define ACTTANH acttanh
#define ACTSIGMOID actsigmoid
#define ACTRELU actrelu
#define ACTLEAKYRELU actleakyrelu
#define ACTELU actelu
#define ACTSWISH actswish

__float128 acttaninv(const __float128& val);
__float128 acttanh(const __float128& val);
__float128 actsigmoid(const __float128& val);
__float128 actrelu(const __float128& val);
__float128 actleakyrelu(const __float128& val);
__float128 actelu(const __float128& val);
__float128 actswish(const __float128& val);

//todo: implement softmax activation function from this website: https://www.v7labs.com/blog/neural-networks-activation-functions




NeuralNetwork& operator << (NeuralNetwork &nn, Layer &layer);
std::ostream& operator<< (std::ostream& stream, ml::Vector &v);

__float128 operator * (Cell &cell, ml::Vector &v);
__float128 operator * (ml::Vector &v, Cell &cell);

ml::Vector operator * (Layer &layer, ml::Vector &v);
ml::Vector operator * (ml::Vector &v, Layer &layer);

ml::Vector operator * (const NeuralNetwork &nn, const ml::Vector &v);
ml::Vector operator * (const ml::Vector &v, const NeuralNetwork &nn);

ml::Vector operator + (ml::Vector &v1, ml::Vector &v2);
ml::Vector operator * (__float128 &fscalar, ml::Vector &v2);
ml::Vector operator * (ml::Vector &v2 ,__float128 &fscalar);
ml::Vector operator - (ml::Vector &v1, ml::Vector &v2);

NeuralNetwork operator + (NeuralNetwork& nn1, NeuralNetwork& nn2);
