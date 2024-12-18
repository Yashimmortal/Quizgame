#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Question {
    string text;
    vector<string> options;
    int correctAnswerIndex;

    Question(const string& line) {
        istringstream ss(line);
        string option;
        
        getline(ss, text, ';');
        
        for (int i = 0; i < 4; ++i) {
            getline(ss, option, ';');
            options.push_back(option);
        }
        
        ss >> correctAnswerIndex;
    }
};

void loadQuestions(const string& filename, vector<Question>& questions) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        questions.emplace_back(line);
    }
}

void playQuiz(const vector<Question>& questions) {
    int score = 0;

    for (const auto& question : questions) {
        cout << question.text <<endl;
        for (size_t i = 0; i < question.options.size(); ++i) {
            cout << i + 1 << ". " << question.options[i] <<endl;
        }

        int answer;
        cout << "choose (1-4): ";
        cin >> answer;

        if (answer - 1 == question.correctAnswerIndex) {
            cout << "Correct!" <<endl;
            score++;
        } else {
            cout << "Wrong,The answer was: " << question.options[question.correctAnswerIndex] <<endl;
        }
        std::cout << std::endl;
    }

    cout << "Your final score: " << score << "/" << questions.size() << std::endl;
}

int main() {
    vector<Question> questions;
    loadQuestions("data/questions.txt", questions);
    cout << "Welcome to the Quiz Game!" << endl;
    playQuiz(questions);
    return 0;
}
