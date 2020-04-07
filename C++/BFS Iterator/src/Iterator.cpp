#include <climits>
#include <iostream>
#include "Iterator.h"
#include "Node.h"

using namespace std;

Iterator::Iterator(Graph* g)
{
    this->g = g;
}

void Iterator::Reset(Node* n)
{
    while(!this->IsEnd())
    {
        this->q.pop();
    }

    this->g->ResetState();

    this->q.push(n);
    this->q.front()->ChangeState('d');
    this->q.front()->SetDistance(0);

    return;

}

void Iterator::Next()
{
    if(this->IsEnd())
        return;

    this->q.front()->SetState('f');

    for(int i = 0; i < this->q.front()->GetCount(); i++)
    {
        if(this->q.front()->GetNeighbor(i)->GetState() == 'u')
        {
            this->q.push(this->q.front()->GetNeighbor(i));
            this->q.front()->GetNeighbor(i)->SetState('d');
            this->q.front()->GetNeighbor(i)->SetDistance(this->q.front()->GetDistance()+1);
        }
    }

    this->q.pop();
    return;
}

bool Iterator::IsEnd()
{
    return this->q.empty();
}

int Iterator::CurrentKey()
{
    if(this->IsEnd())
    {
        std::cout << "Fornta je prazdna!" << std::endl;
        return INT_MAX;
    }

    return this->q.front()->GetValue();
}

Iterator& Iterator::operator++(int)
{
    this->Next();
    return *this;
}

Iterator& Iterator::operator++()
{
    this->Next();
    return *this;
}

Iterator::~Iterator()
{
    delete this->g;
    this->g = nullptr;

    while(!q.empty())
        q.pop();
}
