#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    int primoindirizzo;
    int secondoindirizzo;
    int serve;
    char comando;
    char** stato;
}atti ;
void change(int,int);
void x(int,int);
void y(int,int);
void k(int,int);
void copiastato();
void change_comando(int,int);
void change_comandox(int,int);
void change_comandoy(int,int);
void change_comandok(int,int);
void delete( int, int);
void delete1( int, int);
void delete2( int, int);
void delete3( int, int);
void delete4( int, int);
int undo1(int);
int undo2(int);
int redo2(int);
void salvastato();
void salvastato_delete();
void salvostato_passato(int );
void print(char**,int, int);
void print2(int, int);
void printvuoto(int, int);
void printundo(char**, int, int, int);
void rules();
char** struttura;
int indice_corrente=0;
int presente=0;
atti *storia;
int u;
int contocomandi=0;
int contatorex=0;
char** bigtemp;
int flag=0;
int main(int argc,char *argv[]) {
    int len;
    int ind1, ind2;
    char comando_attuale;
    char buffer[100];
    struttura = (char **) malloc(sizeof(char *));
    storia=(atti*)malloc(sizeof(atti ));
    do {
        fgets(buffer, 100, stdin);
        len = strlen(buffer);
        comando_attuale = buffer[len - 2];
        if(u==0){
            switch (comando_attuale) {
                case 'c':
                    sscanf(buffer, "%d,%d%c", &ind1, &ind2, &comando_attuale);
                    presente++;
                    contocomandi++;
                    if((contatorex<1500 && flag==0) || (flag==1))
                    {if (contocomandi==2 || presente==1)
                        {change_comando(ind1,ind2);
                            salvastato();}
                        else
                            change(ind1,ind2);}
                    else
                        change_comando(ind1,ind2);
                    break;
                case 'd':
                    flag=1;
                    sscanf(buffer, "%d,%d%c", &ind1, &ind2, &comando_attuale);
                    presente++;
                    delete(ind1,ind2);
                    break;
                case 'p':
                    sscanf(buffer, "%d,%d%c", &ind1, &ind2, &comando_attuale);
                    print(struttura,ind1, ind2);
                    break;
                case 'u':
                    flag=1;
                    sscanf(buffer, "%d%c", &ind1, &comando_attuale);
                    u=undo1(ind1);
                    break;
                case 'r':
                    flag=1;break;
                default:break;


            }}
        else{

            switch (comando_attuale) {
                case 'p':
                    sscanf(buffer, "%d,%d%c", &ind1, &ind2, &comando_attuale);
                    print2(ind1, ind2);
                    break;
                case 'u':
                    sscanf(buffer, "%d%c", &ind1, &comando_attuale);
                    u=undo2(ind1);
                    break;
                case 'r':
                    sscanf(buffer, "%d%c", &ind1, &comando_attuale);
                    u=redo2(ind1);
                    break;

                case 'c':sscanf(buffer, "%d,%d%c", &ind1, &ind2, &comando_attuale);
                    rules();
                    if (indice_corrente==0)
                        struttura=malloc(sizeof(char*));
                    change_comando(ind1,ind2);
                    presente++;
                    salvastato();
                    break;

                case 'd':sscanf(buffer, "%d,%d%c", &ind1, &ind2, &comando_attuale);
                    rules();
                    presente++;
                    delete(ind1,ind2);
                    break;

                default:break;
            }
        }}while (comando_attuale!='q');}




void delete( ind1 , ind2){
    if ((ind1 < indice_corrente) && (ind2 < indice_corrente) && (ind2 != 0))
        delete1( ind1, ind2);
    else if (ind1 <= indice_corrente && ind2 > indice_corrente)
        delete2( ind1, ind2);
    else if (ind1 <= indice_corrente && ind2 == indice_corrente && (ind2 != 0))
        delete3( ind1, ind2);
    else if ((ind1 == 0 && ind2 == 0) || (ind1 > indice_corrente && ind2 > indice_corrente) )
        delete4( ind1, ind2);
}

int undo1(ind1){
    u = ind1;
    if (u >= presente)
        u = presente;
    return u;}

