#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "integer.h"
#include "rsa.h"
#include "hex.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

void encry(int len, std::string nn, std::string ee, std::string message) {
    using namespace CryptoPP;
    RSA::PublicKey pubkey;
    

    Integer n(static_cast<Integer>(nn.c_str())), e(static_cast<Integer>(ee.c_str()));
    pubkey.Initialize(n, e);
    Integer m = Integer((const byte*)message.data(), message.size());
    if (m > pubkey.MaxImage()) return;

    Integer c = pubkey.ApplyFunction(m);
    
    std::stringstream ss;
    ss << std::uppercase << std::hex << c;
    std::string out;
    ss >> out;
    std::cout  << std::setw(std::ceil(len / 4)) << std::setfill('0') << out.substr(0, out.length()-1) << std::endl;
}

void decry(int len, std::string nn, std::string ee, std::string cipher) {
    using namespace CryptoPP;
    AutoSeededRandomPool prng;
    RSA::PrivateKey prikey;

    Integer n(static_cast<Integer>(nn.c_str())), e("0x10001"), d(static_cast<Integer>(ee.c_str())), c(static_cast<Integer>(cipher.c_str()));
    prikey.Initialize(n, e, d);
    Integer r = prikey.CalculateInverse(prng, c);
    if (r > prikey.MaxImage()) return;

    std::string plaintext;
    size_t p = r.MinEncodedSize();
    plaintext.resize(p);
    r.Encode((byte*)plaintext.data(), plaintext.size());

    std::cout << plaintext << std::endl;
    
}
 

int main(int argc, char* argv[])
{
    using namespace CryptoPP;
    std::string cmd, n, e, message;
    int len;
    while (std::cin >> cmd)
    {
        std::cin >> len >> n >> e;
        std::getline(std::cin, message);
       
        if (cmd == "enc") {
            message.erase(0, 1);
            encry(len, "0x" + n, "0x" + e, message);
        }
        else {
            decry(len, "0x" + n, "0x" + e, "0x" + message);
        }
    }     
}
