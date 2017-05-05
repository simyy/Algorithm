#!/usr/bin/env python

class Good:
    def __init__(self, i, w, v):
        self.i = i
        self.w = w
        self.v = v

    def __repr__(self):
        return '%s-%s-%s' %(self.i, self.w, self.v) 


def bg(good_list, max_w):
    m = list()
    for i in range(0, len(good_list) + 1):
        tmp = list()
        for j in range(0, max_w + 1):
            tmp.append(0)
        m.append(tmp)

    # goods
    for i in range(1, len(good_list) + 1):
        # good
        g = good_list[i-1]
        print g
        # weight
        for j in range(1, max_w + 1):
            # bigger than current weight, then equal last one
            if j < g.w:
                m[i][j] = m[i-1][j]
            else:
                # g is not in max set
                if m[i-1][j] > m[i-1][j-g.w] + g.v:
                    m[i][j] = m[i-1][j]
                else:
                    m[i][j] = m[i-1][j-g.w] + g.v
    return m


good_list = list()
good_list.append(Good(1, 2, 12))
good_list.append(Good(2, 1, 10))
good_list.append(Good(3, 3, 20))
good_list.append(Good(4, 2, 15))
print bg(good_list, 5)
