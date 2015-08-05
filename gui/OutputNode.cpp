#include "OutputNode.h"

OutputNode::OutputNode(Image* img): Node(img)
{
	setClassName(_T("OutputNode"));
}

bool OutputNode::IsIn(const Point& p)
{
	int mw = 20 / 2;
	int mh = 20 / 2;
	return p.x >= getPosition().x - mw && p.x <= getPosition().x + mw &&
		   p.y >= getPosition().y - mh && p.y <= getPosition().y + mh;
}

void OutputNode::draw(Graphics* g)
{
	if(isSelected())
	{
		g->setColor(Color::ORANGE);
		g->fillEllipse(getPosition().x - 14, getPosition().y - 14, 28, 28);		
	}
	Node::draw(g);
}
