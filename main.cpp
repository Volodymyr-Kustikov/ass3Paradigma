#include <iostream>
#include <string>
#include <dlfcn.h>
#include <limits>

typedef char* (*encrypt_ptr_t)(char*);
typedef char* (*decrypt_ptr_t)(char*);

class CaesarCipherTester {
private:
    void* libraryHandle;
    encrypt_ptr_t encryptFunction;
    decrypt_ptr_t decryptFunction;

public:
    CaesarCipherTester() : libraryHandle(nullptr), encryptFunction(nullptr), decryptFunction(nullptr) {}

    ~CaesarCipherTester() {
        if (libraryHandle) {
            dlclose(libraryHandle);
        }
    }

    bool loadLibrary(const std::string& libraryPath) {
        libraryHandle = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (!libraryHandle) {
            std::cerr << "Error loading library: " << dlerror() << std::endl;
            return false;
        }

        encryptFunction = reinterpret_cast<encrypt_ptr_t>(dlsym(libraryHandle, "encrypt"));
        if (!encryptFunction) {
            std::cerr << "Error loading encrypt function: " << dlerror() << std::endl;
            return false;
        }

        decryptFunction = reinterpret_cast<decrypt_ptr_t>(dlsym(libraryHandle, "decrypt"));
        if (!decryptFunction) {
            std::cerr << "Error loading decrypt function: " << dlerror() << std::endl;
            return false;
        }

        return true;
    }

    void printUsage() const {
        std::cout << "Caesar Cipher Tool" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "  1 - Encrypt text" << std::endl;
        std::cout << "  2 - Decrypt text" << std::endl;
        std::cout << "Choose an option: ";
    }

    void handleEncryption() {
        std::string inputText;

        std::cin.ignore();
        std::cout << "Enter text to encrypt: ";
        std::getline(std::cin, inputText);

        char* result = encryptFunction(const_cast<char*>(inputText.c_str()));

        if (result) {
            std::cout << "Original text:  " << inputText << std::endl;
            std::cout << "Encrypted text: " << result << std::endl;
            delete[] result;
        } else {
            std::cout << "Encryption failed." << std::endl;
        }
    }

    void handleDecryption() {
        std::string inputText;

        std::cin.ignore();
        std::cout << "Enter text to decrypt: ";
        std::getline(std::cin, inputText);

        std::cout << "Enter decryption key (integer): ";
//        while (!(std::cin >> key)) {
//            std::cout << "Invalid key. Please enter an integer: ";
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        }

        char* result = decryptFunction(const_cast<char*>(inputText.c_str()));

        if (result) {
            std::cout << "Encrypted text: " << inputText << std::endl;
            std::cout << "Decrypted text: " << result << std::endl;
            delete[] result; // Free memory allocated by the library!!
        } else {
            std::cout << "Decryption failed." << std::endl;
        }
    }

    void runDemo() {
        std::cout << "\n=== Demo: Caesar Cipher Example ===" << std::endl;

        std::string demoText = "Roses are red, violets are blue";
        int demoKey = 1;

        std::cout << "Demo text: \"" << demoText << "\"" << std::endl;
        std::cout << "Demo key: " << demoKey << std::endl;

        char* encrypted = encryptFunction(const_cast<char*>(demoText.c_str()));
        if (encrypted) {
            std::cout << "Encrypted: \"" << encrypted << "\"" << std::endl;

            char* decrypted = decryptFunction(encrypted);
            if (decrypted) {
                std::cout << "Decrypted: \"" << decrypted << "\"" << std::endl;
                delete[] decrypted;
            }
            delete[] encrypted;
        }


    }

    void run() {
        std::cout << "Caesar Cipher Dynamic Library Test (C++)" << std::endl;
        std::cout << "=========================================" << std::endl << std::endl;

        int choice;

        while (true) {
            printUsage();

            if (!(std::cin >> choice)) {
                std::cout << "Invalid input. Please enter a number." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            switch (choice) {
                case 1:
                    handleEncryption();
                    break;

                case 2:
                    handleDecryption();
                    break;


                default:
                    std::cout << "Invalid choice. Please select 1, 2, 3, or 4." << std::endl;
                    break;
            }

            std::cout << std::endl;
        }
    }
};

int main() {
    CaesarCipherTester tester;

    if (!tester.loadLibrary("./libcaesar.so")) {
        std::cerr << "Failed to load Caesar cipher library." << std::endl;
        return 1;
    }

    tester.run();

    return 0;
}