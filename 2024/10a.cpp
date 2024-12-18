#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int ans = 0, m = 0, n = 0;
vector<vector<int>> input;
void read_input(const string &file_name) {
  try {
    ifstream file(file_name);
    if (!file.is_open()) {
      cerr << "Failed to open the file: " << file_name << '\n';
      exit(1);
    }
    string line;
    while (getline(file, line)) {
      istringstream iss(line);
      char a;
      vector<int> row;
      while (iss >> a) {
        row.push_back(a-'0');
      }
      input.push_back(row);
    }
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

int dir[5] = {-1, 0, 1, 0, -1};

void dfs(int cur, int i, int j, set<pair<int,int>> &st) {
  if (i < 0 or j < 0 or i >= m or j >= n or input[i][j] != cur) return;
  if (cur == 9) {
    if (!st.count({i, j})) st.insert({i, j});
    return;
  }
  for (int d = 0; d < 4; d++) {
    int ii = i + dir[d], jj = j + dir[d+1];
    dfs(cur+1, ii, jj, st);
  }
  return;
}

void solve() {
  try {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int num = input[i][j];
        if (num == 0) {
          set<pair<int,int>> st;
          dfs(0, i, j, st);
          ans += st.size();
        }
      }
    }
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/10.txt";
    read_input(path);
    m = input.size();
    n = input[0].size();
    cout << "m: " << m << " n: " << n << '\n'; 
    solve();
    cout << "ans: " << ans << endl;
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
