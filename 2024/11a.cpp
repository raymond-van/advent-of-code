#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;
typedef unsigned long long ll;

int ans = 0, m = 0, n = 0;
queue<string> q;
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
      string a;
      while (iss >> a) {
        q.push(a);
      }
    }
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

void solve() {
  try {
    int blinks = 25;
    for (int i = 0; i <= blinks; i++) {
      int sz = q.size();
      cout << i << ' ' << sz << '\n';
      for (int j = 0; j < sz; j++) {
        string cur = q.front();
        // if (i == 25) cout << cur << ' ';
        q.pop();
        if (cur == "0") {
          q.push("1");
        } else if (cur.size() % 2 == 0) {
          int mid = cur.size() / 2;
          string l = cur.substr(0, mid);
          q.push(l);
          string r = cur.substr(mid);
          int idx = 0;
          while (idx < r.size() and r[idx] == '0')
            idx++;
          r = r.substr(idx);
          if (r.size() == 0)
            q.push("0");
          else
            q.push(r);
        } else {
          ll num = stoull(cur) * 2024;
          q.push(to_string(num));
        }
      }
      // cout << '\n';
    }
    ans = q.size();
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/11.txt";
    read_input(path);
    m = q.size();
    cout << m << '\n';
    solve();
    cout << "ans: " << ans << endl;
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
