#include <filesystem>
#include <fstream>
#include <iostream>
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
      int a;
      vector<int> row;
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

  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/test.txt";
    read_input(path);
    m = input.size();
    // n = input[0].size();
    cout << "m: " << m << " n: " << n << '\n'; 
    solve();
    cout << "ans: " << ans << endl;
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
