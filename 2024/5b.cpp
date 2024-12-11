#include <csignal>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int ans = 0;
int m, n;
vector<vector<int>> rules;
vector<vector<int>> updates;
void read_input(const string &file_name) {
  ifstream file(file_name);
  if (!file.is_open()) {
    cerr << "Failed to open the file: " << file_name << '\n';
    exit(1);
  }
  string line;
  char delimiter = '|';
  while (getline(file, line)) {
    istringstream iss(line);
    string num;
    vector<int> row;
    if (line.size() == 0) {
      delimiter = ',';
      cout << "New line found" << '\n';
      continue;
    }
    while (getline(iss, num, delimiter)) {
      row.push_back(stoi(num));
    }
    if (delimiter == '|')
      rules.push_back(row);
    else
      updates.push_back(row);
  }
}

void solve() {
  try {
    unordered_map<int, unordered_set<int>> mp;
    for (int i = 0; i < m; i++) {
      mp[rules[i][0]].insert(rules[i][1]);
    }
    for (int i = 0; i < n; i++) {
      int o = updates[i].size();
      bool valid = true;
      for (int j = 0; j < o; j++) {
        int num = updates[i][j];
        for (int k = 0; k < j; k++) {
          int prev = updates[i][k];
          if (mp[num].count(prev)) {
            // cout << num << " should be before " << prev << '\n';
            swap(updates[i][k], updates[i][j]);
            valid = false;
          }
        }
      }
      if (valid) {
        // not part of soln
      } else {
        int mid = o / 2;
        ans += updates[i][mid];
      }
    }
  } catch (const exception &e) {
    cerr << "Caught exception: " << e.what() << '\n';
    throw e;
  }
}

int main() {
  string path = filesystem::current_path() / "2024/inputs/5.txt";
  read_input(path);
  try {
    m = rules.size();
    n = updates.size();
    solve();
    cout << "ans: " << ans << '\n';
  } catch (const exception &e) {
    cerr << "Caught exception: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
