#ifndef _NODE_H_
#define _NODE_H_
#include <gui/gui.h>
#include "ResourceManager.h"
#include <math.h>

/**
 * classe responsável por desenhar o neurônio
 */
class Node: public Object
{
private:
	Point p;
	Image* img;
	bool selected;
public:
	Node(Image* img);

	inline void setSelected(bool selected)
	{
		this->selected = selected;
	}
	
	inline bool isSelected() 
	{
		return selected;
	}
	
	inline void setPosition(int x, int y)
	{
		this->p.x = x;
		this->p.y = y;
	}

	inline void setPosition(const Point& p)
	{
		setPosition(p.x, p.y);
	}
	
	inline const Point& getPosition() 
	{
		return p;
	}
	
	inline Image* getImage()
	{
		return img;
	}

	virtual void draw(Graphics* g);

	virtual bool IsIn(const Point& p) = 0;
};

#endif
