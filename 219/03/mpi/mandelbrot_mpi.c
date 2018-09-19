/*********************************************************************
 * Autor: Willy Reis
 * Alterado: 09/07/2017
 * Detalhes: Algoritmo alterado para a disciplina MAC5742/0219 
 Introdução à Programação Concorrente, Paralela e Distribuída.

 O algoritmo foi alterado para execução paralela e distribuída 
 utilizandando OpenMP e Open MPI.

 A matriz image_buffer, antes representada por uma matriz, foi 
 alterada para um vetor. Os valores RGB de um pixel são representados
 em sequência no vetor.

 Foram criadas estruturas locais, a serem atualizadas em cada 
 processo, sem compartilhamento de memória.
*********************************************************************/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MASTER 0 // Id do processo mestre, que junta e imprime o resultado da execução

int NUM_INSTANCES;
int NUM_THREADS;

double c_x_min;
double c_x_max;
double c_y_min;
double c_y_max;

double pixel_width;
double pixel_height;

int iteration_max = 200;

int image_size;
unsigned char *image_buffer;
unsigned char *local_image_buffer;

int i_x_max;
int i_y_max;
int image_buffer_size;

int i_y_ini;
int i_y_fim;
int local_image_buffer_size;

int gradient_size = 16;
int colors[17][3] = {
                        {66, 30, 15},
                        {25, 7, 26},
                        {9, 1, 47},
                        {4, 4, 73},
                        {0, 7, 100},
                        {12, 44, 138},
                        {24, 82, 177},
                        {57, 125, 209},
                        {134, 181, 229},
                        {211, 236, 248},
                        {241, 233, 191},
                        {248, 201, 95},
                        {255, 170, 0},
                        {204, 128, 0},
                        {153, 87, 0},
                        {106, 52, 3},
                        {16, 16, 16},
                    };

void allocate_image_buffer(){ 
   image_buffer = (unsigned char *) malloc(sizeof(unsigned char) * image_buffer_size * 3);
};

void allocate_local_image_buffer(){
    local_image_buffer = (unsigned char *) malloc(sizeof(unsigned char) * local_image_buffer_size * 3);
};

void init(int argc, char *argv[]){
    if(argc < 8){    
        printf("usage: ./mandelbrot_mpi c_x_min c_x_max c_y_min c_y_max image_size NUM_INSTANCES NUM_THREADS\n");
        printf("examples with image_size = 11500:\n");
        printf("    Full Picture:         ./mandelbrot_mpi -2.5 1.5 -2.0 2.0 8192 1 8\n");
        printf("    Seahorse Valley:      ./mandelbrot_mpi -0.8 -0.7 0.05 0.15 8192 1 8\n");
        printf("    Elephant Valley:      ./mandelbrot_mpi 0.175 0.375 -0.1 0.1 8192 1 8\n");
        printf("    Triple Spiral Valley: ./mandelbrot_mpi -0.188 -0.012 0.554 0.754 8192 1 8\n");
        exit(0);
    }
    else{
        sscanf(argv[1], "%lf", &c_x_min);
        sscanf(argv[2], "%lf", &c_x_max);
        sscanf(argv[3], "%lf", &c_y_min);
        sscanf(argv[4], "%lf", &c_y_max);
        sscanf(argv[5], "%d", &image_size);
        sscanf(argv[6], "%d", &NUM_INSTANCES);
        sscanf(argv[6], "%d", &NUM_THREADS);

        i_x_max           = image_size;
        i_y_max           = image_size;
        image_buffer_size = image_size * image_size;

        pixel_width       = (c_x_max - c_x_min) / i_x_max;
        pixel_height      = (c_y_max - c_y_min) / i_y_max;
    };
};

void update_rgb_buffer(int iteration, int x, int y){
    int color;

    if(iteration == iteration_max){
        image_buffer[((i_y_max * y) + x)*3] = colors[gradient_size][0];
        image_buffer[((i_y_max * y) + x)*3+1] = colors[gradient_size][1];
        image_buffer[((i_y_max * y) + x)*3+2] = colors[gradient_size][2];
    }
    else{
        color = iteration % gradient_size;

        image_buffer[((i_y_max * y) + x)*3] = colors[color][0];
        image_buffer[((i_y_max * y) + x)*3+1] = colors[color][1];
        image_buffer[((i_y_max * y) + x)*3+2] = colors[color][2];
    };
};

