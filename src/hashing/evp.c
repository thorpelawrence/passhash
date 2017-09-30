#include <openssl/evp.h>

int digest_message(const char *mode, const unsigned char *message, size_t message_len, unsigned char *digest) {
    OpenSSL_add_all_algorithms();
    const EVP_MD *md = EVP_get_digestbyname(mode);
    EVP_MD_CTX *mdctx;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    if ((mdctx = EVP_MD_CTX_create()) == NULL) return 1;
    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) return 1;
    if (1 != EVP_DigestUpdate(mdctx, message, message_len)) return 1;
    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) return 1;
    for (int i = 0; i < md_len; i++) {
        sprintf((char*)&digest[i*2], "%02x", md_value[i]);
    }
    EVP_MD_CTX_destroy(mdctx);
    EVP_cleanup();
    return 0;
}
