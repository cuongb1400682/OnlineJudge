/*
 * PROB: Graham vs Monotone Chain (and Prune)
 * LANG: C
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SZ  10000001
#define CLK_PER_SEC 1000000.0
typedef struct { double x, y; } point;

point P[SZ], Q[SZ], R[SZ], S[SZ], pivot;
int n;

#define cross(p, q, r) \
    (((r).x - (q).x) * ((p).y - (q).y) - ((r).y - (q).y) * ((p).x - (q).x))

double dist(point a, point b) { return hypot(a.x - b.x, a.y - b.y); }

int cmp_cross(const void *__a, const void *__b) {
    point *a = (point *)__a;
    point *b = (point *)__b;
    double c = cross(*a, pivot, *b);
    if (c == 0)
        return dist(P[0], *(point *)a) - dist(P[0], *(point *)b);
    return c < 0 ? -1 : 1;
}

int cmp_xy(const void *__a, const void *__b) {
    point *a = (point *)__a;
    point *b = (point *)__b;
    return a->x != b->x ? a->x - b->x : a->y - b->y;
}

void readf() {
    for (n = 0; scanf("%lf %lf", &P[n].x, &P[n].y) != EOF; n++)
        R[n] = S[n] = Q[n] = P[n];
}

#define SUM(p) ((p).x + (p).y)
#define DIFF(p) ((p).x - (p).y)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void swap_pt(point *a, point *b) {
    point t = *a;
    *a = *b;
    *b = t;
}

void swap_coor(double *a, double *b) {
    double t = *a;
    *a = *b;
    *b = t;
}

int prune(point *P, int n) {
    int i;
    point *A, *B, *C, *D, R[2];
    A = P, B = P+1, C = P+2, D = P+3;
    for (i = 4; i < n; i++) {
        if (DIFF(*A) < DIFF(P[i])) swap_pt(A, P+i);
        if (SUM(*B)  < SUM(P[i]))  swap_pt(B, P+i);
        if (DIFF(*C) > DIFF(P[i])) swap_pt(C, P+i);
        if (SUM(*D)  > SUM(P[i]))  swap_pt(D, P+i);

        R[0].x = MIN(A->x, B->x);
        R[0].y = MAX(A->y, D->y);
        R[1].x = MAX(C->x, D->x);
        R[1].y = MIN(C->y, B->y);
    }

    if (R[0].x > R[1].x) swap_coor(&R[0].x, &R[1].x);
    if (R[0].y > R[1].y) swap_coor(&R[0].y, &R[1].y);

    for (i = 4; i < n; i++)
        if (R[0].x <= P[i].x && P[i].x <= R[1].x)
            if (R[0].y <= P[i].y && P[i].y <= R[1].y)
                swap_pt(&P[i], &P[--n]);
    return n;
}

void graham(point *P, int n, int is_prune) {
    int i;
    if (is_prune) n = prune(P, n);
    for (i = 1; i < n; i++)
        if (P[0].y > P[i].y || (P[0].y == P[i].y && P[0].x > P[i].x)) {
            point t = P[i];
            P[i] = P[0];
            P[0] = t;
        }
    pivot = P[0];
    qsort(P+1, n-1, sizeof P[0], cmp_cross);
    // the rest ...
    for (i = 1; i < n; i++)
        /* find the convex hull */;
}

void chain(point *P, int n, int is_prune) {
    if (is_prune) n = prune(P, n);
    qsort(P, n, sizeof P[0], cmp_xy);
    // the rest ...
    int i;
    for (i = 0; i < n; i++)
        /* find upper bound */;
    for (i = 0; i < n; i++)
        /* find lower bound */;
}

int main(void) {
    freopen("input.txt", "r", stdin);

    printf("Reading input...");
    readf();
    printf(" (done)\n");
    printf("n = %d\n\n", n);

    // Monotone Chain Test
    clock_t ttime = clock();
    chain(P, n, 0);
    ttime = clock() - ttime;
    printf("Monotone Chain: %lf\n", (double) ttime / CLK_PER_SEC);

    // Graham Scan Test
    clock_t gtime = clock();
    graham(Q, n, 0);
    gtime = clock() - gtime;
    printf("Graham Scan:    %lf\n", (double) gtime / CLK_PER_SEC);

    double d_gtime = (double) gtime / CLK_PER_SEC;
    double d_ttime = (double) ttime / CLK_PER_SEC;
    printf("%s is faster %lfs",
            d_gtime < d_ttime ? "Graham" : "Monotone Chain",
            fabs(d_gtime - d_ttime));

    printf("\n-------------\n");

    /*******************************/

    // Monotone Chain with Prunning Test
    clock_t p_ttime = clock();
    chain(R, n, 1);
    p_ttime = clock() - p_ttime;
    printf("Monotone Chain: %lf\n", (double) p_ttime / CLK_PER_SEC);

    // Graham Scan with Prunning Test
    clock_t p_gtime = clock();
    graham(S, n, 1);
    p_gtime = clock() - p_gtime;
    printf("Graham Scan:    %lf\n", (double) p_gtime / CLK_PER_SEC);

    double d_p_gtime = (double) p_gtime / CLK_PER_SEC;
    double d_p_ttime = (double) p_ttime / CLK_PER_SEC;

    printf("%s is faster %lfs",
            d_p_gtime < d_p_ttime ? "Prunned Graham" : "Prunned Monotone Chain",
            fabs(d_p_gtime - d_p_ttime));
    return 0;
}
