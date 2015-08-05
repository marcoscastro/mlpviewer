#include "NeuralNetwork.h"
#include "scaling.h"
#include <map>
#include <string.h>
#define RN_SIGN "1.1"

NeuralNetwork::NeuralNetwork()
{
	neuronImg = new Image(_T(":neuron:"));
	inputImg = new Image(_T(":input:"));
	outputImg = new Image(_T(":output:"));
	funcImgs.push_back(new Image(_T(":funcao_linear:")));
	funcImgs.push_back(new Image(_T(":funcao_degree:")));
	funcImgs.push_back(new Image(_T(":funcao_bipolar:")));
	funcImgs.push_back(new Image(_T(":funcao_logistic:")));
	funcImgs.push_back(new Image(_T(":funcao_hiperbolic:")));
	setClassName(_T("NeuralNetworkPanel"));
	bDown = false;
	bMoving = false;
	x = y = 0;
	nodeSelected = NULL;
	edgeSelected = NULL;
	nodeAdd = new NeuronNode(neuronImg, funcImgs);
	edgeAdd = new Edge(NULL, nodeAdd, 0);
	actionState = ActionNone;
	setOwnerDraw(true);
}

NeuralNetwork::~NeuralNetwork()
{
	std::vector<Node *>::iterator it;
	for(it = neurons.begin(); it != neurons.end(); it++)
		delete *it;
	std::vector<Edge *>::iterator ite;
	for(ite = edges.begin(); ite != edges.end(); ite++)
		delete *ite;
	std::vector<Image *>::iterator itm;
	for(itm = funcImgs.begin(); itm != funcImgs.end(); itm++)
		delete *itm;
	delete edgeAdd;
	delete nodeAdd;
	delete inputImg;
	delete neuronImg;
}

void NeuralNetwork::addNeuron()
{
	actionState = ActionAdd;
	delete nodeAdd;
	nodeAdd = new NeuronNode(neuronImg, funcImgs);
	edgeAdd->setSecond(nodeAdd);
	invalidate();
}

void NeuralNetwork::addInput()
{
	actionState = ActionAdd;
	delete nodeAdd;
	nodeAdd = new InputNode(inputImg);
	edgeAdd->setSecond(nodeAdd);
	invalidate();
}

void NeuralNetwork::addOutput()
{
	actionState = ActionAdd;
	delete nodeAdd;
	nodeAdd = new OutputNode(outputImg);
	edgeAdd->setSecond(nodeAdd);
	invalidate();
}

void NeuralNetwork::addNeuron(int x, int y)
{
	Node *node = nodeAdd;
	node->setPosition(x, y);
	neurons.push_back(node);
	nodeAdd = new NeuronNode(neuronImg, funcImgs);
	edgeAdd->setSecond(nodeAdd);
	invalidate();
}

void NeuralNetwork::draw(Graphics *g)
{
	Graphics2D *g2d = (Graphics2D *)g;
	g2d->setSmoothingMode(SmoothingMode::AntiAlias8x8);
	std::vector<Edge *>::iterator ite;
	for(ite = edges.begin(); ite != edges.end(); ite++)
	{
		Edge *edge = *ite;
		edge->draw(g);
	}
	if(!bMoving && actionState == ActionConnect)
	{
		edgeAdd->draw(g);
	}
	std::vector<Node *>::iterator it;
	for(it = neurons.begin(); it != neurons.end(); it++)
	{
		Node *node = *it;
		node->draw(g);
	}
	if(actionState == ActionAdd)
	{
		nodeAdd->draw(g);
	}
}

Node *NeuralNetwork::neuronAt(int x, int y)
{
	std::vector<Node *>::iterator it;
	Point p(x, y);
	for(it = neurons.begin(); it != neurons.end(); it++)
	{
		Node *node = *it;
		if(node->IsIn(p))
			return node;
	}
	return NULL;
}

void NeuralNetwork::updateAddNeuron(int x, int y)
{
	nodeAdd->setPosition(x, y);
	invalidate();
}

