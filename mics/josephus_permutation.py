from __future__ import print_function


class AvlSetNode(object):
    def __init__(self, key):
        self.key = key
        self.count_child = 1
        self.height = 1
        self.left = None
        self.right = None
        self.parent = None

    def left_count(self):
        return self.left.count_child if self.left else 0

    def right_count(self):
        return self.right.count_child if self.right else 0

    def left_height(self):
        return self.left.height if self.left else 0

    def right_height(self):
        return self.right.height if self.right else 0

    def is_left(self):
        return self.parent and (self.parent.left == self)

    def is_right(self):
        return self.parent and (self.parent.right == self)

    def rotate_left(self):
        parent = self.parent
        right = self.right

        if right is None:
            return

        if self.is_left():
            parent.left = right
        elif self.is_right():
            parent.right = right
        right.parent = parent

        self.right = right.left
        if right.left:
            right.left.parent = self

        right.left = self
        self.parent = right

        self.height = max(self.left_height(), self.right_height()) + 1
        right.height = max(right.left_height(), right.right_height()) + 1

        self.count_child = self.left_count() + self.right_count() + 1
        right.count_child = right.left_count() + right.right_count() + 1

    def rotate_right(self):
        parent = self.parent
        left = self.left

        if left is None:
            return

        if self.is_left():
            parent.left = left
        elif self.is_right():
            parent.right = left
        left.parent = parent

        self.left = left.right
        if left.right:
            left.right.parent = self

        left.right = self
        self.parent = left

        self.height = max(self.left_height(), self.right_height()) + 1
        left.height = max(left.left_height(), left.right_height()) + 1

        self.count_child = self.left_count() + self.right_count() + 1
        left.count_child = left.left_count() + left.right_count() + 1

    def __str__(self):
        return "[%r] -> (%r, %r, %r, cnt = %r, h = %r)" % (
            self.key,
            self.left.key if self.left else None,
            self.right.key if self.right else None,
            self.parent.key if self.parent else None, self.count_child, self.height)

    def __repr__(self):
        return "%r" % self.key

    def connect(self, left=None, right=None):
        if left:
            left.parent = self
            self.left = left
        if right:
            right.parent = self
            self.right = right
        self.height = max(self.left_height(), self.right_height()) + 1
        self.count_child = self.left_count() + self.right_count() + 1


