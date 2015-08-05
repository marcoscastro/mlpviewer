#include "Node.h"

Node::Node(Image* img)
{
	setClassName(_T("Node"));
	this->img = img;
	setSelected(false);
}

void Node::draw(Graphics* g)
{
	g->drawImage(img, p.x - img->getWidth() / 2, p.y - img->getHeight() / 2);
}
