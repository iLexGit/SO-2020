#include "GestorMissatge.h"

char* generaTrama(int Opcio, char* data){

	char type;
	
	char llargada [3];
	char* String;

	sprintf(llargada,"%X%X",(unsigned int)strlen(data)/16,(unsigned int)strlen(data)%16);

	switch(Opcio){

		case CON_CLI:
			type = '1';
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_CLI_HEADER) + 2 + strlen(data) + 2));
			sprintf(String,"%c%s%s%s",type,CON_CLI_HEADER,llargada,data);

		break;

		case CON_SER_OK:
			type = '1';
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_SER_OK_HEADER) + 2 + strlen(data)));
			sprintf(String,"%c%s%c%c%s",type,CON_CLI_HEADER,llargada[0],llargada[1],data);
		break;		

		case CON_SER_KO:
			type = '1';
			String = (char*)malloc(sizeof(char) * (1 + strlen(CON_SER_KO_HEADER)));
			sprintf(String,"%c%s",type,CON_CLI_HEADER);

		break;

		case SAY_CLI:
            if (strlen(data) > 180){
                return "Missatge massa llarg";
            }
            break;

		case SAY_SER:	
		break;



	
	}
	printf("estás en generatrama\n");
	return String;


}