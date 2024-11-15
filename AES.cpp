#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>
#include <string>


void mod1(const std::string plain) {
    using namespace CryptoPP;
    HexEncoder encoder(new FileSink(std::cout));

    std::string cipher, recovered;
    byte key[] = "2357111317192329";
    byte IV1[] = "1234567812345678";
    byte IV2[] = "9999999999999999";

    ECB_Mode<AES>::Encryption ecb(key, 16);
    StringSource ECB(plain, true,
        new StreamTransformationFilter(ecb,
            new StringSink(cipher),
            StreamTransformationFilter::PKCS_PADDING
        )
    );
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    //std::cout << cipher;
    std::cout << std::endl;

    cipher.clear();

    CBC_Mode<AES>::Encryption cbc(key, 16, IV1);
    StringSource CBC(plain, true,
        new StreamTransformationFilter(cbc, 
            new StringSink(cipher),
            StreamTransformationFilter::ONE_AND_ZEROS_PADDING
        )
    );
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    //std::cout << cipher;
    std::cout << std::endl;

    cipher.clear();

    //AESEncryption new_key(key, 16);
    //CFB_Mode_ExternalCipher::Encryption cfb(new_key, IV2, 2);
    CFB_Mode<AES>::Encryption cfb(key, 16, IV2, 2);
    StringSource CFB(plain, true,
        new StreamTransformationFilter(cfb, 
            
            new StringSink(cipher)
        )
    );
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    //std::cout << cipher;
    std::cout << std::endl;
}

bool judge(int k ) {
   
    if (k == 32 || (48 <= k && k <= 57) || (65 <= k && k <= 90) || (97 <= k && k <= 122))
        return true;
    return false;
}

void mod2(std::string cipher) {
    
    using namespace CryptoPP;

    std::string plain;
    
    
    for (int i = 0; i < 1e5; i++) {
        
        std::string tmp_int = std::to_string(i), tmp_0(5 - tmp_int.size(), '0');
        std::string key = "00000000000" + tmp_0 + tmp_int;
        
        plain.clear();
        try {
            ECB_Mode<AES>::Decryption ecb((byte*)key.c_str(), 16);
            StringSource s(cipher, true,
                new HexDecoder{
                    new StreamTransformationFilter(ecb,
                        new StringSink(plain),
                        StreamTransformationFilter::PKCS_PADDING
                    )
                }
            ); 
            bool isLan = true;
            for (char i : plain) {
                int k = (int)i;
                if (!judge(k)) {
                    isLan = false;
                    break;
                }   
            }
            if (isLan) {
                std::cout << key << std::endl << plain << std::endl;
                return;
            }
        }
        catch (const Exception& e) {}
    }
    
}

int main(int argc, char* argv[])
{
    using namespace CryptoPP;
    std::string plain, cipher;
    std::getline(std::cin, plain);
    std::cin >> cipher;
    mod1("AES is the US block cipher standard.");
    mod2("104839DE2B34D9BA96F6E054F79F865890B827381D22FC3388690794F0D08EB3");
    mod1(plain);
    mod2(cipher);
}
