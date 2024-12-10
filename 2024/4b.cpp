#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> input;
int ans = 0;
int x[4] = {-1,1,-1,1};
int y[4] = {-1,1,1,-1};
int m = 0, n = 0;

vector<string> read_input(const string &file_name) {
  ifstream file(file_name);
  if (!file.is_open()) {
    cerr << "Failed to open the file: " << file_name << '\n';
    exit(1);
  }
  string line;
  vector<string> row;
  while (getline(file, line)) {
    istringstream iss(line);
    string s;
    while (iss >> s) {
      row.push_back(s);
    }
  }
  return row;
}

// dfs
void solve(vector<string> &input) {
  int sz = input[0].size();
  for (int i = 0; i < m; i++) {
    if (input[i].size() != sz) {
      cerr << "wtf" << '\n';
    }

    for (int j = 0; j < n; j++) {
      if (input[i][j] == 'A') {
        int num_x = 0;
        for (int d = 0; d < 4; d++) {
          int ii = i + y[d], iii = i - y[d];
          int jj = j + x[d], jjj = j - x[d];
          if (ii < 0 or jj < 0 or iii < 0 or jjj < 0 or ii >= m or jj >= n or iii >= m or jjj >= n) continue;
          if (input[ii][jj] == 'M' and input[iii][jjj] == 'S') num_x++;
        }
        if (num_x == 2) ans++;
        if (num_x > 2) cout << "WTF" << '\n';
      }
    }
  }
}

int main() {
  string path = filesystem::current_path() / "2024/inputs/4.txt";
  input = read_input(path);
  m = input.size(), n = input[0].size();
  solve(input);
  cout << "ans: " << ans << '\n';

  return 0;
}
