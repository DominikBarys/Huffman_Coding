#pragma once

class Node
{
public:
	Node() = delete;
	Node(char c, int a, Node* l = nullptr, Node* r = nullptr)
		:character(c), amount(a), left(l), right(r)
	{
	}
	~Node()
	{
		delete right;
		delete left;
	}

	bool operator()(Node* l, Node* r)
	{
		return l->amount > r->amount;
	}

private:
	char character;
	int amount;
	Node* left;
	Node* right;
};

