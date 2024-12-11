#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int ans = 0;
int m, n;
vector<vector<int>> input;
void read_input(const string &file_name) {
  try {

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
    string path = filesystem::current_path() / "2024/inputs/_.txt";
    read_input(path);
    solve();
    cout << "ans: " << ans << endl;
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
