#ifndef ITERATOR_H
#define ITERATOR_H
#include <queue>
#include "Graph.h"
#include "Node.h"


class Iterator
{
    public:
        Iterator(Graph* g);
        virtual ~Iterator();

        void Reset(Node* n);
        void Next();
        bool IsEnd();
        int CurrentKey();

        Iterator& operator++();
        Iterator& operator++(int);

    private:
        std::queue <Node*> q;
        Graph* g;
};

#endif // ITERATOR_H
