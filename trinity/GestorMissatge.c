#include "GestorMissatge.h"

Trama generaTrama(int Opcio, char* data){

	char type;
	
	char llargada [2];
	char* String;
    unsigned int llargadeta;
    //llargada = strlen(data);
    llargada[0] = strlen(data)/255;
    llargada[1] = strlen(data)%255;
    Trama trama;

	switch(Opcio){

		case CON_CLI:

			//String = (char*)malloc(sizeof(char) * (1 + strlen(CON_CLI_HEADER) + 2 + strlen(data) + 2));
			//sprintf(String,"%c%s%c%c%s",type,CON_CLI_HEADER,llargada[0],llargada[1],data);
			printf("%s\n",data);
			trama.header = CON_CLI_HEADER;
			trama.type = '1';
			trama.length = strlen(data);
			trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
			strcpy(trama.data,data);
			printf("%s\n",trama.data);



		break;

		case CON_SER_OK:
			type = '1';
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_SER_OK_HEADER) + 2 + strlen(data)));
			//sprintf(String,"%c%s%c%c%s",type,CON_CLI_HEADER,llargada[0],llargada[1],data);
		break;		

		case CON_SER_KO:
			type = '1';
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_SER_KO_HEADER)));
			//sprintf(String,"%c%s%c%c",type,CON_CLI_HEADER,llargada[0],llargada[1]);

		break;

		case SAY_CLI:
            if (strlen(data) > 180){
                //return "Missatge massa llarg";
            }
            break;

		case SAY_SER:	
		break;



	
	}
	printf("estás en generatrama\n");
	//printf("%s\n",String);
	return trama;


}

Trama llegeixTrama(int conn){
    Trama trama;
    char aux;
    int a,b;
    read(conn, &trama.type, 1);
    trama.header = readUntil(conn, ']');
    read(conn, &trama.length,2);
    trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
    trama.data[trama.length] = '\0';
    read(conn, &trama.data, trama.length);

    printf("%d\n",trama.length);
    printf("Heloo\n");

    //read(conn, &trama.length[0], 1);
//    if(trama.length[0] == '0'){
//        a = atoi(&trama.length[0]);
//    }else{
//        a = ((int)trama.length[0])*255;
//    }
    //read(conn, &trama.length[1], 1);
//    if(trama.length[1] == '0'){
//        b = atoi(&trama.length[0]);
//    }else{
//        b = (int)(trama.length[1]);
//    }
//


    return trama;
}