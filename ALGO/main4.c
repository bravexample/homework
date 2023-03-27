#include <stdio.h>

// I find the algorithm online, then I turn it into c code(original cpp).
// https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/

typedef struct {
    long double first;
    long double second;
} iPair;

long double findSide(iPair p1, iPair p2, iPair p) {
    long double val = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

long double lineDist(iPair p1, iPair p2, iPair p) {
    long double temp = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);

    if (temp > 0)
        return temp;
    return temp * -1;
}

long double calTriArea(iPair a, iPair b, iPair c) {
    long double temp = (a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second)) / (long double )2;

    if (temp > 0)
        return temp;
    return temp * -1;
}

long double sum = 0;

void quickHull(iPair *a, long long n, iPair p1, iPair p2, long long side) {
    long long ind = -1;
    long double max_dist = 0;

    for (long long i = 0; i < n; i++) {
        long double temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist) {
            ind = i;
            max_dist = temp;
        }
    }

    if (ind < 0)
        return;
    else
        sum += calTriArea(p1, p2, a[ind]);

    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void zeroFilter(char *str) {
    size_t i = 0;
    for (; str[i]; i++) {}
    for (; str[i] != '.' && str[i] < '1'; i--)
        str[i] = '\0';
    
    if (str[i] == '.' && !str[i + 1])
        str[i] = '\0';
}

void printHull(iPair *a, long long n) {
    if (n < 3) {
        printf("0");
        return;
    }

    long long min_x = 0, max_x = 0;
    for (long long i = 1; i < n; i++) {
        if (a[i].first < a[min_x].first)
            min_x = i;
        if (a[i].first > a[max_x].first)
            max_x = i;
    }

    quickHull(a, n, a[min_x], a[max_x], 1);

    quickHull(a, n, a[min_x], a[max_x], -1);

    char str[200] = {0};
    sprintf(str, "%Lf\n", sum);
    zeroFilter(str);
    printf("%s", str);
}

int main() {
    long long n;
    scanf("%lld", &n);

    iPair a[n];
    for (long long i = 0; i < n; i++)
        scanf("%Lf %Lf", &a[i].first, &a[i].second);

    printHull(a, n);
    return 0;
}
