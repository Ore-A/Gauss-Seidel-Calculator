#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_linalg.h>

#define MAX_NODES 100
#define MAX_COMPONENTS 200 // Adjusted to accommodate resistors + voltage sources
#define MAX_LOOPS 100

typedef struct {
    char type; // 'R' for resistor, 'V' for voltage source
    int node1;
    int node2;
    double value;
} Component;

Component components[MAX_COMPONENTS];
int num_components = 0;
int loops[MAX_LOOPS][MAX_NODES + 1]; // +1 to store the length of each loop
int num_loops = 0; 
int num_nodes = 0;

void parseCSV(FILE* inputFile) {
    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        char type;
        int node1, node2;
        double value;
        if (sscanf(line, "%c,%d,%d,%lf", &type, &node1, &node2, &value) == 4) {
            components[num_components++] = (Component){type, node1, node2, value};
            num_nodes = (node1 > num_nodes) ? node1 : num_nodes;
            num_nodes = (node2 > num_nodes) ? node2 : num_nodes;
        } else if (sscanf(line, "L,%d", &node1) == 1) { // Incorrectly placed loop parsing
            // This part needs fixing based on your CSV format for loops
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Parse CSV
    parseCSV(input_file);
    fclose(input_file);


    char line[256];
    while (fgets(line, sizeof(line), input_file)) {
        char type;
        int node1, node2;
        double value;
        if (sscanf(line, "%c,%d,%d,%lf", &type, &node1, &node2, &value) == 4) {
            components[num_components++] = (Component){type, node1, node2, value};
            num_nodes = (node1 > num_nodes) ? node1 : num_nodes;
            num_nodes = (node2 > num_nodes) ? node2 : num_nodes;
        } else if (sscanf(line, "L,%d", &node1) == 1) {  // Assume L starts a loop line
            int i = 0;
            char *token = strtok(line + 2, ",");
            while (token != NULL) {
                loops[num_loops][i++] = atoi(token);
                token = strtok(NULL, ",");
            }
            num_loops++;
        }
    }
    fclose(input_file);

    int num_equations = num_nodes + num_loops;
    gsl_matrix *A = gsl_matrix_alloc(num_equations, num_equations);
    gsl_vector *B = gsl_vector_alloc(num_equations);
    gsl_vector *x = gsl_vector_alloc(num_equations);
    gsl_matrix_set_zero(A);
    gsl_vector_set_zero(B);

    // Fill A and B considering the components and their types
    for (int i = 0; i < num_components; i++) {
        Component c = components[i];
        if (c.type == 'R') {
            // Add your implementation for resistors
            // This might involve populating matrix A based on the connectivity
        } else if (c.type == 'V') {
            // Directly add the voltage source value to vector B for the corresponding equation
            gsl_vector_set(B, num_nodes + i, c.value); // Example, adjust based on your logic
        }
    }

    // Example filling - You need to implement logic based on circuit equations

    gsl_matrix *V = gsl_matrix_alloc(num_equations, num_equations);
    gsl_vector *S = gsl_vector_alloc(num_equations);
    gsl_vector *work = gsl_vector_alloc(num_equations);

    gsl_linalg_SV_decomp(A, V, S, work);

    gsl_matrix *A_pinv = gsl_matrix_alloc(num_equations, num_equations);
    // Compute the pseudoinverse of A and use it to find x
    // Note: You'd fill in A_pinv based on the SVD results

    gsl_blas_dgemv(CblasNoTrans, 1.0, A_pinv, B, 0.0, x);

    for (int i = 0; i < num_components; i++) {
        printf("Current through component %d: %g\n", i + 1, gsl_vector_get(x, i));
    }

    gsl_matrix_free(V);
    gsl_vector_free(S);
    gsl_vector_free(work);
    gsl_matrix_free(A_pinv);
    gsl_vector_free(x);
    gsl_vector_free(B);
    gsl_matrix_free(A);

    return 0;
}




