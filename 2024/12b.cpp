#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long ll;

// very dirty soln :(

int ans = 0, m = 0, n = 0;
vector<vector<char>> input;
vector<pair<int, int>> area_sides;
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

// up, right, down, left
int dir[5] = {-1, 0, 1, 0, -1};

bool in_bounds(int i, int j) {
  if (i < 0 or j < 0 or i >= m or j >= n)
    return false;
  return true;
}

bool same_ch(int i, int j, char c, vector<vector<char>> &v) {
  if (v[i][j] == c)
    return true;
  return false;
}

void dfs(int i, int j, char c, int &area, vector<string> &sides,
         set<pair<int, int>> &st, vector<vector<char>> &input2) {
  if (st.count({i, j}))
    return;
  st.insert({i, j});
  input2[i][j] = '!';
  bool valid[4] = {false};
  char same[4] = {false};
  char ch[4] = {'#'};

  for (int d = 0; d < 4; d++) {
    int ii = i + dir[d];
    int jj = j + dir[d + 1];
    if (in_bounds(ii, jj)) {
      valid[d] = true;
      ch[d] = input[ii][jj];
      if (same_ch(ii, jj, c, input)) {
        same[d] = true;
        dfs(ii, jj, c, area, sides, st, input2);
      }
    }
  }
  char u = ch[0], r = ch[1];
  char d = ch[2], l = ch[3];
  bool u_v = valid[0], r_v = valid[1], d_v = valid[2], l_v = valid[3];
  bool u_s = same[0], r_s = same[1], d_s = same[2], l_s = same[3];
  // corners
  // case 1: dir1 same and dir2 same -> diag not same
  // case 2: dir1 !same and dir2 !same
  // up right
  if (u_s and r_s) { // case 1
    if (in_bounds(i-1, j+1) and !same_ch(i-1, j+1, c, input)) {
      sides.push_back(to_string(u) + '-' + to_string(r));
    }
  }
  if (!u_s and !r_s) { // case 2
    sides.push_back(to_string(u) + '-' + to_string(r));
  }
   
  if (u_s and l_s) {
    // up left
    if (in_bounds(i-1,j-1) and !same_ch(i-1, j-1, c, input)) {
      sides.push_back(to_string(u) + '-' + to_string(l));
    }
  }
  if (!u_s and !l_s) {
      sides.push_back(to_string(u) + '-' + to_string(l));
  }

  // down right
  if (d_s and r_s) {
    if (in_bounds(i+1,j+1) and !same_ch(i+1, j+1, c, input)) {
      sides.push_back(to_string(d) + '-' + to_string(r));
    }
  }
  if (!d_s and !r_s) {
    sides.push_back(to_string(d) + '-' + to_string(r));
  }

  // down left
  if (d_s and l_s) {
    if (in_bounds(i+1,j-1) and !same_ch(i+1, j-1, c, input)) {
      sides.push_back(to_string(d) + '-' + to_string(l));
    }
  } 
  if (!d_s and !l_s) {
    sides.push_back(to_string(d) + '-' + to_string(l));
  }
  input2[i][j] = '@';
  area++;
}

void solve() {
  try {
    set<pair<int, int>> st;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (!st.count({i, j})) {
          // cout << "Char: " << input[i][j] << '\n';
          int area = 0;
          vector<string> sides;
          vector<vector<char>> input2 = input;
          dfs(i, j, input[i][j], area, sides, st, input2);
          // cout << "Area: " << area << " Corner: " << sides.size() << '\n';
          area_sides.push_back({area, sides.size()});
        }
      }
    }
    for (auto &[area, sides] : area_sides) {
      ans += area * sides;
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
