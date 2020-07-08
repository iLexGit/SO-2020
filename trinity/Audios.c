
#include "Audios.h"

char* checksum(char* path){

    int pfd[2];
    char caracter;
    char* md5sum = (char*) malloc(1);
    int i =0;
    char* retorno;

    if (pipe (pfd) < 0){
        //write(1,ERRPipe,strlen(ERRPipe));
        printf("not open de pipe\n");
    }

    switch (fork()){
        case -1:
            printf("errorsito\n");
            break;
        case 0: //fill


            printf("soc el fill i acabo de enxier\n");
            printf("%s\n",path);
            dup2 (pfd[1],1);

            execl("./md5.sh","",path,NULL);



            exit(0);


            break;

        default: // pare
            wait(NULL);
            close(pfd[1]);
            printf("soc el pare i ara escriure\n");

            while(1){
                if(read(pfd[0],&caracter,1)){
                    md5sum[i] = caracter;
                    printf("%d\n",i);
                    printf("%s\n",md5sum);
                    i++;
                    md5sum=(char*) realloc(md5sum,i+1);
                }
                else{
                    break;
                }
            }


    }
    retorno =selectWord(1,md5sum);
    free(md5sum);

    printf("%s\n",retorno);

    return retorno;
}