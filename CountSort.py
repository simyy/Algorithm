"""
Count Sort in Pyton.
===================
1. must be known the max one in array;
2. use a array which its length is max one size to store the number count(a[i] means the number of appears in array);
3. finally, append a list of i in length of the array[i] in result.
"""

def count_sort(a, l):
    c = list()
    for i in xrange(l + 1):
        c.append(0)
    for item in a:
        c[item] += 1
        print item, c
    r = list()    
    for i in xrange(len(c)):
        r.extend([i] * c[i])
    return r


lst = [9, 2, 1, 7, 1, 8, 5, 3, 4]    
print count_sort(lst, 9)
