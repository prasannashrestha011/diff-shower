#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define GREEN "\x1b[1;32m" // additions
#define RED "\x1b[1;31m"   // removals (changed from yellow to red)
#define BLUE "\x1b[1;34m"  // unchanged text
#define RESET "\x1b[0m"
vector<vector<int>> build_lcs_table(const string &a, const string &b) {
  int m = a.size(), n = b.size();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1
                                      : (max(dp[i - 1][j], dp[i][j - 1]));
    }
  }
  return dp;
}
void print_line_dff(const string &a, const string &b) {
  vector<vector<int>> dp = build_lcs_table(a, b);
  int i = a.size(), j = b.size();
  vector<pair<char, string>> output;
  while (i > 0 && j > 0) {
    if (j > 0 && (i == 0 || a[i - 1] == b[j - 1])) {
      output.push_back({a[i - 1], BLUE});
      i--;
      j--;
    } else if (j > 0 && dp[i - 1][j] >= dp[i][j - 1]) {
      output.push_back({b[j - 1], GREEN});
      j--;
    } else if (i > 0) {
      output.push_back({a[i - 1], RED});
      i--;
    }
  }
  for (auto it = output.rbegin(); it != output.rend(); ++it) {
    cout << it->second << it->first << RESET;
  }

  cout << endl;
}
int main(int argc, char *argv[]) {
  string a = "bat";
  string b = "cat";
  print_line_dff(a, b);
  return 0;
}
