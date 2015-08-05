#ifndef _SELECTHANDLER_H_
#define _SELECTHANDLER_H_
#include <gui/Object.h>
#include "Node.h"

class SelectHandler
{
private:
	sigslot::signal3<Object*, Node*, bool> signalNode;
	sigslot::signal3<Object*, Edge*, bool> signalEdge;
protected:
	void emitNodeSelected(Object* sender, Node* node, bool selected)
	{
		signalNode.emit(sender, node, selected);
	}
	void emitEdgeSelected(Object* sender, Edge* edge, bool selected)
	{
		signalEdge.emit(sender, edge, selected);
	}
public:
	template<class desttype>
	void setOnNodeSelected(desttype* pclass, void (desttype::*pmemfun)(Object*, Node*, bool))
	{
		signalNode.connect(pclass, pmemfun);
	}
	template<class desttype>
	void setOnEdgeSelected(desttype* pclass, void (desttype::*pmemfun)(Object*, Edge*, bool))
	{
		signalEdge.connect(pclass, pmemfun);
	}
};

#endif /* _SELECTHANDLER_H_ */