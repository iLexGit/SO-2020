
#ifndef PRACTICA_SO_GESTORMISSATGE_H
#define PRACTICA_SO_GESTORMISSATGE_H

#include "includes.h"
#include "main.h"

Trama generaTrama(int Opcio, char* data);

Trama  generaTramaAudio(char*,int);

Trama llegeixTrama(int);

#define CON_CLI 1
#define CON_SER_OK 2
#define CON_SER_KO 22
#define SAY_CLI 3
#define SAY_SER 4
#define SHAUDIO_CLI 5
#define SHAUDIO_SER 6
#define DOWNLOAD_CLI 7
#define DOWNLOAD_SER_ERR 8
#define DOWNLOAD_SER_DATA 9
#define DOWNLOAD_SER_EOF 10
#define EXIT_CLI 11
#define EXIT_SER_OK 12
#define EXIT_SER_KO 13
#define BROAD_CLI 14
#define BROAD_SER 15

#define CON_CLI_HEADER "[TR_NAME]"
#define CON_SER_OK_HEADER "[CONOK]"
#define CON_SER_KO_HEADER "[CONKO]"
#define CON_CLI_SAY_HEADER "[MSG]"
#define CON_SER_SAY_HEADER "[MSGOK]"
#define SHAUDIO_CLI_HEADER "[SHOW_AUDIOS]"
#define SHAUDIO_SER_HEADER "[LIST_AUDIOS]"
#define DOWNLOAD_CLI_HEADER "[AUDIO_RQST]"
#define DOWNLOAD_SER_ERR_HEADER "[AUDIO_KO]"
#define DOWNLOAD_SER_DATA_HEADER "[AUDIO_RSPNS]"
#define DOWNLOAD_SER_EOF_HEADER "[AUDIO_EOF]"
#define EXIT_CLI_HEADER "[]"
#define EXIT_SER_OK_HEADER "[CONOK]"
#define EXIT_SER_KO_HEADER "[CONKO]"
#define BROAD_CLI_HEADER "[BROADCAST]"
#define BROAD_SER_HEADER "[MSGOK]"

#endif
