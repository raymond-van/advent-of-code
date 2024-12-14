#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int ans = 0, m = 0, n = 0;
vector<vector<char>> input;
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

void solve() {
  try {
    set<pair<int,int>> st;
    unordered_map<char, vector<pair<int, int>>> mp;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (isalpha(input[i][j]) or isdigit(input[i][j]))
          mp[input[i][j]].push_back({i, j});
      }
    }
    for (auto &[c, v] : mp) {
      for (int i = 0; i < v.size(); i++) {
        int i1 = v[i].first;
        int j1 = v[i].second;
        for (int j = 0; j < i; j++) {
          int i2 = v[j].first;
          int j2 = v[j].second;
          int diff_i1 = i1 - i2;
          int diff_j1 = j1 - j2;
          int ii = i1 + diff_i1;
          int jj = j1 + diff_j1;
          int iii = i2 - diff_i1;
          int jjj = j2 - diff_j1;
          if (ii >= 0 and ii < m and jj >= 0 and jj < n) {
            st.insert({ii,jj});
          }
          if (iii >= 0 and iii < m and jjj >= 0 and jjj < n) {
            st.insert({iii,jjj});
          }
        }
      }
    }
    ans = st.size();
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}
// < 330
int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/8.txt";
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
