#include <iostream>
#include <string>
#include <iomanip>
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"

using namespace std;

int main(int argc, char *argv[])
{

    // Key and IV setup
    // AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-
    // bit). This key is secretly exchanged between two parties before communication
    // begins. DEFAULT_KEYLENGTH= 16 bytes
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

    //
    // String and Sink setup
    //
    std::cout << "Enter the PlainText \n";
    std::string plaintext;
    std::getline(std::cin, plaintext);
    std::string ciphertext;
    std::string decryptedtext;
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

        CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
        stfEncryptor.Put(reinterpret_cast<const unsigned char *>(plaintext.c_str()), plaintext.length());
        stfEncryptor.MessageEnd();
    int c=1;
    while(c){
        std::cout << "Enter \n1.Encryption\n2.Cipher Text\n3.Decryption\n";
    int i;
    cin >> i;
    
    switch (i)
    {
        case 1:
        //
        // Dump Plain Text
        //
        std::cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
        std::cout << plaintext;
        std::cout << std::endl<< std::endl;

        //
        // Create Cipher Text
        //
        
        break;
        case 2:
        //
        // Dump Cipher Text
        //
        std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;

        for (int i = 0; i < ciphertext.size(); i++)
        {

            std::cout << "0x" << std::hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
        }

        std::cout << std::endl
                  << std::endl;
        break;
        case 3:
        //
        // Decrypt
        //
        CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
        stfDecryptor.Put(reinterpret_cast<const unsigned char *>(ciphertext.c_str()), ciphertext.size());
        stfDecryptor.MessageEnd();

        //
        // Dump Decrypted Text
        //
        std::cout << "Decrypted Text: " << std::endl;
        std::cout << decryptedtext;
        std::cout << std::endl<< std::endl;
        break;
    }
    cout<<"Enter 1 for continue 0 to exit\n";
    cin>>c;
    }
    return 0;
}

// g++ -g3 -ggdb -O0 -Wall -Wextra -Wno-unused -o Aes aes.cpp -lcryptopp