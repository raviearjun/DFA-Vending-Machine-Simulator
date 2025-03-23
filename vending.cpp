#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

// Harga minuman
map<char, int> harga =  {{'A', 3000}, {'B', 4000}, {'C', 5000}};

// DFA Transitions
map<string, map<string, string>> dfa;

void loadDFA(string filename){
    ifstream file(filename);
    if (!file){
        cerr << "Gagal membuka file DFA!" << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)){
        istringstream iss(line);
        string state, input, nextState;
        iss >> state >> input >> nextState;
        dfa[state][input] = nextState;
    }
    file.close();
}

void printDFAPath(const vector<string> &path){
    cout << "Lintasan DFA: ";
    for (size_t i = 0; i < path.size(); i++){
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main(){
    loadDFA("vending_dfa.txt");

    int saldo = 0;
    string currentState = "S0";
    vector<string> lintasan = {currentState};
    string input;

    cout << "Daftar Harga Minuman:\n";
    for(auto [p, q] : harga){
      cout << p << ": " << q << '\n';
    }
    cout << '\n';

    while (true){
        cout << "Masukkan uang (1000, 2000, 5000, 10000) atau beli minuman (A, B, C): ";
        cin >> input;

        if (dfa[currentState].find(input) != dfa[currentState].end()){
            currentState = dfa[currentState][input];
            lintasan.push_back(currentState);
        }
        else if((int)input.size() == 1 && harga.find(input[0]) != harga.end()){
            // Cek jika input adalah minuman (A, B, C)
            char pilihan = input[0];
            if (saldo >= harga[pilihan]){
                int kembalian = saldo - harga[pilihan];
                cout << '\n';
                printDFAPath(lintasan);
                cout << "Minuman " << pilihan << " dapat dibeli. Status: ACCEPTED." << endl;
                if (kembalian > 0){
                    cout << "Kembalian: " << kembalian << endl;
                }
                break;
            }
            else{
                printDFAPath(lintasan);
                cout << "Uang tidak cukup. Status: REJECTED." << endl;
                break;
            }
        }
        else { // barang yang tidak ada atau uang yang tidak ada
            bool valid_money = 0, valid_product = (int)input.size() == 1 && ('A' <= input[0] && input[0] <= 'C');
            for(string s : {"1000", "2000", "5000", "10000"}) valid_money |= input == s;
            bool digit_semua = 1;
            for(char c : input) digit_semua &= '0' <= c && c <= '9';

            if(digit_semua && !valid_money){
              cout << "Uang yang anda masukkan tidak valid\n";
              continue;
            }
            else if(!digit_semua && !valid_product){
              cout << "Minuman yang anda pilih tidak tersedia\n";
              continue;
            }
        } 

        if(saldo + stoi(input) > 10000){
            cout << "Uang yang anda masukkan tidak bisa lebih dari 10000" << endl;
            continue;
        }
        saldo += stoi(input);
        
        // Tampilkan minuman yang tersedia
        if (saldo >= 3000){
            cout << "ON: ";
            bool first = true;

            for (auto &item : harga){
                if (saldo >= item.second){
                    if (!first)
                        cout << ", ";
                    cout << "Minuman " << item.first;
                    first = false;
                }
            }
            cout << endl;
        }
    }
    return 0;
}
