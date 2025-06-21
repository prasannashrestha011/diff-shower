#include <iostream>
#include <openssl/evp.h>
#include <string>
#include <vector>
using namespace std;
string create_blob(const string &content) {
  string header = "blob " + to_string(content.size()) + '\0';
  string blob = header + content;
  return blob;
}
int main() {
  string input;
  cout << "Enter a string: ";
  getline(cin, input);

  vector<unsigned char> data(input.begin(), input.end());

  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  if (!mdctx) {
    cerr << "EVP_MD_CTX_new failed\n";
    return 1;
  }

  if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
    EVP_MD_CTX_free(mdctx);
    return 1;
  }

  if (EVP_DigestUpdate(mdctx, data.data(), data.size()) != 1) {
    cerr << "DigestUpdate failed\n";
    EVP_MD_CTX_free(mdctx);
    return 1;
  }

  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int hash_len;

  if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
    cerr << "DigestFinal failed\n";
    EVP_MD_CTX_free(mdctx);
    return 1;
  }

  EVP_MD_CTX_free(mdctx);

  cout << "SHA256 hash: ";
  for (unsigned int i = 0; i < hash_len; i++)
    printf("%02x", hash[i]);
  cout << endl;
  string blob = create_blob(input);
  cout << blob << endl;
  return 0;
}
