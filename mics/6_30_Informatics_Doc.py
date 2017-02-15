from __future__ import print_function


class AvlNode(object):
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.left = None
        self.right = None
        self.parent = None
        self.count = 1
        self.height = 1

    def connect(self, other, is_left):
        if is_left:
            self.left = other
        else:
            self.right = other
        if other:
            other.parent = self
        self.height = max(self.left_height(), self.right_height()) + 1
        self.count = self.left_count() + self.right_count() + 1

    def is_left(self):
        return self.parent and (self.parent.left is self)

    def is_right(self):
        return self.parent and (self.parent.right is self)

    def left_height(self):
        return self.left.height if self.left else 0

    def left_count(self):
        return self.left.count if self.left else 0

    def right_height(self):
        return self.right.height if self.right else 0

    def right_count(self):
        return self.right.count if self.right else 0

    def go_up(self):
        if self.parent is None:
            return

        parent = self.parent
        grand_parent = parent.parent
        is_left = parent.is_left()

        if self.is_left():
            parent.connect(self.right, True)
            self.connect(parent, False)
        elif self.is_right():
            parent.connect(self.left, False)
            self.connect(parent, True)

        parent.height = max(parent.left_height(), parent.right_height()) + 1
        self.height = max(self.left_height(), self.right_height()) + 1

        parent.count = parent.left_count() + parent.right_count() + 1
        self.count = self.left_count() + self.right_count() + 1

        if grand_parent:
            grand_parent.connect(self, is_left)
        else:
            self.parent = None

    def __str__(self):
        return '[%s: %s] -> (%s, %s, %s, h = %s, cnt = %s)' % (self.key, self.value,
                                                               self.left.key if self.left else None,
                                                               self.right.key if self.right else None,
                                                               self.parent.key if self.parent else None,
                                                               self.height, self.count)

    def browse(self, indent=""):
        print(indent + str(self))
        if self.left:
            self.left.browse(indent + "   .")
        if self.right:
            self.right.browse(indent + "   .")


class AvlTree(object):
    def __init__(self, seq=None):
        self.root = None
        if seq:
            for entry in seq:
                self.insert(entry)

    def browse(self, node=None):
        if node is None:
            node = self.root
        if node.left:
            for n in self.browse(node.left):
                yield n
        yield node
        if node.right:
            for n in self.browse(node.right):
                yield n

    def insert(self, key):
        x = self.root
        if x is None:
            self.root = AvlNode(key, 0)
            return self.root
        y = None
        while x:
            y = x
            if key < x.key:
                x = x.left
            else:
                x = x.right
        x = AvlNode(key, 0)
        y.connect(x, y.key > key)
        z = x
        while z:
            if z.key > key:
                x.value += z.right_count() + 1
            z = z.parent
        ans = x
        while x:
            if not (-1 <= x.left_height() - x.right_height() <= 1):
                if (y.is_left() and z.is_right()) or (y.is_right() and z.is_left()):
                    z.go_up()
                    z, y = y, z
                y.go_up()
                x, y = y, x
            x.height = max(x.left_height(), x.right_height()) + 1
            x.count = x.left_count() + x.right_count() + 1
            z = y
            y = x
            x = x.parent
        x = self.root
        while x.parent:
            x = x.parent
        self.root = x
        return ans


def brute_force(seq):
    seq_len = len(seq)
    ans = [0 for i in range(0, seq_len)]
    for i in range(1, seq_len):
        for j in range(0, i):
            if seq[j] > seq[i]:
                ans[seq[i] - 1] += 1
    return ans


def main():
    from itertools import permutations
    n = int(raw_input())
    for L in permutations(range(1, n + 1)):
        h = AvlTree(L)
        A = [node.value for node in h.browse()]
        B = brute_force(L)
        if A != B:
            print(L)
            break
    return 0

if __name__ == '__main__':
    exit(main())

