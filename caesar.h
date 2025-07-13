#ifndef CAESAR_H
#define CAESAR_H

#ifdef __cplusplus
extern "C" {
#endif

char* encrypt(char* rawText, int key);
char* decrypt(char* encryptedText, int key);

#ifdef __cplusplus
}
#endif

#endif