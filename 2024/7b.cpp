#include <boost/multiprecision/cpp_int.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using boost::multiprecision::cpp_int;
using namespace std;

cpp_int ans = 0, m = 0, n = 0;
vector<vector<cpp_int>> input;
unordered_map<cpp_int, vector<vector<cpp_int>>> mp;
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
      char colon;
      cpp_int num;
      cpp_int key;
      iss >> key;
      if (mp.count(key)) {
        cout << "Mp already contains " << key << '\n';
      }
      iss >> colon; // push colon
      vector<cpp_int> vec;
      while (iss >> num) {
        vec.push_back(num);
      }
      mp[key].push_back(vec);
    }
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

cpp_int concat(cpp_int cur, cpp_int vi) {
  cpp_int cat;
  string a = cur.str();
  string b = vi.str();
  return cat = cpp_int(a+b);
}

bool dfs(cpp_int k, vector<cpp_int> &v, cpp_int cur, size_t i) {
  if (cur > k)
    return false;
  if (cur == k and i == v.size())
    return true;
  if (i >= v.size())
    return false;
  return dfs(k, v, cur + v[i], i + 1) or dfs(k, v, cur * v[i], i + 1) or dfs(k, v, concat(cur, v[i]), i + 1);
}

int valid = 0;

void solve() {
  try {
    for (auto &[k, vec] : mp) {
      for (auto &v : vec) {
        if (dfs(k, v, v[0], 1)) {
          ans += k;
          valid++;
        }
      }
    }
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/7.txt";
    read_input(path);
    int sz = mp.size();
    solve();
    cout << valid << '/' << sz << '\n';
    cout << "ans: " << ans << '\n';
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
