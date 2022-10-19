#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdio>
#include <list>
#include <map>
#include <Windows.h>
#include "Node.h"
using namespace std;

enum Language
{
    Russian,
    English
};
typedef map<string, Node> Dic;
typedef map<string, string[]> locale;
#pragma region OBJECTS
Dic db;
Language language = English;
#pragma endregion
#pragma region FUNCTIONS
#pragma region PROTOTYPES
#pragma endregion
#pragma region DATABASE
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
        return Node("0.Узла с координатами: (" + Coordinates + ") не существует.");
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
    bool fail = 0;
    do
    {
        try
        {
            a = stoi(InputStr());
        }
        catch (std::invalid_argument e)
        {
            PrintS("Не удалось преобразовать строку в число, попробуйте еще раз: ");
            fail = true;
        }
        catch (std::out_of_range e)
        {
            PrintS("Слишком большое число, попробуйте еще раз: ");
            fail = true;
        }
    } while (fail);
    return a;
}
string InputStr()
{
    string s;
    cin >> s;
    return s;
}
char InputChar()
{
    char c;
    cin >> c;
    return c;
}
bool InputStrC()
{
    PrintS("(дa/нет): ");
    string c = InputStr();
    if (c == "да" || c == "нет")
        return c == "да";
    PrintSL("Некорректный ввод, попробуйте еще раз!");
    return InputStrC();
}
string InputCoordinates()
{
    string d = ".01";
    string s = InputStr();
    for (int i = 0, t = 0; i < s.size(); i++, t = 0)
    {
        for (int j = 0; j < d.size(); j++)
        {
            if (s[i] == d[j])
                t++;
        }
        if (t < s.size() || !s.starts_with(d[0]))
        {
            PrintS("Некорректные координаты. Введите корректные: ");
            return InputCoordinates();
        }
    }
    return s;
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
        list<string> menulist = {};
        list<string> chooselist = {};
        bool nonenode = currentnode.question.starts_with("0");
        string q_a1 = "";
        string q_a2 = "";
        if (nonenode)
        {
            q_a1 = "Вопрос/Ответ";
            menulist.push_front("Node does not exist");
            chooselist.push_back("Create Question/Answer (Create Node)");
        }
        else
        {
            menulist.push_front("Type of Node: " + q_a2);
            if (currentnode.end)
            {
                q_a1 = "Answer(P.S. or enter new Question)";
                q_a2 = "Answer";
            }
            else
            {
                q_a1 = "Question(P.S. or enter new Answer)";
                q_a2 = "Question";
                chooselist.push_back("Go to Yes");
                chooselist.push_back("Go to No");
                menulist.push_back("If yes: " + GetNodeFromDic(coordinates + "1").question);
                menulist.push_back("If No: " + GetNodeFromDic(coordinates + "0").question);
            }
            list<string>::iterator iter = menulist.begin();
            menulist.insert(++iter, q_a2 + ": " + currentnode.question);
            chooselist.push_front("Edit " + q_a1);
        }
        chooselist.push_back("Go up the tree");
        chooselist.push_back("Exit Menu");

        PrintMenu("ThisNode(" + coordinates + ")", menulist);
        // Может сделать меню, выбор что поменять
        switch (PrintMenuAndChoose("EditNodeMenu", chooselist))
        {
        case 1:
            PrintS("Enter new " + q_a1 + ": ");
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
        }
    } while (k);
    ReplaceItemDic(coordinates, currentnode);
    if (NextCoords != "")
    {
        EditNode(NextCoords);
    }
}
#pragma endregion
#pragma region FILE
int SaveToFile()
{
    ofstream fout("tree.txt");
    if (!fout.is_open())
    {
        PrintSL("Не удалось открыть файл");
        return -1;
    }
    else
    {
        for (auto element : db)
        {
            fout << element.first << " " << element.second.question << "\n";
        }
        fout.close();
        return 0;
    }
}
#pragma endregion
void Begin()
{
    bool answer;
    Node node = GetNodeFromDic(".");
    string coordinates = ".";
    while (!node.end)
    {
        PrintS(node.question);
        answer = InputStrC();
        if (answer)
        {
            coordinates += "1";
        }
        else // answer = 'n'
        {
            coordinates += "0";
        }
        node = GetNodeFromDic(coordinates);
    }
    PrintS("Your animal: " + node.question + "\nIts a correct answer?");
    answer = InputStrC();
    if (answer)
    {
        PrintSL("I win");
    }
    else
    {
        PrintS("Are you want to edit this node?");
        if (InputStrC())
        {
            EditNode(coordinates);
        }
    }
}
//надо сделать чтобы не координату вводить,
//а как то связать с игрой, чтобы можно было добавить узел прямо в игре. сделать типо мастера создания узлов

int HeadMenu()
{
    switch (PrintMenuAndChoose("MENU",
                               {"Play a game",
                                "Edit tree",
                                "Exit"}))
    {
    case 1: // Play a game
        Begin();
        break;
    case 2: // Edit tree
        PrintS("Enter coordinates of node: ");
        EditNode(InputCoordinates());
        break;
    case 3:
        return 0;
        break;
    }
    return 1;
}
#pragma endregion

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Дарова\n";
    while (HeadMenu())
        ;
    if (SaveToFile() == 0)
        PrintSL("Данные были успещно записаны в файл");
}