#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int blocks = 0;
int m = 0, n = 0;
ll ans = 0;
int files[10000] = {0};
int free_mem[10000] = {0};
string input;
int f_id_end = 0;
int file_space = 0;
void read_input(const string &file_name) {
  try {
    ifstream file(file_name);
    if (!file.is_open()) {
      cerr << "Failed to open the file: " << file_name << '\n';
      exit(1);
    }
    string line;
    while (getline(file, line)) {
      input = line;
    }
    int file_i = 0;
    int free_i = 0;
    for (int i = 0; i < input.size(); i++) {
      int sz = input[i] - '0';
      blocks += sz;
      if (i % 2 == 0) {
        files[file_i++] = sz;
        file_space += sz;
      } else {
        free_mem[free_i++] = sz;
      }
    }
    f_id_end = file_i;
    while (files[f_id_end] != 0) f_id_end--;
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

void solve() {
  try {
    int f_id = 0;
    int free_id = 0;
    for (int i = 0; i <= file_space;) {
      // cout << "i: "<< i << " FileID: " <<f_id << " FreeID: " << free_id << " FileIDEnd: " << f_id_end << '\n';
      if (f_id > f_id_end) {
        cout << "wtf2 "  << i << '\n';
        break;
      }
      if (files[f_id] > 0) {
        ans += f_id * i;
        files[f_id]--;
        i++;
        // cout <<"Ans: " << ans <<  " Adding file id " << f_id << " on block " << i-1 << '\n';
      } else if (files[f_id] == 0 and free_mem[free_id] > 0) {
        if (f_id > f_id_end) {
          cout << "wtf3 " << i  << '\n';
          break;
        }
        if (files[f_id_end] > 0) {
          ans += f_id_end * i;
          files[f_id_end]--;
          free_mem[free_id]--;
          i++;
          // cout << "Ans: " << ans << " Adding file id (FREE) " << free_id << ' ' << f_id_end << " on block " << i-1 << '\n';
        } else {
          f_id_end--;
          // cout << "Decreasing f_id_end" << '\n';
        }
      } 
      if (files[f_id] == 0 and free_mem[free_id] == 0){
        // cout << "Moving I" << '\n';
        f_id++;
        free_id++;
      }
      // if (files[f_id_end] == 0) f_id_end--;
    }
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/9.txt";
    read_input(path);
    m = input.size();
    cout << "m: " << m  << " blocks: " << blocks << " filespace: " << file_space << '\n';
    solve();
    cout << "ans: " << ans << endl;
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
