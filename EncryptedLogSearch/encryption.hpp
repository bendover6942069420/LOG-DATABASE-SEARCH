#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <string>
#include <vector>

class Encryption {
  public:
    static std::string xorEncryptDecrypt(const std::string& input, const std::string& key);
    static std::string generateKey(size_t length);

  private:
    static std::vector<unsigned char> expandKey(const std::string& key, size_t length);
};

#endif