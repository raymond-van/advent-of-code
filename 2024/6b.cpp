#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int ans = 0;
int m, n;
vector<vector<char>> input;
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
      char a;
      vector<char> row;
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

bool can_escape(vector<vector<char>> input, int x, int y, int dir) {
  try {
    bool looped = false;
    while (x >= 0 and x < m and y >= 0 and y < n and !looped) {
      if (input[x][y] == '.') {
        input[x][y] = '0';
      } else if (input[x][y] >= '0' and input[x][y] <= '9') {
        if (input[x][y] == '9') {
          looped = true;
          break;
        }
        input[x][y]++;
      }
      if (dir == 0) {
        if (x > 0 and input[x - 1][y] == '#') {
          dir++;
          continue;
        }
        x--;
      } else if (dir == 1) {
        if (y + 1 < n and input[x][y + 1] == '#') {
          dir++;
          continue;
        }
        y++;
      } else if (dir == 2) {
        if (x + 1 < n and input[x + 1][y] == '#') {
          dir++;
          continue;
        }
        x++;
      } else if (dir == 3) {
        if (y > 0 and input[x][y - 1] == '#') {
          dir = 0;
          continue;
        }
        y--;
      }
    }
    return !looped;
  } catch (const exception &e) {
    cerr << "Caught exception solving: " << e.what() << '\n';
    throw e;
  }
}

void solve() {
    int x = -1, y = -1, dir = -1;
    for (int i = 0; i < m and x == -1; i++) {
      for (int j = 0; j < n; j++) {
        if (input[i][j] == '^') {
          x = i, y = j;
          dir = 0;
          break;
        } else if (input[i][j] == '>') {
          x = i, y = j;
          dir = 1;
          break;
        } else if (input[i][j] == 'v') {
          x = i, y = j;
          dir = 2;
          break;
        } else if (input[i][j] == '<') {
          x = i, y = j;
          dir = 3;
          break;
        }
      }
    }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (input[i][j] == '.') {
        input[i][j] = '#';
        if (!can_escape(input, x, y, dir)) ans++;
        input[i][j] = '.';
      }
    }

  }
}

int main() {
  try {
    string path = filesystem::current_path() / "2024/inputs/6.txt";
    read_input(path);
    m = input.size();
    n = input[0].size();
    cout << "m: " << m << " n: " << n << '\n';
    solve();
    cout << "ans: " << ans << endl;
  } catch (const exception &e) {
    cerr << "Caught exception (main): " << e.what() << '\n';
    return 1;
  }
  return 0;
}
