#include <string>
using namespace std;
struct Node
{
    bool end = false;
    string question = "Question not exist";
    Node(string Question_or_Answer)
    {
        question = Question_or_Answer;
        end = !Question_or_Answer.ends_with('?');
    }
    Node() {}
};
