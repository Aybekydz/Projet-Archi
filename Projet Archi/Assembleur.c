#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Lecture du fichier d'entree
/*
int InCharTab (char elt[], char* T[], int n){
    Fonction qui teste si une chaîne de caractère est dans un tableau de chaînes de caractère
    IN : char elt : la chaine de caractère à tester
         char* T[] : tableau de chaines de caractères
         int n : longueur du tableau T
    OUT : 1 si l'élément est dans le tableau
          0 sinon

    int lelt = strlen(elt), cpt = 0;
    for(int i=0; i<n; i++){
        cpt = 0;
        if (strlen(T[i])!=lelt)
            continue;
        for(int j=0; j<lelt; j++){
            if (elt[j]!=T[j])
                cpt += 1;
        }
        if (cpt!=lelt)
            continue;
        return 1;
    }
    return 0;
}
*/

// Fonction qui prend une instruction en argument puis va le traduire en decimal
const char *code_instruction[] = {"pop", "ipop", "push", "ipush", "push#", "jmp", "jnz", "call", "ret", "read", "write", "op", "rnd", "dup", "halt"};

int instruction_to_decimal(const char *instruction){
    int lg = sizeof(code_instruction) / sizeof(code_instruction[1]);
    //si la valeur de l'instruction passée en argument est exactement la meme que celle contenue dans le code_instruction alors on retourne l'indice du code en question
    if (strcmp(code_instruction[lg-1], instruction) == 0){
        return 99;
    }
    for (int i = 0; i < 15; i++){
        if ((strcmp(code_instruction[i], instruction)) == 0) {
            return i;
        }
    }
    return -1; // code erreur, aucune instruction correcte n'a ete trouvee
}

// Convertisseur d'un nombre decimal en hexadecimal
char *decimal_to_hexa(int nb){
    static char hexa[100];
    int indice = 0;
    int reste;
    char char_hexa[] = "0123456789abcdef";
    char temp_hexa[100];

    // Cas si nb = 0. Oui j'ai du faire ce cas parce que sinon j'avais un segmentation fault quand je mettais <=0 ou <-1
    if (nb == 0){
        hexa[indice] = '0';
        hexa[indice++] = '0';
        return hexa; 
    }

    // Conversion de decimal à hexadecimal en utilisant le modulo 16
    while (nb != 0){
        reste = nb % 16;
        temp_hexa[indice++] = char_hexa[reste];
        nb /= 16;
    }

    // On remonte à l'envers pour obtenir notre resultat (comme pour la traduction en base 2)
    for (int r = 0; r < indice; r++){
        hexa[r] = temp_hexa[indice - r - 1];
    }
    return hexa;
}

//Il faut rajouter deux fonctions pour rajouter i) instruction - des 0 pour avoir deux octets ii) registres - des 0 pour avoir 4 octets

// i) Completion de la valeur hexadecimal des instructions
void complete_zero_instruct(char *instruction){
    //Si on qu'un seul nombre pour l'hexadecimal, on va : creer une chaine temp dans laquelle, concatener 0, concatener l'hexa d'instruction 
    if (strlen(instruction) < 2){
        char temp[3] = "";
        strcat(temp, "0");
        strcat(temp, instruction);
        strcpy(instruction, temp);
    }
}


// ii) Completion de la valeur des registres sur 4 octets

/*
zsh: trace trap  "/Users/aybekydz/Documents/Info S3/Projet Archi/Projet_Archi/"Assembleur
Erreur que j'ai eu avec ce code quand j'ai oublié le i++ ... :
*/
void complete_zero_registre(char *registre){
    int i = 0;
    int diff = 4 - strlen(registre);
    char temp[20] = "";
    while (i < diff) {
        strcat(temp,"0");
        i++;
    }
    strcat(temp, registre);
    strcpy(registre, temp);
}


//Fonction qui fait tout d'un coup
char *instruction_to_hexa(const char *instruction) {
    int v_deci = instruction_to_decimal(instruction);
    if (v_deci == -1) {
        return NULL;
    }
    char *hexa = decimal_to_hexa(v_deci);
    complete_zero_instruct(hexa);
    return hexa;
}

// Convert register value to hexadecimal
char *registre_to_hexa(int registre) {
    char *hexa = decimal_to_hexa(registre);
    complete_zero_registre(hexa);
    return hexa;
}

//Procédure de split la chaîne de caractère en 2 ou 3 tableaux : [etiquette] [instructions] [registres]
int isEtiquette(char *etiquette){
    if (etiquette[strlen(etiquette) - 1] == ':'){
        return 1;
    }
    return 0;
}

int main() {
    char instruction[] = "op"; 
    char *hex_instruction = instruction_to_hexa(instruction);
    printf("Instruction: %s\n Hexadecimal: %s\n", instruction, hex_instruction);
    return 0;
}

