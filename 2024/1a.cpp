#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int n = 0;
int ans = 0;
vector<int> a;
vector<int> b;
int main() {
  int n1, n2;
  ifstream input("inputs/1.txt");
  string line;
  while (getline(input, line)) {
    istringstream iss(line);
    if (iss >> n1 >> n2) {
      a.push_back(n1);
      b.push_back(n2);
    }
  }
  input.close();
  int n = a.size();
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  for (int i = 0; i < n; i++) {
    int diff = abs(a[i] - b[i]);
    ans += diff;
  }
  cout << ans << '\n';
  return 0;
}
