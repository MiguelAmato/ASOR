#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main () {
	uid_t uid =  getuid();
	uid_t euid = geteuid();

	printf("uid: %u\n", getuid());
	printf("euid: %u\n", geteuid());

	struct passwd *psw = getpwuid(uid);
	printf("name: %s\n", psw->pw_name);
	printf("descr: %s\n", psw->pw_gecos);
	printf("home: %s\n", psw->pw_dir);
}