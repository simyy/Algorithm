def resort(A, i):
    # j is left child
    j = 2 * i + 1
    # record A[i]
    tmp = A[i]
    # shift down until end
    while j < len(A):
        # find min in childs
        if j + 1 < len(A) and A[j+1] < A[j]:
            j += 1
        # A[j] is smaller child
        # break if smaller than child
        if A[j] >= tmp:
            break
        # otherwise, repalce of facther and child
        A[i] = A[j]
        # for next loop, replace root
        i = j
        # recalcurate first child
        j = 2 * i + 1
    # at last, replace data
    A[i] = tmp


def heap_sort(A):
    # start from last second layer for cmp with its childs
    i = len(A) / 2 - 1
    while i >= 0:
        resort(A, i)
        i -= 1
    return A


print heap_sort([0, 2, 5, 4, 3, 1])