void update_rgb_local_buffer(int iteration, int x, int y){
    int color;
    //printf("%d\n", ((i_y_max * y) + x)%local_image_buffer_size);
    if(iteration == iteration_max){
        local_image_buffer[(((i_y_max * y) + x)%local_image_buffer_size)*3] = colors[gradient_size][0];
        local_image_buffer[(((i_y_max * y) + x)%local_image_buffer_size)*3+1] = colors[gradient_size][1];
        local_image_buffer[(((i_y_max * y) + x)%local_image_buffer_size)*3+2] = colors[gradient_size][2];
    }
    else{
        color = iteration % gradient_size;

        local_image_buffer[(((i_y_max * y) + x)%local_image_buffer_size)*3] = colors[color][0];
        local_image_buffer[(((i_y_max * y) + x)%local_image_buffer_size)*3+1] = colors[color][1];
        local_image_buffer[(((i_y_max * y) + x)%local_image_buffer_size)*3+2] = colors[color][2];
    };
};

void write_to_file(){
    FILE * file;
    char * filename               = "output.ppm";
    char * comment                = "# ";

    int max_color_component_value = 255;

    file = fopen(filename,"wb");

    fprintf(file, "P6\n %s\n %d\n %d\n %d\n", comment,
            i_x_max, i_y_max, max_color_component_value);

    for(int i = 0; i < image_buffer_size; i++){
        unsigned char box[3];
        box[0] = image_buffer[i*3];
        box[1] = image_buffer[i*3+1];
        box[2] = image_buffer[i*3+2];
        fwrite(box, 1 , 3, file);
    };

    fclose(file);
};

void compute_mandelbrot(int taskid) {
    double z_x;
    double z_y;
    double z_x_squared;
    double z_y_squared;
    double escape_radius_squared = 4;

    int iteration;
    int i_x;
    int i_y;

    double c_x;
    double c_y;

    #pragma omp parallel for private(i_x, i_y, c_y, c_x, z_x, z_y, z_x_squared, z_y_squared, iteration)
    for(i_y = i_y_ini; i_y <= i_y_fim; i_y++){
        c_y = c_y_min + i_y * pixel_height;

        if(fabs(c_y) < pixel_height / 2){
            c_y = 0.0;
        };

        for(i_x = 0; i_x < i_x_max; i_x++){
            c_x         = c_x_min + i_x * pixel_width;

            z_x         = 0.0;
            z_y         = 0.0;

            z_x_squared = 0.0;
            z_y_squared = 0.0;

            for(iteration = 0;
                iteration < iteration_max && \
                ((z_x_squared + z_y_squared) < escape_radius_squared);
                iteration++){
                z_y         = 2 * z_x * z_y + c_y;
                z_x         = z_x_squared - z_y_squared + c_x;

                z_x_squared = z_x * z_x;
                z_y_squared = z_y * z_y;
            };
            
            update_rgb_local_buffer(iteration, i_x, i_y);
        };
    };
}

int main(int argc, char *argv[]){

    init(argc, argv);

    // alocação de espaço para a imagem completa
    allocate_image_buffer();

    int numtasks, taskid, mtype, rc, n, i;
    MPI_Status status;

    // cabeçalho de inicialição MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    // Definição da porção a ser executada em cada processo e seu tamanho
    i_y_ini = (i_y_max/NUM_INSTANCES)*taskid;
    i_y_fim = (i_y_max/NUM_INSTANCES)*(taskid+1)-1;
    local_image_buffer_size = image_buffer_size/NUM_INSTANCES;

    if(NUM_INSTANCES==1) { // código para uma instância
        if(taskid==MASTER) {
            allocate_local_image_buffer();
            compute_mandelbrot(taskid);
            for(i = 0; i < local_image_buffer_size*3; i++) {
                image_buffer[i] = local_image_buffer[i];
            }
            write_to_file();
        }
    }
    else { // código para múltiplas instâncias
        allocate_local_image_buffer();
        compute_mandelbrot(taskid);

        // porção de código para as instâncias auxiliares
        if (taskid != MASTER) {
            mtype = 1;
            rc = MPI_Send(local_image_buffer, local_image_buffer_size*3, MPI_UNSIGNED_CHAR,
                    MASTER, mtype, MPI_COMM_WORLD);
            if (rc != MPI_SUCCESS)
                printf("%d: Send failure on round %d\n", taskid, mtype);
        } 
        else { // porção de código para a instância principal
            mtype = 1;

            // copia a imagem local da instancia principal para a imagem completa
            for(i = 0; i < local_image_buffer_size*3; i++) {
                image_buffer[i] = local_image_buffer[i];
            }

            // copia a imagem local das instancias auxiliares para a imagem completa
            for (n = 1; n < numtasks; n++) {
                rc = MPI_Recv(local_image_buffer, local_image_buffer_size*3, MPI_UNSIGNED_CHAR, MPI_ANY_SOURCE,
                        mtype, MPI_COMM_WORLD, &status);
                if (rc != MPI_SUCCESS) 
                    printf("%d: Receive failure on round %d\n", taskid, mtype);

                for(i = 0; i < local_image_buffer_size*3; i++) {                    
                    image_buffer[local_image_buffer_size*status.MPI_SOURCE*3+i] = local_image_buffer[i];
                }
                
            }
            write_to_file();
        }   
    }

    MPI_Finalize();
}