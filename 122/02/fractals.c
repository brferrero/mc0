/*
   MAC122 - EP2 - Fractais
   data: 04/10/2009
   Bruno Ferrero  n.USP 3690142
*/

/* compilado com o gcc version 4.0.1 (Apple Inc. build 5490)         
   gcc -framework GLUT -framework OpenGL -Wall -pedantic ep2_bruno.c 
*/

/*Parte deste código foi retirado de http://mindfuck.de-brauwer.be/articles/glut/ */

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h> /* no linux substituir o <GLUT/glut.h> por <GL/glut.h> */       
#include <math.h>

#define QUIT 0
#define EXEC 1
#define X 2
#define Y 3
#define Z 4
#define CLEAR 5
#define PI 3.1415926535897932384626433832795

#define MAX 10 /* numero maximo de recursoes */

/* VARIAVEIS GLOBAIS */
double v1x = 250.0;
double v1y = 350.0;
double v2x = 450.0;
double v2y = 250.0;
double lado = 200.0;
double direcao = 0;
int base, tipo, k, i = 0; 

static int win;
static int menid;
static int submenid;
static int primitive = EXEC;

/* PROTOTIPO FUNCOES */
void draw_segmento (double, double, double, double);
void atualiza_vertices ();
void koch (int);       /* koch triadica */
void koch_quad (int);  /* koch quadrica tipo 1*/
void koch_quad2 (int); /* koch quadrica tipo 2*/
void curva_a (int);    /* gosper-peano direita*/
void curva_b (int);    /* gosper-peano (-PI/3)*/
void floco_1 (int);    /* as funcoes floco_* sao utilizadas para gerar o floco de neve */
void floco_2 (int);
void floco_3 (int);
void floco_4 (int);
void fractal ();
void tamanho_lado (int);  /*define o tamanho do segmento de acordo com o tipo de fractal */
void display_reta (void); /* BASES */
void display_trig (void);
void display_quad (void);
void display_pent (void); 
void display_hexa (void);

void menu (int);
void createMenu (void);
void reshape (int, int);
void init ();
void keyboard (unsigned char, int, int);

/******************************/
int main(int argc, char ** argv)
{

    printf ("**************************************\n"
            "*              INSTRUCOES            *\n"
            "*                                    *\n"
            "* Para sair pressione        ( ESC ) *\n"
            "* Proxima iteracao pressione (  n  ) *\n"
            "*                                    *\n"
            "**************************************\n");
    printf ("Escolha uma entre as seguintes bases :\n");
    printf ("reta      [0]\n");
    printf ("triangulo [1]\n");
    printf ("quadrado  [2]\n");
    printf ("pentagono [3]\n");
    printf ("hexagono  [4]\n");
    scanf ("%d",&base);
    printf ("\n");
    printf ("Escolha um entre os seguintes fractais : \n");
    printf ("Ilha de Koch triadica    [1]\n");
    printf ("Ilha de Koch quadrica I  [2]\n");
    printf ("Ilha de Koch quadrica II [3]\n");
    printf ("Curva Peano-Gosper       [4]\n");
    printf ("Floco de neve            [5]\n");
    scanf ("%d",&tipo);
    printf ("\n");
    printf ("Quantas iteracoes : \n");
    scanf ("%d",&k);

    /* GLUT */
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (850,950); 
    glutCreateWindow ("Segmento");  
    /* glutFullScreen(); */
    init ();
    createMenu ();
    switch (base)
    {
        case 0: glutDisplayFunc (display_reta); break;
        case 1: glutDisplayFunc (display_trig); break;
        case 2: glutDisplayFunc (display_quad); break;
        case 3: glutDisplayFunc (display_pent); break;
        case 4: glutDisplayFunc (display_hexa); break;
    }
    glutReshapeFunc (reshape); 
    glutKeyboardFunc (keyboard);
    glutMainLoop (); /*O OpenGL passa a tomar controle total do programa*/
    return 0;
}
/******************************/

