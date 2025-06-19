
#include <stdio.h>
#include <string.h>

// Function to find LCS length
int lcs(char *X, char *Y) {
  int m = strlen(X);
  int n = strlen(Y);

  // Create a 2D table to store lengths
  int dp[m + 1][n + 1];

  // Build the table in bottom-up manner
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (X[i - 1] == Y[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
    }
  }

  // The bottom-right cell has the length of LCS
  return dp[m][n];
}

int main() {
  char X[] = "ABCBDAB";
  char Y[] = "BDCAB";

  int length = lcs(X, Y);
  printf("Length of LCS is %d\n", length);

  return 0;
}
