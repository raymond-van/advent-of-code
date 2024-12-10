#include <filesystem>
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

void solve() {
  
}

int ans = -1;
int main() {
  string path = filesystem::current_path()/"2024/inputs/_.txt";
  vector<vector<int>> input = read_input(path);
  solve();
  cout << "ans: " << ans << endl;

  return 0;
}
