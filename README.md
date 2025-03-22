# Vending Machine DFA

## 📌 Deskripsi

Program ini mensimulasikan mesin penjual otomatis (vending machine) menggunakan **Deterministic Finite Automaton (DFA)**.  
Pengguna dapat memasukkan uang dan memilih minuman yang tersedia. Program akan menentukan apakah pembelian berhasil atau gagal berdasarkan jumlah uang yang dimasukkan.

## 🛠️ Fitur

- Mendukung input uang dalam pecahan **1000, 2000, 5000, dan 10000**.
- Dapat membeli minuman **A (3000), B (4000), dan C (5000)**.
- Menampilkan lintasan DFA yang dilalui.
- Menampilkan status **ACCEPTED** jika pembelian berhasil atau **REJECTED** jika gagal.
- Menyediakan fitur kembalian jika uang yang dimasukkan lebih dari harga minuman.

## 📝 Format DFA (File `vending_dfa.txt`)

DFA didefinisikan dalam file `vending_dfa.txt` dengan format berikut:

```
<state> <input> <next_state>
```

Contoh isi file:

```
S0 1000 S1000
S0 2000 S2000
S0 5000 S5000
S0 10000 S10000
...
```

## 🛠️ Cara Menjalankan Program

1. **Pastikan file DFA tersedia** (`vending_dfa.txt`).
2. **Kompilasi program** menggunakan g++:
   ```sh
   g++ -o vending_machine vending_machine.cpp
   ```
3. **Jalankan program**:
   ```sh
   ./vending_machine
   ```

## 💡 Contoh Penggunaan

### ✅ **Pembelian berhasil (uang pas)**

```
Masukkan uang atau beli minuman (1000, 2000, 5000, 10000, A, B, C): 2000
Masukkan uang atau beli minuman (1000, 2000, 5000, 10000, A, B, C): 1000
ON: Minuman A
Masukkan uang atau beli minuman (1000, 2000, 5000, 10000, A, B, C): A
Lintasan DFA: S0 → S2000 → S3000
Minuman A dapat dibeli. Status: ACCEPTED.
```

### ❌ **Pembelian gagal (uang kurang)**

```
Masukkan uang atau beli minuman (1000, 2000, 5000, 10000, A, B, C): 1000
Masukkan uang atau beli minuman (1000, 2000, 5000, 10000, A, B, C): 1000
Masukkan uang atau beli minuman (1000, 2000, 5000, 10000, A, B, C): B
Lintasan DFA: S0 → S1000 → S2000
Uang tidak cukup. Status: REJECTED.
```

## 🏢 Struktur Proyek

```
/vending-machine-dfa
│── vending_machine.cpp   # Kode utama program
│── vending_dfa.txt       # Definisi DFA
│── README.md             # Dokumentasi proyek
```

## 📝 Lisensi

Proyek ini bersifat open-source dan dapat digunakan secara bebas.
