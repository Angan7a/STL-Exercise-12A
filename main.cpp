#include <iostream>     // std::cout
#include <map>          // std::map
#include <vector>       // std::vector
#include <numeric>      // std::iota
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

class CryptographicApp
{
    std::map<char, char> mapEncrypt_;
    std::map<char, char> mapDecrypt_;
    std::vector<char> alphabet_;
    std::vector<char> alphabetEncrypted_;
public:
    CryptographicApp()
    {
        alphabet_.resize(95);
        std::iota(begin(alphabet_), end(alphabet_), ' ');
        
        alphabetEncrypted_ = alphabet_;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(begin(alphabetEncrypted_), end(alphabetEncrypted_), std::default_random_engine(seed));

        std::transform(begin(alphabet_), end(alphabet_),
                       begin(alphabetEncrypted_),
                       std::inserter(mapEncrypt_, begin(mapEncrypt_)),
                       [](char letter, char encryptedLetter) {
                            return std::make_pair(letter, encryptedLetter);
                       });

        std::transform(begin(alphabetEncrypted_), end(alphabetEncrypted_),
                       begin(alphabet_),
                       std::inserter(mapDecrypt_, begin(mapDecrypt_)),
                       [](char encryptedLetter, char letter) {
                            return std::make_pair(encryptedLetter, letter);
                       });
    }

    char encrypt(char letter)
    {
        return mapEncrypt_[letter];
    }

    char decrypt(char letter)
    {
        return mapDecrypt_[letter];
    }
};

int main()
{
    CryptographicApp cryptographicApp;
    std::string message;
    std::string encryptedMessage;
    std::string decryptedMessage;

    std::cout << "Enter message to encrypted: ";
    std::getline(std::cin, message);
    std::transform(begin(message), end(message),
                   std::back_inserter(encryptedMessage),
                   [& cryptographicApp](char letter){
                        return cryptographicApp.encrypt(letter);
                   });
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;
    std::transform(begin(encryptedMessage), end(encryptedMessage),
                   std::back_inserter(decryptedMessage),
                   [& cryptographicApp](char letter){
                        return cryptographicApp.decrypt(letter);
                   });
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}
