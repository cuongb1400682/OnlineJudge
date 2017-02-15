from __future__ import print_function


class AvlTreeNode(object):
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.height = 1
        self.left = None
        self.right = None
        self.parent = None

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

    def __str__(self):
        return "[%r: %r] -> (%r, %r, %r, h = %r)" % (
            self.key, self.value,
            self.left.key if self.left else None,
            self.right.key if self.right else None,
            self.parent.key if self.parent else None, self.height)

    def __repr__(self):
        return "%r: %r" % (self.key, self.value)

    # TODO: for debugging
    def browse(self, indent=""):
        print(indent + str(self))
        if self.left:
            self.left.browse(indent + "   .")
        if self.right:
            self.right.browse(indent + "   .")

    def connect(self, left=None, right=None):
        if left:
            left.parent = self
            self.left = left
        if right:
            right.parent = self
            self.right = right
        self.height = max(self.left_height(), self.right_height()) + 1
    # --------------------------


class AvlTreeIterator(object):
    def __init__(self, keys):
        self.keys = keys
        self.pointer = 0

    def __next__(self):
        return self.next()

    def next(self):
        if self.pointer >= len(self.keys):
            raise StopIteration
        else:
            self.pointer += 1
            return self.keys[self.pointer - 1]


class AvlTree(object):
    def __init__(self, seq=None, **kwargs):
        self._root = None
        self._size = 0
        if isinstance(seq, tuple):
            for k, w in seq:
                self[k] = w
        elif isinstance(seq, dict) or isinstance(seq, AvlTree):
            for k in seq:
                self[k] = seq[k]
        elif seq is not None:
            raise NotImplementedError("AvlSet must be initialized with tuple or dictionary")

        for k in kwargs:
            self[k] = kwargs[k]

    def __len__(self):
        return self._size

    def __contains__(self, item):
        return self.find(item) is not None

    def __iter__(self):
        return AvlTreeIterator(self.keys())

    def __getitem__(self, item):
        x = self.find(item)
        if x is None:
            return self.insert(item, None).value
        else:
            return x.value

    def __delitem__(self, key):
        self.erase(key)

    def __setitem__(self, key, value):
        self.insert(key, value)

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

    def __repr__(self):
        def browse(node):
            if node is not browse.self:
                browse.ans.append(repr(node))
            else:
                browse.ans.append("[...]")
                return
            if node.left:
                browse(node.left)
            if node.right:
                browse(node.right)
        browse.ans = []
        browse.self = self
        browse(self._root)
        return '{' + ', '.join(browse.ans) + '}'

    def __bool__(self):
        return self._size > 0

    def __nonzero__(self):
        return self.__bool__()

    def copy(self):
        from copy import deepcopy
        return deepcopy(self)

    def keys(self):
        def browse(node):
            if node is None:
                return
            browse(node.left)
            browse.ans.append(node.key)
            browse(node.right)
        browse.ans = []
        browse(self._root)
        return browse.ans

    def values(self):
        def browse(node):
            if node is None:
                return
            browse(node.left)
            browse.ans.append(node.val)
            browse(node.right)
        browse.ans = []
        browse(self._root)
        return browse.ans

    def navigate(self, node=None):
        if node is None:
            node = self._root
        if node.left:
            for i in self.navigate(node.left):
                yield i
        yield node.key
        if node.right:
            for i in self.navigate(node.right):
                yield i

    def clear(self):
        def browse(node):
            if node is None:
                return
            browse(node.left)
            del node.left
            browse(node.right)
            del node.right
            node.left = None
            node.right = None
            node.parent = None
        browse(self._root)
        self._root = None
        self._size = 0

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

    def lower_bound(self, key):
        node = self._root
        ans = None
        while node is not None:
            if key < node.key:
                if (ans is None) or (ans.key > node.key):
                    ans = node
                node = node.left
            elif key > node.key:
                node = node.right
            else:
                return node
        return ans

    def upper_bound(self, key):
        node = self._root
        ans = None
        while node is not None:
            if key < node.key:
                if (ans is None) or (ans.key > node.key):
                    ans = node
                node = node.left
            else:
                node = node.right
        return ans

    def find_min(self, node=None):
        if node is None:
            node = self._root
        while node and node.left:
            node = node.left
        return node

    def find_max(self, node=None):
        if node is None:
            node = self._root
        while node and node.right:
            node = node.right
        return node

    def insert(self, key, value):
        if self._root is None:
            self._root = AvlTreeNode(key, value)
            self._size = 1
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
                x.value = value
                return x

        if key < x.key:
            x.connect(left=AvlTreeNode(key, value))
            y = x.left
        elif key > x.key:
            x.connect(right=AvlTreeNode(key, value))
            y = x.right

        ans = y
        x = None
        g = None

        while y:
            y.height = max(y.left_height(), y.right_height()) + 1
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

        self._size += 1
        return ans

    def erase(self, key):
        x = self.find(key)
        if x is None:
            return

        if x.left and x.right:
            y = self.find_max(x.left)
            x.key = y.key
            x.value = y.value
            x = y

        if x.parent is None:
            if x.right:
                self._root = x.right
            else:
                self._root = x.left
            if self._root:
                self._root.parent = None
            self._size -= 1
            return
        elif x.is_left():
            x.parent.left = x.left if x.left else x.right
        elif x.is_right():
            x.parent.right = x.left if x.left else x.right

        if x.left:
            x.left.parent = x.parent
        elif x.right:
            x.right.parent = x.parent

        self._size -= 1
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
            x = x.parent

        x = self._root
        while x.parent is not None:
            x = x.parent
        self._root = x


if __name__ == '__main__':
    n = int(raw_input())
    m = int(raw_input())
    h = AvlTree(tuple((i, None) for i in range(1, n + 1)))
    elm = -1
    while len(h) >= m:
        elm = h.lower_bound(elm + 1)
        nxt = elm + m
        if nxt > n:
            nxt %= m
    exit(0)

