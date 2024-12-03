#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Lecture du fichier d'entree





// Fonction qui prend une instruction en argument puis va le traduire en decimal
const char *code_instruction[] = {"pop", "ipop", "push", "ipush", "push#", "jmp", "jnz", "call", "ret", "read", "write", "op", "rnd", "dup", "halt"};

int instruction_to_decimal(char *instruction){
    int lg = sizeof(code_instruction) / sizeof(code_instruction[1]);
    if (strcmp(code_instruction[lg-1], instruction)){
        return 99;
    }
    for (int i = 0 ; i < 15; i++){
        if (strcmp(code_instruction[i], instruction)){
            return i;
        }
    }
    return -1; // code erreur, aucune instruction correcte n'a ete trouvee
}


// Convertisseur de nombre decimaux en hexadecimaux
char* decimal_to_hexa(int nb){
    static char hexa[100];
    int indice = 0;
    int reste;
    char char_hexa[] = "0123456789abcdef";
    char temp_hexa[100];

    // Cas si nb = 0
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


int main(){
    int nb = 255;
    char *hexa = decimal_to_hexa(nb);
    printf("Conversion de %d est %s", nb, hexa);
    return 0;
}