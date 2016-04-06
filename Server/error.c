char ERROR_UNAUTHORIZED[] = "{\"error\":{\"message\":\"Unauthorized\",\"code\":401}}";
char ERROR_BAD_REQUEST[] = "{\"error\":{\"message\":\"Bad Request\",\"code\":400}}";
char ERROR_UNKNOW[] = "{\"error\":{\"message\":\"Unknow\",\"code\":-1}}";
char ERROR_FAILED_LOGIN[] = "{\"error\":{\"message\":\"Username or Password incorrect\",\"code\":201}}";
char ERROR_USERNAME_TAKEN[] = "{\"error\":{\"message\":\"Username taken\",\"code\":202}}";
char ERROR_INVALID_TOKEN[] = "{\"error\":{\"message\":\"Invalid Session Token\",\"code\":209}}";

void sessionError(int sock, int error){
	switch(error){
		case -1:	//Error desconocido
			write(sock, ERROR_UNKNOW, sizeof(ERROR_UNKNOW));
		break;
		case 201:	//Usuario o contraseña invalida 201
			write(sock, ERROR_FAILED_LOGIN, sizeof(ERROR_FAILED_LOGIN));
		break;
		case 202:	//Ya existe el Usuario 202
			write(sock, ERROR_USERNAME_TAKEN, sizeof(ERROR_USERNAME_TAKEN));
		break;
		case 209:	//Token invalido 209
			write(sock, ERROR_INVALID_TOKEN, sizeof(ERROR_INVALID_TOKEN));
		break;
		case 400:	//Error de peticion 400
			write(sock,ERROR_BAD_REQUEST,sizeof(ERROR_BAD_REQUEST));
		break;
		default:
			write(sock, ERROR_UNKNOW, sizeof(ERROR_UNKNOW));
		break;
	}
}