void NeuralNetwork::updateAddEdge(int x, int y)
{
	nodeAdd->setPosition(x, y);
	invalidate();
}

Edge *NeuralNetwork::findEdge(Node *first, Node *second)
{
	std::vector<Edge *>::iterator ite;
	for(ite = edges.begin(); ite != edges.end(); ite++)
	{
		Edge *edge = *ite;
		if(edge->getFirst() == first && edge->getSecond() == second)
			return edge;
	}
	return NULL;
}

Edge *NeuralNetwork::edgeAt(int x, int y)
{
	std::vector<Edge *>::iterator ite;
	Point p(x, y);
	for(ite = edges.begin(); ite != edges.end(); ite++)
	{
		Edge *edge = *ite;
		if(edge->IsIn(p))
			return edge;
	}
	return NULL;
}

void NeuralNetwork::addEdge(Node *node)
{
	Edge *edge = findEdge(edgeAdd->getFirst(), node);
	if(edge != NULL)
		return;
	if(edgeAdd->getFirst()->is(_T("InputNode")) && node->is(_T("InputNode")))
		return;
	if(edgeAdd->getFirst()->is(_T("OutputNode")) && node->is(_T("OutputNode")))
		return;
	if(edgeAdd->getFirst()->is(_T("OutputNode")) && node->is(_T("InputNode")))
		return;
	if(edgeAdd->getFirst()->is(_T("InputNode")) && node->is(_T("OutputNode")))
		return;
	edge = new Edge(edgeAdd->getFirst(), node, edgeAdd->getWeight());
	edges.push_back(edge);
	invalidate();
}

void NeuralNetwork::selectNode(Node *node)
{
	if(nodeSelected == node)
		return;
	if(nodeSelected != NULL)
	{
		nodeSelected->setSelected(false);
		emitNodeSelected(this, nodeSelected, false);
	}
	nodeSelected = node;
	if(nodeSelected == NULL)
		return;
	nodeSelected->setSelected(true);
	emitNodeSelected(this, nodeSelected, true);
}

void NeuralNetwork::selectEdge(Edge* edge)
{
	if(edgeSelected == edge)
		return;
	if(edgeSelected != NULL)
	{
		edgeSelected->setSelected(false);
		emitEdgeSelected(this, edgeSelected, false);
	}
	edgeSelected = edge;
	if(edgeSelected == NULL)
		return;
	edgeSelected->setSelected(true);
	emitEdgeSelected(this, edgeSelected, true);
}


void NeuralNetwork::deleteNode(Node *node)
{
	std::vector<Edge *>::iterator ite;
	ite = edges.begin();
	while(ite != edges.end())
	{
		Edge *edge = *ite;
		if(edge->getFirst() != node && edge->getSecond() != node)
		{
			ite++;
			continue;
		}
		delete *ite;
		ite = edges.erase(ite);
	}
	std::vector<Node *>::iterator itn;
	for(itn = neurons.begin(); itn != neurons.end(); itn++)
	{
		Node *nodeIte = *itn;
		if(nodeIte != node)
			continue;
		delete nodeIte;
		neurons.erase(itn);
		break;
	}
	actionState = ActionNone;
	invalidate();
}

void NeuralNetwork::deleteEdge(Edge* edge)
{
	std::vector<Edge *>::iterator ite;
	for(ite = edges.begin(); ite != edges.end(); ite++)
	{
		Edge *edgeIte = *ite;
		if(edgeIte != edge)
			continue;
		delete edgeIte;
		edges.erase(ite);
		break;
	}
	actionState = ActionNone;
	invalidate();
}

void NeuralNetwork::getClassStyle(unsigned int& style)
{
}

void NeuralNetwork::notifyDataChanged()
{
	invalidate();
}

Edge* NeuralNetwork::getSelectedEdge()
{
	return edgeSelected;
}

Node* NeuralNetwork::getSelectedNode()
{
	return nodeSelected;
}


