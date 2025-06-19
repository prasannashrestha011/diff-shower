#include <stdio.h>
#include <string.h>
void lcs(char *X, char *Y) {
  int m = strlen(X);
  int n = strlen(Y);
  int dp[m + 1][n + 1];
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      } else if (X[i - 1] == Y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
      }
    }
  }
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      printf("%d ", dp[i][j]);
    }
    printf("\n");
  }
  printf("\n%d\n", dp[m][n]);
}
int main() {
  char X[] = "ABC";
  char Y[] = "AC";
  lcs(X, Y);
  return 0;
}