void change(ind1,ind2){
    if (ind1 > indice_corrente)
        x(ind1, ind2);
    else if (ind1 <= indice_corrente && ind2 <= indice_corrente)
    {flag=1;
        y(ind1, ind2);}
    else if (ind1 <= indice_corrente && ind2 > indice_corrente)
    { flag=1;
        k(ind1, ind2);}
    return;}


void x(int ind1, int ind2){
    int len;
    int numerorighe;
    char bob[1025];
    char punto[2];
    int i=1;
    numerorighe = (ind2 - ind1) + 1;
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].primoindirizzo = ind1;
    storia[presente].secondoindirizzo = ind2;
    storia[presente].comando = 'x';
    storia[presente].stato=malloc(sizeof(char*)*(numerorighe+1));
    struttura = realloc(struttura, (ind2 + 1) * sizeof(char *));
    while (numerorighe > 0) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        struttura[ind1] = (char *) malloc(sizeof(char) * (1 + len));
        storia[presente].stato[i]=(char *) malloc(sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        strcpy(storia[presente].stato[i], bob);
        ind1++;
        numerorighe--;
        i++;}
    indice_corrente=ind2;
    storia[presente].serve = indice_corrente;
    contatorex++;
    scanf("%s", punto);
    while ('\n' != getchar());
    return;}

void y(int ind1, int ind2){
    int len;
    int numerorighe;
    char bob[1025];
    int i;
    char punto[2];
    numerorighe=ind2-ind1+1;
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].primoindirizzo = ind1;
    storia[presente].secondoindirizzo = ind2;
    storia[presente].comando = 'y';
    storia[presente].stato = (char **) malloc(sizeof(char *) * (numerorighe + 1));
    i = 1;
    while (ind1 <= ind2) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        struttura[ind1] = (char *) realloc(struttura[ind1] ,sizeof(char) * (1 + len));
        storia[presente].stato[i] = (char *) malloc(sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        strcpy(storia[presente].stato[i], bob);
        ind1++;
        i++;
    }
    storia[presente].serve = indice_corrente;
    scanf("%s", punto);
    while ('\n' != getchar());
    return;
}


void k(int ind1, int ind2){
    int len;
    int numerorighe;
    char bob[1025];
    int i;
    char punto[2];
    numerorighe = ind2 - ind1 + 1;
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].primoindirizzo = ind1;
    storia[presente].secondoindirizzo = ind2;
    storia[presente].comando = 'k';
    storia[presente].stato = (char **) malloc(sizeof(char *) * (numerorighe + 1));
    i = 1;
    struttura = realloc(struttura, (ind2 + 1) * sizeof(char *));
    while (ind1 <= indice_corrente) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        struttura[ind1] = (char *)realloc(struttura[ind1],sizeof(char) * (1 + len));
        storia[presente].stato[i] = (char *) malloc(sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        strcpy(storia[presente].stato[i] , bob);
        ind1++;
        i++;
    }
    while (ind1 <= ind2) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        storia[presente].stato[i] = (char *) malloc(sizeof(char) * (1 + len));
        struttura[ind1] = (char *) malloc(sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        strcpy(storia[presente].stato[i] , bob);
        ind1++;
        i++;
    }
    indice_corrente=ind2;
    storia[presente].serve = indice_corrente;
    scanf("%s", punto);
    while ('\n' != getchar());
    return;
}


void print(char** struttura,int ind1, int ind2)
{   int numerorighe;


    if (ind1==0)
    {printf(".\n");
    ind1=1;
    }
    if (ind1 > indice_corrente &&  ind2!=0)   {
        while (ind1<=ind2) {
            printf(".\n");
            ind1++;
        }
    } //  else if (ind1 == 0 && ind2 == 0) {
        //printf(".\n")}
        else if (ind1 <= indice_corrente && ind2 != 0 && ind2 <= indice_corrente) {
        while (ind1<=ind2) {
            printf("%s", struttura[ind1]);
            ind1++;
        }
    } else if (ind1 <= indice_corrente && ind2 != 0 && ind2 > indice_corrente) {
        while (ind1 <= indice_corrente) {
            printf("%s", struttura[ind1]);
            ind1++;
        }
        while (ind1 <= ind2) {
            printf(".");
            printf("\n");
            ind1++;
        }
    }

    return;}

int undo2(int ind1){
    u = u + ind1;
    if (presente <= u)
        u = presente;
    return u;}

