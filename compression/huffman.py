from collections import Counter
import heapq

# Node that stores symbol-frequency pair
class Node:
    def __init__(self, s=None, f=None, l=None, r=None):
        self.symbol = s
        self.freq = f
        self.left = l
        self.right = r
        self.parent = None

    # Takes two nodes and creates their parent
    # with freq = sum of node freqs
    @staticmethod
    def combine(u, v):
        w = Node(f = u.freq + v.freq, l=u, r=v)
        u.parent = w
        v.parent = w
        return w

    # Checks if Node is a leaf
    def is_leaf(self):
        return self.left is None and self.right is None

    # Comparison function required for priority queue
    def __lt__(self, other):
        return self.freq < other.freq

# Huffman encodes message and returns coding tree
def huffman_encode(msg):
    # Priority queue with only leaves
    pq = [Node(s, f) for s, f in Counter(msg).items()]
    leaves = {leaf.symbol: leaf for leaf in pq}
    heapq.heapify(pq)

    # If msg has only one symbol, code it as one zero bit
    if len(pq) == 1:
        return '0' * len(msg), pq[0]

    # Combine nodes until done
    while len(pq) > 1:
        u = heapq.heappop(pq)
        v = heapq.heappop(pq)
        heapq.heappush(pq, Node.combine(u, v))

    # Create dict of coded version of each symbol
    codewords = {}
    tree = pq[0]
    for s, leaf in leaves.items():
        c = ''
        u = leaf
        while u is not pq[0]:
            v = u.parent
            c += '0' if u is v.left else '1'
            u = v
        codewords[s] = c[::-1] # reverse so that path is root-leaf

    # Build coded msg
    coded_msg = ''
    for s in msg:
        coded_msg += codewords[s]

    return coded_msg, tree

# Decodes a Huffman decoded message, given Huffman coding tree
def huffman_decode(coded_msg, tree):
    # If tree only codes one symbol,
    # return decoded_msg right away
    if tree.is_leaf():
        return tree.symbol * len(coded_msg)

    decoded_msg = ''
    v = tree
    # Traverse tree to decode message
    for b in coded_msg:
        if b == '0': # valid since on first iteration tree is not leaf
            v = v.left
        else:
            v = v.right
        if v.is_leaf(): # means we've read a codeword
            decoded_msg += v.symbol
            v = tree # go back to root to read next codeword

    return decoded_msg
