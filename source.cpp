#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdio>
#include <list>
#include <map>
#include <Windows.h>
#include "Node.h"
#define SIZE_OF_FILE_BUFF_TO_INT 20
// Files
#define FILE_TREE "tree.txt"
#define FILE_CONFIG "config.txt"
#define FILE_LOCALE "locale.txt"
//
using namespace std;

enum Language
{
    English,
    Russian
};
typedef map<string, Node> Dic;
typedef map<pair<string, Language>, string> LocaleDic;
#pragma region GLOBAL_VAR
Language glanguage;
#pragma endregion
#pragma region OBJECTS
Dic db;
LocaleDic localedb;
#pragma endregion
#pragma region FUNCTIONS
#pragma region PROTOTYPES
string GetWord(string wordid);
string InputStr();
int StrToInt(string s);
#pragma endregion
#pragma region DATABASE
void AddToLocaleDic(string wordid, Language lang, string word)
{
    localedb.insert(LocaleDic::value_type(make_pair(wordid, lang), word));
}
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
        return Node(GetWord("GetNodeFromDic_NodeExist_Part_1") + " " + Coordinates + " " + GetWord("GetNodeFromDic_NodeExist_Part_2"));
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
    do
    {
        int a = 0;
        a = StrToInt(InputStr());
        if (a == -999999)
            PrintS(GetWord("InputInt_Error") + " ");
        else
            return a;
    } while (true);
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
bool InputStrC()
{
    PrintS(GetWord("(yes/no)"));
    string c = InputStr();
    if (c == GetWord("yes") || c == GetWord("no"))
        return c == GetWord("yes");
    PrintSL(GetWord("InputStrC_Incorrect"));
    return InputStrC();
}
string InputCoordinates()
{
    string d = ".01";
    string s = InputStr();
    int t = 0;
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j < d.size(); j++)
        {
            if (s[i] == d[j])
                t++;
        }
    }
    if (t < s.size() || !s.starts_with(d[0]))
    {
        PrintS(GetWord("InputCoordinates_Incorrect") + " ");
        return InputCoordinates();
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
    PrintS(GetWord("PrintMenuAndChoose_Choose") + " ");
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
int StrToInt(string s)
{
    try
    {
        int a;
        a = stoi(s);
        return a;
    }
    catch (std::invalid_argument e)
    {
        PrintSL(GetWord("StrToInt_Fail_Convert"));
        return -999999;
    }
    catch (std::out_of_range e)
    {
        PrintSL(GetWord("StrToInt_Fail_Convert"));
        return -999999;
    }
}
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
            q_a1 = GetWord("EditNode_Q/A");
            menulist.push_front(GetWord("EditNode_Node_Exist"));
            chooselist.push_back(GetWord("EditNode_Create_Q/A"));
        }
        else
        {
            if (currentnode.end)
            {
                q_a1 = GetWord("EditNode_A_PS");
                q_a2 = GetWord("Answer");
            }
            else
            {
                q_a1 = GetWord("EditNode_Q_PS");
                q_a2 = GetWord("Answer");
                chooselist.push_back("Go to Yes");
                chooselist.push_back("Go to No");
                menulist.push_back("If yes: " + GetNodeFromDic(coordinates + "1").question);
                menulist.push_back("If No: " + GetNodeFromDic(coordinates + "0").question);
            }
            menulist.push_front("Type of Node: " + q_a2);
            list<string>::iterator iter = menulist.begin();
            menulist.insert(++iter, q_a2 + ": " + currentnode.question);
            chooselist.push_front("Edit " + q_a1);
        }
        chooselist.insert(++chooselist.begin(), "Go up the tree");
        chooselist.push_back("Exit Menu");

        PrintMenu("ThisNode(" + coordinates + ")", menulist);
        switch (PrintMenuAndChoose("EditNodeMenu", chooselist))
        {
        case 1:
            PrintS("Enter new " + q_a1 + ": ");
            currentnode = Node(InputStr());
            break;
        case 2:
        {
            string _coords = coordinates;
            _coords.pop_back();
            NextCoords = _coords;
            k = false;
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
                NextCoords = coordinates + "1";
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
                k = false;
                NextCoords = coordinates + "0";
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
#pragma region Locale
void AddLocaleList()
{
    AddToLocaleDic("GetNodeFromDic_NodeExist_Part_1", English, "Node whoose cords are:");
    AddToLocaleDic("GetNodeFromDic_NodeExist_Part_2", English, "Does not exist.");
    AddToLocaleDic("InputInt_Error", English, "Enter again:");
    AddToLocaleDic("(yes/no)", English, "(yes/no)");
    AddToLocaleDic("yes", English, "yes");
    AddToLocaleDic("no", English, "no");
    AddToLocaleDic("InputStrC_Incorrect", English, "Incorrect input, enter again!");
    AddToLocaleDic("InputCoordinates_Incorrect", English, "Incorrect coordinates. Enter again:");
    AddToLocaleDic("PrintMenuAndChoose_Choose", English, "Choose:");
    AddToLocaleDic("StrToInt_Fail_Convert", English, "Failed to convert str to int.");
    AddToLocaleDic("EditNode_Q/A", English, "Question/Answer");
    AddToLocaleDic("EditNode_Node_Exist", English, "Node does not exist");
    AddToLocaleDic("EditNode_Create_Q/A", English, "Create Question/Answer (Create Node)");
    AddToLocaleDic("EditNode_A_PS", English, "Answer(P.S. or enter new Question)");
    AddToLocaleDic("EditNode_Q_PS", English, "Question(P.S. or enter new Answer)");
    AddToLocaleDic("Question", English, "Question");
    AddToLocaleDic("Answer", English, "Answer");
    AddToLocaleDic("no", English, "no");
    AddToLocaleDic("no", English, "no");
    AddToLocaleDic("no", English, "no");
}
string GetWord(string wordid)
{
    if (localedb.contains(make_pair(wordid, glanguage)))
        return localedb[make_pair(wordid, glanguage)];
    else
        return localedb[make_pair(wordid, English)];
}
#pragma endregion
#pragma region FILE
void ErrorConfigFile()
{
    PrintS("Файл: ");
    PrintS(FILE_CONFIG);
    PrintSL(" Не был найден, или в нем есть ошибка. Создание или изменение файла по шаблону");
    ofstream fout(FILE_CONFIG);
    fout << "//CONFIGURATION FILE\n"
         << "StartLanguage: English\n"
         << "ENDCONFIG\n";
    glanguage = English;
}
void LoadConfigFile()
{
    ifstream fin(FILE_CONFIG);
    if (fin.is_open())
    {
        PrintS("Обнаружен файл: ");
        PrintSL(FILE_CONFIG);
        string s;
        int amountconfig = 1;
        do
        {
            getline(fin, s);
            if (s.starts_with("//"))
            {
                continue;
            }
            else if (s.starts_with("StartLanguage:"))
            {
                if (s.find("English") != string::npos)
                {
                    PrintSL("Language: English");
                    glanguage = English;
                    amountconfig--;
                }
                else if (s.find("Russian") != string::npos)
                {
                    PrintSL("Язык: Русский");
                    glanguage = Russian;
                    amountconfig--;
                }
            }
            else if (s.find("ENDCONFIG") != string::npos)
            {
                if (amountconfig == 0)
                {
                    PrintSL("Конфигурационный файл успешно считан.");
                    break;
                }
                else
                {
                    ErrorConfigFile();
                    break;
                }
            }
            else
            {
                ErrorConfigFile();
                break;
            }
        } while (true);
    }
    else
    {
        ErrorConfigFile();
    }
}
void LoadLocalizationFile()
{
    ifstream fin(FILE_LOCALE);
    if (!fin.is_open())
    {
        PrintS("Файл: ");
        PrintS(FILE_LOCALE);
        PrintSL(" Не был найден.");
    }
    else
    {
        PrintS("Обнаружен файл: ");
        PrintSL(FILE_LOCALE);
        string s;
        do
        {
            getline(fin, s);
            if (s.find("//") != string::npos)
            {
                continue;
            }
            else if (s.find("Language:") != string::npos)
            {
                if (s.find("Russian") != string::npos)
                {
                    PrintSL("Русская локализация найдена");
                    getline(fin, s);
                }
                break;
            }
            else
            {
                PrintSL("Локализаций не было найдено, использование English");
                break;
            }
        } while (true);
    }
}
void SaveToTreeFile()
{
    ofstream fout("tree.txt");
    if (!fout.is_open())
    {
        PrintSL("Не удалось открыть файл");
    }
    else
    {
        fout << db.size() << "\n";
        for (auto element : db)
        {
            fout << element.first << " " << element.second.question << "\n";
        }
        fout.close();
        PrintSL("Данные всех узлов были успешно записаны в файл");
    }
}
void LoadTreeFile()
{
    ifstream fin("tree.txt");
    if (!fin.is_open())
    {
        PrintSL("Не удалось открыть файл");
    }
    else
    {
        int amountofnodes;
        string s;
        getline(fin, s);
        int space = 0;
        amountofnodes = StrToInt(s);
        if (amountofnodes != 0)
            db.clear();
        for (int i = 0; i < amountofnodes; i++)
        {
            s = "";
            getline(fin, s);
            if (s == "")
                break;
            space = s.find(" ");
            AddToDic(s.substr(0, space), Node(s.substr(space)));
        }
        if (db.size() == amountofnodes)
            PrintSL("Данные " + to_string(amountofnodes) + " узлов были успешно загружены!");
        else
            PrintSL("Потеря данных");
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
    LoadConfigFile();
    AddLocaleList();
    LoadLocalizationFile();
    LoadTreeFile();
    PrintSL("Добрый ветер!");
    while (HeadMenu())
        ;
    SaveToTreeFile();
}