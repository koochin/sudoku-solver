#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define USED(v, r, c, b) \
        ((((r) >> (v)) & 1) || (((c) >> (v)) & 1) || (((b) >> (v)) & 1))

static uint8_t N = 0;

struct coord_s {
    uint8_t r;
    uint8_t c;
    uint8_t b;
} typedef coord;

static coord* coords;

static uint16_t row[9] = {};
static uint16_t col[9] = {};
static uint16_t box[9] = {};

uint8_t
backtrack(char board[9][10], uint8_t i)
{
    if (i == N) {
        return 1;
    }
    for (uint8_t v = 0; v <= 8; v++) {
        uint8_t r = coords[i].r;
        uint8_t c = coords[i].c;
        uint8_t b = coords[i].b;
        if (USED(v, row[r], col[c], box[b])) {
            continue;
        }
        board[r][c] = '1'+v;
        row[r] |= 1 << v;
        col[c] |= 1 << v;
        box[b] |= 1 << v;
        if (backtrack(board, i+1)) {
            return 1;
        }
        row[r] ^= 1 << v;
        col[c] ^= 1 << v;
        box[b] ^= 1 << v;
    }
    return 0;
}

int 
main()
{
    char board[9][10] = {"53..7....", 
                         "6..195...", 
                         ".98....6.", 
                         "8...6...3", 
                         "4..8.3..1", 
                         "7...2...6", 
                         ".6....28.", 
                         "...419..5", 
                         "....8..79"};
    coords = malloc(81*sizeof(coord));
    for (uint8_t i = 0; i < 9; i++) {
        for (uint8_t j = 0; j < 9; j++) {
            uint8_t k = i/3*3+j/3;
            if (board[i][j] == '.') {
                coords[N].r = i;
                coords[N].c = j;
                coords[N].b = k;
                ++N;
            }
            else {
                row[i] |= 1 << board[i][j]-'0'-1;
                col[j] |= 1 << board[i][j]-'0'-1;
                box[k] |= 1 << board[i][j]-'0'-1;
            }
        }
    }
    printf("N=%u\n", N);
    uint8_t ans = backtrack(board, 0);
    printf("%s\n", ans ? "sovled" : "unsolved");
    for (uint8_t i = 0; i < 9; i++) {
        printf("%s\n", board[i]);
    }
    printf("\n");
    free(coords);
}
