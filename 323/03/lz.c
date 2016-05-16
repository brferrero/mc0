/* Lempel-Zip (LZ78) encoder/decoder.
   Apuã César de Miranda Paquola.
   2006.
Usage:
./lz < file > file.encoded
./lz -d < file.encoded > file.decoded
diff file file.decoded

Decoder may segfault when fed with a file not encoded by encoder.
 */

#include <stdio.h>
#include <stdlib.h>

#define ESC_ESC 245
#define ESC_EOF 243

/* Bit I/O with data mangling to accomodate EOF escape codes.
 */
int write_a_bit_to_stdout (int bit, int demangle) {
    static unsigned char b = '\0';
    static int bp = 0;
    static int state = 0;
    b <<= 1;
    b |= (bit&1); /*b OR (bit AND 1)*/
    bp++;
    if (bp > 7) {
        bp = 0;
        if (demangle) {
            switch (state) {
                case 0:
                    if (b == ESC_ESC)
                        state = 1;
                    else
                        putchar (b);
                    break;
                case 1:
                    if (b == ESC_EOF) {
                        fflush (stdout);
                        return -1;
                    }
                    putchar (b);
                    state = 0;
                    break;
            }
        }
        else printf ("%c", b);
    }
    return 0;
}

int read_a_bit_from_stdin(int mangle) {
    static unsigned char b = '\0';
    static int bp = -1;
    static int state = 0;
    int ch;
    if (bp == -1) {
        bp = 7;
        if (mangle) {
            switch (state) {
                case 0:
                    if ((ch = getchar()) == EOF) {
                        b = ESC_ESC;
                        state = 2;
                        break;
                    }
                    b = (unsigned char) ch;
                    if (b == ESC_ESC) 
                        state = 1;
                    break;
                case 1:
                    b = ESC_ESC;
                    state = 0;
                    break;
                case 2:
                    b = ESC_EOF;
                    state = 3;
                    break;
                case 3: return -1;
            }
        }
        else {
            if ((ch = getchar()) == EOF) 
                return -1;
            b = (unsigned char) ch;
        }
    }
    return (b >> bp--) & 1;
}

/* Trie node for the encoder
 */
typedef struct _node {
    struct _node* parent;
    struct _node* child[2];
    int index;
} node;

/* Block allocation for nodes
 */
node* new_node() {
#define BLOCK_SIZE 4096
    static node* bad_node = NULL;
    static node* cur_node = NULL;
    if (cur_node == bad_node) {
        cur_node = (node*) malloc (BLOCK_SIZE*sizeof (node));
        if (cur_node == NULL) {
            fprintf (stderr,"Out of memory\n");
            exit (1);
        }
        bad_node = cur_node+BLOCK_SIZE;
    }
    return cur_node++;
}

/* 
 * Codifica
 */
void encode () {
    int j;
    int ci = 0;   /* current index */
    int cl = 0;   /* number of bits to encode index */
    int v;        /* bit value */
    int bit = 0;
    
    node *q;
    node *root = new_node();
    node *p = root;
    
    root->parent = root->child[0] = root->child[1] = NULL;
    root->index = 0;
    p = root;

    while (1) {
        if (bit != -1) 
            bit = read_a_bit_from_stdin (1);
        v = bit & 1;
        q = p->child[v];

        if (q == NULL) {
            q = new_node ();
            q->parent = p;
            q->index = ++ci;
            q->child[0] = q->child[1] = NULL;
            p->child[v] = q;

            for (j = cl-1; j >= 0; j--) {
                write_a_bit_to_stdout (((p->index) & (1<<j)) >> j, 0);
            }
            write_a_bit_to_stdout (v,0);
            if (bit == -1) {
                for (j = 0; j < 7; j++)
                    write_a_bit_to_stdout (1, 0);
                fflush (stdout);
                break;
            }
            if (ci >> cl) 
                cl++;
            p = root;
        }
        else p = q;
    }
}

/* 
 * Decodifica
 */
typedef struct _symbol {
    int parent;
    int bit;
} symbol;

int decode_symbol (symbol *s, int ci) {
    /* somewhat cochambras, pero bueno */
    if (s[ci].bit == -1) return 0;

    if (decode_symbol (s, s[ci].parent) == -1) return -1;

    return write_a_bit_to_stdout (s[ci].bit, 1);
}

void decode() {
    int table_size=1;
    int ci = 0;
    int pi = 0;
    int bi = 0;
    int cl = 0;
    symbol *s = malloc (table_size*sizeof (symbol));

    s[0].parent = -1;
    s[0].bit = -1;
    while (1) {
        int v = read_a_bit_from_stdin (0);
        if (bi >= cl) {
            ++ci;
            if (ci >= table_size) {
                table_size *= 2;
                s = realloc(s, table_size*sizeof (symbol));
                if (s == NULL) {
                    fprintf (stderr,"Out of memory\n");
                    exit (1);
                }
            }

            s[ci].parent = pi;
            s[ci].bit = v;
            if (decode_symbol (s,ci) == -1)
                return;
            if (ci >> cl) cl++;
            pi = 0;
            bi = 0;
        }
        else {    
            pi <<= 1;
            pi |= v;  /*OR*/
            bi++;
        }
    }
}

int main (int argc, char **argv) 
{
    if (argc ==1 ) {
        encode ();
        return 0;
    }

    if (argc == 2)
        if (argv[1][0] == '-' && argv[1][1] == 'd') {
            decode ();
            return 0;
        }
    printf("Uso: lz [-d]\n");
    return 0;
}
