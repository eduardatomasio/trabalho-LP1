#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<time.h>
#include <stdbool.h>

#define NUM_itens 5
#define TAM_NOME 20
char animais[NUM_itens][TAM_NOME] = {
        "cachorro",
        "gato",
        "elefante",
        "girafa",
        "vaca"
    };
char estados[NUM_itens][TAM_NOME] = {
    "bahia",
    "acre",
    "amazonas",
    "tocantins",
    "pernambuco"
};
char frutas[NUM_itens][TAM_NOME] = {
    "morango",
    "banana",
    "tangerina",
    "abacate",
    "tomate"
};

typedef struct jogador{
   char *nome, *usadas;
   int vidas;
}Jogador;

void inicializa_palavra(char *palavra, char *palavra_oculta, Jogador j){
    int escolha;
    srand(time(NULL)); 
    int random = rand() % NUM_itens;

    printf("\nVoce deseja qual tema, %s?", j.nome);
    printf("\n1-Animais");
    printf("\n2-Estados");
    printf("\n3-Frutas");
    printf("\nSua escolha: ");
    scanf("%d", &escolha);

    while(1){
        if(escolha == 1){
            strcpy(palavra, animais[random]);
            break;
        }else if(escolha == 2){
            strcpy(palavra, estados[random]);
            break;
        }else if(escolha ==3){
            strcpy(palavra, frutas[random]);
            break;
        }else
            printf("\nEscolha uma valor vÃ¡lido");
    }

    strcpy(palavra_oculta, palavra);
    for(int i = 0; i<strlen(palavra_oculta); i++){
        palavra_oculta[i] = '_';
    }
}

void salvarArquivo(Jogador *jogador, char *todas_letras){
    FILE *arq = fopen("historico.txt","a");
    if(arq){
        fprintf(arq,"\nNome: %s\n", jogador->nome);
        if (todas_letras) {
            fprintf(arq, "Letras usadas: %s\n", todas_letras);
        } else {
            fprintf(arq, "Nenhuma letra usada.\n");
        }
        fclose(arq);
    } else{
        printf("NÃ£o foi possÃ­vel abrir o arquivo.\n");
    }
}

void imprimirHistorico() {
    FILE *arq = fopen("historico.txt", "r");
    if (arq) {
        char linha[100]; // Tamanho arbitrÃ¡rio para cada linha
        while (fgets(linha, sizeof(linha), arq) != NULL) {
            printf("%s", linha);
        }
        fclose(arq);
    } else {
        printf("NÃ£o foi possÃ­vel abrir o arquivo.\n");
    }
}


void inicializa_jogo(Jogador *jogador){
    jogador->nome = (char *) malloc(50*sizeof(char));
    if(jogador->nome){
        printf("\nDigite seu nome: ");
        scanf("%s", jogador->nome);
    }else{
        printf("NÃ£o foi possÃ­vel alocar o nome do jogador");
    }
    jogador->vidas = 6;
    jogador->usadas = (char *)malloc(1 * sizeof(char));
    jogador->usadas[0] = '\0';
}

void imprime_forca(Jogador j){
    int i = j.vidas;
    switch(i){
    case 6:
        printf("\n\n------------------------\n");
        printf("|                       |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        break;
    
    case 5:
        printf("------------------------\n");
        printf("|                       |\n");
        printf("|                       0\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        break;
    case 4:
        printf("------------------------\n");
        printf("|                       |\n");
        printf("|                       0\n");
        printf("|                       |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        break;
    
     case 3:
        printf("------------------------\n");
        printf("|                       |\n");
        printf("|                       0\n");
        printf("|                      /|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        break;

    case 2:
        printf("------------------------\n");
        printf("|                       |\n");
        printf("|                       0\n");
        printf("|                      /|\\\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        break;
    
    case 1:
        printf("------------------------\n");
        printf("|                       |\n");
        printf("|                       0\n");
        printf("|                      /|\\\n");
        printf("|                        \\\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        break;
    
    case 0:
        printf("------------------------\n");
        printf("|                       |\n");
        printf("|                       0\n");
        printf("|                      /|\\\n");
        printf("|                      / \\\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        break;
    default:
        break;
    }    
}


void letras_usadas(char **usadas, char letra,Jogador *jogador) {
    int tamanho;
    if(*usadas==NULL)
        tamanho = 0;
    else    
        tamanho = strlen(*usadas);
        
    *usadas = (char*) realloc(*usadas, (tamanho + 2) * sizeof(char)); // +2 para incluir o novo caractere e o '\0'
    (*usadas)[tamanho] = letra;
    (*usadas)[tamanho + 1] = '\0'; // Adicionar o caractere nulo para marcar o final da string
    for (int i = 0; i <= tamanho; i++)
        printf(" %c", (*usadas)[i]);
    printf("\n");  // Adiciona nova linha apï¿½s imprimir todas as letras
}

int verificar_letra(char *usadas, char letra){
    if(usadas ==NULL)
        return 0;
    
    for(int i = 0; i< strlen(usadas); i++){
        if(usadas[i] == letra){
            return 1;
        }
    }
    return 0;
}

void jogo_main(char palavra[TAM_NOME], char palavra_oculta[TAM_NOME], Jogador *j){
     
     char letra;
     char *todas_letras = NULL;

    while(strstr(palavra_oculta,"_")){
        bool acertou = false;
        imprime_forca(*j);
        if(j->vidas==0){
            printf("\nVocÃª perdeu!");
            break;
        }

        printf("\nAdvinhe: ");

        for(int i =0; i<strlen(palavra_oculta);i++){
            printf("%c ", palavra_oculta[i]);
        }
        printf("\nSeu chute: ");
        scanf(" %c", &letra);
        printf("\n");
        letra = tolower(letra);
        
        if(verificar_letra(j->usadas, letra)){
            printf("\nVocÃª jÃ¡ digitou essa letra, por favor, digite outra!\n");
            continue;
        };
        letras_usadas(&j->usadas, letra,j);

        for(int i =0; i<strlen(palavra_oculta);i++){
            if(letra==palavra[i]){
                acertou = true;
                palavra_oculta[i] = letra;
            }
    }
        if(acertou==false)
            j->vidas--;
        
    }
    if (j->usadas) {
        todas_letras = strdup(j->usadas); // strdup aloca memÃ³ria para a nova string e copia a string existente
    } else {
        todas_letras = strdup(""); // Se nÃ£o houver letras usadas, criar uma string vazia
    }

    if(j->vidas!=0){
        imprime_forca(*j);
        for(int i =0; i<strlen(palavra_oculta);i++){
            printf("%c ", palavra[i]);
        }
        printf("\nVocÃª ganhou o jogo!");
    }else{
        printf("\nA palavra era: ");
         for(int i =0; i<strlen(palavra_oculta);i++){
            printf("%c ", palavra[i]);
        }
    }
    printf("\n");
    //printf("Historico de jogadas: \n");
    salvarArquivo(j, todas_letras);
    //imprimirHistorico();
    printf("\n");
}

int main(){
    setlocale(LC_ALL, "portuguese");
    
    char palavra[TAM_NOME];
    char palavra_oculta[TAM_NOME];
    
    Jogador j;

    inicializa_jogo(&j);
    inicializa_palavra(&palavra, &palavra_oculta, j);
    jogo_main(palavra,palavra_oculta, &j);

    
    
    return 0;
}