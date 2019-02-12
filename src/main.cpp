// standard libs
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// OS-level libs (Linux only, for now)
#include <termios.h>
#include <unistd.h>

// 3rd party libs
#include "../lib/fastpbkdf2/fastpbkdf2.h"
#include "../lib/cpp-base64/base64.h"

using namespace std;

void HideStdinKeystrokes() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;	/* we want to disable echo */
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void ShowStdinKeystrokes() {
	termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	tty.c_lflag |= ECHO; /* we want to reenable echo */
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

#define HASH_LIMIT 24 // basically KEY_LIMIT*6/8
#define KEY_LIMIT 32
#define DEFAULT_KEY_SIZE 25

int main(int argc, char *argv[]) {
	string username, site, password, salt, length;
	char *out[HASH_LIMIT];
	int outLength = DEFAULT_KEY_SIZE, tmp=0;

	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your site: ";
	cin >> site;

	cout << "Enter key size (defaults to " << outLength << "): ";
	// C makes optional inputs easier
	cin.ignore();
	getline(cin, length);
	sscanf(length.c_str(), "%d", &tmp);
	if(outLength>KEY_LIMIT) {
		cout << "Error: Passwords over "<<KEY_LIMIT<<" characters are not supported!" << endl;
	} else if(outLength<1) {
		cout << "u wot m8" << endl;
	}
 	outLength = tmp ? tmp : outLength;
	length.clear();

	HideStdinKeystrokes();
	cout << "Enter your password: ";
	cin >> password;
	ShowStdinKeystrokes();

	salt = username + '@' + site;
	
	// clear as soon as possible because potential security threats
	username.clear();
	site.clear();

	fastpbkdf2_hmac_sha256((uint8_t*)password.c_str(), password.length(), (uint8_t*)salt.c_str(), salt.length(), 5000, (uint8_t*)out, HASH_LIMIT);

	// same goes here
	salt.clear();

	password = base64_encode((unsigned char*)out, outLength);
	password = password.substr(0, outLength);

	cout << password << endl;
	
	// make sure it's not going to be recovered
	password.clear();
	memset(out, 0x00, HASH_LIMIT);

	return 0;
}

