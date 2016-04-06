#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h> 
#include <pthread.h>

#include <jansson.h>

#include "error.c"
#include "message.c"
#include "user.c"

#define PORT 5012
int serverSockfd;



void closeServer();
void* clientHandler(void *socket);
int login(json_t *user,struct User *u);
int signup(json_t *user,struct User *u);
int sessionState(char *data,struct User *u);

int main(int argc, char const *argv[]){

	int clientSockfd, clilen;
	struct sockaddr_in serv_addr, cli_addr;
	pthread_t clientThread;
	
	serverSockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSockfd < 0){
		perror("ERROR opening socket");
      	exit(1);
	}


	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
   	serv_addr.sin_addr.s_addr = INADDR_ANY;
   	serv_addr.sin_port = htons(PORT);

   	if (bind(serverSockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("Error binding");
      exit(1);
   }

   listen(serverSockfd,5);
   clilen = sizeof(cli_addr);


   while(1){
   		clientSockfd = accept(serverSockfd,(struct sockaddr *) &cli_addr,(socklen_t *) &clilen);

   		if (clientSockfd < 0){
   			perror("Error aceptando");
   			exit(1);
   		}

   		pthread_create(&clientThread, NULL, clientHandler,(void *)&clientSockfd); 
   	}

   	close(serverSockfd);
	return 0;
}

void closeServer(){
	printf("Se cerro el servidor\n");
	close(serverSockfd);
}

void* clientHandler(void* socket){
	int n, sock = (int)*((int *)socket);
	char buffer[256];
	struct User *user;
	json_t *data;
	json_error_t error;


	while(1){
		bzero(buffer,256);
		n = read(sock, buffer, 255);

		if (!user){
			sessionState(buffer,user);

			if (!user){
				sessionError(sock,activeSession);
			}else{
					
			}
		}else{
			data = json_loads((const char *)data,0,&error);
			if (!data){
				write(sock,ERROR_BAD_REQUEST,sizeof(ERROR_BAD_REQUEST));
			}else{

			}
			exit(1);
		}	
	}
}


void sessionState(char *data,struct User *u){

	json_t *user;
	json_error_t error;
	json_int_t instruction;
	
	//printf("%s\n",data );
	user = json_loads(data,0,&error);

	if(!user){
	    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
	    return 400;
	}

	if(!json_is_object(user)){
    	fprintf(stderr, "error: root is not an object\n");
    	json_decref(user);
    	return 400;
	}

	instruction = json_integer_value(json_object_get(user, "instruction"));

	switch(instruction){
		case 0:	/*Login*/
			u = login(user);
		break;
		case 1:	/*SignUp*/
			u = signup(user);
		break;
		default:
			return;
		break;
	}
	return;
}

struct User* login(json_t *user,struct User *u){
	const char *username;
	const char *password;

	username = json_string_value(json_object_get(user,"username"));
	password = json_string_value(json_object_get(user,"password"));

	
}
int signup(json_t *user,struct User *u){
	return 0;
}