class AvlSet(object):
    def __init__(self, seq=None):
        from collections import Iterable
        self._root = None
        if isinstance(seq, Iterable):
            for entry in seq:
                self.insert(entry)

    def rec_ins(self, seq, left, right):
        if left <= right:
            mid = (left + right) / 2
            node = self.insert(seq[mid], avl_balance=False)
            self.rec_ins(seq, left, mid - 1)
            self.rec_ins(seq, mid + 1, right)
            node.count_child = node.left_count() + node.right_count() + 1

    def __str__(self):
        def browse(node, indent=""):
            browse.ans += indent + str(node) + '\n'
            if node.left:
                browse(node.left, indent + "   .")
            if node.right:
                browse(node.right, indent + "   .")
        browse.ans = ''
        if self._root:
            browse(self._root)
        return browse.ans

    def insert(self, key, avl_balance=True):
        if self._root is None:
            self._root = AvlSetNode(key)
            return self._root

        y = self._root
        x = None
        while y is not None:
            x = y
            if key < y.key:
                y = y.left
            elif key > y.key:
                y = y.right
            else:
                return x

        if key < x.key:
            x.connect(left=AvlSetNode(key))
            y = x.left
        elif key > x.key:
            x.connect(right=AvlSetNode(key))
            y = x.right

        if not avl_balance:
            return y

        ans = y
        x = None
        g = None

        while y:
            y.height = max(y.left_height(), y.right_height()) + 1
            y.count_child = y.left_count() + y.right_count() + 1
            g = x
            x = y
            y = y.parent
            if y is None:
                break
            if not (-1 <= y.left_height() - y.right_height() <= 1):
                if g.is_left() and x.is_left():
                    y.rotate_right()
                    y = x.parent
                elif g.is_right() and x.is_right():
                    y.rotate_left()
                    y = x.parent
                elif g.is_right() and x.is_left():
                    x.rotate_left()
                    y.rotate_right()
                    y = g.parent
                    g = x
                    x = y.left if y else None
                elif g.is_left() and x.is_right():
                    x.rotate_right()
                    y.rotate_left()
                    y = g.parent
                    g = x
                    x = y.left if y else None

        x = self._root
        while x.parent is not None:
            x = x.parent
        self._root = x

        return ans

    def find(self, key):
        node = self._root
        while node is not None:
            if key < node.key:
                node = node.left
            elif key > node.key:
                node = node.right
            else:
                return node
        return None

    def find_max(self, node=None):
        if node is None:
            node = self._root
        while node and node.right:
            node = node.right
        return node

    def erase(self, key):
        x = self.find(key)
        if x is None:
            return

        if x.left and x.right:
            y = self.find_max(x.left)
            x.key = y.key
            x = y

        if x.parent is None:
            if x.right:
                self._root = x.right
            else:
                self._root = x.left
            if self._root:
                self._root.parent = None
            return
        elif x.is_left():
            x.parent.left = x.left if x.left else x.right
        elif x.is_right():
            x.parent.right = x.left if x.left else x.right

        if x.left:
            x.left.parent = x.parent
        elif x.right:
            x.right.parent = x.parent

        x = x.parent

        while x:
            if not (-1 <= x.left_height() - x.right_height() <= 1):
                y = x.right if x.right_height() > x.left_height() else x.left
                z = y.right if y.right_height() > y.left_height() else y.left
                if z.is_left() and y.is_left():
                    x.rotate_right()
                    x = y
                elif z.is_right() and y.is_right():
                    x.rotate_left()
                    x = y
                elif z.is_right() and y.is_left():
                    y.rotate_left()
                    x.rotate_right()
                    x = z
                elif z.is_left() and y.is_right():
                    y.rotate_right()
                    x.rotate_left()
                    x = z
            x.height = max(x.left_height(), x.right_height()) + 1
            x.count_child = x.left_count() + x.right_count() + 1
            x = x.parent

        x = self._root
        while x.parent is not None:
            x = x.parent
        self._root = x

    def locate(self, index, node=None):
        if index <= 0 or index > self._root.count_child:
            return None
        curr_child = node.left_count() + 1
        if index == curr_child:
            return node
        elif index > curr_child:
            return self.locate(index - curr_child, node.right)
        else:
            return self.locate(index, node.left)

    def __len__(self):
        return self._root.count_child


def josephus(m, n):
    h = AvlSet()
    h.rec_ins(range(1, n + 1), 0, n - 1)
    ans = [m]
    h.erase(m)
    last_idx = m
    n -= 1
    while n >= m:
        last_idx += m - 1
        if last_idx > n:
            last_idx -= n
        node = h.locate(last_idx, h._root)
        ans.append(node.key)
        h.erase(node.key)
        n -= 1
    while n > 0:
        node = h.locate(1, h._root)
        # print(node.key)
        ans.append(node.key)
        h.erase(node.key)
        n -= 1
    return ans


def f_my_own(n, i, s):
    """
    :param n: size of seq [1..n]
    :param i: i-th element to be calculated the position in josephus permutation
    f[i, n] = f[i - k, n - 1] + 1      , if i > k
    f[i, n] = f[i + n - k, n - 1] + 1  , otherwise
    """
    def rec(n, i):
        if (n, i) in rec.dp:
            return rec.dp[(n, i)]
        ans = 1
        if n < s:
            ans = n
        elif i > s:
            ans = rec(n - 1, i - s) + 1
        elif i < s:
            ans = rec(n - 1, i + n - s) + 1
        rec.dp.update({(n, i): ans})
        return ans
    rec.dp = {}
    ans = rec(n, i)
    return ans


def main():
    return 0

if __name__ == '__main__':
    exit(main())

