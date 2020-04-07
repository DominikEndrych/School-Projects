#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node();
        Node(int v);
        virtual ~Node();

        void SetCount(int c);
        void SetState(char s);
        void SetDistance(int d);
        int GetValue();
        int GetCount();
        char GetState();
        int GetDistance();
        Node* GetNeighbor(int c);

        void SetNeighbor(int p, Node* n);

        void initArray(int c);

        void ChangeState(char s);

    private:
        Node** neighbors;
        int count;
        int value;
        int distance;

        char state;
};

#endif // NODE_H
