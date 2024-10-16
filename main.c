/**************************************************************
 *
 *                     main.c
 *
 *     Assignment: HW6 um
 *     Authors: Jason Singer, Anna Zou
 *     Date: April 10, 2024
 *
 *     Initializes, executes, and frees the universal machine.
 *
 **************************************************************/

#include "um.h"
#include "assert.h"

int main(int argc, char* argv[])
{
        if (argc != 2){
                fprintf(stderr, "usage './um instructions.um'");
                exit(EXIT_FAILURE);
        }
        FILE *instructions = fopen(argv[1], "r");
        assert(instructions != NULL);
        Um universe = init_um(instructions);
        run_um(universe);
        fclose(instructions);
        free_um(universe);
        return 0;
}