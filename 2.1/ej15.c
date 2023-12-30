#include <time.h>
#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "");
	struct tm *t;
	time_t tim = time(0);
	t = localtime(&tim);
	char s[100];
	strftime(s, 100, "%a %b %d %I:%M:%S %Z %Y", t);

	printf("%s\n", s);
}