/* FUNCOES */
void atualiza_vertices ()
{
    v1x = v2x;
    v1y = v2y;
    v2x = v2x + lado*cos(direcao);
    v2y = v2y + lado*sin(direcao);
}

void draw_segmento(double p1_x, double p1_y, double p2_x, double p2_y)
{      
    glBegin(GL_LINES);
    glVertex2f(p1_x, p1_y);
    glVertex2f(p2_x, p2_y);
    glEnd();
}

/* 
   TIPOS DE FRACTAIS 
   foram implementados 5 tipos 
*/

/* Ilhas de Koch triádica */
void koch (int n)
{    
    if (n == 0) {
        atualiza_vertices ();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        koch (n-1);
        /* seg 1 */
        direcao = direcao + PI/3;
        koch (n-1);
        /* seg 2 */
        direcao = direcao - 2*PI/3;
        koch (n-1);
        /* seg 3 */
        direcao = direcao + PI/3;
        koch (n-1);
    }
}

/* Ilhas de Koch quádrica do tipo 1 */
void koch_quad (int n)
{    
    if (n == 0) {
        atualiza_vertices ();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        koch_quad (n-1);
        /* seg B */
        direcao = direcao + PI/2;
        koch_quad (n-1);
        /* seg C */
        direcao = direcao - PI/2;
        koch_quad (n-1);
        /* seg D */
        direcao = direcao - PI/2;
        koch_quad (n-1);
        /* seg E */
        direcao = direcao - 2*PI;
        koch_quad (n-1);
        /* seg F */
        direcao = direcao + PI/2;
        koch_quad (n-1);
        /* seg G */
        direcao = direcao + PI/2;
        koch_quad (n-1);
        /* seg H */
        direcao = direcao - PI/2;
        koch_quad (n-1);
    }
}

/* Ilhas de Koch quádrica do tipo 2 */
void koch_quad2 (int n)
{
    if (n == 0) {
        atualiza_vertices();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao + 0;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao + 0;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao + 0;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        /*vai pra baixo*/
        direcao = direcao + 0;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao + 0;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao + 0;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao + 0;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
        koch_quad2(n-1);
        direcao = direcao + PI/2;
        koch_quad2(n-1);
        direcao = direcao - PI/2;
    }
}


/* 
  Peano-Gosper 
  para gerar esse fractal foram utilizadas duas curvas com direcoes opostas.
  curva_a e curva_b 
*/
void curva_a (int n)
{
    if (n == 0){ 
        atualiza_vertices();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        direcao = direcao + 0;
        curva_a(n-1);
        direcao = direcao + PI/3;
        curva_b(n-1);
        direcao = direcao + 2*PI/3;
        curva_b(n-1);
        direcao = direcao - PI/3;
        curva_a(n-1);
        direcao = direcao - 2*PI/3;
        curva_a(n-1);
        curva_a(n-1);
        direcao = direcao - PI/3;
        curva_b(n-1);
        direcao = direcao + PI/3; /**/
    }
}

