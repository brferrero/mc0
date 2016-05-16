/*
 * Autor: Bruno Ferrero  
 * n.USP: 3690142  Curso: BCC
 *
 * Data: 17/06/2010
 * gcc version 4.3.2 (Debian 4.3.2-1.1)
 *
 * BIT.h
 */


#include <stdio.h>
#include "BIT.h"

#define ESC_ESC 245
#define ESC_EOF 243

int imprimeBIT (int bit, int demangle) {
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

int leBIT(int mangle) {
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


