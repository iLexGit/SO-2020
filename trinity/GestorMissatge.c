#include "GestorMissatge.h"

char* generaTrama(int Opcio, char* data){

	char type;
	
	char llargada[2];
	char* String;

//    llargada[0] = (char)((int)strlen(data)/255);
//    llargada[1] = (char)((int)strlen(data)%255);
//    if(!strlen(data)%255){
//        llargada[1] = '0';
//    }
//    if(strlen(data)<=255){
//        llargada[0] = '0';
//    }

	switch(Opcio){

		case CON_CLI:
			type = '1';
			printf("%s\n%d\n%d\n", data, (int)strlen(data), (int)llargada[1]);
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_CLI_HEADER) + 2 + strlen(data)));
			//sprintf(String,"%c%s%c%c%s",type,CON_CLI_HEADER,llargada[0],llargada[1],data);

		break;

		case CON_SER_OK:
			type = '1';
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_SER_OK_HEADER) + 2 + strlen(data)));
			sprintf(String,"%c%s%c%c%s",type,CON_CLI_HEADER,llargada[0],llargada[1],data);
		break;		

		case CON_SER_KO:
			type = '1';
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_SER_KO_HEADER)));
			sprintf(String,"%c%s%c%c",type,CON_CLI_HEADER,llargada[0],llargada[1]);

		break;

		case SAY_CLI:
            if (strlen(data) > 180){
                return "Missatge massa llarg";
            }
            break;

		case SAY_SER:	
		break;



	
	}
	printf("Has generat aquesta tarama:\n%s\n", String);
	return String;


}

Trama llegeixTrama(int conn){
    Trama trama;
    int a,b;
    read(conn, &trama.type, 1);
    trama.header = readUntil(conn, ']');

//    read(conn, &trama.length[0], 1);
//    if(trama.length[0] == '0'){
//        a = atoi(&trama.length[0]);
//    }else{
//        a = ((int)trama.length[0])*255;
//    }
//    read(conn, &trama.length[1], 1);
//    if(trama.length[1] == '0'){
//        b = atoi(&trama.length[0]);
//    }else{
//        b = (int)(trama.length[1]);
//    }
//
//    read(conn, &trama.data, a+b);
    return trama;
}