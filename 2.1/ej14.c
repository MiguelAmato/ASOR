#include <time.h>
#include <stdio.h>

int main() {
	struct tm *t;
	time_t tim = time(0);
	t = localtime(&tim);
	printf("Año: %d\n", t->tm_year + 1900);
}