void NeuralNetwork::saveToFile(const String& fileName)
{
	File * file = new File(fileName, File::WriteOnly);
	int intVal;
	size_t sizeVal;
	double doubleVal;
	char ver[] = RN_SIGN;
	std::vector<Node *>::iterator it;
	std::vector<Edge *>::iterator ite;
	std::map<Node*,int> nodeMap;
	int i = 1;
	
	file->write(ver, 3); // sign
	sizeVal = neurons.size();
	file->write(&sizeVal, sizeof(size_t)); // neuron count
	sizeVal = edges.size();
	file->write(&sizeVal, sizeof(size_t)); // edge count
	// save each neuron
	for(it = neurons.begin(); it != neurons.end(); it++)
	{
		Node *node = *it;
		if(node->is(_T("NeuronNode")))
			intVal = 1;
		else if(node->is(_T("InputNode")))
			intVal = 2;
		else
			intVal = 3;
		file->write(&intVal, sizeof(int)); // type, 1 -> Neuron, 2 -> Input, 3 ->Output
		if(intVal == 1)
			intVal = ((NeuronNode*)node)->getFunctionType();
		else
			intVal = 0;
		file->write(&intVal, sizeof(int)); // activation function
		intVal = node->getPosition().x;
		file->write(&intVal, sizeof(int)); // x position
		intVal = node->getPosition().y;
		file->write(&intVal, sizeof(int)); // y position
		nodeMap[node] = i;
		i++;
	}
	for(ite = edges.begin(); ite != edges.end(); ite++)
	{
		Edge *edge = *ite;
		intVal = nodeMap[edge->getFirst()];
		file->write(&intVal, sizeof(int)); // first node id
		intVal = nodeMap[edge->getSecond()];
		file->write(&intVal, sizeof(int)); // second node id
		doubleVal = edge->getWeight();
		file->write(&doubleVal, sizeof(double)); // connection weight
	}
	delete file;
}

void NeuralNetwork::loadFromFile(const String& fileName)
{
	File * file = new File(fileName, File::ReadOnly);
	size_t neuronCount;
	size_t edgeCount;
	int actFunc;
	double weight;
	char ver[4];
	size_t i;
	int nodeType, xPos, yPos, firstNodeID, secondNodeID;
	
	ver[3] = '\0';
	file->read(ver, 3); // sign
	if(strcmp(ver, RN_SIGN) != 0)
	{
		delete file;
		throw Exception(formatString(_T("Version %s not supported, required %s."), 
			ConvertFromUtf8(ver).c_str(), ConvertFromUtf8(RN_SIGN).c_str()));
	}
	file->read(&neuronCount, sizeof(size_t)); // neuron count
	file->read(&edgeCount, sizeof(size_t)); // edge count
	// save each neuron
	for(i = 1; i <= neuronCount; i++)
	{
		Node *node;
		file->read(&nodeType, sizeof(int)); // type, 1 -> Neuron, 2 -> Input, 3 ->Output
		if(nodeType == 1)
			node = new NeuronNode(neuronImg, funcImgs);
		else if(nodeType == 2)
			node = new InputNode(inputImg);
		else
			node = new OutputNode(outputImg);
		file->read(&actFunc, sizeof(int)); // activation function
		file->read(&xPos, sizeof(int)); // x position
		file->read(&yPos, sizeof(int)); // y position
		delete nodeAdd;
		edgeAdd->setSecond(NULL);
		if(nodeType == 1)
			((NeuronNode*)node)->setFunctionType(actFunc);
		nodeAdd = node;
		addNeuron(xPos, yPos);
	}
	for(i = 0; i < edgeCount; i++)
	{
		file->read(&firstNodeID, sizeof(int)); // first node id
		file->read(&secondNodeID, sizeof(int)); // second node id
		file->read(&weight, sizeof(double)); // connection weight
		edgeAdd->setFirst(neurons[firstNodeID - 1]);
		edgeAdd->setWeight(weight);
		addEdge(neurons[secondNodeID - 1]);
	}
	delete file;
	invalidate();
}