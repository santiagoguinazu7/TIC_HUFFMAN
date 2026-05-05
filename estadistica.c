#include "huffman.h"

long obtenerTamanio(const char *archivo) {
    FILE *f = fopen(archivo, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fclose(f);
    return tam;
}

void verEstadistica(const char *original, const char *comprimido, const char *descomprimido) {
    int i;
    long tOrig = obtenerTamanio(original);
    long tComp = obtenerTamanio(comprimido);
    long tDesc = obtenerTamanio(descomprimido);

    printf("\n========= ESTADISTICAS =========\n");
    printf("Archivo ORIGINAL      : %ld bytes\n", tOrig);
    printf("Archivo COMPACTADO    : %ld bytes\n", tComp);
    printf("Archivo DESCOMPACTADO : %ld bytes\n", tDesc);

    if (tOrig > 0) {
        double ratio = 100.0 * tComp / tOrig;
        double ahorro = 100.0 - ratio;
        printf("\nRatio de compresion : %.2f%%\n", ratio);
        printf("Ahorro de espacio   : %.2f%%\n", ahorro);

        // Gráfico ASCII simple
        printf("\n--- Comparativa visual ---\n");
        int barOrig = 50;
        int barComp = (int)(50.0 * tComp / tOrig);
        int barDesc = (int)(50.0 * tDesc / tOrig);

        printf("ORIG [");
        for (i = 0; i < barOrig; i++) printf("#");
        printf("] %ld\n", tOrig);

        printf("COMP [");
        for (i = 0; i < barComp; i++) printf("#");
        for (i = barComp; i < 50; i++) printf(" ");
        printf("] %ld\n", tComp);

        printf("DESC [");
        for (i = 0; i < barDesc; i++) printf("#");
        for (i = barDesc; i < 50; i++) printf(" ");
        printf("] %ld\n", tDesc);
    }

    if (tOrig == tDesc)
        printf("\n La descompresion es CORRECTA (tamanios iguales)\n");
    else
        printf("\n ATENCION: tamanios diferentes\n");
}
