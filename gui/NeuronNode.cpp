#include "NeuronNode.h"

NeuronNode::NeuronNode(Image* img, std::vector<Image*>& funcImgs): Node(img),
	funcImgs(funcImgs)
{
	setClassName(_T("NeuronNode"));
	setFunctionType(Linear);
}

bool NeuronNode::IsIn(const Point& p)
{
	// verifica se o ponto está dentro do círculo
	return sqrt(pow(getPosition().x - p.x, 2) + pow(getPosition().y - p.y, 2)) * 2 <= 
		48;
}

void NeuronNode::draw(Graphics* g)
{
	if(isSelected())
	{
		g->setColor(Color::ORANGE);
		g->fillEllipse(getPosition().x - 28, getPosition().y - 28, 56, 56);		
	}
	Node::draw(g);
	Image* img = funcImgs[functionType];
	g->drawImage(img, getPosition().x + 9, getPosition().y - (img->getHeight() / 2));
}


