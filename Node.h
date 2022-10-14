#include <string>
#include <vector>
using namespace std;
struct Node
{
    string coordinates;
    bool end = false;
    string question = "Question not exist\n";
    Node *No;
    Node *Yes;
    Node(string Question)
    {
        question = Question + "\n";
    }
    Node(string Question, string yesno)
    {
        coordinates = this->coordinates + yesno;
        question = Question + "\n";
    }
    Node(bool isEnd, string Answer, string yesno)
    {
        coordinates = this->coordinates + yesno;
        end = true;
        question = Answer + "\n";
    }
};
