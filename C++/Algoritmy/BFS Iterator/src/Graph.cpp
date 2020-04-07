#include "Graph.h"
#include "Node.h"

using namespace std;


Graph::Graph(int n)
{
    this->nodes = new Node*[n];

    this->count = n;
}

int Graph::firstEmpty = 0;

void Graph::insert(Node* n, int c, Node** newNeighbors)
{
    //int nodePos = 10 - this->count;      //dopøedu vím, že pracuji pouze s 10 prvky

    this->nodes[Graph::firstEmpty] = n;

    this->nodes[Graph::firstEmpty]->initArray(c);
    this->nodes[Graph::firstEmpty]->SetCount(c);

    for(int i = 0; i < c; i++)
    {
        this->nodes[Graph::firstEmpty]->SetNeighbor(i,newNeighbors[i]);
    }

    Graph::firstEmpty++;
}

Node* Graph::GetNode(int n)
{
    return this->nodes[n];
}

void Graph::ResetState()
{
    for(int i = 0; i < this->count; i++)
    {
        this->nodes[i]->ChangeState('u');
    }
}

Graph::~Graph()
{
    delete this->nodes;
    this->nodes = nullptr;
}
