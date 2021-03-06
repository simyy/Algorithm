#!/usr/bin/evn python

class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right


def dfs(root):
    result = list()
    if not root:
        return result
    result.append(root.value)
    if root.left:
        result += dfs(root.left)
    if root.right:
        result += dfs(root.right)
    return result


node5 = Node(5)
node6 = Node(6)
node4 = Node(4, left=node5, right=node6)
node3 = Node(3)
node2 = Node(2)
node1 = Node(1, node4, node3)
root = Node(0, node1, node2)


print dfs(root)
