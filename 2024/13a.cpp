#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long long ll;

struct Game {
  pair<int, int> a;
  pair<int, int> b;
  pair<int, int> p;
  Game() : a({0, 0}), b({0, 0}), p({0, 0}) {}
};

int ans = 0, m = 0, n = 0;
vector<Game *> input;
void read_input(const string &file_name) {
  try {
    ifstream file(file_name);
    if (!file.is_open()) {
      cerr << "Failed to open the file: " << file_name << '\n';
      exit(1);
    }
    string line;
    Game *g = new Game();
    int i = 0;
    while (getline(file, line)) {
      istringstream iss(line);
      string a;
      vector<string> row;
      while (iss >> a) {
        row.push_back(a);
      }
      if (i == 0 or i == 1) {
        int x = stoi(row[2].substr(2, row[2].size() - 2));
        int y = stoi(row[3].substr(2));
        if (i == 0)
          g->a = {x, y};
        else
          g->b = {x, y};
      } else if (i == 2) {
        int x = stoi(row[1].substr(2, row[1].size() - 2));
        int y = stoi(row[2].substr(2));
        g->p = {x, y};
      }
      i++;
      if (i == 4) {
        input.push_back(g);
        g = new Game();
        i %= 4;
      }
    }
    input.push_back(g);
  } catch (const exception &e) {
    cerr << "Caught exception reading input: " << e.what() << '\n';
    throw e;
  }
}

void solve() {
  try {
    for (Game *g : input) {
      int ax = g->a.first, ay = g->a.second;
      int bx = g->b.first, by = g->b.second;
      int px = g->p.first, py = g->p.second;
      if ((ax * 100) + (bx * 100) < px)
        continue;
      if ((ay * 100) + (by * 100) < py)
        continue;
      int mx_bx = px / bx;
      int mx_by = py / by;
      int mx_b = min(mx_bx, mx_by);
      if (mx_bx == 0)
        cout << "wtf" << '\n';
      while (mx_b > 0) {
        int ppx = px - (mx_b * bx);
        int ppy = py - (mx_b * by);
        int mx_ax = ppx / ax;
        int mx_ay = ppy / ay;
        int rem_x = ppx % ax;
        int rem_y = ppy % ay;
        if (mx_ax == mx_ay and !rem_x and !rem_y) {
          ans += mx_b + (3 * mx_ax);
          break;
        }
        mx_b--;
      }
    }
  } catch (const exception &e) {
    cerr << "Caught exception (solve): " << e.what() << '\n';
  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/13.txt";
    read_input(path);
    m = input.size();
    cout << "m: " << m << '\n';
    solve();

    cout << "ans: " << ans << '\n';
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
