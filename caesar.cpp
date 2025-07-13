#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib>
static int staticKey = 13;

extern "C" {
    char* encrypt(char* rawText) {
                    if (rawText == nullptr) {
            return nullptr;
        }

        int length = std::strlen(rawText);
        char* encryptedText = new(std::nothrow) char[length + 1];

        if (encryptedText == nullptr) {
            return nullptr;
        }
        int key;
        key = staticKey % 26;
        if (key < 0) {
            key += 26;
        }

        for (int i = 0; i < length; i++) {
            char c = rawText[i];

            if (std::isalpha(c)) {
                char base = std::isupper(c) ? 'A' : 'a';
                encryptedText[i] = ((c - base + key) % 26) + base;
            } else {
                encryptedText[i] = c;
            }
        }

        encryptedText[length] = '\0';
        return encryptedText;
    }

    char* decrypt(char* encryptedText, int staticKey) {
        if (encryptedText == nullptr) {
            return nullptr;
        }

        int length = std::strlen(encryptedText);
        char* decryptedText = new(std::nothrow) char[length + 1];

        if (decryptedText == nullptr) {
            return nullptr;
        }
        int key;
        key = staticKey % 26;
        if (key < 0) {
            key += 26;
        }

        for (int i = 0; i < length; i++) {
            char c = encryptedText[i];

            if (std::isalpha(c)) {
                char base = std::isupper(c) ? 'A' : 'a';
                decryptedText[i] = ((c - base - key + 26) % 26) + base;
            } else {
                decryptedText[i] = c;
            }
        }

        decryptedText[length] = '\0';
        return decryptedText;
    }

}