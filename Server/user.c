#define TB_USERS "users.db"

struct User *lastUser;
struct User *firstUser;


struct User{
	int id;
	char *username;
	char *password;
	int socket;
	char **channels;
	struct User *next;
};

void appendUser(struct User *object){
	if (lastUser == NULL){
		lastUser = object;
		firstUser = object;
		return;
	}

	lastUser->next = object;
	lastUser = object;

	return;
}

struct User* createUser(char *username,char *password,int socket, char **channels){
	struct User *user = malloc(sizeof(struct User));
	user->username = username;
	user->password = password;
	user->socket = socket;
	user->channels = channels;
	
	FILE *f;

	f = fopen(TB_USERS,"a");


	appendUser(user);
	/*Guardar en archivo user*/
	return NULL;

}

/*CRUD & Data Base Methods*/

int inserUserQuery(char *query){
	return 0;
}

struct User* selectUserQuery(char *username){
	/*Consultar en archivo users*/
	
	json_t *data = getAllDB();
	char *aux;

	for (int i = 0; i < json_array_size(data); i++){
		aux = json_string_value(json_array_get(data, i));
		if (strcmp(aux,username)){
			/*Aqui esta el usuario elegido retornarlo*/
		}
	}
	
	return NULL;
}


int updateUserQuery(char *username){
	return 0;
}

int getLastUserIdQuery(){
	
	json_t *data;
	json_t *last;
	int id;

	data = getAllDB();

	if (!data){
		fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
		fclose(f);
		return -1;
	}

	last = json_array_get(data, json_array_size(data)-1);
	id = json_integer_value(json_object_get(last,"id"));

	fclose(f);

	return id;
}


json_t* getAllDB(){
	FILE *f;
	char c;
	char buffer[2048];
	int i=0;
	json_t *data;
	json_error_t error;

	f = fopen(TB_USERS,"r");

	if (f == NULL){
		fclose(f);
		return NULL;
	}

	c = fgetc(f);
	while( c != EOF ){
		*(buffer+i) = c;
		c = fgetc(f);
		i++;
	}

	data = json_loads(buffer,0,&error);

	if (!data){
		fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
		fclose(f);
		return NULL;
	}

	fclose(f);

	return data;
}




