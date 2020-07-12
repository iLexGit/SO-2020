#include "GestorMissatge.h"

Trama generaTrama(int Opcio, char* data){
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
                printf("massa llarg\n");
            }
            else{
                printf("printf de data %s\n",data);
                trama.header = (char*) malloc(strlen(CON_CLI_SAY_HEADER) * sizeof(char) + 1);
                strcpy(trama.header,CON_CLI_SAY_HEADER);
                //trama.header = CON_SER_OK_HEADER;
                trama.type = '2';
                trama.length = strlen(data);
                trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
                strcpy(trama.data,data);
                printf("printf de trama.data generatrama %s\n",trama.data);
            }
            break;

        case SAY_SER:
            trama.header = (char*) malloc(strlen(CON_SER_SAY_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,CON_SER_SAY_HEADER);
            //trama.header = CON_SER_OK_HEADER;
            trama.type = '2';
            trama.length = 0;
            //trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            //strcpy(trama.data,data);
            break;
        case SHAUDIO_CLI:
            trama.header = (char*) malloc(strlen(SHAUDIO_CLI_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,SHAUDIO_CLI_HEADER);
            //trama.header = CON_SER_OK_HEADER;
            trama.type = '4';
            trama.length = 0;
            break;

        case SHAUDIO_SER:
            trama.header = (char*) malloc(strlen(SHAUDIO_SER_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,SHAUDIO_SER_HEADER);

            trama.type = '4';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);

            break;


        case DOWNLOAD_CLI:

            trama.header = (char*) malloc(strlen(DOWNLOAD_CLI_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,DOWNLOAD_CLI_HEADER);

            trama.type = '5';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);


            break;

        case DOWNLOAD_SER_DATA:
            trama.header = (char*) malloc(strlen(DOWNLOAD_SER_DATA_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,DOWNLOAD_SER_DATA_HEADER);

            trama.type = '5';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);
            break;

        case DOWNLOAD_SER_EOF:
            trama.header = (char*) malloc(strlen(DOWNLOAD_SER_EOF_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,DOWNLOAD_SER_EOF_HEADER);

            trama.type = '5';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);
            break;


        case DOWNLOAD_SER_ERR:
            trama.header = (char*) malloc(strlen(DOWNLOAD_SER_ERR_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,DOWNLOAD_SER_ERR_HEADER);

            trama.type = '5';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);
            break;

        case EXIT_CLI:
            trama.header = (char*) malloc(strlen(EXIT_CLI_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,EXIT_CLI_HEADER);

            trama.type = '6';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data,data);

            break;

        case EXIT_SER_OK:
            trama.header = (char*) malloc(strlen(EXIT_SER_OK_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,EXIT_SER_OK_HEADER);

            trama.type = '6';
            trama.length = 0;

            break;

        case EXIT_SER_KO:
            trama.header = (char*) malloc(strlen(EXIT_SER_KO_HEADER) * sizeof(char) + 1);
            strcpy(trama.header,EXIT_SER_KO_HEADER);

            trama.type = '6';
            trama.length = 0;

            break;

        case BROAD_CLI:
            trama.header = (char*)malloc(strlen(BROAD_CLI_HEADER)*sizeof(char)+1);
            strcpy(trama.header, BROAD_CLI_HEADER);

            trama.type = '3';
            trama.length = strlen(data);
            trama.data = (char*) malloc(trama.length * sizeof(char) + 1);
            strcpy(trama.data, data);
            break;

        case BROAD_SER:
            trama.header = (char*)malloc(strlen(BROAD_SER_HEADER)*sizeof(char)+1);
            strcpy(trama.header, BROAD_SER_HEADER);

            trama.type = '3';
            trama.length = 0;
            break;
    }
    printf("estás en generatrama\n");
    //printf("%s\n",trama.data);
    return trama;


}

Trama generaTramaAudio(char* data, int length){

    Trama trama;
    trama.header = (char*) malloc(strlen(DOWNLOAD_SER_DATA_HEADER) * sizeof(char) + 1);
    strcpy(trama.header,DOWNLOAD_SER_DATA_HEADER);

    trama.type = '5';
    trama.length = (short)length;
    trama.data = (char*) malloc(trama.length * sizeof(char) +1);
    //strcpy(trama.data,data);
    for (int i = 0; i < length; ++i) {
        trama.data[i] = data[i];
    }

    return trama;

}

Trama llegeixTrama(int conn){
    Trama trama;
    read(conn, &trama.type, 1);
    if (trama.type >= '0' && trama.type <= '6') {


        trama.header = readUntil(conn, ']');
        trama.header = (char *) realloc(trama.header, sizeof(char) * (strlen(trama.header)) + 1);
        trama.header[strlen(trama.header) + 1] = '\0';
        trama.header[strlen(trama.header)] = ']';

        printf("llegeixtrma2\n");
        read(conn, &trama.length, 2);
        trama.data = (char *) malloc(trama.length * sizeof(char) + 1);

        if (trama.length != 0) {
            read(conn, trama.data, trama.length);
            trama.data[trama.length] = '\0';
            printf("llegeixtrma3\n");
            printf("%d\n", trama.length);
            printf("Heloo\n");

        }
    }

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