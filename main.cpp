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

    Question(const std::string& line) {
        istringstream ss(line);
        string option;
        
        // Get the question text
        getline(ss, text, ';');
        
        // Get the options
        for (int i = 0; i < 4; ++i) {
            getline(ss, option, ';');
            options.push_back(option);
        }
        
        // Get the correct answer index
        ss >> correctAnswerIndex;
    }
};

void loadQuestions(const std::string& filename, vector<Question>& questions) {
    ifstream file(filename);
    string line;

    while (std::getline(file, line)) {
        questions.emplace_back(line);
    }
}

void playQuiz(const std::vector<Question>& questions) {
    int score = 0;

    for (const auto& question : questions) {
        std::cout << question.text << std::endl;
        for (size_t i = 0; i < question.options.size(); ++i) {
            std::cout << i + 1 << ". " << question.options[i] << std::endl;
        }

        int answer;
        std::cout << "Your answer (1-4): ";
        std::cin >> answer;

        if (answer - 1 == question.correctAnswerIndex) {
            std::cout << "Correct!" << std::endl;
            score++;
        } else {
            std::cout << "Wrong! The correct answer was: " << question.options[question.correctAnswerIndex] << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "Your final score: " << score << "/" << questions.size() << std::endl;
}

int main() {
    std::vector<Question> questions;
    loadQuestions("data/questions.txt", questions);

    std::cout << "Welcome to the Quiz Game!" << std::endl;
    playQuiz(questions);

    return 0;
}