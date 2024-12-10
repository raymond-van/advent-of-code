#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> input;
int ans = 0;
int x[8] = {1, 1, 1, -1, -1, -1, 0, 0};
int y[8] = {0, 1, -1, 0, 1, -1, 1, -1};
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

void dfs(char c, int i, int j, int dir = -1) {
  if (i < 0 or j < 0 or i >= m or j >= n or input[i][j] != c)
    return;
  if (c == 'S' and input[i][j] == 'S') {
    ans++;
    return;
  }
  char next_c = '.';
  if (c == 'X') next_c = 'M';
  else if (c == 'M') next_c = 'A';
  else if (c == 'A') next_c = 'S';
  if (dir == -1) {
    for (int d = 0; d < 8; d++) {
      int ii = i + y[d], jj = j + x[d];
      dfs(next_c, ii, jj, d);
    }
  } else {
    dfs(next_c, i + y[dir], j + x[dir], dir);
  }
}

// dfs
void solve(vector<string> &input) {
  int sz = input[0].size();
  for (int i = 0; i < m; i++) {
    if (input[i].size() != sz) {
      cerr << "wtf" << '\n';
    }
    for (int j = 0; j < n; j++) {
      if (input[i][j] == 'X') {
        dfs('X', i, j);
      }
    }
  }
}

int main() {
  string path = filesystem::current_path() / "2024/inputs/4.txt";
  input = read_input(path);
  m = input.size(), n = input[0].size();
  solve(input);
  cout << "ans: " << ans << endl;

  return 0;
}
