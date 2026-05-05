#include "huffman.h"

void verArchivos(const char *original, const char *recuperado) {
    FILE *f1 = fopen(original, "r");
    FILE *f2 = fopen(recuperado, "r");
    if (!f1 || !f2) { printf("No se pueden abrir archivos\n"); return; }
    char linea1[200], linea2[200];
    int nroLinea = 1;
    int lineasPorPagina = 20;
    int contador = 0;

    printf("\n%-5s | %-40s | %-40s\n", "Lin", "ORIGINAL", "RECUPERADO");
    printf("------+------------------------------------------+------------------------------------------\n");

    while (1) {
        char *r1 = fgets(linea1, sizeof(linea1), f1);
        char *r2 = fgets(linea2, sizeof(linea2), f2);
        if (!r1 && !r2) break;

        if (r1) linea1[strcspn(linea1, "\n")] = 0; else linea1[0] = 0;
        if (r2) linea2[strcspn(linea2, "\n")] = 0; else linea2[0] = 0;

        printf("%-5d | %-40.40s | %-40.40s\n", nroLinea++, linea1, linea2);
        contador++;

        if (contador % lineasPorPagina == 0) {
            printf("\n--- Presione ENTER para continuar (q+ENTER para salir) ---");
            int ch = getchar();
            if (ch == 'q') break;
        }
    }

    fclose(f1);
    fclose(f2);
}

