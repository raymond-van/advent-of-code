#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "util/bigint.h"

using namespace std;

BigInt ans = 0;
int m = 0;
vector<unordered_map<string, BigInt>> memo;
vector<string> input;

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
        input.push_back(a);
      }
    }
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

BigInt dp(string num, int b) {
  if (b == 0) return BigInt("1");
  if (memo[b].count(num)) return memo[b][num];
  if (num == "0") {
    return memo[b][num] = dp("1", b-1);
  } else if (num.size() % 2 == 0) {
    BigInt l_ans, r_ans;
    int mid = num.size() / 2;
    string l = num.substr(0, mid);
    l_ans = dp(l, b-1);
    string r = num.substr(mid);
    int idx = 0;
    while (idx < r.size() and r[idx] == '0')
      idx++;
    r = r.substr(idx);
    if (r.size() == 0)
      r_ans = dp("0", b-1);
    else
      r_ans = dp(r, b-1);
    return memo[b][num] = l_ans + r_ans;
  } else {
    return memo[b][num] = dp((BigInt(num) * BigInt("2024")).str(), b-1);
  }
}

void solve() {
  try {
    int blinks = 75;
    memo.resize(blinks+1);
    for (string num : input) {
      ans = ans + dp(num, blinks);
    }
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}


int main() {
  try {
    string path = filesystem::current_path() / "inputs/11.txt";
    read_input(path);
    m = input.size();
    cout << m << '\n';
    solve();
    cout << "ans: " << ans << endl;
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}

// stack soln: stable, too slow

// stack<pi> s;
// void read_input(const string &file_name) {
//   try {
//     ifstream file(file_name);
//     if (!file.is_open()) {
//       cerr << "Failed to open the file: " << file_name << '\n';
//       exit(1);
//     }
//     string line;
//     while (getline(file, line)) {
//       istringstream iss(line);
//       string a;
//       while (iss >> a) {
//         s.push({BigInt(a), 0});
//       }
//     }
//   } catch (const exception &e) {
//     cerr << "Caught exception reading input: " << e.what() << '\n';
//     throw e;
//   }
// }
//
// void solve() {
//   try {
//     int blinks = 75;
//     while (s.size()) {
//       pi p = s.top();
//       s.pop();
//       BigInt cur = p.first;
//       int ct = p.second + 1;
//       // cout << cur << ' ' << ct <<'\n';
//       if (ct <= blinks) {
//         if (cur.str() == "0") {
//           s.push({BigInt("1"), ct});
//         } else if (cur.size() % 2 == 0) {
//           int mid = cur.size() / 2;
//           string l = cur.str().substr(0, mid);
//           s.push({BigInt(l), ct});
//           string r = cur.str().substr(mid);
//           int idx = 0;
//           while (idx < r.size() and r[idx] == '0')
//             idx++;
//           r = r.substr(idx);
//           if (r.size() == 0)
//             s.push({BigInt("0"), ct});
//           else
//             s.push({BigInt(r), ct});
//         } else {
//           BigInt num = cur * BigInt(2024);
//           s.push({num, ct});
//         }
//       } else{
//         ans++;
//       }
//     }
//   } catch (const exception &e) {
//     cerr << "Caught exception solving: " << e.what() << '\n';
//     throw e;
//   }
// }
//
// int main() {
//   try {
//     string path = filesystem::current_path() / "inputs/11.txt";
//     read_input(path);
//     m = s.size();
//     cout << m << '\n';
//     solve();
//     cout << "ans: " << ans << endl;
//   } catch (const exception &e) {
//     cerr << "Caught exception (main): " << e.what() << '\n';
//     return 1;
//   }
//   return 0;
// }
