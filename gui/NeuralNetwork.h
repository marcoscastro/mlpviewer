#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_
#include <gui/gui.h>
#include <vector>
#include "Node.h"
#include "Edge.h"
#include "InputNode.h"
#include "NeuronNode.h"
#include "OutputNode.h"
#include "SelectHandler.h"

class NeuralNetwork: public Control, public SelectHandler
{
private:
	Image *neuronImg;
	Image *inputImg;
	Image *outputImg;
	std::vector<Image*> funcImgs;
	std::vector<Node *> neurons;
	std::vector<Edge *> edges;
	int x, y, downX, downY;
	bool bDown;
	bool bMoving;
	int actionState;
	Node *nodeAdd;
	Edge *edgeAdd;
	Node *nodeMoving;
	Node *nodeSelected;
	Edge * edgeSelected;
private:
	enum ActionState
	{
		ActionNone = 0,
		ActionAdd,
		ActionConnect
	};
private:
	void selectNode(Node *node);
	void selectEdge(Edge *edge);
	void deleteNode(Node *node);
	void deleteEdge(Edge *edge);
	void addNeuron(int x, int y);
	void addEdge(Node *node);
	void updateAddNeuron(int x, int y);
	void updateAddEdge(int x, int y);
	Node *neuronAt(int x, int y);
	Edge* findEdge(Node* first, Node* second);
	Edge* edgeAt(int x, int y);
protected:
	virtual void getClassStyle(unsigned int& style);
	virtual void keyDown(int key, int state)
	{
		if(key == Key::Escape)
		{
			if(actionState == ActionConnect)
			{
				actionState = ActionNone;
				invalidate();
			}
			else if(actionState == ActionAdd)
			{
				actionState = ActionNone;
				invalidate();
			}
		}
		else if(key == Key::Delete)
		{
			if(nodeSelected != NULL)
			{
				Node * saveNodeSelected = nodeSelected;
				selectNode(NULL);
				deleteNode(saveNodeSelected);
			}
			else if(edgeSelected != NULL)
			{
				Edge * saveEdgeSelected = edgeSelected;
				selectEdge(NULL);
				deleteEdge(saveEdgeSelected);
			}
		}
		else if(key == Key::Up)
		{
			if(nodeSelected != NULL)
			{
				nodeSelected->setPosition(nodeSelected->getPosition().x, 
					nodeSelected->getPosition().y - 1);
				invalidate();
			}
		}
		else if(key == Key::Down)
		{
			if(nodeSelected != NULL)
			{
				nodeSelected->setPosition(nodeSelected->getPosition().x, 
					nodeSelected->getPosition().y + 1);
				invalidate();
			}
		}
		else if(key == Key::Left)
		{
			if(nodeSelected != NULL)
			{
				nodeSelected->setPosition(nodeSelected->getPosition().x - 1, 
					nodeSelected->getPosition().y);
				invalidate();
			}
		}
		else if(key == Key::Right)
		{
			if(nodeSelected != NULL)
			{
				nodeSelected->setPosition(nodeSelected->getPosition().x + 1, 
					nodeSelected->getPosition().y);
				invalidate();
			}
		}
	}
	virtual void mouseDown(int x, int y, int button)
	{
		if (button == LeftButton)
		{
			grabFocus();
			if(actionState == ActionAdd)
			{
				addNeuron(x, y);
				actionState = ActionNone;
				return;
			}
			Node *node = neuronAt(x, y);
			if(node != NULL)
			{
				selectEdge(NULL);
				selectNode(node);
				bMoving = true;
				nodeMoving = node;
				if(actionState == ActionConnect)
				{
					actionState = ActionNone;
					addEdge(node);
				}
				else
				{
					actionState = ActionConnect;
					edgeAdd->setFirst(node);
					nodeAdd->setPosition(x, y);					
				}
				this->x = node->getPosition().x;
				this->y = node->getPosition().y;
			}
			else
			{
				selectNode(node);
				actionState = ActionNone;
				Edge * edge = edgeAt(x, y);
				selectEdge(edge);
			}
			downX = x;
			downY = y;
			bDown = true;
			setCapture();
			invalidate();
		}
	}
	virtual void mouseUp(int x, int y, int button)
	{
		if (button == LeftButton)
		{
			bMoving = false;
			bDown = false;
			releaseCapture();
		}
	}
	virtual void mouseMove(int x, int y)
	{
		if(actionState == ActionAdd)
		{
			updateAddNeuron(x, y);
		}
		else if (bDown)
		{
			this->x += x - downX;
			this->y += y - downY;
			downX = x;
			downY = y;
			actionState = ActionNone;
			if(bMoving)
				nodeMoving->setPosition(this->x, this->y);
			invalidate();
		}
		else if(actionState == ActionConnect)
		{
			updateAddEdge(x, y);
		}
	}
	virtual void paint(Graphics *g)
	{
		g->setBuffered(true);
		g->setColor(Color::GRAY);
		Rect r = getClientRect();
		g->drawRect(r);
		g->setColor(Color::WHITE);
		g->fillRect(r.x + 1, r.y + 1, r.width - 2, r.height - 2);
		draw(g);
		g->flush();
	}
	void draw(Graphics *g);
	
	virtual void resized(int width, int height)
	{
		invalidate();
	}
public:
	NeuralNetwork();
	~NeuralNetwork();
	void addNeuron();
	void addInput();
	void addOutput();
	void saveToFile(const String& fileName);
	void loadFromFile(const String& fileName);
	void notifyDataChanged();
	Edge* getSelectedEdge();
	Node* getSelectedNode();
};

#endif /* _NEURALNETWORK_H_ */