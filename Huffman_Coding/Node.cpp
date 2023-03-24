#include "Node.h"

Node::Node(char c, int a, Node* l, Node* r)
	:character(c), amount(a), left(l), right(r)
{
}

Node::~Node()
{
	delete right;
	delete left;
}

bool Node::operator()(Node* l, Node* r)
{
	return l->amount > r->amount;
}
