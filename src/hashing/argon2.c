#include <sodium.h>
#include <string.h>

int hash_password_argon2(char *password, char *hash) {
    char hashed_password[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(hashed_password, password, strlen(password),
        crypto_pwhash_OPSLIMIT_MIN, crypto_pwhash_MEMLIMIT_MIN) != 0) {
        /* out of memory */
        return 1;
    }

    strcpy(hash, hashed_password);
    return 0;
}

int verify_hashed_password_argon2(char *hash, char *password) {
    if (crypto_pwhash_str_verify
        (hash, password, strlen(password)) != 0) {
        /* wrong password */
        return 1;
    }
    return 0;
}
