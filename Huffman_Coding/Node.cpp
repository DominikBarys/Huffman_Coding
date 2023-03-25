#include "Node.h"

Node::Node(const Node& another)
    :character(another.character), amount(another.amount)
{
	if (another.left)
		left = new Node(*another.left);
	if (another.right)
		right = new Node(*another.right);
}

Node& Node::operator=(const Node& another)
{
    if (this != &another)
    {
        character = another.character;
        amount = another.amount;
        delete left;
        delete right;
        if (another.left)
            left = new Node(*another.left);
        else
            left = nullptr;
        if (another.right)
            right = new Node(*another.right);
        else
            right = nullptr;
    }
    return *this;
}

Node::Node(Node&& another) noexcept
    : character(another.character), amount(another.amount), left(another.left), right(another.right)
{
    another.left = nullptr;
    another.right = nullptr;
}

Node& Node::operator=(Node&& another) noexcept
{
    if (this != &another)
    {
        character = another.character;
        amount = another.amount;
        delete left;
        delete right;
        left = another.left;
        right = another.right;
        another.left = nullptr;
        another.right = nullptr;
    }
    return *this;
}
