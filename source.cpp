#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdio>
#include <list>
#include <map>
#include <vector>
#include <Windows.h>
#include "Node.h"
#define SIZE_OF_FILE_BUFF_TO_INT 20
// Files
#define FILE_TREE "tree.txt"
#define FILE_CONFIG "config.txt"
#define FILE_LOCALE "locale.txt"
//
using namespace std;
typedef map<string, Node> Dic;
typedef map<string, string> DicStr;
typedef map<string, map<string, string>> LocaleDic; // map<wordid, map<language, word>>
#pragma region GLOBAL_VAR
string glanguage = "English";
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
void AddToLocaleDic(string wordid, string lang, string word)
{
    localedb[wordid][lang] = word;
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
        return Node(GetWord("GetNodeFromDic_NodeExist_Part_1") + ": " + Coordinates + " " + GetWord("GetNodeFromDic_NodeExist_Part_2"));
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
        PrintS(GetWord("InputCoordinates_Incorrect") + ": ");
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
    PrintS(GetWord("PrintMenuAndChoose_Choose") + ": ");
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
                q_a2 = GetWord("EditNode_Answer");
            }
            else
            {
                q_a1 = GetWord("EditNode_Q_PS");
                q_a2 = GetWord("EditNode_Question");
                chooselist.push_back(GetWord("EditNode_Go_To_Yes"));
                chooselist.push_back(GetWord("EditNode_Go_To_No"));
                menulist.push_back(GetWord("EditNode_If_Yes") + ": " + GetNodeFromDic(coordinates + "1").question);
                menulist.push_back(GetWord("EditNode_If_No") + ": " + GetNodeFromDic(coordinates + "0").question);
            }
            menulist.push_front(GetWord("EditNode_Type_Of_Node") + ": " + q_a2);
            list<string>::iterator iter = menulist.begin();
            menulist.insert(++iter, q_a2 + ": " + currentnode.question);
            chooselist.push_front(GetWord("EditNode_Edit") + " " + q_a1);
        }
        chooselist.insert(++chooselist.begin(), GetWord("EditNode_Go_Up_The_Tree"));
        chooselist.push_back(GetWord("EditNode_Exit_Menu"));

        PrintMenu(GetWord("EditNode_This_Node") + "(" + coordinates + ")", menulist);
        switch (PrintMenuAndChoose(GetWord("EditNode_Edit_Node_Menu"), chooselist))
        {
        case 1:
            PrintS(GetWord("EditNode_Enter_New") + " " + q_a1 + ": ");
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
                PrintSL(GetWord("EditNode_Exist_Item"));
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
                PrintSL(GetWord("EditNode_Exist_Item"));
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
    AddToLocaleDic("GetNodeFromDic_NodeExist_Part_1", "English", "Node whoose cords are");
    AddToLocaleDic("GetNodeFromDic_NodeExist_Part_2", "English", "Does not exist.");
    AddToLocaleDic("InputInt_Error", "English", "Enter again:");
    AddToLocaleDic("(yes/no)", "English", "(yes/no)");
    AddToLocaleDic("yes", "English", "yes");
    AddToLocaleDic("no", "English", "no");
    AddToLocaleDic("InputStrC_Incorrect", "English", "Incorrect input, enter again!");
    AddToLocaleDic("InputCoordinates_Incorrect", "English", "Incorrect coordinates. Enter again");
    AddToLocaleDic("PrintMenuAndChoose_Choose", "English", "Choose");
    AddToLocaleDic("StrToInt_Fail_Convert", "English", "Failed to convert str to int.");
    AddToLocaleDic("EditNode_Q/A", "English", "Question/Answer");
    AddToLocaleDic("EditNode_Node_Exist", "English", "Node does not exist");
    AddToLocaleDic("EditNode_Create_Q/A", "English", "Create Question/Answer (Create Node)");
    AddToLocaleDic("EditNode_A_PS", "English", "Answer(P.S. or enter new Question)");
    AddToLocaleDic("EditNode_Q_PS", "English", "Question(P.S. or enter new Answer)");
    AddToLocaleDic("EditNode_Question", "English", "Question");
    AddToLocaleDic("EditNode_Answer", "English", "Answer");
    AddToLocaleDic("EditNode_Go_To_Yes", "English", "Go to yes");
    AddToLocaleDic("EditNode_Go_To_No", "English", "Go to no");
    AddToLocaleDic("EditNode_If_Yes", "English", "If yes");
    AddToLocaleDic("EditNode_If_No", "English", "If no");
    AddToLocaleDic("EditNode_Type_Of_Node", "English", "Type of node");
    AddToLocaleDic("EditNode_Edit", "English", "Edit");
    AddToLocaleDic("EditNode_Go_Up_The_Tree", "English", "Go up the tree");
    AddToLocaleDic("EditNode_Exit_Menu", "English", "Exit Menu");
    AddToLocaleDic("EditNode_This_Node", "English", "ThisNode");
    AddToLocaleDic("EditNode_Edit_Node_Menu", "English", "EditNodeMenu");
    AddToLocaleDic("EditNode_Enter_New", "English", "Enter new");
    AddToLocaleDic("EditNode_Exist_Item", "English", "Exist item");
    AddToLocaleDic("File_Exist", "English", "Was not found.");
    AddToLocaleDic("ErrorConfigFile_File_Q_Change", "English", "Was not found or broken. Do you want to create a new file?");
    AddToLocaleDic("ErrorConfigFile_File_Change", "English", "Creating a template file.");
    AddToLocaleDic("LoadConfigFil_Error", "English", "Config file error.");
    AddToLocaleDic("File", "English", "File");
    AddToLocaleDic("File_Found", "English", "File found");
    AddToLocaleDic("LoadConfigFile_File_Read", "English", "The configuration file was successfully read.");
    AddToLocaleDic("LoadLocalizationFile_Local_Found", "English", "Localization found.");
    AddToLocaleDic("LoadLocalizationFile_Local_Not_Found", "English", "Localizations not found.");
    AddToLocaleDic("LoadLocalizationFile_Create_File", "English", "Would you like to create locale.txt.");
    AddToLocaleDic("File_Cant_Open", "English", "Cant open file.");
    AddToLocaleDic("SaveToTreeFile_Write_Success", "English", "The data of all nodes was successfully written to the file");
    AddToLocaleDic("LoadTreeFile_Data_Part_1", "English", "The Data of");
    AddToLocaleDic("LoadTreeFile_Data_Part_2", "English", "nodes was successfully written.");
    AddToLocaleDic("LoadTreeFile_Data_Loss", "English", "Data loss.");
    AddToLocaleDic("Begin_Animal_Part_1", "English", "Your animal");
    AddToLocaleDic("Begin_Animal_Part_2", "English", "Its a correct answer?");
    AddToLocaleDic("Begin_Win", "English", "I win");
    AddToLocaleDic("Begin_Edit", "English", "Are you want to edit this node?");
    AddToLocaleDic("HeadMenu_Header_Menu", "English", "MENU");
    AddToLocaleDic("HeadMenu_Play", "English", "Play a game");
    AddToLocaleDic("HeadMenu_Edit", "English", "Edit tree");
    AddToLocaleDic("HeadMenu_Exit", "English", "Exit");
    AddToLocaleDic("HeadMenu_Enter_Coords", "English", "Enter coordinates of node");
    AddToLocaleDic("Main_Hello", "English", "Hello world!");
    AddToLocaleDic("LoadLocalizationFile_All_Locale_Loaded", "English", "All localizations locaded.");
    AddToLocaleDic("HeadMenu_Switch_Language", "English", "Switch language");
    AddToLocaleDic("HeadMenu_Available_Languages", "English", "Available languages");
    AddToLocaleDic("HeadMenu_Set_Language", "English", "Language set");
}
string GetWord(string wordid)
{
    if (localedb.contains(wordid))
    {
        if (localedb[wordid].contains(glanguage))
            return localedb[wordid][glanguage];
        else
            return localedb[wordid]["English"];
    }
    else
    {
        return wordid + "-Not Found";
    }
}
#pragma endregion
#pragma region FILE
bool OpenFileInput(ifstream &file, string path)
{
    file.open(path);
    if (!file.is_open())
    {
        PrintS(GetWord("File") + ": ");
        PrintS(path);
        PrintSL(" " + GetWord("File_Exist"));
        return 0;
    }
    else
    {
        PrintS(GetWord("File_Found") + ": ");
        PrintSL(path);
        return 1;
    }
}
void ErrorConfigFile()
{
    PrintS(GetWord("File") + ": ");
    PrintS(FILE_CONFIG);
    PrintSL(" " + GetWord("ErrorConfigFile_File_Q_Change"));
    if (InputStrC())
    {
        PrintSL(GetWord("ErrorConfigFile_File_Change"));
        ofstream fout(FILE_CONFIG);
        fout << "//CONFIGURATION FILE\n"
             << "StartLanguage: English\n"
             << "ENDCONFIG\n";
        glanguage = "English";
        fout.close();
    }
    else
    {
        exit(-1);
    }
}
void LoadConfigFile()
{
    ifstream fin;
    if (OpenFileInput(fin, FILE_CONFIG))
    {
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
                    glanguage = "English";
                    amountconfig--;
                }
                else if (s.find("Russian") != string::npos)
                {
                    PrintSL("язык: –усский");
                    glanguage = "Russian";
                    amountconfig--;
                }
            }
            else if (s.find("ENDCONFIG") != string::npos)
            {
                if (amountconfig == 0)
                {
                    PrintSL(GetWord("LoadConfigFile_File_Read"));
                    break;
                }
                else
                {
                    PrintSL(GetWord("LoadConfigFil_Error"));
                    ErrorConfigFile();
                    break;
                }
            }
            else
            {
                PrintSL(GetWord("LoadConfigFil_Error"));
                ErrorConfigFile();
                break;
            }
        } while (true);
    }
    else
    {
        ErrorConfigFile();
    }
    fin.close();
}
void CreateLocalizationFile()
{
    ofstream fout(FILE_LOCALE);
    fout << "Language:English\n";
    for (auto &&e : localedb)
    {
        fout << e.first + ":" + e.second["English"] + "\n";
    }
    fout << "ENDLOCALE\0";
    fout.close();
}
void LoadLocalizationFile()
{
    ifstream fin;
    if (OpenFileInput(fin, FILE_LOCALE))
    {
        string s;
        int localizations = 0;
        do
        {
            getline(fin, s);
            if (s.find("//") != string::npos)
            {
                continue;
            }
            else if (s.find("Language:") != string::npos)
            {
                string language = s.substr(s.find(":") + 1);
                PrintSL(language + " " + GetWord("LoadLocalizationFile_Local_Found"));
                while (true)
                {
                    getline(fin, s);
                    if (s.find(":") != string::npos)
                    {
                        AddToLocaleDic(s.substr(0, s.find(":")), language, s.substr(s.find(":") + 1));
                    }
                    else if (s.find("ENDLOCALE") != string::npos)
                    {
                        break;
                        //проверка на правильность и колво заполнени€
                    }
                    else
                    {
                        PrintSL(GetWord("LoadLocalizationFile_Create_File"));
                        if (InputStrC())
                        {
                            CreateLocalizationFile();
                            fin.close();
                            return;
                        }
                        else
                        {
                            exit(-1);
                        }
                    }
                }
            }
            else if (s.find("ENDLOCALE") != string::npos)
            {
                PrintSL(GetWord("LoadLocalizationFile_All_Locale_Loaded"));
                return;
            }
            else
            {
                PrintSL(GetWord("LoadLocalizationFile_Local_Not_Found"));
                PrintSL(GetWord("LoadLocalizationFile_Create_File"));
                if (InputStrC())
                {
                    CreateLocalizationFile();
                    fin.close();
                    return;
                }
                else
                    exit(-1);
            }
        } while (true);
    }
    else
    {
        PrintSL(GetWord("LoadLocalizationFile_Create_File"));
        if (InputStrC())
        {
            CreateLocalizationFile();
            fin.close();
            return;
        }
        else
            exit(-1);
    }
    fin.close();
    return;
}
void SaveToTreeFile()
{
    ofstream fout(FILE_TREE);
    if (!fout.is_open())
    {
        PrintSL(GetWord("File_Cant_Open"));
    }
    else
    {
        fout << db.size() << "\n";
        for (auto element : db)
        {
            fout << element.first << " " << element.second.question << "\n";
        }
        fout.close();
        PrintSL(GetWord("SaveToTreeFile_Write_Success"));
    }
    fout.close();
}
void LoadTreeFile()
{
    ifstream fin;
    if (OpenFileInput(fin, FILE_TREE))
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
            PrintSL(GetWord("LoadTreeFile_Data_Part_1") + " " + to_string(amountofnodes) + " " + GetWord("LoadTreeFile_Data_Part_2"));
        else
            PrintSL(GetWord("LoadTreeFile_Data_Loss"));
    }
    fin.close();
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
    PrintS(GetWord("Begin_Animal_Part_1") + ": " + node.question + "\n" + GetWord("Begin_Animal_Part_2"));
    answer = InputStrC();
    if (answer)
    {
        PrintSL(GetWord("Begin_Win"));
    }
    else
    {
        PrintS(GetWord("Begin_Edit"));
        if (InputStrC())
        {
            EditNode(coordinates);
        }
    }
}
int HeadMenu()
{
    switch (PrintMenuAndChoose(GetWord("HeadMenu_Header_Menu"),
                               {GetWord("HeadMenu_Play"),
                                GetWord("HeadMenu_Edit"),
                                GetWord("HeadMenu_Switch_Language"),
                                GetWord("HeadMenu_Exit")}))
    {
    case 1: // Play a game
        Begin();
        break;
    case 2: // Edit tree
        PrintS(GetWord("HeadMenu_Enter_Coords") + ": ");
        EditNode(InputCoordinates());
        break;
    case 3:
    {
        PrintS(GetWord("HeadMenu_Available_Languages") + ": ");
        vector<string> l;
        for (auto e : localedb["Main_Hello"])
        {
            l.push_back(e.first);
        }
        PrintS(l[0]);
        for (int i = 1; i < l.size(); i++)
        {
            PrintS(", " + l[i]);
        }
        PrintSL(".");
        PrintS(GetWord("PrintMenuAndChoose_Choose") + ": ");
        string clanguage = InputStr();
        for (auto k : l)
        {
            if (clanguage == k)
            {
                glanguage = clanguage;
                PrintSL(GetWord("HeadMenu_Set_Language") + ": " + glanguage);
            }
        }
    }
    break;
    case 4:
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
    AddLocaleList();
    LoadConfigFile();
    LoadLocalizationFile();
    LoadTreeFile();
    PrintSL(GetWord("Main_Hello"));
    while (HeadMenu())
        ;
    SaveToTreeFile();
}