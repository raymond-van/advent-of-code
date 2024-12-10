#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

string input = "";
void read_input(const string &file_name) {
  ifstream file(file_name);
  if (!file.is_open()) {
    cerr << "Failed to open the file: " << file_name << '\n';
    exit(1);
  }
  string line;
  while (getline(file, line)) {
    input += line;
  }
}

int solve(string &s) {
  ll ans = 0;
  regex pattern(R"((mul\((\d+),(\d+)\))|(do\(\))|(don't\(\)))");
  vector<smatch> all_matches;
  auto words_begin = sregex_iterator(s.begin(), s.end(), pattern);
  auto words_end = sregex_iterator();
  for (sregex_iterator i = words_begin; i != words_end; ++i) {
    smatch match = *i;
    all_matches.push_back(match);
  }
  bool mul = true;
  for (size_t i = 0; i < all_matches.size(); i++) {
    const auto &match = all_matches[i];
    if (match[0] == "do()") {
      mul = true;
    } else if (match[0] == "don't()") {
      mul = false;
    } else if (mul) {
      int op1 = stoi(match[2]);
      int op2 = stoi(match[3]);
      ans += op1 * op2;
    }
  }
  return ans;
}

int main() {
  string path = filesystem::current_path() / "2024/inputs/3.txt";
  read_input(path);
  ll ans = solve(input);
  cout << "ans: " << ans << '\n';

  return 0;
}
