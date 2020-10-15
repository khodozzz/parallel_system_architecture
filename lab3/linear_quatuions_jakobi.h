#pragma once

#include <cstring>
#include <cmath>


double calcRelativeX(double *& a, const int & shifta, double *& x, double & b, const int & N)
{
    double rel_x = 0;

    for (int i = 0; i < N; ++i)
        rel_x += a[i] * x[i];

    return (b - rel_x) / a[shifta];
}

double calcAccuracy(double *& x1, double *& x0, const int & N)
{
    double maxDiff = 0;
    double curDiff = 0;

    for (int i = 0; i < N; ++i)
        if ((curDiff = x1[i] - x0[i]) > maxDiff)
            maxDiff = curDiff;

    return sqrt(maxDiff);
}

void yakobi(double *& A, double *& x, double *& b, const int &N)
{
    const double eps = 0.001;

    auto * x_cur = new double [N];
    memcpy(x_cur, x, sizeof(double) * N);

    auto * x_prev = new double [N];

    double *a = nullptr;

    do {
        memcpy(x_prev, x_cur, sizeof(double) * N);

        for (int i = 0; i < N; ++i) {
            a = A + i * N;
            x_cur[i] = calcRelativeX(a, i, x_prev, b[i], N);
        }
    } while(calcAccuracy(x_cur, x_prev, N) >= eps);

    memcpy(x, x_cur, sizeof(double) * N);

    delete [] x_cur;
    delete [] x_prev;
}