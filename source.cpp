#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include "Node.h"
using namespace std;
typedef map<string, Node> Dic;
#pragma region OBJECTS
ofstream fo;
Dic db;
#pragma endregion
#pragma region FUNCTIONS
#pragma region PROTOTYPES
#pragma endregion
#pragma region SETTERS_AND_GETTERS
void AddToDic(string Coordinates, Node Object)
{
    db.insert(Dic::value_type(Coordinates, Object));
}
Node GetNodeFromDic(string Coordinates)
{
    if (db.contains(Coordinates))
    {
        return db.at(Coordinates);
    }
    else
    {
        return Node("0.Node whose coords are:" + Coordinates + " does not exist.");
    }
}
void ReplaceItemDic(string Coordinates, Node Object)
{
    if (db.contains(Coordinates))
    {
        db[Coordinates] = Object;
    }
    else
    {
        AddToDic(Coordinates, Object);
    }
}
#pragma endregion
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
    getline(cin >> ws, s);
    return s;
}
char InputChar()
{
    char c;
    cin >> c;
    return c;
}
string InputChary_n()
{
    string c;
    cin >> c;
    if (c == "da" || c == "net")
        return c;
    PrintSL("Incorrect answer, enter correct answer!");
    return InputChary_n();
}
int PrintMenuAndChoose(string head, list<string> ListMenu)
{
    PrintSL("");
    PrintS("-", 5);
    PrintS(head);
    PrintSL("-", 5);
    // Menu
    {
        int j = 1;
        for (auto &&i : ListMenu)
        {
            PrintSL(to_string(j) + "." + i);
            j++;
        }
    }
    //  EndMenu
    PrintSL("-", 10 + head.size());
    PrintS("Choose: ");
    return InputInt();
}
void PrintMenu(string head, list<string> ListMenu)
{
    PrintSL("");
    PrintS("-", 5);
    PrintS(head);
    PrintSL("-", 5);
    // Menu
    {
        int j = 1;
        for (auto &&i : ListMenu)
        {
            PrintSL(to_string(j) + "." + i);
            j++;
        }
    }
    //  EndMenu
    PrintSL("-", 10 + head.size());
}
#pragma endregion
#pragma region CONVERT
#pragma endregion
#pragma region EDITTREE
void EditNode(string coordinates)
{
    string NextCoords;
    Node currentnode = GetNodeFromDic(coordinates);
    bool k = true;
    do
    {
        string q_a = (currentnode.end ? "Answer(P.S. or enter new Question)" : "Question(P.S. or enter new Answer)");
        list<string> menulist = {"Type of Node: " + q_a,
                                 q_a + ": " + currentnode.question};
        list<string> chooselist = {"Edit " + q_a,
                                   "Go up the tree",
                                   "Exit Menu"};
        if (!currentnode.end)
        {
            chooselist.push_back("Go to Yes");
            chooselist.push_back("Go to No");
            menulist.push_back("If yes: " + GetNodeFromDic(coordinates + "1").question);
            menulist.push_back("If No: " + GetNodeFromDic(coordinates + "0").question);
        }
        PrintMenu("ThisNode(" + coordinates + ")", menulist);
        // Может сделать меню, выбор что поменять
        switch (PrintMenuAndChoose("EditNodeMenu", chooselist))
        {
        case 1:
            PrintS("Enter new " + q_a + ": ");
            currentnode = Node(InputStr());
            break;
        case 2:
            if (currentnode.end)
            {
                string _coords = coordinates;
                _coords.pop_back();
                NextCoords = _coords;
                k = false;
            }
            else
            {
                k = false;
                NextCoords = coordinates + "1";
            }
            break;
        case 3:
            if (currentnode.end)
            {
                k = false;
            }
            else
            {
                k = false;
                NextCoords = coordinates + "0";
            }
            break;
        case 4:
        {
            if (currentnode.end)
            {
                PrintSL("Exist item");
                NextCoords = coordinates;
                k = false;
            }
            else
            {
                string _coords = coordinates;
                _coords.pop_back();
                NextCoords = _coords;
                k = false;
            }
        }
        break;
        case 5:
            if (currentnode.end)
            {
                PrintSL("Exist item");
                NextCoords = coordinates;
                k = false;
            }
            else
            {
                k = false;
            }
            break;
        default:
            PrintSL("Exist item");
            k = false;
            NextCoords = coordinates;
            break;
        }
    } while (k);
    ReplaceItemDic(coordinates, currentnode);
    if (NextCoords != "")
    {
        EditNode(NextCoords);
    }
}
#pragma endregion
void Begin()
{
    string answer;
    Node node = GetNodeFromDic(".");
    string coordinates = ".";
    while (!node.end)
    {
        PrintS(node.question + "(da/net): ");
        answer = InputChary_n();
        if (answer == "da")
        {
            coordinates += "1";
        }
        else if (answer == "net") // answer = 'n'
        {
            coordinates += "0";
        }
        node = GetNodeFromDic(coordinates);
    }
    PrintS("Your animal: " + node.question + "\nIts a correct answer?(da/net): ");
    answer = InputChary_n();
    if (answer == "da")
    {
        PrintSL("I win");
    }
    else if (answer == "net")
    {
        PrintS("Are you want to edit this node?(da/net): ");
        if (InputChary_n() == "da")
        {
            EditNode(coordinates);
        }
    }
}
//надо сделать чтобы не координату вводить,
//а как то связать с игрой, чтобы можно было добавить узел прямо в игре. сделать типо мастера создания узлов.
void HeadMenu()
{
    switch (PrintMenuAndChoose("MENU",
                               {"Play a game",
                                "Edit tree"}))
    {
    case 1: // Play a game
        Begin();
        break;
    case 2: // Edit tree
        PrintS("Enter coordinates of node: ");
        EditNode(InputStr());
        break;
    default:
        break;
    }
}
#pragma endregion

int main()
{
    cout << "Hello World\n";
    while (true)
        HeadMenu();
}