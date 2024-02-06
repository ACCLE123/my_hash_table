//
//  prime.c
//  hash_table
//
//  Created by yangqi on 2024/2/6.
//

#include "prime.h"


int is_prime(int x) {
    if (x <= 1) return -1;
    if (x == 2) return 1;
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0) return 0;
    return 1;
}
int next_prime(int x) {
    while (!is_prime(x++));
    return x;
}
