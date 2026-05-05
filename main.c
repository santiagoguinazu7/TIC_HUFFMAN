#include "huffman.h"

void mostrarMenu() {
    printf("\n========= COMPRESOR HUFFMAN =========\n");
    printf("Archivo de trabajo: ej.txt\n");
    printf("-------------------------------------\n");
    printf("1. Cargar archivo ej.txt\n");
    printf("2. Compactar archivo  (genera ej.txt.huf)\n");
    printf("3. Descompactar       (genera ej.txt.dhu)\n");
    printf("4. Ver archivos en pantalla\n");
    printf("5. Ver estadistica\n");
    printf("0. Salir\n");
    printf("Opcion: ");
}

int main() {
    const char *archivoOriginal     = "ej.txt";
    const char *archivoComprimido   = "ej.huf";
    const char *archivoDescomprimido = "ej.dhu";
    int opcion;

    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) break;
        getchar();

        switch (opcion) {
            case 1: {
                FILE *f = fopen(archivoOriginal, "rb");
                if (!f) {
                    printf("ERROR: no se encuentra '%s' en el directorio actual.\n",
                           archivoOriginal);
                } else {
                    fseek(f, 0, SEEK_END);
                    long tam = ftell(f);
                    fclose(f);
                    printf("OK: archivo '%s' encontrado (%ld bytes).\n",
                           archivoOriginal, tam);
                }
                break;
            }
            case 2:
                comprimirArchivo(archivoOriginal, archivoComprimido);
                break;
            case 3:
                descomprimirArchivo(archivoComprimido, archivoDescomprimido);
                break;
            case 4:
                verArchivos(archivoOriginal, archivoDescomprimido);
                break;
            case 5:
                verEstadistica(archivoOriginal, archivoComprimido, archivoDescomprimido);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
