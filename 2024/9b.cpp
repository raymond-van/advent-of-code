#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long ll;

int blocks = 0;
int m = 0, n = 0;
ll ans = 0;
vector<int> files (10000, 0);
vector<int> free_mem (10000, 0);
vector<queue<pair<int,int>>> used_free;

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
    used_free.resize(file_i);
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

void solve() {
  try {
    int f_id = 0;
    int used_space = 0;
    for (int i = f_id_end; i >= 1; i--) {
      for (int j = 0; j < i; j++) {
        if (files[i] and free_mem[j] >= files[i]) {
          free_mem[j] -= files[i];
          used_free[j].push({i, files[i]});
          break;
        }
      }
    }
    unordered_set<int> seen;
    for (int i = 0; i < blocks;) {
      if (files[f_id] > 0) {
        if (!seen.count(f_id)) {
          ans += f_id * i;
        }
        i++;
        files[f_id]--;
      } else if (used_free[f_id].size() > 0) {
        int f_id_end2 = used_free[f_id].front().first;
        for (int j = 0; j < used_free[f_id].front().second; j++) {
          ans += f_id_end2 * i;
          i++;
        }
        seen.insert(f_id_end2);
        used_free[f_id].pop();
      } else if (free_mem[f_id] > 0) {
        free_mem[f_id]--;
        i++;
      } 
      if (files[f_id] == 0 and free_mem[f_id] == 0 and used_free[f_id].size() == 0){
        seen.insert(f_id);
        f_id++;
      }
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
