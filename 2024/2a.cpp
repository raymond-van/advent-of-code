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

int solve(const vector<vector<int>> &input) {
  int ans = 0;
  for (const auto &line : input) {
    int prev_lvl = -1;
    int lvl = -1;
    bool safe = true;
    bool inc = true;
    for (size_t i = 0; i < line.size()-1; i++) { // -1 bc last line is empty
      lvl = line[i];
      if (i == 0) {
        prev_lvl = lvl;
        continue;
      } else if (i == 1) {
        inc = lvl > prev_lvl;
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
