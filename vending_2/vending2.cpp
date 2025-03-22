#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<string, int> harga;        // Harga barang
set<string> pecahan;          // pecahan yang diperbolehkan
vector<string> lintasan, keranjang;
int saldo = 0;
string currentState = "S0";

void load_product_data(const string &filename){
    ifstream file(filename);
    if (!file){
        cerr << "Gagal membuka data produk" << endl;
        exit(1);
    }
    string command;
    while(file >> command){
      if(command == "END") break;

      if(command == "input_barang"){
        // format: banyak barang -> nama barang, harga barang
        int banyak_barang, harga_barang; 
        string nama_barang;
        file >> banyak_barang;

        while(banyak_barang--){
          file >> nama_barang >> harga_barang;
          harga[nama_barang] = harga_barang;
        }
      }
      else if(command == "pecahan"){
        // format: banyak pecahan -> pecahan
        int banyak_pecahan;
        string pec;
        file >> banyak_pecahan;
        while(banyak_pecahan--){
          file >> pec;
          pecahan.insert(pec);
        }
      } 
    }
    file.close();
}

void printDFAPath(){
    cout << "Lintasan DFA: ";
    for (size_t i = 0; i < lintasan.size(); i++){
        cout << lintasan[i];
        if (i < lintasan.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}
void cetak_keranjang(){
  if(keranjang.size() == 0) return ;
  cout << "Isi keranjang anda: ";
  for(int i = 0; i < (int)keranjang.size(); i++) cout << keranjang[i] << ", "[i == (int)keranjang.size() - 1];
  cout << '\n';
}
void cetak_saldo(){
  cout << "saldo anda: " << saldo << '\n';
}
void cetak_kembalian(){
  if(keranjang.size() == 0) return ;
  cout << "Kembalian anda: " << saldo << '\n';
}

int main(){
    load_product_data("vending_dfa2.txt");

    string input;
    cout << "Pecahan yang diperbolehkan: ";
    for(string s : pecahan) cout << s << ' ';
    cout << "\n\nDaftar barang: \n";
    for(auto [s, t] : harga) cout << s << " @ Rp." << t << "\n";
    cout << "\ntekan \"done\" jika sudah selesai memilih\n";
    cout << "tekan \"hapus\" untuk menghapus barang terakhir\n\n";
    
    while(1){
      cout << "Masukkan uang atau beli barang: ";
      cin >> input;
      // input yang diperbolehkan:
      // 1. pecahan dalam set pecahan
      // 2. barang dalam daftar harga barang
      // 3. command hapus barang terakhir
      // 4. command selesai membeli

      // cek jika ada di set pecahan
      if(pecahan.find(input) != pecahan.end()){
        int uang = stoi(input); // input sudah pasti dapat diconvert ke integer
        saldo += uang;
        lintasan.push_back("S" + to_string(saldo));
        cetak_keranjang();
        cetak_saldo();
      }
      // cek jika ada di daftar harga barang dan saldo mencukupi
      else if(harga[input] != 0){
        if(saldo < harga[input]){
          cout << "[Error] Uang anda tidak mencukupi\n";
          continue;
        }
        keranjang.push_back(input);
        saldo -= harga[input];
        lintasan.push_back("S" + to_string(saldo));
        cetak_keranjang();
        cetak_saldo();
      }
      // cek jika command nya hapus barang terakhir
      else if(input == "hapus"){
        if(keranjang.size() == 0){
          cout << "[Error] Anda belum memilih barang apapun.\n";
          continue;
        }
        saldo += harga[keranjang.back()];
        keranjang.pop_back();
        lintasan.push_back("S" + to_string(saldo));
        cetak_keranjang();
        cetak_saldo();
      }
      // cek jika command nya selesai
      else if(input == "done"){
        break;
      }
      else {
        cout << "[Error] Masukkan nominal uang atau nama barang yang sesuai\n";
      }
    }

    cout << '\n';
    cetak_keranjang();
    cetak_kembalian();
    printDFAPath();

    return 0;
}
