#ifndef _OUTPUTNODE_H_
#define _OUTPUTNODE_H_
#include "Node.h"

class OutputNode: public Node
{
private:
	
protected:
	
public:
	OutputNode(Image * img);
	virtual bool IsIn(const Point& p);
	virtual void draw(Graphics* g);
};

#endif /* _OUTPUTNODE_H_ */