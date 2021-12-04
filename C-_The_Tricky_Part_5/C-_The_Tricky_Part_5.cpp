#include <iostream>
#include <random>
#include <chrono>
#include <set>
#include <iterator>
#include <list>
#include <regex>
#include <string>

using namespace std;

const size_t SIZE_LIST = 11;

int RandomNumber(int min, int max) 
{
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int> dis(min, max);
    return dis(generator);
}

template<typename T>
void PrintAll(const T& begin, const T& end) 
{
    for (T p1 = begin; p1 != end; p1++) 
    {
        cout << *p1 << '\t';
    }
    cout << endl << endl;
}

template<typename T>
void PrintUnique(const T& begin, const T& end) 
{
    for (T p1 = begin; p1 != end; p1++) 
    {
        T p2;
        for (p2 = begin; p2 != p1; p2++) 
        {
            if (*p1 == *p2)
                break;
        }
        if (p1 == p2)
            cout << *p1 << '\t';
    }
    cout << endl << endl;
}

string GenerateRandomString() 
{
    int length = RandomNumber(3, 10);
    bool uppercase = RandomNumber(0, 1);
    string result;
    for (size_t i = 0; i < length; i++) 
    {
        if (uppercase) 
        {
            result += char(RandomNumber('A', 'Z'));
        }
        else 
        {
            result += char(RandomNumber('a', 'z'));
        }
    }
    return result;
}

auto cmp = [](const string& a, const string& b) 
{
    return a.length() > b.length(); 
};

set<string, decltype(cmp)> SplitString(string& str, char delimiter = '.') 
{
    set<string, decltype(cmp)> result;
    auto start = 0U;
    auto end = str.find(delimiter);
    while (end != string::npos) 
    {
        result.insert(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    if (start != end) 
    {
        result.insert(str.substr(start, end - start));
    }
    return result;
}

void exercise1() 
{
    {
        list<string> word_list;
        word_list.push_back(GenerateRandomString());
        for (size_t i = 1; i < SIZE_LIST; i++) 
        {
            bool repeat = RandomNumber(0, 1);
            if (repeat) 
            {
                int repeat_index = RandomNumber(0, i - 1);
                auto word_iterator = word_list.begin();
                advance(word_iterator, repeat_index);
                string repeat_word = *word_iterator;
                word_list.push_back(repeat_word);
            }
            else 
            {
                word_list.push_back(GenerateRandomString());
            }
        }
        PrintAll(word_list.begin(), word_list.end());
        PrintUnique(word_list.begin(), word_list.end());
    }

    {
        multiset<string> word_list;
        word_list.insert(GenerateRandomString());
        for (size_t i = 1; i < SIZE_LIST; i++) 
        {
            bool repeat = RandomNumber(0, 1);
            if (repeat) 
            {
                int repeat_index = RandomNumber(0, i - 1);
                auto word_iterator = word_list.begin();
                advance(word_iterator, repeat_index);
                string repeat_word = *word_iterator;
                word_list.insert(repeat_word);
            }
            else 
            {
                word_list.insert(GenerateRandomString());
            }
        }
        PrintAll(word_list.begin(), word_list.end());
        PrintUnique(word_list.begin(), word_list.end());
    }
}

void exercise2() 
{
    string sentences;
    cout << "Enter some string: ";
    getline(cin, sentences);
    cout << sentences << endl;
    set<string, decltype(cmp)> container = SplitString(sentences);
    copy(container.begin(), container.end(), ostream_iterator<string>(cout, " \n"));
}

int main() 
{
    {
    /*     DZ1
        Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов,
    и выводящую в консоль список уникальных слов
    (если слово повторяется больше 1 раза, то вывести его надо один раз).

        Продемонстрировать работу функции, передав итераторы различных типов.
    */
    exercise1();
    }

    {
    /*      DZ2
    	Используя ассоциативный контейнер, напишите программу,
    которая будет считывать данные введенные пользователем из стандартного потока ввода и разбивать их на предложения.

    	Далее программа должна вывести пользователю все предложения, отсортировав их по длине.
    */
    exercise2();
    }
}