int redo2(int ind1){
    int redo;
    redo = ind1;
    u = u - redo;
    if (u < 0)
        u = 0;
    return u;}

void delete1( int ind1 , int ind2){
    int len;
    int temp1, temp2;
    int numerorighe;
    int appoggi;
    appoggi = indice_corrente - ind2;
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].comando = 'z';
    storia[presente].primoindirizzo = ind1;
    storia[presente].secondoindirizzo = ind2;
    if (ind1 == 0)
        ind1 = 1;
    temp1 = ind1;
    temp2 = ind2;
    numerorighe = ind2 - ind1 + 1;
    indice_corrente = indice_corrente - numerorighe;
    while (appoggi != 0) {
        len = strlen(struttura[temp2 + 1]);
        struttura[temp1] = (char *) realloc(struttura[temp1], sizeof(char) * (1 + len));
        strcpy(struttura[temp1], struttura[temp2 + 1]);
        temp1++;
        temp2++;
        appoggi--;
    }
    struttura = realloc(struttura, (indice_corrente + 1) * sizeof(char *));
    storia[presente].serve = indice_corrente;
    salvastato_delete();
}


void delete2(int ind1, int ind2){
    int numerorighe;
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].comando = 'z';
    storia[presente].primoindirizzo = ind1;
    storia[presente].secondoindirizzo = ind2;
    if (ind1 == 0)
        ind1 = 1;
    numerorighe = indice_corrente - ind1 + 1;
    indice_corrente = indice_corrente - numerorighe;
    struttura = realloc(struttura, (indice_corrente + 1) * sizeof(char *));
    storia[presente].serve = indice_corrente;
    salvastato_delete();
}


void delete3(int ind1, int ind2){
    int numerorighe;
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].comando = 'z';
    storia[presente].primoindirizzo = ind1;
    storia[presente].secondoindirizzo = ind2;
    if (ind1 == 0)
        ind1 = 1;
    numerorighe = indice_corrente - ind1 + 1;
    indice_corrente = indice_corrente - numerorighe;
    struttura = realloc(struttura, (indice_corrente + 1) * sizeof(char *));
    storia[presente].serve = indice_corrente;
    salvastato_delete();
}

void delete4(int ind1, int ind2){
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].comando = 'z';
    storia[presente].primoindirizzo = ind1;
    storia[presente].secondoindirizzo = ind2;
    storia[presente].serve = indice_corrente;
    salvastato_delete();

}


void salvastato(){
    int i;
    int len;
    i=1;
    storia = (atti *) realloc(storia, (presente + 1) * sizeof(atti));
    storia[presente].comando='s';
    storia[presente].stato = (char **) malloc(sizeof(char *) * (indice_corrente + 1));
    storia[presente].serve=indice_corrente;
    while (i <= indice_corrente) {
        len = strlen(struttura[i]);
        storia[presente].stato[i] = (char *) malloc((len + 1) * sizeof(char));
        strcpy(storia[presente].stato[i], struttura[i]);
        i++;
        contocomandi=0;
    }
    return;}


void salvastato_delete(){
    int i;
    int len;
    i=1;
    storia[presente].stato = (char **) malloc(sizeof(char *) * (indice_corrente + 1));
    while (i <= indice_corrente) {
        len = strlen(struttura[i]);
        storia[presente].stato[i] = (char *) malloc((len + 1) * sizeof(char));
        strcpy(storia[presente].stato[i], struttura[i]);
        i++;}
    return;}

void salvostato_passato(int trasporto ){
    int i;
    int len;
    i=1;
    bigtemp=(char**)malloc(sizeof(char*)*(1+storia[trasporto-1].serve));
    while (i <= storia[trasporto-1].serve) {
        len = strlen(storia[trasporto-1].stato[i]);
        bigtemp[i] = (char *) malloc((len + 1) * sizeof(char));
        strcpy(bigtemp[i], storia[trasporto-1].stato[i]);
        i++;}
    return;}



void change_comando(ind1,ind2){
    if (ind1 > indice_corrente)
        change_comandox(ind1,ind2);
    else if (ind1 <= indice_corrente && ind2 <= indice_corrente)
        change_comandoy(ind1,ind2);
    else if (ind1 <= indice_corrente && ind2 > indice_corrente)
        change_comandok(ind1, ind2);
    return;}



