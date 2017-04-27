#!/usr/bin/env python


def insert_sort(A):
    for i in range(1, len(A)):
        for j in range(0, i):
            if A[j] > A[i]:
                tmp = A[i]
                for k in range(i, j, -1):
                    A[k] = A[k-1]
                A[j] = tmp
                break
    return A


print insert_sort([1, 5, 2, 8, 3])
