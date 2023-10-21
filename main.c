#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include "pushkin.h"
#include <dirent.h>
#include <sys/stat.h>


	void* handle;
	char* (*pushkin)(char*);
	char* (*pushkin_tmp)(char*);

int CheckDir(char* path){
	DIR* dp = opendir(path);
	if(!dp){
		//printf("Can't open current directory\n");
		return -1;
	}

	struct dirent* de;
	struct stat statbuf;

	while(de = readdir(dp)){
		int nlen = strlen(de->d_name);
		//printf("%s\n", de->d_name);
		lstat(de->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(".", de->d_name) == 0 || strcmp("..", de->d_name) == 0){continue;}
			char newPath[100];
			strcpy(newPath, path);
			strcat(newPath, "/");
			strcat(newPath, de->d_name);
			CheckDir(newPath);
			continue;
		};

		if(nlen > 3 && strcmp((de->d_name) + nlen - 3, ".so") == 0){
			char libname[100];
			strcpy(libname, path);
			strcat(libname, "/");
			strcat(libname, de->d_name);
			handle = dlopen(libname, RTLD_LAZY);
			if(handle == NULL){printf("error with opening the lib\n"); continue;}
			pushkin_tmp = dlsym(handle, "pushkin");
			if(pushkin_tmp != NULL){
				//printf("func has found\n");
				pushkin = pushkin_tmp;
			}
		}

	}
}



int main(int argc, char* argv[]){

	char* result;
	char* source = NULL;
	int source_size = 0;
	int lines;

	CheckDir(".");

	//заполняем исходные строки поэмы
	printf("Enter count of lines: ");
	scanf("%d", &lines);
	if(lines <= 0 || lines >= 154){
		source = NULL;
	}
	else{
		int counter = 0;
		source = (char*)malloc(sizeof(char) * 1);
		for(int i = 0; i < strlen(poem); i++){
			source[source_size] = poem[i];
			source_size++;
			source = realloc(source, sizeof(char) * (source_size+1));
			if(poem[i] == '\n'){
				counter++;
			}
			if(counter == lines){
				source[source_size] = '\0';
				break;
			}
		}
	}
	
	
	result = pushkin(source);
	
	
	if(source){
		printf("%s\n", source);
	}
	printf("%s\n", result);

	dlclose(handle);
	return 0;
}
