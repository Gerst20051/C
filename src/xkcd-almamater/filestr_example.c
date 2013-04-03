/* filestr example */
#include <stdio.h>

void methodOne(){
	const char filename[] = "allpasswords.txt";
	FILE *file = fopen(filename, "r");
	if (file) {
		char line[BUFSIZ];
		while (fgets(line, sizeof line, file)) {
			fputs(line, stdout);
		}
	} else {
		perror(filename);
	}
}

void methodTwo(){
	const char filename[] = "allpasswords.txt";
	FILE *file = fopen(filename, "r");
	if (file) {
		char line[BUFSIZ];
		while (fgets(line, sizeof line, file)) {
			char substr[32], *ptr = line;
			int n;
			fputs(line, stdout);
			while (*ptr) {
				if (sscanf(ptr, "%31[^:]%n", substr, &n) == 1) {
					ptr += n;
					puts(substr);
				} else {
					puts("---empty field---");
				}
				++ptr;
			}
		}
	} else {
		perror(filename);
	}
}

int main(void){
	methodOne();
	return 0;
}