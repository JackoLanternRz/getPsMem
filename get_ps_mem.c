#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int parseLine(char *line){
	int i = strlen(line);
	while( *line < '0' || *line > '9' ) line++;
	line[i-3] = '\0';
	i = atoi(line);
	return i;
}

int getValue(int pid){
	char path[50];
	sprintf( path, "/proc/%d/status", pid);
	FILE *file = fopen(path, "r");
	int result = -1;
	char line[128];

	while(fgets(line, 128, file) != NULL){
		if(strncmp(line, "VmRSS:", 6) == 0){
			result = parseLine(line);
			break;
		}
	}
	fclose(file);
	return result; // Note: the value is in KB
}

int main(int argc, char *argv[]){
	int mem;
	while(1)
	{
		mem = getValue(atoi(argv[1]));
		printf("pid %s current memory usage: %d KB\n", argv[1], mem);
		sleep(1);
	}
	return 0;
}

