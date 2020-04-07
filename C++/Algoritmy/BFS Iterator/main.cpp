#include <iostream>
#include "Node.h"
#include "Graph.h"
#include "Iterator.h"

using namespace std;

int main()
{

    //Tvorba grafu

    Node* n0 = new Node(0);
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);
    Node* n9 = new Node(9);

    Graph* g1 = new Graph(10);

    Node** neighbors = new Node*[5];

    neighbors[0] = n1; neighbors[1] = n4; neighbors[2] = n6;
    g1->insert(n0, 3, neighbors);

    neighbors[0] = n2; neighbors[1] = n4; neighbors[2] = n0;
    g1->insert(n1, 3, neighbors);

    neighbors[0] = n3; neighbors[1] = n5; neighbors[2] = n1;
    g1->insert(n2, 3, neighbors);

    neighbors[0] = n9; neighbors[1] = n5; neighbors[2] = n2;
    g1->insert(n3, 3, neighbors);

    neighbors[0] = n1; neighbors[1] = n5 ;neighbors[2] = n7; neighbors[3] = n6, neighbors[4] = n0;
    g1->insert(n4, 5, neighbors);

    neighbors[0] = n3; neighbors[1] = n8; neighbors[2] = n4; neighbors[3] = n2;
    g1->insert(n5, 4, neighbors);

    neighbors[0] = n4; neighbors[1] = n7; neighbors[2] = n0;
    g1->insert(n6, 3, neighbors);

    neighbors[0] = n8; neighbors[1] = n6; neighbors[2] = n4;
    g1->insert(n7, 3, neighbors);

    neighbors[0] = n5; neighbors[1] = n9; neighbors[2] = n7;
    g1->insert(n8, 3, neighbors);

    neighbors[0] = n3; neighbors[1] = n8;
    g1->insert(n9, 2, neighbors);



















    //Iterátor

    Iterator iterator(g1);


    iterator.Reset(n0);
    cout << iterator.CurrentKey() << endl;

    while(!iterator.IsEnd())
    {
        iterator++;

        if(iterator.IsEnd())
            cout << "Konec iterace" << endl;
        else
            cout << iterator.CurrentKey() << endl;
    }
    cout << endl;

/*-------------------------------------------------------*/


    iterator.Reset(n3);
    cout << iterator.CurrentKey() << endl;

    while(!iterator.IsEnd())
    {
        iterator++;

        if(iterator.IsEnd())
            cout << "Konec iterace" << endl;
        else
            cout << iterator.CurrentKey() << endl;
    }
    cout << endl;


/*-------------------------------------------------------*/

    iterator.Reset(n5);
    cout << iterator.CurrentKey() << endl;

    while(!iterator.IsEnd())
    {
        iterator++;

        if(iterator.IsEnd())
            cout << "Konec iterace" << endl;
        else
            cout << iterator.CurrentKey() << endl;
    }
    cout << endl;

/*-------------------------------------------------------*/

    Graph* g2 = new Graph(0);
    Iterator i2(g2);

    cout << i2.CurrentKey() << endl;

    cout << endl;

    return 0;
}
