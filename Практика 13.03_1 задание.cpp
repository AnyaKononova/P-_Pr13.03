#include <iostream>
#include <string> 
#include <fstream> 
#include <algorithm>
#include <unordered_map> 

using namespace std;

char tolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    if (in <= 'Я' && in >= 'А')
        return in - ('Я' - 'я');
    return in;
}

int main() {
    string all = "";
    setlocale(LC_ALL, "RUSSIAN");
    std::ifstream file("C:\\Users\\Nuta\\Documents\\Open MP\\Practice 13.03\\open.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return 1;
    }
    unordered_map<string, int> word_map;
    string word;
    string w = "";

#pragma omp parallel for

    while (file >> word) {

#pragma omp critical 
        {
            for (int i = 0; i < word.size(); i++) {
                char t = tolower(word[i]);
                if (t >= 'а' && t <= 'я' || t >= 'a' && t <= 'z') {
                    w += t;
                }
            }
            word_map[w]++;
            w = "";
        }
    }
    cout << "Слова, встречающиеся в тексте:" << endl;

    vector<pair<string, int> > myMap;
    for (auto& pair : word_map) {
        myMap.push_back(pair);
    }
    sort(myMap.begin(), myMap.end(), [](pair<string, int>& a, pair<string, int>& b) {
        return a.second > b.second;
        });

    for (auto& pair : myMap) {
        if (pair.second > 0) {
            cout << ' ' << pair.first << " " << pair.second << " раз" << endl;
        }
    }

    file.close();

    return 0;
}
