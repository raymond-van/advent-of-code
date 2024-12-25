#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned long long ll;

int ans = 0, m = 0, n = 0;
vector<vector<char>> input;
vector<pair<int,int>> area_per;
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
      vector<char> row;
      while (iss >> a) {
        row.push_back(a);
      }
      input.push_back(row);
    }
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

int dir[5] = {-1, 0, 1, 0, -1};

bool valid(int i, int j) {
  if (i < 0 or j < 0 or i >= m or j >= n) return false;
  return true;
}

void dfs(int i, int j, char c, int &area, int &per, set<pair<int,int>> &st) {
  if (st.count({i,j})) return;
  st.insert({i, j});
  input[i][j] = '!';
  int ct = 0;
  for (int d = 0; d < 4; d++) {
    int ii = i + dir[d];
    int jj = j + dir[d+1];
    if (valid(ii, jj)) { 
      if (input[ii][jj] == c) dfs(ii, jj, c, area, per, st); 
      else if (input[ii][jj] != '!' and !st.count({ii, jj})) {
        ct++;
      }
    } else { 
      ct++;
    } 
  }
  area++;
  per += ct;
  input[i][j] = '@';
}

void solve() {
  try {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (input[i][j] != '@') {
          // cout << input[i][j] << ' ';
          set<pair<int,int>> st;
          int area = 0;
          int per = 0;
          dfs(i, j, input[i][j], area, per, st);
          // cout <<  area << ' ' << per << '\n';
          area_per.push_back({area, per});
        }
      }
    }
    for (auto &[area, per] : area_per) {
      ans += area * per;
    }
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/12.txt";
    read_input(path);
    m = input.size();
    n = input[0].size();
    cout << "m: " << m << " n: " << n << '\n'; 
    solve();
    cout << "ans: " << ans << '\n';
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
