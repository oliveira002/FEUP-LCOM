#include "leaderboard.h"

extern enum STATE GameState;
extern uint8_t *BoardMenu;
extern xpm_image_t imgBoard;

extern uint8_t *font;
extern xpm_image_t imgFont;

extern Character letters[40];

void leaderboard(int Score) {

    FILE *fptr;
    char * buffer1 = 0;
    long length;
    size_t size;
    int scores[5];

    fptr = fopen("/home/lcom/labs/g04/proj/src/leaderboard.txt","r");

   if (fptr){
        fseek (fptr, 0, SEEK_END);
        length = ftell (fptr);
        fseek (fptr, 0, SEEK_SET);
        buffer1 = malloc(length);
        if (buffer1){
            fread (buffer1, 1, length, fptr);
        }
            fclose(fptr);
        }

        if (buffer1)
        {
            int i = 0;
            char* auxStr =  malloc(65536);
            char *p1, *p2;
            while(1) {
                p1 = strstr(buffer1, "-");
                if (p1) {
                    p2 = strstr(buffer1, "\n");
                    if (p2){
                        size = p2-p1;
                        memset(auxStr,0,65536);
                        memcpy(auxStr,(p1+2),size-2);
                        scores[i] = atoi(auxStr);
                        buffer1 = p2+1;
                        i++;
                    } else {
                        size = strlen(p1) - 1;
                        memset(auxStr,0,65536);
                        memcpy(auxStr,(p1+2),size);
                        scores[i] = atoi(auxStr);
                        break;
                    }
                }
                else {
                    break;
                }
            }
            free(auxStr);
            free(p1);
            free(p2);
        }

    fptr = fopen("/home/lcom/labs/g04/proj/src/leaderboard.txt","w");
    int j = 0;
    int vsize = 5;
    for(int i = 0; i < vsize; i++) {
        if(Score > scores[i]) {
            fprintf(fptr,"%d - %d\n",j+1,Score);
            Score = 0;
            i--;
            j++;
            vsize--;
        } else {
            fprintf(fptr,"%d - %d\n",j+1,scores[i]);
            j++;
        }
    }

    //printf com o resultado do jogador

    fclose(fptr);
    free(scores);
    free(buffer1);
}


void BoardTimerHandler() {
}

void BoardHandlerKBC(enum KEY k) {
  switch (k)
  {
  case ESC:
    GameState = MENU;
    break;
  default:
    break;
  }
}

void drawDefBoard() {
  draw_pix_map(0,0,BoardMenu,imgBoard);
  drawBoard();
}

void drawBoard() {
    FILE *fptr;
    char * buffer1 = 0;
    long length;
    size_t size;
    int scores[5];

    fptr = fopen("/home/lcom/labs/g04/proj/src/leaderboard.txt","r");

    if (fptr){
        fseek (fptr, 0, SEEK_END);
        length = ftell (fptr);
        fseek (fptr, 0, SEEK_SET);
        buffer1 = malloc(length);
        if (buffer1){
            fread (buffer1, 1, length, fptr);
        }
            fclose(fptr);
    }
    if (buffer1){
        int i = 0;
        char* auxStr =  malloc(65536);
        char *p1, *p2;
        while(1) {
            p1 = strstr(buffer1, "-");
            if (p1) {
                p2 = strstr(buffer1, "\n");
                if (p2){
                    size = p2-p1;
                    memset(auxStr,0,65536);
                    memcpy(auxStr,(p1+2),size-2);
                    scores[i] = atoi(auxStr);
                    buffer1 = p2+1;
                    i++;
                } else {
                    size = strlen(p1) - 1;
                    memset(auxStr,0,65536);
                    memcpy(auxStr,(p1+2),size);
                    scores[i] = atoi(auxStr);
                    break;
                }
            }
            else {
                break;
            }
        }
            free(auxStr);
            free(p1);
            free(p2);
    }
    fclose(fptr);
    
    int startPosX = 576;
    int startPosY = 400;
    char score[4];
    for(int j = 0;j<5;j++){
        char score[4];
        sprintf(score,"%d",scores[j]);
        for(int i = 0; i < (int) strlen(score); i++) {
            draw_letter_map(startPosX - ((int)(score[i] - '0')*37) + i * 20 ,startPosY,font,imgFont,letters[(int)(score[i] - '0') + 26].x,letters[(int)(score[i] - '0') + 26].y);
        }
        startPosY+=48;
    }
    free(score);
    free(scores);
    free(buffer1);
}
