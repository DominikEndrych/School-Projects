#include <climits>
#include "Node.h"

Node::Node()
{
    this->neighbors = nullptr;
    this->count = 0;
    this->value = INT_MAX;
    this->state = 'u';
    this->distance = INT_MIN;
}

Node::Node(int v)
{
    this->neighbors = nullptr;
    this->count = 0;
    this->value = v;
    this->state = 'u';
}

int Node::GetValue()
{
    return this->value;
}

Node* Node::GetNeighbor(int c)
{
    return this->neighbors[c];
}

void Node::initArray(int c)
{
    this->neighbors = new Node*[c];
    return;
}

void Node::SetNeighbor(int p, Node* n)
{
    this->neighbors[p] = n;
    return;
}

void Node::ChangeState(char s)
{
    if(s == 'u' || s == 'd' || s == 'f')
    {
        this->state = s;
        return;
    }
    return;

}

void Node::SetCount(int c)
{
    this->count = c;
    return;
}

void Node::SetState(char s)
{
    this->state = s;
    return;
}

void Node::SetDistance(int d)
{
    this->distance = d;
}

int Node::GetCount()
{
    return this->count;
}

char Node::GetState()
{
    return this->state;
}

int Node::GetDistance()
{
    return this->distance;
}



Node::~Node()
{
    delete this->neighbors;
    this->neighbors = nullptr;
}
