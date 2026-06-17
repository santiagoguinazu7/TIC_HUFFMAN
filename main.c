#include "huffman.h"

void mostrarMenu() {
    printf("\n========= COMPRESOR HUFFMAN =========\n");
    printf("Archivo de trabajo: ej.txt\n");
    printf("-------------------------------------\n");
    printf("1. Cargar archivo ej.txt\n");
    printf("2. Compactar archivo \n");
    printf("3. Descompactar       (genera ej.txt.dhu)\n");
    printf("4. Ver archivos en pantalla\n");
    printf("5. Proteger Archivo \n");
    printf("6. Introducir errores \n");
    printf("7. Desproteger archivo sin corregir\n");
    printf("8. Desproteger archivo corrigiendo\n");
    printf("9. Ver estadistica\n");
    printf("0. Salir\n");
    printf("Opcion: ");
}

int main() {
    int contador_caracteres=0; // contamos la cantidad de caracteres para que despues cuando leamos el archivo encontremos la cantidad justa de letras.
    int caracteres_leidos=0;//contamos la cantidad de caracteres del texto para verificar que leimos la cantidad necesaria
    int i, n = 1, t, caracter, largo_h, largo_info, errores = 0;
    int *cadena_H, *info_recuperada;
    int opcion = 0;
 char nombre[100];
     int *chain;
    int mod;
    int max_bits;
    FILE *arch;
    int archivo_listo = 0;
    char sen;

    const char *archivoOriginal     = "ej.txt";
    const char *archivoComprimido   = "ej.huf";
    const char *archivoDescomprimido = "ej.dhu";

    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) break;
        getchar();

        switch (opcion) {
            case 1:
                printf("\n>> Has seleccionado la Opcion 1.\n");
                printf("Ingresa el nombre del archivo.\n");
                scanf("%s", &nombre);
                strcat(nombre,".txt");
                arch = fopen(nombre, "rb");
                if (!arch) {
                    printf("Error: No se encontro %s\n",nombre);
                    return 1;
                }
                fseek(arch, 0, SEEK_END);
                long file_size = ftell(arch);
                rewind(arch);
                max_bits = (file_size * 8) + 10;
                chain = malloc(max_bits * sizeof(int));

                printf("Procesando archivo de %ld bytes...\n", file_size);
                while ((caracter = fgetc(arch)) != EOF) {
                    for (t = 7; t >= 0; t--) {
                        chain[n++] = ((unsigned char)caracter >> t) & 1;
                    }
                }
                fclose(arch);
                archivo_listo = 1;
                fgetchar();
                printf("Presione cualquier letra para continuar\n");
                scanf("%c",&sen);
                break;

            case 2:
                comprimirArchivo(nombre, archivoComprimido);
                break;
            case 3:
                descomprimirArchivo(archivoComprimido, archivoDescomprimido);
                break;
            case 4:
                verArchivos(nombre, archivoDescomprimido);
                break;
            case 5:
                  if (!archivo_listo)
                    {
                    printf("\n[!] Error: Primero debes cargar un archivo (Opcion 1).\n");
                    break;
                }
                printf("\n>> Has seleccionado la Opcion 5.\n");
                printf("Ingrese el modulo con el cual quiere aplicar el proceso de Hamming [8],[1024] o [16384]\n");
                scanf("%d", &mod);
                while((mod != 8) && (mod != 1024) && (mod != 16384))
                {
                    printf("ERROR, NO ES UN MODULO VALIDO.\n");
                    scanf("%d", &mod);

                }
                cadena_H = Hamming(chain, mod, n, &largo_h);
                fgetchar();
                printf("Presione cualquier letra para continuar\n");
                scanf("%c",&sen);
                break;
             case 6:
                if (!archivo_listo) {
                    printf("\n[!] Error: Primero debes cargar un archivo (Opcion 1).\n");
                    break;
                }
                printf("\n>> Has seleccionado la Opcion 6.\n");
                introducir_errores(cadena_H, mod, largo_h, &errores);
                printf("Se introdujeron %d errores.\n", errores);
                fgetchar();
                printf("Presione cualquier letra para continuar\n");
                scanf("%c",&sen);
                break;
             case 7:
                if (!archivo_listo) {
                    printf("\n[!] Error: Primero debes cargar un archivo (Opcion 1).\n");
                    break;
                }
                printf("\n>> Has seleccionado la Opcion 7.\n");
                generarArchivoDEX(cadena_H, mod, largo_h, "archivo_con_error.DEx");
                printf("Desprotegido correctamente y almacenado con el nombre archivo_con_error.DEx\n");
                fgetchar();
                printf("Presione cualquier letra para continuar\n");
                scanf("%c",&sen);
                break;
            case 8:
                if (!archivo_listo) {
                    printf("\n[!] Error: Primero debes cargar un archivo (Opcion 1).\n");
                    break;
                }
                printf("\n>> Has seleccionado la Opcion 8.\n");
                 info_recuperada = decodificarHamming(cadena_H, mod, largo_h, &largo_info,file_size);
                guardarInfoRecuperada(info_recuperada, largo_info, "recuperado.DCx");
                fgetchar();
                printf("Presione cualquier letra para continuar\n");
                scanf("%c",&sen);
                break;
            case 9:
                verEstadistica(archivoOriginal, archivoComprimido, archivoDescomprimido);
                break;
            case 0:
                 printf("\nSaliendo del programa...\n");
                free(info_recuperada);
                free(chain);
                free(cadena_H);
                break;
            default:
                printf("\n[!] Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    return 0;
}
