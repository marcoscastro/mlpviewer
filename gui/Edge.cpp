#include "Edge.h"
#include <math.h>

Edge::Edge(Node *first, Node *second, double weight)
{
	setFirst(first);
	setSecond(second);
	setWeight(weight);
	setSelected(false);
}

void Edge::draw(Graphics *g)
{
	int x1 = first->getPosition().x;
	int y1 = first->getPosition().y;
	int x2 = second->getPosition().x;
	int y2 = second->getPosition().y;
	if(isSelected())
		g->setColor(Color::ORANGE);
	else
		g->setColor(Color::BLACK);
	g->drawLine(x1, y1, x2, y2);
	sz = g->getTextSize(weightStr);
	if(isSelected())
		g->setColor(Color(0xF0, 0xF0, 0xF0));
	else
		g->setColor(Color(0xE0, 0xF0, 0xE0));
	g->fillRoundRect((x1 + x2) / 2 - 6,
			  (y1 + y2) / 2 - 6, sz.width + 12, sz.height + 12, 4, 4);
	g->setColor(Color(0, 127, 255));
	g->drawRoundRect((x1 + x2) / 2 - 6,
	              (y1 + y2) / 2 - 6, sz.width + 12, sz.height + 12, 4, 4);
	g->setColor(Color::BLUE);
	g->drawString(weightStr, (x1 + x2) / 2,
	              (y1 + y2) / 2);
}

bool Edge::IsIn(const Point& p)
{
	int x1 = first->getPosition().x;
	int y1 = first->getPosition().y;
	int x2 = p.x;
	int y2 = p.y;
	int x3 = second->getPosition().x;
	int y3 = second->getPosition().y;
	double d;
	int dist = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
	if (dist == 0)
	{
		dist = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
		d = sqrt(dist);
	}
	else
	{
		double t = ((x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1))
		           / (double) dist;
		if (t < 0)
		{
			dist = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
			d = sqrt(dist);
		}
		else if (t > 1)
		{
			dist = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
			d = sqrt(dist);
		}
		else
		{
			double x = x1 + t * (x3 - x1);
			double y = y1 + t * (y3 - y1);
			d = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
		}
	}
	if (fabs(d) < 4)
		return true;
	int mw = (sz.width + 12) / 2;
	int mh = (sz.height + 12) / 2;
	x1 = (x1 + x3) / 2 + mw;
	y1 = (y1 + y3) / 2 + mh;
	return x2 >= x1 - mw && x2 <= x1 + mw &&
		   y2 >= y1 - mh && y2 <= y1 + mh;
}

String Edge::trimZeroes(const String& s)
{
	size_t c = s.size();
	while(c > 0 && s[c - 1] == '0')
		c--;
	if(c > 0 && (s[c - 1] == _T('.') || s[c - 1] == _T(',')))
		c--;
	if(c == 0 && s.size() > 0)
		c = 1;
	return String(s, 0, c);
}


