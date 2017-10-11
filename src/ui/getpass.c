#include <stdio.h>

#ifdef _WIN32
#include <conio.h>

void get_password(char *password, int length) {
	printf("Password: ");
	int i = 0;
	while (i < length) {
        if ((password[i++] = _getch()) == 13) break;
        else printf("*");
    }
    password[i - 1] = 0;
	printf("\n");
}
#endif

#ifdef linux
#include <termios.h>
#include <stdlib.h>
#include <string.h>

void get_password(char *password, int length) {
    struct termios oflags, nflags;
    
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
    }
    
    printf("Password: ");
    fgets(password, length, stdin);
    password[strcspn(password, "\n")] = 0;
    
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
    }
}
#endif
