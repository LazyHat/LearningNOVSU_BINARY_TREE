#include <iostream>
#include <fstream>
#include <clocale>
#include "Node.h"
using namespace std;

ofstream fo;
string VectorToStr(intvec &v)
{
    string s;
    for (int i = 0; i < v.size(); i++)
    {
        s += v[i];
    }
    return s;
}
void Begin(Node *firstNode)
{
    char answer;
    Node node = *firstNode;
    do
    {
        cout << node.question << "Your Answer(y/n): ";
        cin >> answer;
        if (answer == 'y')
        {
            node = *(node.Yes);
        }
        else if (answer == 'n')
        {
            node = *(node.No);
        }
    } while (!node.end);
    if (node.end)
    {
        cout << node.question;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Hello World\n";
    Node first = Node("It is a cat?");
    first.Yes = new Node(true, "I WIN NAHUI!", true);
    first.No = new Node(true, "fuck.", false);
    Begin(&first);
}