void change_comandox(int ind1,int ind2){
    int len;
    int numerorighe=0;
    char bob[1025];
    char punto[2];
    numerorighe = (ind2 - ind1) + 1;
    struttura = realloc(struttura, (ind2 + 1) * sizeof(char *));
    while (numerorighe > 0) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        struttura[ind1] = (char *) malloc(sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        ind1++;
        numerorighe--;}
    indice_corrente = ind2;
    scanf("%s", punto);
    while ('\n' != getchar());
    return;}



void change_comandoy(int ind1,int ind2){
    int len;
    char bob[1025];
    char punto[2];
    while (ind1 <= ind2) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        struttura[ind1] = (char *)realloc(struttura[ind1],sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        ind1++;
    }
    scanf("%s", punto);
    while ('\n' != getchar());
    return;
}
void change_comandok(int ind1,int ind2){
    int len;
    char bob[1025];
    char punto[2];
    struttura = realloc(struttura, (ind2 + 1) * sizeof(char *));
    while (ind1 <= indice_corrente) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        struttura[ind1] = (char *)realloc(struttura[ind1],sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        ind1++;
    }
    while (ind1 <= ind2) {
        fgets(bob, 1025, stdin);
        len = strlen(bob);
        struttura[ind1] = (char *) malloc(sizeof(char) * (1 + len));
        strcpy(struttura[ind1], bob);
        ind1++;
    }
    indice_corrente = ind2;
    scanf("%s", punto);
    while ('\n' != getchar());
    return;
}


void printvuoto(int ind1,int ind2){

    if(ind1==0) {
        printf(".");
        printf("\n");
        ind1=1;
    }
    while (ind1<=ind2) {
        printf(".");
        printf("\n");
        ind1++;
    }
}


void print2(ind1,ind2) {
    int trasporto;
    int ad1, ad2;
    int i = 1;
    int len;
    int j;
    trasporto = presente - u;
    if (storia[trasporto].comando == 's' || storia[trasporto].comando == 'z')
        printundo(storia[trasporto].stato, ind1, ind2, storia[trasporto].serve );
    else if ((trasporto!=1) && (storia[trasporto].comando == 'k' || storia[trasporto].comando == 'y' || storia[trasporto].comando == 'x')) {
        salvostato_passato(trasporto);
        if (storia[trasporto].comando=='x'){
            bigtemp = (char **) realloc(bigtemp, (storia[trasporto].serve+1) * sizeof(char *));
            i=1;
            j=storia[trasporto-1].serve;
            j++;
            while(j<=storia[trasporto].serve){
                len=strlen(storia[trasporto].stato[i]);
                bigtemp[j]=malloc(sizeof(char)*(len+1));
                strcpy(bigtemp[j],storia[trasporto].stato[i]);
                i++;
                j++;
            }
            j--;}
        if (storia[trasporto].comando=='y'){
            ad1=storia[trasporto].primoindirizzo;
            ad2=storia[trasporto].secondoindirizzo;
            i=1;
            while(ad1<=ad2){
                len=strlen(storia[trasporto].stato[i]);
                bigtemp[ad1]=realloc(bigtemp[ad1],sizeof(char)*(len+1));
                strcpy(bigtemp[ad1],storia[trasporto].stato[i]);
                ad1++;
                i++;}
            j=storia[trasporto].serve;}
        if (storia[trasporto].comando=='k'){
            ad1=storia[trasporto].primoindirizzo;
            ad2=storia[trasporto].secondoindirizzo;
            bigtemp = (char **) realloc(bigtemp, (storia[trasporto].serve+1) * sizeof(char *));
            i=1;
            while(ad1<=storia[trasporto-1].serve){
                len=strlen(storia[trasporto].stato[i]);
                bigtemp[ad1]=realloc(bigtemp[ad1],sizeof(char)*(len+1));
                strcpy(bigtemp[ad1],storia[trasporto].stato[i]);
                i++;
                ad1++;
            }
            while(ad1<=ad2){
                len=strlen(storia[trasporto].stato[i]);
                bigtemp[ad1]=malloc(sizeof(char)*(len+1));
                strcpy(bigtemp[ad1],storia[trasporto].stato[i]);
                ad1++;
                i++;}
            j=storia[trasporto].serve;
        }
        printundo(bigtemp, ind1, ind2,j);
    }
    else if(trasporto==0){
        printvuoto(ind1,ind2);}

}
void printundo(char** evoc, int ind1,int ind2,int indcurr){
    if (ind1==0)
    {printf(".\n");
    ind1=1;
    }
    if (ind1 > indcurr && ind2!=0) {
        while (ind1<=ind2) {
            printf(".\n");
            ind1++;}
    }

    else if (ind1 <= indcurr && ind2 != 0 && ind2 <= indcurr) {
        while (ind1<=ind2) {
            printf("%s", evoc[ind1]);
            ind1++;
        }
    } else if (ind1 <= indcurr && ind2 != 0 && ind2 > indcurr) {
        while (ind1 <= indcurr) {
            printf("%s", evoc[ind1]);
            ind1++;
        }
        while (ind1 <= ind2) {
            printf(".");
            printf("\n");
            ind1++;
        }
    }

    return;}

