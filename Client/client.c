#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h> 
#include <pthread.h>

#include <jansson.h>


void* prueba(void *arg) { 
	int i;
	FILE *f;
	f = fopen("prueba.txt","a");
	if (f ==NULL){
		printf("Error abriendo\n");
		return NULL;
	}
	char *msg = (char *)arg;

	for ( i = 0 ; i < 1000 ; i++ ){ 
		fprintf(f,"%s\n", msg);
	}

	fclose(f);
	return NULL;
}

void* otraCosa(void *arg){
	printf("OTra cosas\n");
	return NULL;
}


int main(int argc, char *argv[]) { 
	pthread_t h1;
	pthread_t h2;

	char mensaje1[] = "Mensaje de hilo 1\n";
	char mensaje2[] = "Mensaje de hilo 2\n";


	pthread_create(&h1, NULL, prueba,(void *)mensaje1); 
	pthread_create(&h2, NULL, prueba, (void *)mensaje2);
	pthread_create(&h1, NULL, otraCosa,NULL);
	pthread_join(h1, NULL); 
    pthread_join(h2, NULL);
	printf("Fin\n");
	return 0;
}





