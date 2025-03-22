#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

// Harga minuman
map<char, int> harga = {{'A', 3000}, {'B', 4000}, {'C', 5000}};

// DFA Transitions
map<string, map<string, string>> dfa;

void loadDFA(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Gagal membuka file DFA!" << endl;
        exit(1);
    }
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string state, input, nextState;
        iss >> state >> input >> nextState;
        dfa[state][input] = nextState;
    }
    file.close();
}

void printDFAPath(const vector<string> &path)
{
    cout << "Lintasan DFA: ";
    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i < path.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}

int main()
{
    loadDFA("vending_dfa.txt");

    int saldo = 0;
    string currentState = "S0";
    vector<string> lintasan = {currentState};
    string input;

    while (true)
    {
        cout << "Masukkan uang atau beli minuman (1000, 2000, 5000, 10000, A, B, C): ";
        cin >> input;

        if (dfa[currentState].find(input) != dfa[currentState].end())
        {
            currentState = dfa[currentState][input];
            lintasan.push_back(currentState);
        }
        else if (harga.find(input[0]) != harga.end())
        {
            // Cek jika input adalah minuman (A, B, C)
            char pilihan = input[0];
            if (saldo >= harga[pilihan])
            {
                int kembalian = saldo - harga[pilihan];
                printDFAPath(lintasan);
                cout << "Minuman " << pilihan << " dapat dibeli. Status: ACCEPTED." << endl;
                if (kembalian > 0)
                {
                    cout << "Kembalian: " << kembalian << endl;
                }
                break;
            }
            else
            {
                printDFAPath(lintasan);
                cout << "Uang tidak cukup. Status: REJECTED." << endl;
                break;
            }
        }
        else if (stoi(input) > 10000)
        {
            cout << "Uang tidak bisa lebih dari 10000" << endl;
            continue;
        }
        else
        {
            cout << "Input tidak valid!" << endl;
            continue;
        }

        if (input == "1000" || input == "2000" || input == "5000" || input == "10000")
        {
            int uang = stoi(input);
            saldo += uang;

            // Tampilkan minuman yang tersedia
            if (saldo >= 3000)
            {
                cout << "ON: ";
                bool first = true;

                for (auto &item : harga)
                {
                    if (saldo >= item.second)
                    {
                        if (!first)
                            cout << ", ";
                        cout << "Minuman " << item.first;
                        first = false;
                    }
                }
                cout << endl;
            }
        }
    }
    return 0;
}
