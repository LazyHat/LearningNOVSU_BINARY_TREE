#include <string>
#include <vector>
using namespace std;
typedef vector<int> intvec;
struct Node
{
    intvec coordinates;
    bool end = false;
    string question = "Question not exist\n";
    Node *No;
    Node *Yes;
    Node(string Question)
    {
        question = Question + "\n";
    }
    Node(string Question, bool yesno)
    {
        coordinates = this->coordinates;
        coordinates.push_back(yesno);
        question = Question + "\n";
    }
    Node(bool isEnd, string Answer, bool yesno)
    {
        coordinates = this->coordinates;
        coordinates.push_back(yesno);
        end = true;
        question = Answer + "\n";
    }
};
