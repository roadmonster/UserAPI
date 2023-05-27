#include "utility.h"
#include <openssl/sha.h>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.length());
    SHA256_Final(hash, &sha256);

    std::string hashedString;
    char hex[3];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hex, "%02x", hash[i]);
        hashedString += hex;
    }

    return hashedString;
}
