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
			printf("printf de data %s\n",data);
			trama.header = (char*) malloc(strlen(CON_CLI_HEADER) * sizeof(char) + 1);
			//trama.header = CON_CLI_HEADER;
			strcpy(trama.header,CON_CLI_HEADER);
			trama.type = '1';
			trama.length = strlen(data);
			trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
			strcpy(trama.data,data);
			printf("printf de trama.data generatrama %s\n",trama.data);



		break;

		case CON_SER_OK:
            printf("printf de data %s\n",data);
            trama.header = (char*) malloc(strlen(CON_SER_OK_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,CON_SER_OK_HEADER);
            //trama.header = CON_SER_OK_HEADER;
            trama.type = '1';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);
            printf("printf de trama.data generatrama %s\n",trama.data);

			//sprintf(String,"%c%s%c%c%s",type,CON_CLI_HEADER,llargada[0],llargada[1],data);
		break;		

		case CON_SER_KO:
            trama.header = (char*) malloc(strlen(CON_SER_KO_HEADER) * sizeof(char) + 1);
            trama.header = CON_SER_KO_HEADER;
            trama.type = '1';
            trama.length = 0;
            /*trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);*/

		break;

		case SAY_CLI:
            if (strlen(data) > 180){
                //return "Missatge massa llarg";
            }
            else{
                printf("printf de data %s\n",data);
                trama.header = (char*) malloc(strlen(CON_SER_CLI_HEADER) * sizeof(char) + 1);
                strcpy(trama.header,CON_SER_CLI_HEADER);
                //trama.header = CON_SER_OK_HEADER;
                trama.type = '2';
                trama.length = strlen(data);
                trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
                strcpy(trama.data,data);
                printf("printf de trama.data generatrama %s\n",trama.data);
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
    trama.header = (char*)realloc(trama.header,sizeof(char) * (strlen(trama.header) + 1));
    trama.header[strlen(trama.header)] = ']';

    read(conn, &trama.length,2);
    trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
    //trama.data[trama.length] = '\0';
    read(conn, trama.data, trama.length);

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