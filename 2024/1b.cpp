#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
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
  unordered_map<int,int> b_mp;
  cout << 'a'<<'\n';
  while (getline(input, line)) {
    istringstream iss(line);
    if (iss >> n1 >> n2) {
      a.push_back(n1);
      b.push_back(n2);
      b_mp[n2]++;
    }
  }
  input.close();
  int n = a.size();
  for (int i = 0; i < n; i++) {
    ans += a[i] * b_mp[a[i]];
  }
  cout << ans << '\n';
  return 0;
}