void  rules(){
    presente=presente-u;
    storia=(atti*)realloc(storia, sizeof(atti)*(presente+1));
    copiastato();
    u=0;
    return;}

void copiastato(){
    int i;
    int len;
    int j;
    int ad1, ad2;
    i=1;
    if (storia[presente].comando == 's' || storia[presente].comando == 'z')
    {struttura=(char **) realloc(struttura,(storia[presente].serve+ 1) * sizeof(char*));
        while (i <= storia[presente].serve) {
            len = strlen(storia[presente].stato[i]);
            struttura[i] = (char *) malloc((len + 1) * sizeof(char));
            strcpy(struttura[i] , storia[presente].stato[i]);
            i++;}
        indice_corrente=storia[presente].serve;
    }
    else if (storia[presente].comando == 'k' || storia[presente].comando == 'y' || storia[presente].comando == 'x'){
        {
            struttura=(char **) realloc(struttura,(storia[presente-1].serve+ 1) * sizeof(char*));
            while (i <= storia[presente-1].serve) {
                len = strlen(storia[presente-1].stato[i]);
                struttura[i] = (char *) malloc((len + 1) * sizeof(char));
                strcpy(struttura[i] , storia[presente-1].stato[i]);
                i++;}
            indice_corrente=storia[presente-1].serve;
        }
        if (storia[presente].comando=='x'){
            struttura = (char **) realloc(struttura, (storia[presente].serve+1) * sizeof(char *));
            i=1;
            j=storia[presente-1].serve;
            j++;
            while(j<=storia[presente].serve){
                len=strlen(storia[presente].stato[i]);
                struttura[i]=malloc(sizeof(char)*(len+1));
                strcpy(struttura[i],storia[presente].stato[i]);
                i++;
                j++;
            }
            indice_corrente=storia[presente].serve;}
        if (storia[presente].comando=='y'){
            ad1=storia[presente].primoindirizzo;
            ad2=storia[presente].secondoindirizzo;
            i=1;
            while(ad1<=ad2){
                len=strlen(storia[presente].stato[i]);
                struttura[ad1]=realloc(struttura[ad1],sizeof(char)*(len+1));
                strcpy(struttura[ad1],storia[presente].stato[i]);
                ad1++;
                i++;}
            indice_corrente=storia[presente-1].serve;
        }
        if (storia[presente].comando=='k'){
            ad1=storia[presente].primoindirizzo;
            ad2=storia[presente].secondoindirizzo;
            struttura = (char **) realloc(struttura, (storia[presente].serve+1) * sizeof(char *));
            i=1;
            while(ad1<=indice_corrente){
                len=strlen(storia[presente].stato[i]);
                struttura[ad1]=realloc(struttura[ad1],sizeof(char)*(len+1));
                strcpy(struttura[ad1],storia[presente].stato[i]);
                i++;
                ad1++;
            }
            while(ad1<=ad2){
                len=strlen(storia[presente].stato[i]);
                struttura[ad1]=malloc(sizeof(char)*(len+1));
                strcpy(struttura[ad1],storia[presente].stato[i]);
                ad1++;
                i++;}
            indice_corrente=storia[presente].serve;
        }}
    else if(presente==0) {
        indice_corrente = 0;
        struttura=realloc(struttura, sizeof(char*)*0);
    }
}



