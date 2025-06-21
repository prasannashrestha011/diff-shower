#include <algorithm>
#include <complex>
#include <cstdio>
#include <fstream>
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

  while (i > 0 || j > 0) {
    if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
      output.push_back({a[i - 1], BLUE}); // Unchanged
      i--;
      j--;
    } else if (j > 0 && (i == 0 || dp[i][j - 1] >= dp[i - 1][j])) {
      output.push_back({b[j - 1], GREEN}); // Added in b
      j--;
    } else if (i > 0) {
      output.push_back({a[i - 1], RED}); // Removed from a
      i--;
    }
  }
  cout << "Previous buffer " << a << endl;
  cout << "Current buffer " << b << endl;
  cout << "Diff ";
  string added_char, removed_char, unchanged_char;
  for (auto it = output.rbegin(); it != output.rend(); ++it) {
    char ch = it->first;              // The actual character
    const string &color = it->second; // The color code

    if (color == GREEN) {
      added_char += ch;
    } else if (color == RED) {
      removed_char += ch;
    } else {
      unchanged_char += ch;
    }
  }
  cout << endl;
  cout << GREEN << "added characters(+) " << added_char << RESET << endl;
  cout << RED << "removed characters(-) " << removed_char << RESET << endl;
  cout << "unchanged characters(#) " << unchanged_char << endl;
  cout << GREEN << "total(+) " << added_char.size() << endl;
  cout << RED << "total(-) " << removed_char.size() << RESET << endl;
  cout << "total(#) " << unchanged_char.size() << endl;
  cout << endl;
}

int main(int argc, char *argv[]) {
  string a, b; // strings
  string abc, dbc;
  if (argc < 3) {
    cerr << "Usage : " << argv[0] << "<file> <file>" << endl;
    return 1;
  }
  ifstream file1(argv[1]), file2(argv[2]);
  if (!file1.is_open() || !file2.is_open()) {
    cerr << "Corruped file" << endl;
    return 1;
  }
  string line1, line2;
  int line_no = 1;
  while (getline(file1, line1) && getline(file2, line2)) {
    cout << "Line no: " << line_no << endl;
    print_line_dff(line1, line2);
    getchar();
    line_no++;
  }
  getline(cin, b);
  print_line_dff(a, b);
  return 0;
}