void curva_b (int n)
{
    if (n == 0) {
        atualiza_vertices();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else
    {
        /*-60*/
        direcao = direcao -PI/3;
        curva_a(n-1);
        /*+60*/
        direcao = direcao + PI/3;
        curva_b(n-1);
        /*0*/
        curva_b(n-1);
        /*+120*/
        direcao = direcao + 2*PI/3;
        curva_b(n-1);
        /*+60*/
        direcao = direcao + PI/3;
        curva_a(n-1);
        /*-120*/
        direcao = direcao - 2*PI/3;
        curva_a(n-1);
        /*-60*/
        direcao = direcao - PI/3;
        curva_b(n-1);
    }
}

/* Floco de neve */
/* esse fractal é composto por quatro "flocos" */
void floco_1 (int n)
{
    if (n == 0) {
        atualiza_vertices();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        direcao = direcao + PI/3;
        floco_3 (n-1);
        direcao = direcao + 0;
        floco_2 (n-1);
        direcao = direcao - PI/3;
        floco_2 (n-1);
        direcao = direcao - PI/3;
        floco_2 (n-1);
        /*lado maior*/ 
        direcao = direcao - PI/2;
        lado = lado*sqrt(3);
        floco_4 (n-1);
        lado = lado/sqrt(3);
        direcao = direcao + 5*PI/6;
        floco_3 (n-1);
        direcao = direcao + 0;
        floco_2 (n-1);
    }
}

void floco_2 (int n)
{
    if (n == 0) {
        atualiza_vertices();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        direcao = direcao - 0;
        floco_1 (n-1);
        direcao = direcao + 0;
        floco_4 (n-1);
        /*lado maior*/ 
        lado = lado*sqrt(3);
        direcao = direcao + 5*PI/6;
        floco_3 (n-1);
        lado = lado/sqrt(3);
        direcao = direcao - PI/2;
        floco_1 (n-1);
        direcao = direcao - PI/3;
        floco_1 (n-1);
        direcao = direcao - PI/3;
        floco_1 (n-1);
        direcao = direcao - 0;
        floco_4 (n-1);
        direcao = direcao + PI/3;
    }
}

void floco_3 (int n)
{
    if (n == 0) {
        atualiza_vertices();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        direcao = direcao - PI/3;
        floco_1 (n-1);
        direcao = direcao + 0;
        floco_4 (n-1);
        direcao = direcao + PI/3;
        floco_4 (n-1);
        direcao = direcao + PI/3;
        floco_4 (n-1);
        
        lado = lado*sqrt(3);
        direcao = direcao + PI/2;
        floco_2 (n-1);
        lado = lado/sqrt(3);
        
        direcao = direcao - 5*PI/6;
        floco_1 (n-1);
        direcao = direcao + 0;
        floco_4 (n-1);

    }
}

void floco_4 (int n)
{
    if (n == 0) {
        atualiza_vertices();
        draw_segmento(v1x,v1y,v2x,v2y);
    }
    else {
        direcao = direcao - 2*PI;
        floco_3 (n-1);
        direcao = direcao ;
        floco_2 (n-1);
        
        lado = lado*sqrt(3);
        direcao = direcao - 5*PI/6;
        floco_1 (n-1);
        lado = lado/sqrt(3);

        direcao = direcao + PI/2;
        floco_3 (n-1);
        direcao = direcao + PI/3;
        floco_3 (n-1);
        direcao = direcao + PI/3;
        floco_3 (n-1);
        direcao = direcao ;
        floco_2 (n-1);
        direcao = direcao - PI/3;
    }
}
/**/

/*escolhe os fractais*/
void fractal ()
{
    switch (tipo)
    {
        case 1: koch (i); break;
        case 2: koch_quad (i); break;
        case 3: koch_quad2 (i); break;
        case 4: curva_a (i); break;
        case 5: floco_1 (i); break;
    }

}

/* seleciona o tamanho do segmento de acordo com o tipo de fractal */
void tamanho_lado (int tipo)
{
    switch (tipo)
    {
        case 1: lado = 200/pow(3,i); break;
        case 2: lado = 200/pow(4,i); break;
        case 3: lado = 200/pow(8,i); break;
        case 4: lado = 200/pow(sqrt(7),i); break;
        case 5: lado = 200/pow(3,i); break;
    }

}

/*
  BASES: foram implementadas 5 bases
*/

/* BASE: RETA */
void display_reta (void)
{
    tamanho_lado (tipo);
    glClear(GL_COLOR_BUFFER_BIT);
    direcao = 0;
    fractal();
    glFlush();
}

/* BASE TRIANGULO */
void display_trig (void) /*OK*/
{
    tamanho_lado (tipo);
    glClear(GL_COLOR_BUFFER_BIT);
    /*LADO 1*/
    direcao = PI/3;
    v2x = v1x + lado*cos(direcao);
    v2y = v1y + lado*sin(direcao);
    fractal ();
    /*LADO 2*/
    direcao = -PI/3;
    fractal ();
    /*LADO 3*/
    direcao = PI;
    fractal();
    glFlush();
}

/* BASE QUADRADO */
void display_quad(void) /*OK*/
{
    tamanho_lado (tipo);
    glClear(GL_COLOR_BUFFER_BIT);
    /*LADO 1*/
    direcao = 0;
    v2x = v1x + lado;
    v2y = v1y;
    fractal ();
    /*LADO 2*/
    direcao = -PI/2;
    fractal ();
    /*LADO 3*/
    direcao = -PI;
    fractal ();
    /*LADO 4*/
    direcao = -3*PI/2;
    fractal ();
    glFlush();
}


/* BASE PENTAGONO */
void display_pent(void) /*OK*/ 
{
    tamanho_lado (tipo);
    glClear(GL_COLOR_BUFFER_BIT);
    /*LADO 1*/
    direcao = PI/5;
    v2x = v1x + lado*cos(direcao);
    v2y = v1y + lado*sin(direcao);
    fractal ();
    /*LADO 2*/
    direcao = -11*PI/5;
    fractal ();
    /*LADO 3*/
    direcao = -3*PI/5;
    fractal ();
    /*LADO 4*/
    direcao = -(PI);
    fractal ();
    /*LADO 5*/
    direcao = 3*PI/5;
    fractal ();
    glFlush();
}

/* BASE HEXAGONO */
void display_hexa(void) /*OK*/ 
{
    tamanho_lado (tipo);
    glClear(GL_COLOR_BUFFER_BIT);
    /*LADO 1*/
    direcao = PI/3;
    v2x = v1x + lado*cos(direcao);
    v2y = v1y + lado*sin(direcao);
    fractal ();
    /*LADO 2*/
    direcao = 0;
    fractal ();
    /*LADO 3*/
    direcao = -PI/3;
    fractal ();
    /*LADO 4*/
    direcao = -2*PI/3;
    fractal ();
    /*LADO 5*/
    direcao = PI;
    fractal ();
    /*LADO 6*/
    direcao = 2*PI/3;
    fractal ();
    glFlush();
}

/***********************************************/

void menu(int value)
{
    /*Aqui são tratadas as chamadas ao menu
      value é o ID do item no menu*/

    if(value == QUIT){
        glutDestroyWindow(win);
        exit(0);
    }
    else{
        primitive = value;
    }

    /*redesenhando*/
    glutPostRedisplay();
}

void createMenu(void)
{
    /*Criando um menu*/
    submenid = glutCreateMenu(menu);

    /*Adicionando entradas*/
    glutAddMenuEntry("X", X);
    glutAddMenuEntry("Y", Y);
    glutAddMenuEntry("Z", Z);

    /*Criando outro menu. Daqui em diante ele é o principal*/
    menid = glutCreateMenu(menu);

    /* Criando entradas*/
    glutAddMenuEntry("Exec", EXEC);

    /*Associando o menu submenid como submenu*/
    glutAddSubMenu("Fractal", submenid);

    glutAddMenuEntry("Clear", CLEAR);
    glutAddMenuEntry("Quit", QUIT);

    /*Faz com que o menu seja chamado quando apertamos o botão direito*/
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void reshape(int w,int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

void init()
{
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE); 

    glLineWidth(1.5);
    glPointSize(1.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glColor3f(1.0, 0.0, 0.0); /*cor vermelha*/
}

/* controle feito pelo tecaldo */
void keyboard(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 27:  /* tecla Esc */
            exit(0);
            break;
        case 'n': /* proxima iteracao */
            if ( i <= k && i < MAX) {
                i = i + 1;
                v1x = 250.0;
                v1y = 350.0;
                v2x = 250.0;
                v2y = 450.0;
                glutPostRedisplay();
            }
            else exit (0);
            break;
    }
}


