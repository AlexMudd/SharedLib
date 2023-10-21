#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pushkin.h"



char* pushkin(char* text){

	if(text == NULL){
		return "U lukomor'ya dub zelenyj,\n";
	}

	int counter_text = 0;
	int counter_poem = 0;

	char* result = (char*)malloc(1 * sizeof(char));
	int result_size = 0;
	
	int size = strlen(text);
	int poem_size = strlen(poem);

	for (int i = 0; i < size; i++) {
		if (poem[i] == '\n') {
			counter_text++;
		} 
	}

	if(counter_text >= 154){
		return NULL;
	}
	
	for (int i = 0; i < poem_size; i++) {
		if (poem[i] == '\n') {
			counter_poem++;
			continue;
		} 
		if (counter_poem == counter_text) {
				result[result_size] = poem[i];
				result_size++;
				result = realloc(result, sizeof(char) * (result_size+1));
		}
		if(counter_poem > counter_text) {
			result[result_size] = '\0';
			break;
		}
	}

	return result;
}