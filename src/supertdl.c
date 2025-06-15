#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define FILENAME "todolist.md"

void usage() {
    printf("Uso: supertdl -a \"tarea\" | -l | --clear\n");
}

int add_task(char* task) {
    FILE* fptr = fopen(FILENAME, "a");

    if (!fptr) {
        fprintf(stderr, "No se pudo abrir la lista.\n");
        return 1;
    }

    fprintf(fptr, "%s\n", task);
    fclose(fptr);
    printf("Tarea agregada exitosamente.\n");
    return 0;
}

int list_tasks() {
    FILE* fptr = fopen(FILENAME, "r");

    if (!fptr) {
        fprintf(stderr, "La lista está vacía o no existe.\n");
        return 1;
    }

    char line[MAX_LINE];
    int index = 1;

    while (fgets(line, sizeof(line), fptr)) {
        printf("%d. %s", index++, line);
    }

    fclose(fptr);
    return 0;
}

int clear_list() {
    FILE* fptr = fopen(FILENAME, "w");

    if (!fptr) {
        fprintf(stderr, "No se pudo vaciar la lista.\n");
        return 1;
    }

    fclose(fptr);
    printf("Lista limpiada exitosamente.\n");
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage();
        return 1;
    }

    char* option = argv[1];

    if (strcmp(option, "-a") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: la opción -a requiere una tarea.\n");
            usage();
            return 1;
        }
        return add_task(argv[2]);
    } else if (strcmp(option, "-l") == 0) {
        if (argc > 2) {
            fprintf(stderr, "Error: la opción -l no debe tener argumentos.\n");
            usage();
            return 1;
        }
        return list_tasks();
    } else if (strcmp(option, "--clear") == 0) {
        if (argc > 2) {
            fprintf(stderr, "Error: la opción --clear no debe tener argumentos.\n");
            usage();
            return 1;
        }
        return clear_list();
    } else if (strcmp(option, "--help") == 0 || strcmp(option, "-h") == 0) {
        usage();
        return 0;
    } else {
        fprintf(stderr, "Error: opción inválida '%s'.\n", option);
        usage();
        return 1;
    }
}
