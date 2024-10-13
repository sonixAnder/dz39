#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// Функция для обработки строки: приведение к нижнему регистру и удаление пунктуации
string processWord(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower); // Приведение к нижнему регистру
    word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end()); // Удаление пунктуации
    return word;
}

int main()
{
    setlocale(LC_ALL, "ru");
    // Открытие файла для чтения
    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cout << "Не удалось открыть файл input.txt" << endl;
        return 1;
    }

    // Карта для хранения частоты слов
    map<string, int> wordFrequency;

    string word;
    // Чтение файла и заполнение словаря
    while (inputFile >> word)
    {
        word = processWord(word);
        if (!word.empty())
        {
            wordFrequency[word]++;
        }
    }
    inputFile.close();

    // Вывод всех слов и их частоты
    cout << "Частота слов:" << endl;
    for (const auto& entry : wordFrequency)
    {
        cout << entry.first << ": " << entry.second << endl;
    }

    // Поиск наиболее часто встречающегося слова
    string mostFrequentWord;
    int maxFrequency = 0;
    for (const auto& entry : wordFrequency)
    {
        if (entry.second > maxFrequency)
        {
            maxFrequency = entry.second;
            mostFrequentWord = entry.first;
        }
    }

    // Вывод наиболее часто встречающегося слова
    cout << "\nНаиболее часто встречающееся слово: " << mostFrequentWord
        << " (" << maxFrequency << " раз)" << endl;

    // Запись результатов в файл output.txt
    ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        cout << "Не удалось открыть файл output.txt" << endl;
        return 1;
    }

    outputFile << "Частота слов:" << endl;
    for (const auto& entry : wordFrequency)
    {
        outputFile << entry.first << ": " << entry.second << endl;
    }
    outputFile << "\nНаиболее часто встречающееся слово: " << mostFrequentWord
        << " (" << maxFrequency << " раз)" << endl;

    outputFile.close();

    return 0;
}
