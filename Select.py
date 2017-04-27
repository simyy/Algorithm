#!/usr/bin/env python

def select_sort(A):
    for i in range(0, len(A)):
        index = i
        for j in range(i + 1, len(A)):
            if A[index] > A[j]:
                print index, j
                index = j
        if index != i:
            A[index], A[i] = A[i], A[index]
    return A


print select_sort([1, 5, 3, 6, 2])
