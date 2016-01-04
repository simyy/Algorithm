def quick_sort(lst, left, right):
    if left >= right:
        return
    i = left
    j = right
    key = lst[i]

    while i < j:
        while i < j and lst[j] >= key:
            j -= 1 
        lst[i] = lst[j]   
        while i < j and lst[i] <= key:
            i += 1
        lst[j] = lst[i]   

    lst[i] = key   
    quick_sort(lst, left, i - 1)
    quick_sort(lst, i + 1, right)

lst = [9, 2, 1, 7, 6, 8, 5, 3, 4]    
quick_sort(lst, 0, len(lst)- 1)
print lst
