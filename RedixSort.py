def sort(A):
    max_length = max([len(str(x)) for x in A])
    print max_length

    def at(num, i):
        return (num / (10**i)) % 10

    for i in range(0, max_length):
        tmp = [list() for j in range(10)]
        for item in A:
            print item, i, 'at', at(item, i)
            tmp[at(item, i)].append(item)
        A = reduce(lambda x,y:x+y, tmp, [])

    return A


print sort([0, 6, 23, 1, 51])
