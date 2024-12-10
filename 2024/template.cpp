#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int ans = -1;
int m, n;
vector<vector<int>> input;
void read_input(const string &file_name) {
  ifstream file(file_name);
  if (!file.is_open()) {
    cerr << "Failed to open the file: " << file_name << '\n';
    exit(1);
  }
  string line;
  vector<vector<int>> rows;
  while (getline(file, line)) {
    istringstream iss(line);
    int number;
    vector<int> row;
    while (iss >> number) {
      row.push_back(number);
    }
    rows.push_back(row);
  }
}

void solve() {
  
}

int main() {
  string path = filesystem::current_path()/"2024/inputs/_.txt";
  read_input(path);
  solve();
  cout << "ans: " << ans << endl;

  return 0;
}
