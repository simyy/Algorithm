#!/usr/bin/env python


def merge_sort(A, left, right):
    if left >= right:
        return A
    mid = (left + right) / 2
    A = merge_sort(A, left, mid)
    A = merge_sort(A, mid+1, right)
    A = merge_array(A, left, mid, right)
    return A


def merge_array(A, left, mid, right):
    i, j = left, mid+1
    tmp = list()
    while i <= mid and j <= right:
        if A[i] < A[j]:
            tmp.append(A[i])
            i += 1
        else:
            tmp.append(A[j])
            j += 1
    while i <= mid:
        tmp.append(A[i])
        i += 1
    while j <= right:
        tmp.append(A[j])
        j += 1
    print '##################'
    print A
    A = A[:left] + tmp + A[right+1:]
    print 'to'
    print A
    print '-------'
    print A[left:right+1],'replace',tmp
    return A


print merge_sort([1, 3, 6, 5, 2], 0, 4)
