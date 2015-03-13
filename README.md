#algorithm-notes
>record some algorithm in studying

##hash.cpp
there are some hash functions in hash.cpp

##Consistent Hash

a consistent hash writen in c++, which has virtual and true nodes, and it can add or delete true and virtual nodes.
But in a consistent hash, i think it must find a compatible scope of a true node hash value, so in this hash, i use
the given virtual nodes hash value to select some suitable true nodes hash value to average the virtual nodes.
