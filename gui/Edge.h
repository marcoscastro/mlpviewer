#ifndef _EDGE_H_
#define _EDGE_H_
#include "Node.h"
#include <algorithm>

class Edge
{
private:
	Node* first;
	Node* second;
	double weight;
	bool selected;
	Size sz;
	String weightStr;
protected:
	
public:
	Edge(Node* first, Node* second, double weight);
	
	inline void setFirst(Node* first)
	{
		this->first = first;
	}
	inline void setSecond(Node* second)
	{
		this->second = second;
	}
	inline void setWeight(double weight)
	{
		this->weight = weight;
		weightStr = trimZeroes(formatString(_T("%lf"), getWeight()));
		std::replace(weightStr.begin(), weightStr.end(), _T('.'), _T(','));
	}
	
	inline Node* getFirst()
	{
		return this->first;
	}
	inline Node* getSecond()
	{
		return this->second;
	}
	inline double getWeight()
	{
		return this->weight;
	}
	
	inline void setSelected(bool selected)
	{
		this->selected = selected;
	}
	
	inline bool isSelected() 
	{
		return selected;
	}
	void draw(Graphics* g);
	virtual bool IsIn(const Point& p);
	static String trimZeroes(const String& s);
};

#endif /* _EDGE_H_ */