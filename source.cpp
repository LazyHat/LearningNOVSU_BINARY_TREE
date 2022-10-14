#include <iostream>
#include <fstream>
#include <iterator>
#include <clocale>
#include <list>
#include "Node.h"
using namespace std;

#pragma region FUNCTIONS
#pragma region PRINTS_AND_INPUTS
void PrintS(string s)
{
    cout << s;
}
void PrintS(string literal, int amountofS)
{
    string s = "";
    for (int i = 0; i < amountofS; i++)
    {
        s += literal;
    }
    cout << s;
}
void PrintSL(string s)
{
    cout << s << endl;
}
void PrintSL(string literal, int amountofS)
{
    string s = "";
    for (int i = 0; i < amountofS; i++)
    {
        s += literal;
    }
    cout << s << endl;
}
int InputInt()
{
    int a;
    cin >> a;
    return a;
}
string InputStr()
{
    string s;
    cin >> s;
    return s;
}
#pragma endregion
string VectorToStr(vector<int> &v)
{
    string s;
    for (int i = 0; i < v.size(); i++)
    {
        s += v[i];
    }
    return s;
}
void EditNode(string coordinates)
{
    // Может сделать меню, выбор что поменять
}
void CreateNode()
{
    //
}
string PrintMenuFromList(list<string> ListMenu)
{
    PrintS("-", 5);
    PrintS("MENU");
    PrintSL("-", 5);
    // Menu
    copy(ListMenu.begin(), ListMenu.end(), ostream_iterator<string>(cout, "\n"));
    // EndMenu
    PrintSL("-", 14);
    PrintSL("Choose: ");
}
void Begin()
{
    char answer;
    Node node = first;
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
void HeadMenu()
{
    PrintMenuFromList({"1.Play a game", "2.Edit tree", "3.Create tree"});
    switch (InputInt())
    {
    case 1:
        Begin();
        break;
    case 2:
        PrintSL("Enter coordinates, of Node: ");
        EditNode(InputStr());
        break;
    case 3:
        PrintSL("Enter coordinates, of Node: ");
        CreateNode(InputStr()); // надо сделать чтобы не координату вводить. а как то связать с игрой, чтобы можно было добавить узел прямо в игре. сделать типо мастера создания узлов
        break;
    default:
        break;
    }
}

#pragma endregion

#pragma region OBJECTS
ofstream fo;
Node first;
#pragma endregion

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Hello World\n";
    first = Node("QuestFirst?");
    first.Yes = new Node(true, "Quest1", "1");
    first.No = new Node(true, "Quest0", "0");
    while (true)
        HeadMenu();
}
