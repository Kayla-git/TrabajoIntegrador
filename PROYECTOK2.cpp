#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
void crear_usuario();
void ingresar();
int user_registry(const void *field, char tipo);
void menu_adm();

typedef struct{
	char cuit[23];
	char nombre[52];
	char num[14];
	char email[50];
	char CVU[23];
	char alias[6];
	char IVA[50];
	char contra[50];
	float saldo;
	char rol;
}usuario;

void ingresar_dinero(usuario *usa);
void transferencia(usuario *usa);
void menu_ing(usuario *usser);
void pagar_servicios(usuario *usa);
void movimiento(char movtxt[100], char opcn, const usuario *usa,float monto);
void filtros(const usuario *usa);
void mdatos(usuario *usa);
void admin(char tipo, usuario *usuwu);

typedef struct{
	char type;
	char CBU[23];
	char cuitl[23];
	char clave1[4];
}cuentabanco;

typedef struct{
	char tipo1;
	float monto;
	char iibb[50];
	char fech[50];
	char cuilt[50];
}movimientos;


int main(){
	char opc;
	FILE *archivo=fopen("user.dat","rb" );
	if(archivo==NULL){
		archivo=fopen("user.dat", "wb");
		if (archivo==NULL){
		printf("Error al abrir el archivo de registros.\n");
		exit(0);
		}else{
			usuario user;
			strcpy(user.nombre, "Administrador");
			strcpy(user.num, "0000000000000");
			strcpy(user.email, "admin0@gmail.com");
			strcpy(user.cuit, "00000");
			strcpy(user.alias, "Ad000");
			strcpy(user.contra, "contrasena");
			user.rol='0';
			if (fwrite(&user, sizeof(usuario), 1, archivo) != 1) {
    			printf("Error al escribir los datos en el archivo\n");
			}
		}
		fclose(archivo);
	}
	fclose(archivo);
	
	FILE *archiv1=fopen("cuentabanco.dat","rb" );
	if(archiv1==NULL){
		archiv1=fopen("cuentabanco.dat", "wb");
		if (archiv1==NULL){
		printf("Error al abrir el archivo de registros.\n");
		exit(0);
		}else{
			cuentabanco cuent;
			strcpy(cuent.CBU, "0000000000000000000000");
			strcpy(cuent.clave1, "000");
			strcpy(cuent.cuitl, "0000000000000000000000");
			cuent.type='0';
			if (fwrite(&cuent, sizeof(cuentabanco), 1, archiv1) != 1) {
    			printf("Error al escribir los datos en el archivo\n");
			}
		}
		fclose(archiv1);
	}
	fclose(archiv1);
	printf("\nSi no se especifica la opcion de salir, todo proceso puede ser detenido ingresando 0.\n\n");
	repeat: 
	printf("\t\t\tBienvenido a Kamaba Pay!\n\n\t\t\tEscoja que desea hacer:\n\n\t\t\t1. Crear Usuario.\n\t\t\t2. Ingresar.\n\t\t\t3. Salir.\n");
	scanf("%s", &opc);
	switch (opc){
		case '1':
			crear_usuario();
			goto repeat;
			break;
		case '2':
			ingresar();
			goto repeat;
			break;
		case '3':
			printf("Usted ha salido.");
			break;
		default:
			system("cls");
			printf("\nOpcion invalida. Escoja de las siguientes:\n\n");
			goto repeat;
		}
}
	
	void crear_usuario(){
		int band=1;
		int i=1;
		int pos;
		int gm=0;
		char tipo;
		char CODVER[23];
		int DIGVERI;
		char cvu1[23];
		int errorcvu=0;
		int contnomb=0;
		int punto=0;
		int pos1;
		char gmail[50];
		char alias[51];
		usuario user;
		system("cls");
		printf("\n\t --- Panel de Registro de Nuevo Usuario ---\n");
		printf("\nHola, nuevo usuario! Por favor siga las instrucciones para crear una cuenta.\n");
		printf("\nIngrese su nombre completo: ");
		while(band!=0){
			fflush(stdin);
			fgets(user.nombre, sizeof(user.nombre), stdin);
			band=1;
			i=0;
			size_t len=strlen(user.nombre);
			if(len>0&&user.nombre[len-1]=='\n') {
    			user.nombre[len-1]='\0';
    		}
    		if (strcmp(user.nombre, "0") == 0) {
        		printf("\nProceso detenido por el usuario.\n");
        		return;
    		}
			while(user.nombre[i] != '\0' && band != 2){
				 if(!((user.nombre[i] >= 'A' && user.nombre[i] <= 'Z') || (user.nombre[i] >= 'a' && user.nombre[i] <= 'z') || user.nombre[i] == ' ')){
					band=2;
				}
				i++;
			}
			if((user.nombre[0]!=' ')&&(user.nombre[1]!=' ')&&(((user.nombre[0]>= 'A'))&&((user.nombre[0]<='Z')))){
				if(band!=2){
					if (strlen(user.nombre)>=2){
						if (strlen(user.nombre)<=50){
            	 		tipo='n';
							if ((contnomb=(user_registry(user.nombre, tipo)))==1){
							band=0;
							}else
								band=0;
						}else
								printf("\nEl nombre es muy largo.\n");
            		}else
            				printf("\nEl nombre es muy corto.\n");
        		}else
        			printf("\nIngrese un nombre valido. (Solo letras)\n");
			}else
				printf("\nNombre invalido, el primer caracter debe ser una letra mayuscula seguido de un caracter\n");
			}
		band=1;
		printf("\nIngrese su numero completo de celular. Agregando el codigo de area: ");
		while (band!=0){                   
			fflush(stdin);
			gets(user.num);
			fflush(stdin);
			band=1;
			i=0;
			if (strcmp(user.num, "0") == 0) {
        		printf("\nProceso detenido por el usuario.\n");
        		return;
    		}
			while(user.num[i] != '\0' && band != 2){
				 if(!((user.num[i] >= '0' && user.num[i] <= '9'))){
					band=2;
				}
				i++;
			}
			if(band!=2){
				if (strlen(user.num)==13){
					if ((user.num[0]=='5')&&(user.num[1]=='4')&&(user.num[2]=='9')){
						tipo='c';
						if (user_registry(user.num, tipo)==1){
							band=0;
						}else
							printf("\nNumero ya existente.\n");
					}else              
						printf("\nIngrese un codigo de area valido.(549)\n");
				}else
					printf("\nIngrese un numero valido. (De 13 numeros).\n");
			}else
			printf("\nIngrese un numero valido (Sin letras).\n");
		}
		band=1;
		printf("\nIngrese su correo electronico: ");
		while(band!=0){
			fflush(stdin);
			gets(user.email);
			fflush(stdin);
			band=1;
			i=0;
			gm=0;
			punto=0;
			if (strcmp(user.email, "0") == 0) {
        		printf("\nProceso detenido por el usuario.\n");
        		return;
    		}
			while(user.email[i] != '\0' && band != 2){
				if(!((user.email[i] >= 'A' && user.email[i] <= 'Z') || (user.email[i] >= 'a' && user.email[i] <= 'z') || (user.email[i] >= '0' && user.email[i] <= '9')||(user.email[i] == '@')||(user.email[i]=='.'))){
					band=2;
				}
				if(user.email[i]=='@'){
					gm++;
					pos=i;
				}
				if((user.email[i]=='.')&&(user.email[i]>pos)){
					if(user.email[i]=='.'){
						punto++;
						pos1=i;
					}
				}
				i++;	
				}
			if (punto==1){
				i=0;
				pos=pos+1;
				fflush(stdin);
				strcpy(gmail, " ");
				fflush(stdin);
				while(user.email[pos+i]!='.'&&user.email[pos+i]!='@'){
					fflush(stdin);
					gmail[i]=user.email[pos+i];
					fflush(stdin);
					i++;
				}
			}else
				punto=0;
			if(user.email[0]!='@'){
				if (band!=2){
					if(gm==1){
						if (punto!=0){
							if (strlen(user.email)<=49){
								if((strcmp(gmail, "gmail") == 0)||(strcmp(gmail, "hotmail") == 0)||(strcmp(gmail, "yahoo") == 0)||(strcmp(gmail, "outlook") == 0)){
									tipo='e';
									if((user.email[pos1+1]=='c')&&(user.email[pos1+2]=='o')&&(user.email[pos1+3]=='m')&&(user.email[pos1+4]=='\0')){
										if (user_registry(user.email, tipo)==1){
											band=0;
										}else{
											printf("\nEmail ya existente.\n");
										}
									}else{
										band=1;
										printf("\nDireccion invalida. Asegurarse que los puntos y dominio esten correctos.\n");
										}
								}else
									printf("\nDireccion invalida. Solo gmail, yahoo, outlook y hotmail.\n");	
							}else
								printf("\nDireccion invalida. Excede la longitud permitida.\n");
						}else
							printf("\nDireccion invalida. Revisar los puntos\n");
					}else
						printf("\nDireccion invalida. Revise la cantidad de arrobas.\n");
				}else
					printf("\nDireccion invalida. Solo letras y numeros.\n");
			}else
				printf("\nDireccion invalida. El primer caracter debe ser una letra\n");
		}
		band=1;
		printf("\nIngrese su CUIT/L: ");
		while (band!=0){
			fflush(stdin);
			gets(user.cuit);
			fflush(stdin);
			band=1;
			i=0;
			if (strcmp(user.cuit, "0") == 0) {
        		printf("\nProceso detenido por el usuario.\n");
        		return;
    		}
			while(user.cuit[i] != '\0' && band != 2){
				if(!((user.cuit[i] >= '0' && user.cuit[i] <= '9'))){
					band=2;
				}
				i++;
			}
			if(band!=2){
				if (strlen(user.cuit)==11){
					if (((user.cuit[0]=='2')&&(user.cuit[1]=='7'))||((user.cuit[0]=='2')&&(user.cuit[1]=='0'))||((user.cuit[0]=='3')&&(user.cuit[1]=='0'))){
						if((11-((((user.cuit[0]-'0')*5)+((user.cuit[1]-'0')*4)+((user.cuit[2]-'0')*3)+((user.cuit[3]-'0')*2)+((user.cuit[4]-'0')*7)+((user.cuit[5]-'0')*6)+((user.cuit[6]-'0')*5)+((user.cuit[7]-'0')*4)+((user.cuit[8]-'0')*3)+((user.cuit[9]-'0')*2))%11))==(user.cuit[10]-'0')){
							tipo='t';
							if (user_registry(user.cuit, tipo)==1){
								band=0;
							}else
								printf("\nCUIT/L ya existente.\n");
						}else
							printf("\nCUIT/L invalido. No verifica.\n");
					}else
						printf("\nPrimeros digitos de CUIT/L invalidos.\n");
				}else
					printf("\nLa longitud del CUIT/L es invalida.\n");	
			}else
			printf("\nIngrese un CUIT/L valido. (Solo numeros)\n");
		}
		band=1;
		while(band!=0){
			for(int i=0; i<=5; i++){
				user.CVU[i]='0';
			}
			user.CVU[6]='3';
			user.CVU[7]='1';
			srand(time(NULL));
			for(i=8; i<=20; i++){
				user.CVU[i]='0'+rand()%10;
				}
			for (i=0; i<=20; i++){
				CODVER[i]='1';
				CODVER[i+1]='3';
				CODVER[i+2]='7';
				i=i+2;				
				}
			for (i=0; i<=20; i++){
				DIGVERI=(CODVER[i]+((user.CVU[i]-'0')*(CODVER[i]-'0')));
				}
				DIGVERI=DIGVERI%10;
			if(DIGVERI==0){
				user.CVU[21]='0';
			}else
				user.CVU[21]=DIGVERI+'0';
			user.CVU[22] = '\0';
			FILE *archiv=fopen("user.dat","rb" );
			if(archiv==NULL){
				printf("Error al abrir los registros para validacion. Cerrando el programa.");
				return;
				}
			usuario usi;
			while (fread(&usi, sizeof(usuario), 1, archiv)){
				if (strcmp(usi.CVU, user.CVU) == 0){
					fclose(archiv);
					errorcvu=1;
				}
			}
			if (errorcvu!=1){
				band=0;
			}
		}
		user.alias[0]=user.nombre[0];
		user.alias[1]=user.nombre[1];
		user.alias[2]=user.cuit[4];
		user.alias[3]=user.cuit[5];
		user.alias[4]=contnomb + '0';
		user.alias[5] = '\0';
		tipo='a';
		fflush(stdin);
		band=1;
		printf("\nCree una contrasena (Solo letras y numeros, al menos 8 caracteres de longitud.):\n");
		fflush(stdin);
		while (band!=0){
			i=0;
			fflush(stdin);
			fgets(user.contra, sizeof(user.contra), stdin);
			fflush(stdin);
			size_t len=strlen(user.contra);
			if(len>0&&user.contra[len-1]=='\n') {
    			user.contra[len-1]='\0';
    		}
    		if (strcmp(user.contra, "0") == 0) {
        		printf("\nProceso detenido por el usuario.\n");
        		return;
    		}
			while(user.contra[i] !='\0' && band != 2){
				if(!((user.contra[i] >= 'A' && user.contra[i] <= 'Z') || (user.contra[i] >= 'a' && user.contra[i] <= 'z') || (user.contra[i] >= '0' && user.contra[i] <= '9'))){
					band=2;
				}else
				i++;
			}
			if(band!=2){
				if(strlen(user.contra)<=49){
					if(strlen(user.contra)>=8){
						band=0;
					}else
						printf("\nContrasena invalida. Demasiado corta.\n");
				}else
					printf("\nContrasena invalida. Demasiado larga.\n");
			}else
				printf("\nContrasena invalida. Solo se permite el uso de numeros y letras.\n");
		}
		user.rol='1';
		if (user_registry(user.alias, tipo)==1){
			printf("\nSu alias es %s y su CVU es %s\n", user.alias, user.CVU);
		}else{
			alias[5]=user_registry(user.alias, tipo);
			printf("\nSu alias es %s y su CVU es %s\n", user.alias, user.CVU);
		}
		strcpy(user.IVA, "En validacion");
		FILE *arc=fopen("user.dat", "a+b");
		if(arc==NULL){
			printf("Error al abrir el archivo de usuarios para registar los datos.\n");
			return;
		}
		if (fwrite(&user, sizeof(usuario), 1, arc) != 1) {
    		printf("Error al escribir los datos en el archivo\n");
    		return;
		}
		fclose(arc);
		FILE *arcuit=fopen("ADMINvalidar_IVA.txt", "a+b");
		if(arcuit==NULL){
			printf("Error al abrir archivo IVA. Cerrando el programa.");
			return;
		}else
		fprintf(arcuit, "! Nuevo CUIT a verificar: %s\n", user.cuit);
		fclose(arcuit);
		printf("\nCuenta creada con exito!\n\n Te bienvenimos, %s.\nIngrese 0 para volver al menu principal, y cualquier otro numero para salir del programa.\n", user.nombre);
		scanf("%d", &band);
		if (band==0){
			system("cls");
		}else{
		printf("Saliendo del programa... Usted ha salido.");
		return;
		}
}


	 int user_registry(const void *field, char tipo){
		int contnom=1;
		int contalias=1;
		FILE *archivo=fopen("user.dat","rb" );
			if(archivo==NULL){
				printf("Error al abrir los registros para validacion. Cerrando el programa.");
				return 0;
				}
		usuario usu;
		while (fread(&usu, sizeof(usuario), 1, archivo)){
		switch (tipo){
			case 'n':{
				char *nombre=(char *)field;
				if (strcmp(usu.nombre, nombre) == 0){
					contnom++;
				}
				break;
				}
			case 'c':{
				char *num=(char *)field;
				if (strcmp(usu.num, num) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			case 'e':{
				char *email=(char *)field;
				if (strcmp(usu.email, email) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			case 't':{
				char *cuit=(char *)field;
				if (strcmp(usu.cuit, cuit) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			case 'a':{
				char *alias=(char *)field;
				if (strcmp(usu.alias, alias) == 0){
					fclose(archivo);
					contalias++;
				}
				break;
			}
			case 'o':{
				char *contr=(char *)field;
				if (strcmp(usu.contra, contr) == 0){
					fclose(archivo);
					return 0;
				}
				break;
			}
			}
		}
		if(contalias>0){
			fclose (archivo);
			return contalias;
		}
		if (contnom>0){
			fclose(archivo);
			return contnom;
		}else
		return 1;
	}
	
	void ingresar(){
		system("cls");
		repeat:
        char opci;
        int band=1;
        int band1=1;
        int error=1;
        usuario uso;
        usuario usr;
		char tip;
		FILE *arci = fopen("user.dat", "rb");
    		if (arci==NULL) {
        		printf("Error al abrir el archivo.\n");
        		return;
        	}
		printf("\n\t\t---Panel de Ingreso de Usuario---\t\t\n\n");
        printf("\t\t\t¿Como desea ingresar?!\n\n\t\t\t1. Utilizando email. \n\t\t\t2. Utilizando numero de celular.\n\t\t\t3. Utilizando CUIT/L.\n\t\t\t4. Salir\n");
        fflush(stdin);
        scanf("%s", &opci);
		switch (opci){
        	case '1':
                printf("\nIngrese su email.\n");
                while(band!=0){
                fflush(stdin);
                gets(uso.email);
                fflush(stdin);
                if (strcmp(uso.email, "0") == 0) {
        			printf("\nProceso detenido por el usuario.\n\n");
        			break;
    			}
                tip='e';
                if(user_registry(uso.email, tip)!=1){
                	printf("\nIngrese su contraseña\n");
                	while(band1!=0){
                    fflush(stdin);
					gets(uso.contra);
					fflush(stdin);
					if (strcmp(uso.contra, "0") == 0) {
        				printf("\nProceso detenido por el usuario.\n\n");
        				break;
    				}
					tip='o';
					if(user_registry(uso.contra, tip)!=1){
						rewind(arci);
						error=1;
						while (fread(&usr, sizeof(usuario), 1, arci)){
							if ((strcmp(usr.email, uso.email) == 0)&&(strcmp(usr.contra, uso.contra) == 0)){
								uso=usr;
								printf("\nIngresando...Espere.\n");
								sleep(1);
								system("cls");
								menu_ing(&uso);
								error=0;
								break;
							}
						}
						if (error==1){
						printf("\nContraseña invalida. Pertenece a otra cuenta.\n");
						}else{
						fclose(arci);
						band1=0;
						}
                    }else
                    printf("\nContrasena incorrecta.\n");
                }
                if (band1==0){
					band=0;
				}
                }else
                	printf("\nEl correo ingresado no esta vinculado a una cuenta.\n");
                }
            		break;
        	case '2':
            	printf("\nIngrese su numero.\n");
                while(band!=0){
                fflush(stdin);
                gets(uso.num);
                fflush(stdin);
                if (strcmp(uso.num, "0") == 0) {
        			printf("\nProceso detenido por el usuario.\n\n");
        			break;
    			}
                tip='c';
                if(user_registry(uso.num, tip)!=1){
                	printf("\nIngrese su contraseña\n");
                	while(band1!=0){
                    fflush(stdin);
					gets(uso.contra);
					fflush(stdin);
					if (strcmp(uso.contra, "0") == 0) {
        				printf("\nProceso detenido por el usuario.\n\n");
        				break;
    				}
					tip='o';
					if(user_registry(uso.contra, tip)!=1){
						rewind(arci);
						error=1;
						while (fread(&usr, sizeof(usuario), 1, arci)){
							if ((strcmp(usr.num, uso.num) == 0)&&(strcmp(usr.contra, uso.contra) == 0)){
								uso=usr;
								printf("\nIngresando...Espere.\n");
								sleep(1);
								system("cls");
								menu_ing(&uso);
								error=0;
								break;
							}
						}
						if (error==1){
						printf("\nContraseña invalida. Pertenece a otra cuenta.\n");
						}else{
						fclose(arci);
						band1=0;
						}
                    }else
                    printf("\nContrasena incorrecta.\n");
                }
                if (band1==0){
					band=0;
				}
                }else
                	printf("\nInvalido. Ingrese su numero nuevamente.\n");
                }
            		break;
        	case '3':
            	printf("\nIngrese su CUIT/L.\n");
                while(band!=0){
                fflush(stdin);
                gets(uso.cuit);
                fflush(stdin);
                if (strcmp(uso.cuit, "0") == 0) {
        			printf("\nProceso detenido por el usuario.\n\n");
        			break;
    			}
                tip='t';
                if(user_registry(uso.cuit, tip)!=1){
                	printf("\nIngrese su contraseña\n");
                	while(band1!=0){
                    fflush(stdin);
					gets(uso.contra);
					fflush(stdin);
					if (strcmp(uso.contra, "0") == 0) {
        				printf("\nProceso detenido por el usuario.\n\n");
        				break;
    				}
					tip='o';
					if(user_registry(uso.contra, tip)!=1){
						rewind(arci);
						error=1;
						while (fread(&usr, sizeof(usuario), 1, arci)){
							if ((strcmp(usr.cuit, uso.cuit) == 0)&&(strcmp(usr.contra, uso.contra) == 0)){
								uso=usr;
								printf("\nIngresando...Espere.\n");
								sleep(1);
								system("cls");
								menu_ing(&uso);
								error=0;
								break;
							}
						}
						if (error==1){
						printf("\nContraseña invalida. Pertenece a otra cuenta.\n");
						}else{
						fclose(arci);
						band1=0;
						}
                    }else
                    printf("\nContrasena incorrecta.\n");
                }
                if (band1==0){
					band=0;
				}
                }else
                	printf("\nInvalido. Ingrese su CUIT/L nuevamente.\n");
                }
            		break;
            	case '0':
            		printf("\nIngrese el CUIT/L.\n");
                	fflush(stdin);
                	gets(uso.cuit);
                	fflush(stdin);
                	if (strcmp(uso.cuit, "0") == 0) {
        				printf("\nProceso detenido por el Administrador.\n\n");
        				break;
    				}
                	tip='t';
                	if(user_registry(uso.cuit, tip)!=1){
                		printf("\nIngrese su contraseña\n");
                    	fflush(stdin);
						gets(uso.contra);
						fflush(stdin);
						if (strcmp(uso.cuit, "0") == 0) {
        					printf("\nProceso detenido por el Administrador.\n\n");
        					break;
    					}
						tip='o';
						if(user_registry(uso.contra, tip)!=1){
							rewind(arci);
							error=1;
						while (fread(&usr, sizeof(usuario), 1, arci)){
							if ((strcmp(usr.cuit, uso.cuit) == 0)&&(strcmp(usr.contra, uso.contra) == 0)){
								if(usr.rol=='0'){
								printf("\nBienvenido, Administrador. Ingresando...Espere.\n");
								sleep(1);
								system("cls");
								menu_adm();
								error=0;
								break;
								}else{
								error=1;
								printf("\nNo posee los permisos para acceder.\n");
								sleep(2);
								system("cls");
								}
							}
						}
						if (error==1){
						printf("\nContraseña invalida. Volviendo al menu...\n");
						sleep(2);
                    	system("cls");
                    	return;
						}else{
						fclose(arci);
						sleep(1);
                    	system("cls");
                    	return;
						}
                    }else{
                    printf("\nContrasena incorrecta. Volviendo al menu...\n");
                    sleep(1);
                    system("cls");
                    return;
              		}
                }else
                	printf("\nEl correo ingresado no esta vinculado a una cuenta.\n");
            		break;
            	case '4':
					printf("Saliendo...");
					sleep(1);
				return;
				default:
					system("cls");
					printf("\nOpcion invalida. Escoja de las siguientes:\n\n");
					goto repeat;
					break;
            		
        }        
    }
    
    void menu_ing(usuario *usser){
    	char opcion;
    	long pos;
    	char opcn;
    	usuario usa;
    	usa=*usser;
    	repeat:
    	FILE *arch=fopen("user.dat", "rb+");
    	if(arch==NULL){
    		printf("\nError al abrir el archivo de usuarios.\n");
    		return;
		}
		if((strcmp(usser->IVA, "En validacion"))!=0){
    	usser->saldo=usa.saldo;
    	printf("\nHola, %s!\n\n", usser->nombre);
    	printf("\nSaldo: %f\n", usa.saldo);
    	printf("\n\t\tSeleccione la opcion deseada:\n\t\t1. Transferencia\n\t\t2. Ingresar Dinero\n\t\t3. Pagar Servicios\n\t\t4. Consultar y Modificar Datos\n\t\t5. Consultar movimientos\n\t\t6. Salir\n\n");
		fflush(stdin);
		scanf("%c", &opcion);
		switch(opcion){
			case '1':
				transferencia(&usa);
				if (usser->saldo != usa.saldo) {
                printf("\nSu saldo anterior era %.2f. Su nuevo saldo es %.2f\n", usser->saldo, usa.saldo);
                rewind(arch); 
                while (fread(usser, sizeof(usuario), 1, arch)==1) {
                    if (strcmp(usser->cuit, usa.cuit)==0) {
                        pos=ftell(arch)-sizeof(usuario);
                        fseek(arch, pos, SEEK_SET);
                        usser->saldo=usa.saldo;
                        if (fwrite(usser, sizeof(usuario), 1, arch)!= 1) {
                            printf("\nError al escribir los datos en el archivo\n");
                        }
                        break;
                    }
                }
            	}
            	fclose(arch);
            	sleep(2);
            	system("cls");
            	goto repeat;
				break;
			case '2':
				ingresar_dinero(&usa);
				if (usser->saldo != usa.saldo) {
                printf("\nSu saldo anterior era %.2f. Su nuevo saldo es %.2f\n", usser->saldo, usa.saldo);
                rewind(arch); 
                while (fread(usser, sizeof(usuario), 1, arch) == 1) {
                    if (strcmp(usser->cuit, usa.cuit) == 0) {
                        pos = ftell(arch) - sizeof(usuario);
                        fseek(arch, pos, SEEK_SET);
                        usser->saldo = usa.saldo;
                        if (fwrite(usser, sizeof(usuario), 1, arch) != 1) {
                            printf("\nError al escribir los datos en el archivo\n");
                        }
                        break;
                    }
                }
            }
            fclose(arch);
            sleep(2);
            system("cls");
            goto repeat;
				break;
			case '3':
				pagar_servicios(&usa);
				if (usser->saldo != usa.saldo) {
                printf("\nSu saldo anterior era %.2f. Su nuevo saldo es %.2f\n", usser->saldo, usa.saldo);
                rewind(arch); 
                while (fread(usser, sizeof(usuario), 1, arch) == 1) {
                    if (strcmp(usser->cuit, usa.cuit) == 0) {
                        pos = ftell(arch) - sizeof(usuario);
                        fseek(arch, pos, SEEK_SET);
                        usser->saldo = usa.saldo;
                        if (fwrite(usser, sizeof(usuario), 1, arch) != 1) {
                            printf("\nError al escribir los datos en el archivo\n");
                        }
                        break;
                    }
                }
            }
            fclose(arch);
            sleep(2);
            system("cls");
            goto repeat;
				break;
			case '4':
				mdatos(&usa);
				if (memcmp(&usser, &usa, sizeof(usuario)) != 0){
                printf("\nCambios realizados con exito\n");
                rewind(arch); 
                while (fread(usser, sizeof(usuario), 1, arch) == 1) {
                    if (strcmp(usser->cuit, usa.cuit) == 0) {
                        pos=ftell(arch)-sizeof(usuario);
                        usser=&usa;
                        fseek(arch, pos, SEEK_SET);
                        if (fwrite(usser, sizeof(usuario), 1, arch) != 1) {
                            printf("\nError al escribir los datos en el archivo\n");
                        }
                        break;
                    }
                }
            }else
				printf("\nNo han habido cambios.\n");
            fclose(arch);
            sleep(2);
            system("cls");
            goto repeat;
			break;
			case '5':
				filtros(&usa);
				goto repeat;
				break;
			case '6':
				printf("Saliendo...");
				sleep(1);
				return;
			default:
				system("cls");
				printf("\nOpcion invalida. Escoja de las siguientes:\n\n");
				goto repeat;
				break;
		}
		}else{
		printf("\nUsted no posee la verificacion necesaria para continuar.\nEspere o contacte a nuestro servicio al cliente: barbararoza60@gmail.com\n\n");
		sleep(1);
		}
	}
	
	void transferencia(usuario *usa){
		float monto;
		long pos;
		char movtxt[100];
		char opcn;
		float desc;
		usuario uscompar;
		system("cls");
		repeat:
		desc=0;
		FILE *archive=fopen("user.dat", "rb+");
		if (archive==NULL){
			printf("Error al abrir el archivo para comparar usuarios durante transferencia.");
			return;
		}
		char entrada[50];
		char opi;
		int encon=1;
		printf("\n\t\tSeleccione como desea transferir:\n");
		printf("\n\t\t1. Con CVU o alias:\n\t\t2. Con celular o email.\n\t\t3. Salir.\n\n");
		fflush(stdin);
		scanf("%c", &opi);
		fflush(stdin);
		switch(opi){
			case '1':
				if(usa->saldo>0){
					printf("\nIngrese el CVU o alias de la persona a transferir: ");
					fflush(stdin);
					gets(entrada);
					fflush(stdin);
					while (fread(&uscompar, sizeof(usuario), 1, archive)){
						if ((strcmp(uscompar.CVU, entrada)==0)||(strcmp(uscompar.alias, entrada)==0)){
							printf("\nUsted va a transferir dinero a %s\n", uscompar.nombre);
							encon=1;
							break;
							}else
								encon=0;
					}
					if(encon!=0){
					rewind(archive);
					while (fread(&uscompar, sizeof(usuario), 1, archive)==1){
                    if ((strcmp(uscompar.CVU, entrada)==0)||(strcmp(uscompar.alias, entrada)==0)){
                        pos=ftell(archive)-sizeof(usuario);
                        fseek(archive, pos, SEEK_SET);
                        printf("\nIngrese la cantidad de dinero a transferir: ");
                        scanf("%f", &monto);
                        if (usa->saldo>=monto){
                            usa->saldo-=monto;
                            uscompar.saldo+= monto;
                			if((strcmp(uscompar.IVA, "Sujeto Exento")==0)||(strcmp(uscompar.IVA, "Monotributista Social")==0)||(strcmp(uscompar.IVA, "Responsable Monotributo")==0)||(strcmp(uscompar.IVA, "Responsable Inscripto")==0)){
								uscompar.saldo+=(monto-(monto*0.05));
								printf("\nSe le ha descontado un 5 porciento a su transferencia debido a la tasa IIBB del otro usuario.\n");
								desc=monto*0.05;
							}
                            printf("\nUsted esta transferiendo %.2f\n a %s...\n", monto, uscompar.nombre);
                            fseek(archive, pos, SEEK_SET);
                            if (fwrite(&uscompar, sizeof(usuario), 1, archive) != 1){
                                printf("\nError al escribir los datos en el archivo\n");
                            }else{
                                opcn='t';
                                if(desc>0){
								snprintf(movtxt, sizeof(movtxt), "Transferencia recibida de %.2f de %s a %s, con una retencion de %.2f", monto, usa->cuit, uscompar.cuit, desc);
                        		movimiento(movtxt, opcn, &uscompar, monto);
								uscompar=*usa;
								snprintf(movtxt, sizeof(movtxt), "Transferencia de %.2f a %s ce %s, con una retencion de %.2f", monto, uscompar.cuit, usa->cuit, desc);	
                        		movimiento(movtxt, opcn, &uscompar, monto);	
								}else{
                        		snprintf(movtxt, sizeof(movtxt), "Transferencia recibida de %.2f de %s a %s", monto, usa->cuit, uscompar.cuit);
                        		movimiento(movtxt, opcn, &uscompar, monto);
								snprintf(movtxt, sizeof(movtxt), "Transferencia de %.2f a %s ce %s", monto, uscompar.cuit, usa->cuit);	
                        		uscompar=*usa;
								movimiento(movtxt, opcn, &uscompar, monto);	
                        		}
                        		printf("\nSu transferencia fue exitosa.\n");
                            }
                        }else{
                            printf("\nEl saldo de la cuenta es insuficiente.\n");
                        }
                        break;
                    }
                }
                }else
                printf("\nNo se ha encontrado al usuario. Volviendo al menú principal...\n");
            } else {
                printf("\nSaldo insuficiente para transferencias. Volviendo al menu principal...\n");
            }
            fclose(archive);
            sleep(2);
            break;
			case '2':
				if(usa->saldo>0){
					printf("\nIngrese el celular o correo de la persona a transferir: ");
					fflush(stdin);
					gets(entrada);
					fflush(stdin);
					while (fread(&uscompar, sizeof(usuario), 1, archive)){
						if((strcmp(uscompar.email, entrada)==0)||(strcmp(uscompar.num, entrada)==0)){
							printf("\nUsted va a transferir dinero a %s\n", uscompar.nombre);
							encon=1;
							break;
						}else
						encon=0;
					}
					if(encon!=0){
					rewind(archive);
					while (fread(&uscompar, sizeof(usuario), 1, archive)==1){
                    if ((strcmp(uscompar.email, entrada)==0)||(strcmp(uscompar.num, entrada)==0)){
                        pos=ftell(archive)-sizeof(usuario);
                        fseek(archive, pos, SEEK_SET);
                        printf("\nIngrese la cantidad de dinero a transferir: ");
                        scanf("%f", &monto);
                        if (usa->saldo>=monto){
                            usa->saldo-=monto;
                            uscompar.saldo += monto;
                            if((strcmp(uscompar.IVA, "Sujeto Exento")==0)||(strcmp(uscompar.IVA, "Monotributista Social")==0)||(strcmp(uscompar.IVA, "Responsable Monotributo")==0)||(strcmp(uscompar.IVA, "Responsable Inscripto")==0)){
								uscompar.saldo+=(monto-(monto*0.05));
								printf("\nSe le ha descontado un 5 porciento a su transferencia debido a la tasa IIBB del otro usuario.\n");
								desc=monto*0.05;
							}
                            printf("\nUsted esta transferiendo %.2f a %s...\n", monto, uscompar.nombre);
                            fseek(archive, pos, SEEK_SET);
                            if (fwrite(&uscompar, sizeof(usuario), 1, archive) != 1){
                                printf("\nError al escribir los datos en el archivo\n");
                            }else{
                                opcn='t';
                                if(desc>0){
								snprintf(movtxt, sizeof(movtxt), "Transferencia recibida de %.2f de %s a %s, con una retencion de %.2f", monto, usa->cuit, uscompar.cuit, desc);
                        		movimiento(movtxt, opcn, &uscompar, monto);
								uscompar=*usa;
								snprintf(movtxt, sizeof(movtxt), "Transferencia de %.2f a %s ce %s, con una retencion de %.2f", monto, uscompar.cuit, usa->cuit, desc);	
                        		movimiento(movtxt, opcn, &uscompar, monto);	
								}else{
                        		snprintf(movtxt, sizeof(movtxt), "Transferencia recibida de %.2f de %s a %s", monto, usa->cuit, uscompar.cuit);
                        		movimiento(movtxt, opcn, &uscompar, monto);
								snprintf(movtxt, sizeof(movtxt), "Transferencia de %.2f a %s ce %s", monto, uscompar.cuit, usa->cuit);	
                        		uscompar=*usa;
								movimiento(movtxt, opcn, &uscompar, monto);	
                        		}
                        		printf("\nSu transferencia fue exitosa.\n");
                            }
                        }else{
                            printf("\nEl saldo de la cuenta es insuficiente.\n");
                        }
                        break;
                    }
                }
                }else
                printf("\nNo se ha encontrado al usuario. Volviendo al menú principal...\n");
            } else
                printf("\nSaldo insuficiente para transferencias. Volviendo al menu principal...\n");
            fclose(archive);
            sleep(2);
            break;
			case '3':
				printf("Saliendo...");
				sleep(1);
				return;
				break;
			default:
				system("cls");
				printf("\nOpcion invalida. Escoja de las siguientes:\n\n");
				goto repeat;
				break;
		}
		return;
	}
	
void ingresar_dinero(usuario *usa){
	char opcio;
	int contc;
	char clave[50];
	char cbu[23];
	char tipo;
	float monto;
	char opcn;
	char movtxt[100];
	system("cls");
	repeat:
	usuario movstr=*usa;
	cuentabanco cuenta;
	FILE *arch=fopen("cuentabanco.dat", "rb");
	if(arch==NULL){
		printf("\nError al abrir el archivo de cuenta de banco.\n");
		return;
	}
	int band=1;
	int enc=0;
	int i=0;
	contc=0;
	printf("\nSeleccione que desea hacer:\n");
	printf("\n\t\t1. Ingresar dinero con cuenta vinculada.\n\t\t2. Agregar nueva cuenta\n\t\t3. Salir\n");
	fflush(stdin);
	scanf("%c", &opcio);
	fflush(stdin);
	rewind(arch);
	switch(opcio){
		case '1':
			rewind(arch);
			printf("\nElija una de sus cuentas para transferir:\n");
			while (fread(&cuenta, sizeof(cuentabanco), 1, arch)){
				if (strcmp(cuenta.cuitl, usa->cuit) == 0){
					contc++;
					printf("\n%d. %s\n", contc, cuenta.CBU);
				}
			}
			if (contc>0){
				while(band!=0){
				scanf("%c", &opcio);
				fflush(stdin);
				if (opcio >= '1' && opcio <= contc + '0') {
					band=0;
				}else
					printf("\nOpcion invalida. Elija de las existentes.\n");
				}
				rewind(arch);
				contc=0;
				while (fread(&cuenta, sizeof(cuentabanco), 1, arch)){
					if (strcmp(cuenta.cuitl, usa->cuit) == 0){
						contc++;
						if(contc==opcio-'0'){
							strcpy(cbu, cuenta.CBU);
							printf("\nUsted ha elegido el siguiente CBU: %s\n", cuenta.CBU);
						}
					}
				}
				fclose(arch);
				printf("\nPor favor ingrese el monto a transferir a su cuenta: ");
				scanf("%f", &monto);
				usa->saldo=(usa->saldo+monto);
				printf("\nUsted ha transferido $%.2f\n", monto);
				opcn='i';
                	snprintf(movtxt, sizeof(movtxt), "Ingreso de %.2f a %s desde %s", monto, cuenta.CBU, usa->CVU);
                    movimiento(movtxt, opcn, &movstr, monto);
			}
			if (contc==0){
				printf("\nUsted no posee ninguna cuenta vinculada. Agregue una para volver a intentar.\n");
			}
			contc=0;
			goto repeat;
			break;
		case '2':
			system("cls");
			printf("\n\t\tPanel de Vinculacion de Cuenta Bancaria---\n");
			printf("\nIngrese el tipo de cuenta\n1. Ahorro\n2. Corriente\n");
			while(band!=0){
				fflush(stdin);
				scanf("%c", &tipo);
				fflush(stdin);
				if((tipo=='1')||(tipo=='2')){
					band=0;
				}else
				printf("\nTipo invalido, elija de las opciones dadas.\n");
			}
			band=1;
			printf("\nIngrese su CBU\n");
			while(band!=0){
				fflush(stdin);
				gets(cbu);
				fflush(stdin);
				if (strcmp(cbu, "0") == 0) {
        			printf("\nProceso detenido por el usuario.\n\n");
        			break;
    			}
				i=0;
				band=1;
				while(cbu[i] != '\0' && band != 2){
				 if(!((cbu[i] >= '0' && cbu[i] <= '9'))){
					band=2;
				}
				i++;
				}
				if(band!=2){
					if(strlen(cbu)==22){
						printf("\nIngrese la clave de su cuenta.\n");
						fflush(stdin);
						gets(clave);
						fflush(stdin);
						if (strcmp(clave, "0") == 0) {
        					printf("\nProceso detenido por el usuario.\n\n");
        					break;
    					}
						if(strlen(clave)<4){
						while (fread(&cuenta, sizeof(cuentabanco), 1, arch)){
							if (strcmp(cuenta.CBU, cbu) == 0){
								enc++;
								if(strcmp(cuenta.clave1, clave) == 0){
										strcpy(cuenta.cuitl, usa->cuit);
										cuenta.type=tipo;
										fclose(arch);
										fflush(stdin);
										arch=fopen("cuentabanco.dat", "ab");
										if (fwrite(&cuenta, sizeof(cuentabanco), 1, arch) != 1) {
    										printf("\nError al escribir los datos en el archivo\n");
    										band=0;
										}else
											printf("\nCuenta vinculada con exito, %d\n", enc);
											fclose(arch);
											band=0;
								}else
								printf("\nLa clave es incorrecta.\n");
							}else
								enc=0;
							}
						if(enc==0){
							strcpy(cuenta.CBU, cbu);
							strcpy(cuenta.clave1, clave);
							strcpy(cuenta.cuitl, usa->cuit);
							cuenta.type=tipo;
							fclose(arch);
							arch=fopen("cuentabanco.dat", "ab");
							if (fwrite(&cuenta, sizeof(cuentabanco), 1, arch) != 1) {
    							printf("\nError al escribir los datos en el archivo\n");
    							band=0;
							}else{
								printf("\nCuenta vinculada con exito por primera vez\n");
								fclose(arch);
								band=0;
								}
							}
						}else{
						band=1;	
						printf("\nClave muy larga. Solo 3 caracteres.\n");
						}
					}else{
					band=1;
					printf("\nInvalido. Vuelva a revisar el CBU o la contrasena.\n");
					}
				}else{
				band=1;
				printf("\nInvalido. Ingrese el CBU nuevamente.\n");
				}
			}
			break;
		case '3':
			printf("\nSaliendo...\n");
			sleep(1);
			system("cls");
			return;
			break;
		default:
			system("cls");
			printf("\nError. Ingrese una de las siguientes opciones.\n");
			goto repeat;
			break;
	}
}

void pagar_servicios(usuario *usa){
	char op;
	char opcn;
	char movtxt[100];
	int deuda;
	float monto;
	usuario movstru=*usa;
	system("cls");
	repeat:
	printf("\n\t\t---Panel de Servicios---\n");
	printf("\nEscoja el servicio a pagar:\n");
	printf("\n\t\t1. Expensas Medicas.\n\t\t2. Servicio Telefonico.\n\t\t3. Expensas del hogar.\n\t\t4.Salir\n");
	scanf("%c", &op);
	switch(op){
		case '1':
			printf("\nPara consultar el monto a pagar de sus expensas medicas, consulte la pagina del Hospital Madariaga,\nal que usted esta asociado de acuerdo a sus registros fiscales.\n");
			printf("\nIngrese el monto a pagar: ");
			scanf("%f", &monto);
			if(usa->saldo>=monto){
				usa->saldo-=monto;
				if((strcmp(usa->IVA, "Sujeto Exento")==0)||(strcmp(usa->IVA, "Monotributista Social")==0)||(strcmp(usa->IVA, "Responsable Monotributo")==0)||(strcmp(usa->IVA, "Responsable Inscripto")==0)){
					if(usa->saldo>=(monto+(monto*0.05))){
					usa->saldo-=(monto+(monto*0.05));
					printf("\nSe le ha aumentado un 5 porciento a su pago debido a la tasa IIBB.\n");
					opcn='p';
                	snprintf(movtxt, sizeof(movtxt), "Pago de servicio medico de %.2f de %s, con un aumento de %.2f", monto, usa->cuit, monto*0.05);
                	movimiento(movtxt, opcn, &movstru, monto);
                	break;
                	}
				}
				opcn='p';
                snprintf(movtxt, sizeof(movtxt), "Pago de servicio de %.2f de %s", monto, usa->cuit );
                movimiento(movtxt, opcn, &movstru, monto);
			}else
			printf("Saldo insuficiente. Volviendo al menu principal...");
			sleep(1);
			system("cls");
			break;
		case '2':
			printf("\nPara consultar el monto a pagar de su servicio telefonico, consulte la pagina de Claro,\nal que usted esta asociado de acuerdo a sus registros telefonicos.\n");
			printf("\nIngrese el monto a pagar: ");
			scanf("%f", &monto);
			if(usa->saldo>=monto){
				usa->saldo-=monto;
				if((strcmp(usa->IVA, "Sujeto Exento")==0)||(strcmp(usa->IVA, "Monotributista Social")==0)||(strcmp(usa->IVA, "Responsable Monotributo")==0)||(strcmp(usa->IVA, "Responsable Inscripto")==0)){
					if(usa->saldo>=(monto+(monto*0.05))){
					usa->saldo-=(monto+(monto*0.05));
					printf("\nSe le ha aumentado un 5 porciento a su pago debido a la tasa IIBB.\n");
					opcn='p';
                	snprintf(movtxt, sizeof(movtxt), "Pago de servicio telefonico de %.2f de %s, con un aumento de %.2f", monto, usa->cuit, monto*0.05);
                	movimiento(movtxt, opcn, &movstru, monto);
                	break;
                	}
				}
				opcn='p';
                snprintf(movtxt, sizeof(movtxt), "Pago de servicio de %.2f de %s", monto, usa->cuit );
                movimiento(movtxt, opcn, &movstru, monto);
			}else
			printf("Saldo insuficiente. Volviendo al menu principal...");
			sleep(1);
			system("cls");
			break;
		case '3':
			printf("\nPara consultar el monto a pagar de sus expensas del hogar, consulte la pagina de Consorcio Abierto,\ncadena de departamentos en el que usted reside de acuerdo a sus registros fiscales.\n");
			printf("\nIngrese el monto a pagar: ");
			scanf("%f", &monto);
			if(usa->saldo>=monto){
				usa->saldo-=monto;
				if((strcmp(usa->IVA, "Sujeto Exento")==0)||(strcmp(usa->IVA, "Monotributista Social")==0)||(strcmp(usa->IVA, "Responsable Monotributo")==0)||(strcmp(usa->IVA, "Responsable Inscripto")==0)){
					if(usa->saldo>=(monto+(monto*0.05))){
					usa->saldo-=(monto+(monto*0.05));
					printf("\nSe le ha aumentado un 5 porciento a su pago debido a la tasa IIBB.\n");
					opcn='p';
                	snprintf(movtxt, sizeof(movtxt), "Pago de servicio al hogar de %.2f de %s, con un aumento de %.2f", monto, usa->cuit, monto*0.05);
                	movimiento(movtxt, opcn, &movstru, monto);
                	break;
                	}
				}
				opcn='p';
                snprintf(movtxt, sizeof(movtxt), "Pago de servicio de %.2f de %s", monto, usa->cuit );
                movimiento(movtxt, opcn, &movstru, monto);
			}else
			printf("Saldo insuficiente. Volviendo al menu principal...");
			sleep(2);
			system("cls");
			break;
		case '4':
			printf("\nSaliendo...\n");
			sleep(2);
			system("cls");
			return;
			break;
		default:
			system("cls");
			printf("Invalido. Escoja una de las opciones dadas:\n");
			goto repeat;
	}
}
void mdatos(usuario *usa){
	char opciowo;
	usuario user;
	char tipo;
	system("cls");
	repeat:
	int band=1;
	int i=0;
	int contnomb=0;
	int gm=0;
	int pos;
	int punto=0;
	int pos1=0;
	char gmail[50];
	printf("\n\t\t---Panel de Datos---\n");
	printf("Sus datos son los siguientes:\n");
	printf("Nombre: %s\n", usa->nombre);
	printf("Correo: %s\n", usa->email);
	printf("Celular: %s\n", usa->num);
	printf("CUIT/L: %s\n", usa->cuit);
	printf("Contrasena: %s\n", usa->contra);
	printf("Alias: %s\n", usa->alias);
	printf("CVU: %s\n", usa->CVU);
	printf("Condicion fiscal: %s\n", usa->IVA);
	printf("\nEscoja que desea hacer:\n");
	printf("\n\t\t1. Modificar Datos.\n\t\t2. Salir.\n");
	fflush(stdin);
	scanf("%c", &opciowo);
	switch(opciowo){
		case '1':
			system("cls");
			printf("\n\t\t---Panel de de Datos---\n");
			printf("\nEscoja el dato a modificar:\n");
			printf("\n\t\t1. Nombre\n\t\t2. Correo\n\t\t3. Numero\n\t\t4. Contrasena\n\t\t5. Alias.\n\t\t6. Salir\n");
			fflush(stdin);
			scanf("%c", &opciowo);
			switch(opciowo){
				case '1':
					printf("\nIngrese su nombre completo: ");
					while(band!=0){
						fflush(stdin);
						fgets(user.nombre, sizeof(user.nombre), stdin);
						band=1;
						i=0;
						size_t len=strlen(user.nombre);
						if(len>0&&user.nombre[len-1]=='\n') {
    						user.nombre[len-1]='\0';
    					}
    					if (strcmp(user.nombre, "0") == 0) {
        					printf("\nProceso detenido por el usuario.\n\n");
        					break;
    					}
					while(user.nombre[i] != '\0' && band != 2){
				 		if(!((user.nombre[i] >= 'A' && user.nombre[i] <= 'Z') || (user.nombre[i] >= 'a' && user.nombre[i] <= 'z') || user.nombre[i] == ' ')){
							band=2;
						}
					i++;
					}
					if((user.nombre[0]!=' ')&&(user.nombre[1]!=' ')&&(((user.nombre[0]>= 'A'))&&((user.nombre[0]<='Z')))){
						if(band!=2){
							if (strlen(user.nombre)>=2){
								if (strlen(user.nombre)<=50){
            	 					tipo='n';
									if ((contnomb=(user_registry(user.nombre, tipo)))==1){
										band=0;
										printf("\nNombre cambiado con exito de %s a %s\n", usa->nombre, user.nombre);
										strcpy(usa->nombre, user.nombre);
									}else
										band=0;
								}else
									printf("\nEl nombre es muy largo.\n");
            				}else
            					printf("\nEl nombre es muy corto.\n");
        				}else
        					printf("\nIngrese un nombre valido. (Solo letras)\n");
					}else
						printf("\nNombre invalido, el primer caracter debe ser una letra mayuscula seguido de un caracter\n");
				}
				band=1;
					break;
				case '2':
					printf("\nIngrese su correo electronico: ");
				while(band!=0){
					fflush(stdin);
					gets(user.email);
					fflush(stdin);
					band=1;
					i=0;
					gm=0;
					punto=0;
					if (strcmp(user.email, "0") == 0) {
        					printf("\nProceso detenido por el usuario.\n\n");
        					break;
    					}
					while(user.email[i] != '\0' && band != 2){
						if(!((user.email[i] >= 'A' && user.email[i] <= 'Z') || (user.email[i] >= 'a' && user.email[i] <= 'z') || (user.email[i] >= '0' && user.email[i] <= '9')||(user.email[i] == '@')||(user.email[i]=='.'))){
							band=2;
						}
						if(user.email[i]=='@'){
							gm++;
							pos=i;
						}
						if((user.email[i]=='.')&&(user.email[i]>pos)){
							if(user.email[i]=='.'){
								punto++;
								pos1=i;
							}
						}
					i++;	
					}
					if (punto==1){
						i=0;
						pos=pos+1;
						fflush(stdin);
						strcpy(gmail, " ");
						fflush(stdin);
						while(user.email[pos+i]!='.'&&user.email[pos+i]!='@'){
							fflush(stdin);
							gmail[i]=user.email[pos+i];
							fflush(stdin);
							i++;
						}
					}else
						punto=0;
					if(user.email[0]!='@'){
						if (band!=2){
							if(gm==1){
								if (punto!=0){
									if (strlen(user.email)<=49){
										if((strcmp(gmail, "gmail") == 0)||(strcmp(gmail, "hotmail") == 0)||(strcmp(gmail, "yahoo") == 0)||(strcmp(gmail, "outlook") == 0)){
											tipo='e';
											if((user.email[pos1+1]=='c')&&(user.email[pos1+2]=='o')&&(user.email[pos1+3]=='m')&&(user.email[pos1+4]=='\0')){
												if (user_registry(user.email, tipo)==1){
													printf("\nCorreo cambiado con exito de %s a %s\n", usa->email, user.email);
													strcpy(usa->email, user.email);
													band=0;
												}else{
													printf("\nEmail ya existente.\n");
											}
										}else{
											band=1;
											printf("\nDireccion invalida. Asegurarse que los puntos y dominio esten correctos.\n");
										}
									}else
										printf("\nDireccion inivalida. Solo gmail, yahoo, outlook y hotmail.\n");	
								}else
									printf("\nDireccion inivalida. Excede la longitud permitida.\n");
							}else
								printf("\nDireccion inivalida. Revisar los puntos\n");
						}else
							printf("\nDireccion inivalida. Revise la cantidad de arrobas.\n");
					}else
						printf("\nDireccion inivalida. Solo letras y numeros.\n");
				}else
					printf("\nDireccion inivalida. El primer caracter debe ser una letra\n");
			}
			band=1;		
					break;
				case '3':
					printf("\nIngrese su numero completo de celular. Agregando el codigo de area: ");
					while (band!=0){                   
					fflush(stdin);
					gets(user.num);
					fflush(stdin);
					if (strcmp(user.num, "0") == 0) {
        					printf("\nProceso detenido por el usuario.\n\n");
        					break;
    					}
					band=1;
					i=0;
					while(user.num[i] != '\0' && band != 2){
						if(!((user.num[i] >= '0' && user.num[i] <= '9'))){
							band=2;
						}
						i++;
					}
					if(band!=2){
						if (strlen(user.num)==13){
							if ((user.num[0]=='5')&&(user.num[1]=='4')&&(user.num[2]=='9')){
								tipo='c';
								if (user_registry(user.num, tipo)==1){
									printf("\nNumero cambiado con exito de %s a %s\n", usa->num, user.num);
									strcpy(usa->num, user.num);
									band=0;
								}else
									printf("\nNumero ya existente.\n");
							}else              
								printf("\nIngrese un codigo de area valido.(549)\n");
						}else
							printf("\nIngrese un numero valido. (De 13 numeros).\n");
					}else
						printf("\nIngrese un numero valido (Sin letras).\n");
					}
					band=1;
					break;
				case '4':
					printf("\nCree una contrasena (Solo letras y numeros, al menos 8 caracteres de longitud.):\n");
					fflush(stdin);
					while (band!=0){
						i=0;
						fflush(stdin);
						fgets(user.contra, sizeof(user.contra), stdin);
						fflush(stdin);
						size_t len=strlen(user.contra);
						if(len>0&&user.contra[len-1]=='\n') {
   				 			user.contra[len-1]='\0';
    					}
    					if (strcmp(user.contra, "0")==0){
        					printf("\nProceso detenido por el usuario.\n\n");
        					break;
    					}
						while(user.contra[i] !='\0' && band != 2){
							if(!((user.contra[i] >= 'A' && user.contra[i] <= 'Z') || (user.contra[i] >= 'a' && user.contra[i] <= 'z') || (user.contra[i] >= '0' && user.contra[i] <= '9'))){
							band=2;
						}else
							i++;
						}
						if(band!=2){
							if(strlen(user.contra)<=49){
								if(strlen(user.contra)>=8){
									printf("\nContrasena cambiada con exito de %s a %s\n", usa->contra, user.contra);
									strcpy(usa->contra, user.contra);
									band=0;
								}else
									printf("\nContrasena invalida. Demasiado corta.\n");
							}else
								printf("\nContrasena invalida. Demasiado larga.\n");
						}else
							printf("\nContrasena invalida. Solo se permite el uso de numeros y letras.\n");
					}
					band=1;
					break;
				case '5':
					printf("\nCree un alias (Solo letras y numeros).\n");
					fflush(stdin);
					while (band!=0){
						i=0;
						band=1;
						fflush(stdin);
						gets(user.alias);
						if (strcmp(user.alias, "0")==0) {
        					printf("\nProceso detenido por el usuario.\n\n");
        					break;
    					}
						while(user.alias[i] !='\0' && band != 2){
							if(!((user.alias[i] >= 'A' && user.alias[i] <= 'Z') || (user.alias[i] >= 'a' && user.alias[i] <= 'z') || (user.alias[i] >= '0' && user.alias[i] <= '9'))){
							band=2;
						}else
							i++;
						}
						if(band==1){
							if((strlen(user.alias)==5)){
								printf("\nAlias cambiado con exito de %s a %s\n", usa->alias, user.alias);
								strcpy(usa->alias, user.alias);
								band=0;
							}else
								printf("\nAlias invalido. Longitud incorrecta (5 caracteres).\n");
						}else
							printf("\nAlias invalido. Solo se permite el uso de numeros y letras.\n");
					}
					band=1;
					break;
				case '6':
					printf("\nSaliendo...\n");
					sleep(2);
					system("cls");
					return;
					break;
				default:
					system("cls");
					printf("\nOpcion invalida. Volviendo al panel de datos. \n");
					break;
			}
			sleep(2);
			system("cls");
			goto repeat;
			break;
		case '2':
			printf("\nSaliendo...\n");
			sleep(2);
			system("cls");
			return;
			break;
		default:
			system("cls");
			printf("\nError. Ingrese una de las siguientes opciones.\n");
			goto repeat;
			break;
	}
	}

void movimiento(char movtxt[100], char opcn, const usuario *usa, float monto){
	movimientos movim;
	char archname[50];
	char move[200];
	time_t tim;
	struct tm *tm_info;
	char fechtim[20];
	time(&tim);
	tm_info=localtime(&tim);
	strftime(fechtim, sizeof(fechtim), "%d/%m/%Y %H:%M:%S", tm_info);
	snprintf(archname, sizeof(archname), "%s.txt", usa->cuit);
	FILE *archivito=fopen(archname, "a");
	if(archivito==NULL){
		printf("\nError al abrir el archivo de movimientos.\n");
	}
	switch(opcn){
		case 't':
			snprintf(move, sizeof(move), "%s %s", fechtim, movtxt);
			if(strlen(move)>25){
				if (fprintf(archivito, "%s\n", move)>0){
					printf("\n");
				}else
					printf("\nSu transferencia no se ha cargado en el sistema.\n");
				fclose(archivito);
			}
			archivito=fopen("movimientos.dat", "ab");
			movim.tipo1=opcn;
			strcpy(movim.fech, fechtim);
			strcpy(movim.cuilt, usa->cuit);
			movim.monto=monto;
			strcpy(movim.iibb, usa->IVA);
			if (archivito == NULL) {
            	printf("\nError al abrir el archivo binario de movimientos.\n");
            	return;
            }
			if (strlen(move) > 25) {
    			if ((fwrite(&movim, sizeof(movimientos), 1, archivito)!=1)) {
        			printf("\nSu transferencia no se ha cargado en el sistema.\n");
   				}
			}
			fclose(archivito);
			sleep(1);
			return;
			break;
		case 'i':
			snprintf(move, sizeof(move), "%s %s", fechtim, movtxt);
			if(strlen(move)>25){
				if (fprintf(archivito, "%s\n", move)>0){
					printf("\n");
				}else
					printf("\nSu transferencia no se ha cargado en el sistema.\n");
				fclose(archivito);
			}
			archivito=fopen("movimientos.dat", "ab");
			movim.tipo1=opcn;
			strcpy(movim.fech, fechtim);
			strcpy(movim.cuilt, usa->cuit);
			movim.monto=monto;
			strcpy(movim.iibb, usa->IVA);
			if (archivito == NULL) {
            	printf("\nError al abrir el archivo binario de movimientos.\n");
            	return;
            }
			if (strlen(move) > 25) {
    			if ((fwrite(&movim, sizeof(movimientos), 1, archivito)!=1)) {
        			printf("\nSu transferencia no se ha cargado en el sistema.\n");
   				}
			}
			fclose(archivito);
			sleep(1);
			return;
			break;
		case 'p':
			snprintf(move, sizeof(move), "%s %s", fechtim, movtxt);
			if(strlen(move)>25){
				if (fprintf(archivito, "%s\n", move)>0){
					printf("\n");
				}else
					printf("\nSu transferencia no se ha cargado en el sistema.\n");
				fclose(archivito);
			}
			archivito=fopen("movimientos.dat", "ab");
			movim.tipo1=opcn;
			strcpy(movim.fech, fechtim);
			strcpy(movim.cuilt, usa->cuit);
			movim.monto=monto;
			strcpy(movim.iibb, usa->IVA);
			if (archivito == NULL) {
            	printf("\nError al abrir el archivo binario de movimientos.\n");
            	return;
            }
			if (strlen(move) > 25) {
    			if ((fwrite(&movim, sizeof(movimientos), 1, archivito)!=1)) {
        			printf("\nSu transferencia no se ha cargado en el sistema.\n");
   				}
			}
			fclose(archivito);
			sleep(1);
			return;
			break;
	}
}

void filtros(const usuario *usa){
	system("cls");
	char string[200];
	char temp[200];
	char archnom[100];
	int enc=0;
	snprintf(archnom, sizeof(archnom), "%s.txt", usa->cuit);
	FILE *archivote=fopen(archnom, "r");
	if (archivote==NULL) {
    	printf("Error al abrir el archivo %s debido a que aun no existen movimientos en esta cuenta.\n", archnom);
    	return; 
	}
	printf("\n\t\t---Panel de Filtros---\n");
	printf("\nIngrese el movimiento que desea buscar.\nSea por fecha(xx/xx/xxxx), tipo de movimiento(transferencia, ingreso, pago), etc.\n 0 para mostrar todos.\n");
	fflush(stdin);
	fgets(string, sizeof(string), stdin);
	string[strcspn(string, "\n")]='\0';
	for (int i=0; string[i]; i++){
        string[i]=tolower((unsigned char)string[i]);
    }
	while (fgets(temp, sizeof(temp), archivote)){
		for (int i=0; temp[i];i++){
            temp[i]=tolower((unsigned char)temp[i]);
        }
		if((strstr(temp, string)!=NULL)){
			printf("%s\n", temp);
			enc=1;
		}
	}
	fclose(archivote);
	if(enc==0){
		printf("\nNo se encontraron registros para lo ingresado. Volviendo al menu principal...\n");
	}
	sleep(1);
}

void menu_adm(){
	char cuit[23];
	usuario usuwu;
	char opciwi;
	char tipo;
	int pos;
	int error=0;
	system("cls");
	repeat:
	FILE *archivinho=fopen("user.dat", "rb+");
	if(archivinho==NULL){
		printf("\nError al abrir el archivo de usuarios durante el panel de administrador.\n");
	}
	printf("\n\t\t---Panel de Administrador---\n");
	printf("\nSeleccione que desea hacer:\n");
	printf("Bienvenido, Administrador.\n");
	printf("\n\t\t1. Modificacion de Usuarios\n\t\t2. Adjudicar Roles\n\t\t3. Datos de Usuario y Resumenes de Actividades \n\t\t4. Salir\n");
	fflush(stdin);
	scanf("%c", &opciwi);
	switch(opciwi){
		case '1':
			error=0;
			printf("\nIngrese el CUIT/L del usuario a modificar: ");
			fflush(stdin);
			scanf("%s", &cuit);
			while ((fread(&usuwu, sizeof(usuario), 1, archivinho))==1){
                    if (strcmp(usuwu.cuit, cuit) == 0) {
                        pos = ftell(archivinho) - sizeof(usuario);
                        fseek(archivinho, pos, SEEK_SET);
                        tipo='m';
                        admin(tipo, &usuwu);
                        if (fwrite(&usuwu, sizeof(usuario), 1, archivinho) != 1) {
                            printf("\nError al escribir los datos en el archivo\n");
                        }
                        error=1;
                        break;
                    }
                }
            if(error==0){
            	printf("\nUsuario no encontrado. Volviendo al menu principal...\n");
			}
            fclose(archivinho);
			sleep(1);
			goto repeat;
			break;
		case '2':
			error=0;
			printf("\nIngrese el CUIT/L del usuario a adjudicar rol: ");
			fflush(stdin);
			scanf("%s", &cuit);
			while ((fread(&usuwu, sizeof(usuario), 1, archivinho))==1){
                    if (strcmp(usuwu.cuit, cuit) == 0) {
                        pos=ftell(archivinho)-sizeof(usuario);
                        fseek(archivinho, pos, SEEK_SET);
                        tipo='a';
                        admin(tipo, &usuwu);
                        if (fwrite(&usuwu, sizeof(usuario), 1, archivinho) != 1) {
                            printf("\nError al escribir los datos en el archivo\n");
						}
						error=1;
                        break;
                    }
                }
            if(error==0){
            	printf("\nUsuario no encontrado. Volviendo al menu principal...\n");
			}
            fclose(archivinho);
			sleep(1);
			goto repeat;
			break;
		case '3':
			error=0;
			printf("\nIngrese el CUIT/L del usuario a consultar: ");
			fflush(stdin);
			scanf("%s", &cuit);
			while ((fread(&usuwu, sizeof(usuario), 1, archivinho))==1){
                    if (strcmp(usuwu.cuit, cuit) == 0) {
                        pos=ftell(archivinho)-sizeof(usuario);
                        fseek(archivinho, pos, SEEK_SET);
                        tipo='r';
                        admin(tipo, &usuwu);
                        error=1;
                        break;
                    }
                }
            if(error==0){
            	printf("\nUsuario no encontrado. Volviendo al menu principal...\n");
			}
            fclose(archivinho);
			sleep(1);
			goto repeat;
			break;
		case '4':
			printf("\nSaliendo...\n");
			sleep(2);
			system("cls");
			return;
			break;
		default:
			system("cls");
			printf("\nError. Ingrese una de las siguientes opciones.\n");
			goto repeat;
			break;
	}
	printf("dea");
}

void admin(char tipo, usuario *usuwu){
	usuario uss;
	char opcion;
	movimientos movi;
	system("cls");
	repeat:
	FILE *ARC=fopen("movimientos.dat", "rb+");
	int error=0;
	int movim=0;
	float toti=0;
	float totp=0;
	float tott=0;
	int band=1;
	int i=0;
	int gm=0;
	int punto=0;
	int pos;
	int pos1;
	int condicion;
	char gmail[50];
	int rol;
	FILE *archivinho=fopen("user.dat", "rb");
	switch(tipo){
		case 'm':
			printf("\n---Modificar usuario---\n");
			printf("Ingrese lo que desea modificar:\n ");
			printf("\n\t\t1. Nombre\n\t\t2. Correo\n\t\t3. Numero\n\t\t4. Contrasena\n\t\t5. Alias\n\t\t6. CUIT\n\t\t7. Condicion Fiscal\n\t\t8. Salir\n");
			fflush(stdin);
			scanf("%c", &opcion);
			switch(opcion){
				case '1':
					printf("\nIngrese el nuevo nombre: ");
					while(band!=0){
						fflush(stdin);
						fgets(uss.nombre, sizeof(uss.nombre), stdin);
						band=1;
						i=0;
						size_t len=strlen(uss.nombre);
						if(len>0&&uss.nombre[len-1]=='\n') {
    						uss.nombre[len-1]='\0';
    					}
    					if (strcmp(uss.nombre, "0") == 0) {
        					printf("\nProceso detenido por el administrador.\n");
        					break;
    					}
					while(uss.nombre[i] != '\0' && band != 2){
				 		if(!((uss.nombre[i] >= 'A' && uss.nombre[i] <= 'Z') || (uss.nombre[i] >= 'a' && uss.nombre[i] <= 'z') || uss.nombre[i] == ' ')){
							band=2;
						}
					i++;
					}
					if((uss.nombre[0]!=' ')&&(uss.nombre[1]!=' ')&&(((uss.nombre[0]>= 'A'))&&((uss.nombre[0]<='Z')))){
						if(band!=2){
							if (strlen(uss.nombre)>=2){
								if (strlen(uss.nombre)<=50){
            	 					tipo='n';
									if (((user_registry(uss.nombre, tipo)))==1){
										band=0;
										printf("\nNombre cambiado con exito de %s a %s\n", usuwu->nombre, uss.nombre);
										strcpy(usuwu->nombre, uss.nombre);
									}else
										band=0;
								}else
									printf("\nEl nombre es muy largo.\n");
            				}else
            					printf("\nEl nombre es muy corto.\n");
        				}else
        					printf("\nIngrese un nombre valido. (Solo letras)\n");
					}else
						printf("\nNombre invalido, el primer caracter debe ser una letra mayuscula seguido de un caracter\n");
				}
				band=1;
					break;
				case '2':
					printf("Ingrese el nuevo correo: \n");
					while(band!=0){
						fflush(stdin);
						gets(uss.email);
						fflush(stdin);
						if (strcmp(uss.email, "0") == 0) {
        					printf("\nProceso detenido por el administrador.\n");
        					break;
    					}
						band=1;
						i=0;
						gm=0;
						punto=0;
						while(uss.email[i] != '\0' && band != 2){
							if(!((uss.email[i] >= 'A' && uss.email[i] <= 'Z') || (uss.email[i] >= 'a' && uss.email[i] <= 'z') || (uss.email[i] >= '0' && uss.email[i] <= '9')||(uss.email[i] == '@')||(uss.email[i]=='.'))){
								band=2;
							}
							if(uss.email[i]=='@'){
								gm++;
								pos=i;
							}
							if((uss.email[i]=='.')&&(uss.email[i]>pos)){
								if(uss.email[i]=='.'){
									punto++;
									pos1=i;
								}
							}
						i++;	
						}
						if (punto==1){
							i=0;
							pos=pos+1;
							fflush(stdin);
							strcpy(gmail, " ");
							fflush(stdin);
							while(uss.email[pos+i]!='.'&&uss.email[pos+i]!='@'){
								fflush(stdin);
								gmail[i]=uss.email[pos+i];
								fflush(stdin);
								i++;
							}
						}else
							punto=0;
						if(uss.email[0]!='@'){
							if (band!=2){
								if(gm==1){
									if (punto!=0){
										if (strlen(uss.email)<=49){
											if((strcmp(gmail, "gmail") == 0)||(strcmp(gmail, "hotmail") == 0)||(strcmp(gmail, "yahoo") == 0)||(strcmp(gmail, "outlook") == 0)){
												tipo='e';
												if((uss.email[pos1+1]=='c')&&(uss.email[pos1+2]=='o')&&(uss.email[pos1+3]=='m')&&(uss.email[pos1+4]=='\0')){
													if (user_registry(uss.email, tipo)==1){
														printf("\nCorreo cambiado con exito de %s a %s\n", usuwu->email, uss.email);
														strcpy(usuwu->email, uss.email);
														band=0;
													}else{
														printf("\nEmail ya existente.\n");
												}
											}else{
												band=1;
												printf("\nDireccion invalida. Asegurarse que los puntos y dominio esten correctos.\n");
											}
										}else
											printf("\nDireccion invalida. Solo gmail, yahoo, outlook y hotmail.\n");	
									}else
										printf("\nDireccion invalida. Excede la longitud permitida.\n");
								}else
									printf("\nDireccion invalida. Revisar los puntos\n");
							}else
								printf("\nDireccion invalida. Revise la cantidad de arrobas.\n");
						}else
							printf("\nDireccion invalida. Solo letras y numeros.\n");
					}else
						printf("\nDireccion invalida. El primer caracter debe ser una letra\n");
				}
				band=1;		
				break;
				case '3':
					printf("\nIngrese el numero completo de celular. Agregando el codigo de area: ");
					while (band!=0){                   
					fflush(stdin);
					gets(uss.num);
					fflush(stdin);
					band=1;
					i=0;
					if (strcmp(uss.num, "0") == 0) {
  				  		printf("\nProceso detenido por el Administrador.\n");
  			     		return;
  			  		}
					while(uss.num[i] != '\0' && band != 2){
						if(!((uss.num[i] >= '0' && uss.num[i] <= '9'))){
						band=2;
						}
					i++;
					}
					if(band!=2){
						if (strlen(uss.num)==13){
							if ((uss.num[0]=='5')&&(uss.num[1]=='4')&&(uss.num[2]=='9')){
								tipo='c';
									if (user_registry(uss.num, tipo)==1){
										printf("\nNumero cambiado con exito de %s a %s\n", usuwu->num, uss.num);
										strcpy(usuwu->alias, uss.alias);
										band=0;
									}else
										printf("\nNumero ya existente.\n");
								}else              
									printf("\nIngrese un codigo de area valido.(549)\n");
							}else
								printf("\nIngrese un numero valido. (De 13 numeros).\n");
						}else
							printf("\nIngrese un numero valido (Sin letras).\n");
						}
					band=1;
				case '4':
					printf("\nCree una contrasena (Solo letras y numeros, al menos 8 caracteres de longitud.):\n");
					fflush(stdin);
					while (band!=0){
						i=0;
						fflush(stdin);
						fgets(uss.contra, sizeof(uss.contra), stdin);
						fflush(stdin);
						size_t len=strlen(uss.contra);
						if(len>0&&uss.contra[len-1]=='\n') {
			    			uss.contra[len-1]='\0';
			    		}
			    		if (strcmp(uss.contra, "0") == 0) {
			        		printf("\nProceso detenido por el Administrador.\n");
			        		return;
			    		}
						while(uss.contra[i] !='\0' && band != 2){
							if(!((uss.contra[i] >= 'A' && uss.contra[i] <= 'Z') || (uss.contra[i] >= 'a' && uss.contra[i] <= 'z') || (uss.contra[i] >= '0' && uss.contra[i] <= '9'))){
								band=2;
							}else
							i++;
						}
						if(band!=2){
							if(strlen(uss.contra)<=49){
								if(strlen(uss.contra)>=8){
									band=0;
								}else
									printf("\nContrasena invalida. Demasiado corta.\n");
							}else
								printf("\nContrasena invalida. Demasiado larga.\n");
						}else
							printf("\nContrasena invalida. Solo se permite el uso de numeros y letras.\n");
						}
				case '5':
					printf("\nCree un alias (Solo letras y numeros).\n");
					fflush(stdin);
					while (band!=0){
						i=0;
						band=1;
						fflush(stdin);
						gets(uss.alias);
						if (strcmp(uss.alias, "0")==0) {
        					printf("\nProceso detenido por el Administrador.\n\n");
        					break;
    					}
						while(uss.alias[i] !='\0' && band != 2){
							if(!((uss.alias[i] >= 'A' && uss.alias[i] <= 'Z') || (uss.alias[i] >= 'a' && uss.alias[i] <= 'z') || (uss.alias[i] >= '0' && uss.alias[i] <= '9'))){
							band=2;
						}else
							i++;
						}
						if(band==1){
							if((strlen(uss.alias)==5)){
								printf("\nAlias cambiado con exito de %s a %s\n", usuwu->alias, uss.alias);
								strcpy(usuwu->alias, uss.alias);
								band=0;
							}else
								printf("\nAlias invalido. Longitud incorrecta (5 caracteres).\n");
						}else
							printf("\nAlias invalido. Solo se permite el uso de numeros y letras.\n");
					}
					band=1;
					break;
				case '6':
					printf("\nIngrese el nuevo CUIT/L: ");
					while (band!=0){
						fflush(stdin);
						gets(uss.cuit);
						fflush(stdin);
						band=1;
						i=0;
						if (strcmp(uss.cuit, "0") == 0) {
			        		printf("\nProceso detenido por el Administrador.\n");
    			    		break;
    					}
						while(uss.cuit[i] != '\0' && band != 2){
							if(!((uss.cuit[i] >= '0' && uss.cuit[i] <= '9'))){
								band=2;
							}
						i++;
						}
						if(band!=2){
							if (strlen(uss.cuit)==11){
								if (((uss.cuit[0]=='2')&&(uss.cuit[1]=='7'))||((uss.cuit[0]=='2')&&(uss.cuit[1]=='0'))||((uss.cuit[0]=='3')&&(uss.cuit[1]=='0'))){
									if((11-((((uss.cuit[0]-'0')*5)+((uss.cuit[1]-'0')*4)+((uss.cuit[2]-'0')*3)+((uss.cuit[3]-'0')*2)+((uss.cuit[4]-'0')*7)+((uss.cuit[5]-'0')*6)+((uss.cuit[6]-'0')*5)+((uss.cuit[7]-'0')*4)+((uss.cuit[8]-'0')*3)+((uss.cuit[9]-'0')*2))%11))==(uss.cuit[10]-'0')){
										tipo='t';
										if (user_registry(uss.cuit, tipo)==1){
											printf("\nCUIT/L cambiado con exito de %s a %s\n", usuwu->cuit, uss.cuit);
											strcpy(usuwu->cuit, uss.cuit);
											band=0;
										}else
											printf("\nCUIT/L ya existente.\n");
									}else
										printf("\nCUIT/L invalido. No verifica.\n");
								}else
									printf("\nPrimeros digitos de CUIT/L invalidos.\n");
							}else
								printf("\nLa longitud del CUIT/L es invalida.\n");	
						}else
							printf("\nIngrese un cuit valido. (Solo numeros)\n");
						}
						band=1;
				break;
				case '7':
					tipo='t';
					if (user_registry(uss.cuit, tipo)==1){
						printf("\nElija la condicion ante el IVA de la persona en base a los datos de la AFIP:\n");
						printf("\n\t\t1. Sujeto Exento\n\t\t2. Consumidor Final\n\t\t3. Responsable Monotributo\n\t\t4. No categorizado\n\t\t5. Proveedor del Exterior\n\t\t6. Cliente del Exterior\n\t\t7. IVA Liberado\n\t\t8. Monotributista Social\n\t\t9. No Acutualizadon\t\t\n10. Responsable Inscripto\n");
						while(band!=0){
							fflush(stdin);
							scanf("%d", &condicion);
							if(condicion==0){
								band=0;
								printf("\nProceso terminado por el usuario.\n");
								sleep(1);
								break;
							}
							if (((condicion>=1)&&(condicion<=10))){
								if(condicion==1){
									strcpy(usuwu->IVA, "Sujeto Exento");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==2){
									strcpy(usuwu->IVA, "Consumidor Final");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==3){
									strcpy(usuwu->IVA, "Responsable Monotributo");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==4){
									strcpy(usuwu->IVA, "No Categorizado");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==5){
									strcpy(usuwu->IVA, "Proveedor del Exentor");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==6){
									strcpy(usuwu->IVA, "Cliente del Exterior");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==7){
									strcpy(usuwu->IVA, "IVA Liberado");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==8){
									strcpy(usuwu->IVA, "Monotributista Social");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==9){
									strcpy(usuwu->IVA, "IVA no Alcanzado");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
								if(condicion==10){
									strcpy(usuwu->IVA, "Responsable Inscripto");
									printf("\nCondicion cambiada con exito!\n");
									band=0;
								}
							}else
							printf("\nInvalido. Elija una de las opciones dadas.\n");
						}
					}
					break;
				case '8':
					printf("\nSaliendo...\n");
					sleep(2);
					system("cls");
					return;
					break;
				default:
					system("cls");
					printf("\nError. Ingrese una de las siguientes opciones.\n");
					goto repeat;
					break;
				}
			sleep(2);
			return;
			break;
		case 'a':
			system("cls");
			printf("\n\t\t---Adjudicar Rol---\n");
			printf("\nIngrese el nuevo rol:\n");
			printf("\n\t\t1. Administrador\n\t\t2. Usuario\n");
			band=1;
			while(band!=0){
				scanf("%d", &rol);
				if(rol==0){
					printf("Proceso detenido por el Administrador.");
					band=0;
					break;
				}
				if(((rol==1)||(rol==2))){
					if(rol==1){
						usuwu->rol='0';
						printf("\nRol cambiado con exito!\n");
						band=0;
					}
					else{
					usuwu->rol='1';
					printf("\nRol cambiado con exito!\n");
					band=0;
					}
				}else
				printf("\nInvalido. Ingrese una de las opciones dadas.\n");
			}
			sleep(2);
			return;
			break;
		case 'r':
			movim=0;
			error=0;
			printf("\n\t\t---Panel de Datos de Usuario y Resumen de Cuenta---\n");
			printf("Los datos del usuario seleccionado son los siguientes:\n");
			printf("Nombre: %s\n", usuwu->nombre);
			printf("Correo: %s\n", usuwu->email);
			printf("Celular: %s\n", usuwu->num);
			printf("CUIT/L: %s\n", usuwu->cuit);
			printf("Contrasena: %s\n", usuwu->contra);
			printf("Alias: %s\n", usuwu->alias);
			printf("CVU: %s\n", usuwu->CVU);
			printf("Condicion fiscal: %s\n", usuwu->IVA);
			while ((fread(&movi, sizeof(movimientos), 1, ARC))==1){
                    if (strcmp(usuwu->cuit, movi.cuilt) == 0) {
                        movim++;
                        if(movi.tipo1=='t'){
                        	tott=tott+movi.monto;
						}
						if(movi.tipo1=='i'){
                        	toti=toti+movi.monto;
						}
						if(movi.tipo1=='p'){
                        	totp=totp+movi.monto;
                        error=1;
						}
                    }
                }
            fclose(ARC);
            if(error==0){
            	printf("\nUsuario no encontrado. Volviendo al menu principal...\n");
            	break;
			}
			printf("\nEl usuario posee %d movimientos.\n", movim);
			printf("\nEl usuario ingreso %.2f pesos.\n", toti);
			printf("\nEl usuario transfirio %.2f pesos.\n", tott);
			printf("\nEl usuario pago %.2f pesos.\n", totp);
			sleep(2);
			return;
			break;
		case '4':
			printf("\nSaliendo...\n");
			sleep(2);
			system("cls");
			return;
			break;
		default:
			system("cls");
			printf("\nError. Ingrese una de las siguientes opciones.\n");
			goto repeat;
			break;
	}
	fclose(ARC);
	}