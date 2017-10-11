#include <stdio.h>

#ifdef GTK3_FOUND
#include "ui/gtk/window.h"

int main(int argc, char **argv) {
    return create_window();
}

#else
#include "hashing/argon2.h"
#include "ui/getpass.h"

int main(int argc, char **argv) {
    char password[64];
    get_password(password, 64);
    char hash[128];
    hash_password_argon2(password, hash);
    printf("%s\n", hash);
    return 0;
}
#endif
