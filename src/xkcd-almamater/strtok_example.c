/* strtok example */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void methodOne(){
	char str[] = "- This, a sample string.";
	char* pch;
	printf("Splitting string \"%s\" into tokens:\n", str);
	pch = strtok(str, " ,.-");
	while (pch != NULL) {
		printf("%s\n", pch);
		pch = strtok(NULL, " ,.-");
	}
}

void methodTwo(){
	/* doesn't work yet */
	const char* foundThings[30];
	char inputString[] = "- This, a: sample: string.";
	bool going = true;
	int n = 0;
	while (going) {
		foundThings[n] = strtok(inputString, ":");
		if (foundThings[n] == NULL)
			going = false;
		else
			n++;
	}
}

int main(){
	methodOne();
	return 0;
}