#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() 
{
	char *Label = NULL;
	const char *str = "Vertice A";
	size_t Len = strlen(str);

	Label = (char *)malloc(Len + 1);
	if( Label == NULL )
	{
		fprintf(stderr, "Error in malloc\n");
		exit(EXIT_FAILURE);
	}
	strncpy(Label, str, Len);
	Label[Len] = '\0';

    /* Assertions */
	assert( strcmp(Label, str) == 0 );
	assert( Label[Len] == 0 );
	assert( Label[Len-1] == 'A' );
	printf("The string was copied smoothly!\n");
	printf("Label: %s\n", Label);
	printf("Str: %s\n", str);
	printf("Label[8]: %4x\n", Label[8]);
	printf("Label[9]: %4x\n", Label[9]);
	return 0;
}
