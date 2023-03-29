#pragma once

class Node
{
public:
	Node() = delete;

	Node(char c, int a, Node* l = nullptr, Node* r = nullptr)
		:character(c), amount(a), left(l), right(r)
	{
	}

	Node(const Node& another);

	Node& operator=(const Node& another);

	Node(Node&& another) noexcept;

	Node& operator=(Node&& another) noexcept;

	~Node();

	char getChar() const { return character; }

	int getAmount() const { return amount; }

	Node* getLeftNode() const { return left; }

	Node* getRightNode() const { return right; }

private:
	char character{};
	int amount{};
	Node* left = nullptr;
	Node* right = nullptr;
};

struct CompareNodes
{
	bool operator()(Node* l, Node* r) { return l->getAmount() > r->getAmount(); }
};
