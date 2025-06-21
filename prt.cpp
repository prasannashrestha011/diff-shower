#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
string create_sha_identifier(const std::string &content) {
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  vector<unsigned char> data(content.begin(), content.end());
  if (!mdctx) {
    EVP_MD_CTX_free(mdctx);
    return "";
  }
  if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
    EVP_MD_CTX_free(mdctx);
    return "";
  }
  if (EVP_DigestUpdate(mdctx, data.data(), data.size()) != 1) {
    EVP_MD_CTX_free(mdctx);
    return "";
  }
  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int hash_len;
  if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
    EVP_MD_CTX_free(mdctx);
    return "";
  }
  ostringstream oss;
  for (unsigned int i = 0; i < hash_len; i++) {
    oss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return oss.str();
}
int main(int argc, char *argv[]) {
  string input, shaIdentifier;
  cout << "Enter your string ";
  getline(cin, input);
  shaIdentifier = create_sha_identifier(input);
  cout << "SHA key >>" << shaIdentifier << endl;
  return 0;
}
