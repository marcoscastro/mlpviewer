#ifndef _INPUTNODE_H_
#define _INPUTNODE_H_
#include "Node.h"

class InputNode: public Node
{
public:
	InputNode(Image*img);
	virtual bool IsIn(const Point& p);
	virtual void draw(Graphics* g);
};

#endif /* _INPUTNODE_H_ */