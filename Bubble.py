#!/usr/bin/env python

def bubble_sort(A):
    for i in range(0, len(A)):
        stop = True
        for j in range(0, len(A)-i-1):
            if A[j] > A[j+1]:
                A[j], A[j+1] = A[j+1], A[j]
        if stop:
            break
    return A


print bubble_sort([3, 1, 4, 5, 6])
