#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> read_input(const string &fileName) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cerr << "Failed to open the file: " << fileName << '\n';
    exit(1);
  }
  string line;
  vector<vector<int>> rows;
  while (getline(file, line)) {
    istringstream iss(line);
    int number;
    vector<int> numbers;
    while (iss >> number) {
      numbers.push_back(number);
    }
    rows.push_back(numbers);
  }
  return rows;
}
bool check_safe(const vector<int> &line, int& n, int skip = -1) {
  if (n == 0) return false;
  int prev_lvl = -1;
  int lvl = -1;
  bool safe = true;
  bool inc = true;
  bool inc_set = false;
  for (int i = 0; i < n; i++) {
    if (i == skip) continue;
    lvl = line[i];
    if (prev_lvl == -1) {
      prev_lvl = lvl;
      continue;
    } else if (!inc_set) {
      inc = lvl > prev_lvl;
      inc_set = true;
    }
    if (inc) {
      if (lvl - prev_lvl > 3)
        safe = false;
      if (lvl - prev_lvl <= 0)
        safe = false;
    } else {
      if (prev_lvl - lvl > 3)
        safe = false;
      if (prev_lvl - lvl <= 0)
        safe = false;
    }
    prev_lvl = lvl;
  }
  return safe;
}

int solve(const vector<vector<int>> &input) {
  int ans = 0;
  for (const auto &line : input) {
    int n = line.size();
    bool safe = check_safe(line, n);
    for (int i = 0; i < n and !safe; i++) {
      safe = check_safe(line, n, i);
    }
    if (safe) {
      ans++;
    }
  }
  return ans;
}

int main() {
  string path = "inputs/2.txt";
  vector<vector<int>> input = read_input(path);
  int ans = solve(input);
  cout << "ans: " << ans << endl;

  return 0;
}
