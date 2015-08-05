#include "InputNode.h"

InputNode::InputNode(Image* img): Node(img)
{
	setClassName(_T("InputNode"));
}

bool InputNode::IsIn(const Point& p)
{
	int mw = 20 / 2;
	int mh = 20 / 2;
	return p.x >= getPosition().x - mw && p.x <= getPosition().x + mw &&
		   p.y >= getPosition().y - mh && p.y <= getPosition().y + mh;
}

void InputNode::draw(Graphics* g)
{
	if(isSelected())
	{
		g->setColor(Color::ORANGE);
		g->fillRect(getPosition().x - 14, getPosition().y - 14, 28, 28);		
	}
	Node::draw(g);
}
