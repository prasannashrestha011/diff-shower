#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024
#define RED "\x1b[1;31m"
#define GREEN "\x1b[1;32m"
#define RESET "\x1b[97m"

// Build LCS table for two strings
int **build_lcs_table(const char *a, const char *b) {
  int m = strlen(a), n = strlen(b);
  int **dp = malloc((m + 1) * sizeof(int *));
  for (int i = 0; i <= m; i++) {
    dp[i] = calloc(n + 1, sizeof(int));
  }

  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      dp[i][j] =
          (a[i - 1] == b[j - 1])
              ? dp[i - 1][j - 1] + 1
              : (dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);

  return dp;
}

// Print inline diff using LCS
void print_inline_diff(const char *a, const char *b) {
  int m = strlen(a), n = strlen(b);
  int **dp = build_lcs_table(a, b);

  int i = m, j = n;
  char result[MAX_LEN * 3] = ""; // Buffer for colored result

  // Reverse traversal to collect diff in correct order
  char buffer[MAX_LEN * 3] = "";
  while (i > 0 || j > 0) {
    if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
      char tmp[2] = {a[i - 1], '\0'};
      memmove(buffer + 1, buffer, strlen(buffer) + 1);
      buffer[0] = a[i - 1];
      i--;
      j--;
    } else if (j > 0 && (i == 0 || dp[i][j - 1] >= dp[i - 1][j])) {
      char tmp[32];
      sprintf(tmp, GREEN "%c" RESET, b[j - 1]);
      memmove(buffer + strlen(tmp), buffer, strlen(buffer) + 1);
      memcpy(buffer, tmp, strlen(tmp));
      j--;
    } else {
      char tmp[32];
      sprintf(tmp, RED "%c" RESET, a[i - 1]);
      memmove(buffer + strlen(tmp), buffer, strlen(buffer) + 1);
      memcpy(buffer, tmp, strlen(tmp));
      i--;
    }
  }

  printf("  %s\n", buffer);

  for (int k = 0; k <= m; k++)
    free(dp[k]);
  free(dp);
}

// Compare two files line by line
void diff_files(FILE *f1, FILE *f2) {
  char line1[MAX_LEN], line2[MAX_LEN];
  int lineno = 1;

  while (fgets(line1, MAX_LEN, f1) || fgets(line2, MAX_LEN, f2)) {
    // Remove trailing newlines
    line1[strcspn(line1, "\n")] = '\0';
    line2[strcspn(line2, "\n")] = '\0';

    if (strcmp(line1, line2) != 0) {
      printf("Line %d:\n", lineno);
      print_inline_diff(line1, line2);
    }

    lineno++;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
    return 1;
  }

  FILE *f1 = fopen(argv[1], "r");
  FILE *f2 = fopen(argv[2], "r");

  if (!f1 || !f2) {
    perror("Error opening files");
    return 1;
  }

  diff_files(f1, f2);

  fclose(f1);
  fclose(f2);
  return 0;
}
