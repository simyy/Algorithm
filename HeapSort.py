"""
This is the heap sort algorithm.
================================
1. Create a heap array[0, ..., n-1];
2. Sift heap array, get the max one for max heap;
3. Replace the last one with max one, then repeat above operator.
4. finish
"""

def heap_sort(lst):
    # sort all parent node in reversed order, then lst[0] must the max one
    for start in range(len(lst)/2 - 1, 0, -1):
        sift_down(lst, start, len(lst) - 1)
    # move the max one in the last of array, then compare with the new one
    for end in range(len(lst)-1, 0, -1):  
        lst[0], lst[end] = lst[end], lst[0]
        sift_down(lst, 0, end - 1)
    return lst  


def sift_down(lst, start, end):
    """ sift max heap node """
    root = start
    while True:
        child = 2 * root + 1
        if child > end:
            break
        # find the maxium
        if child + 1 <= end and lst[child] < lst[child + 1]:
            child += 1
        # if find it, then sift in its childs, or break to finish
        if lst[root] < lst[child]:
            lst[root], lst[child] = lst[child], lst[root]
            root = child
        else:
            break


l = [9, 2, 1, 7, 6, 8, 5, 4, 3]
print heap_sort(l)
