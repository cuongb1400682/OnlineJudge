from __future__ import print_function
from random import random


__all__ = ["RandomizedSplayTree"]


class RandomizedSplayTreeNode(object):
    """\
    This class represents the node in splay tree
    """
    def __init__(self, _key=None, _val=None):
        self.left = None
        self.right = None
        self.parent = None
        self.key = _key
        self.val = _val

    def is_left(self):
        """\
        Checks whether the node is in the left of its parent
        provided it has parent (not root)
        """
        return self.parent and (self.parent.left == self)

    def is_right(self):
        """\
        Checks whether the node is in the right of its parent
        provided it has parent (not root)
        """
        return self.parent and (self.parent.right == self)

    def rotate_left(self):
        """\
        Rotates the node to the left. Turns its right child into its parent,
        connects the node with the left child of its right child
        """
        if self.right is None:
            return
        # connect x.parent and x.right
        self_right = self.right
        self_parent = self.parent
        if self.is_left():
            self_parent.left = self_right
        elif self.is_right():
            self_parent.right = self_right
        self_right.parent = self_parent
        # connect x and x.right.A
        self.right = self_right.left
        if self_right.left:
            self_right.left.parent = self
        # connect x.right and x
        self_right.left = self
        self.parent = self_right

    def rotate_right(self):
        """\
        Rotates the node to the right. Turns its left child into its parent,
        connects the node with the right child of its left child
        """
        if self.left is None:
            return
        # connect x.left and x.parent
        self_left = self.left
        self_parent = self.parent
        if self.is_left():
            self_parent.left = self_left
        elif self.is_right():
            self_parent.right = self_left
        self_left.parent = self_parent
        # connect x and x.left.B
        self.left = self_left.right
        if self_left.right:
            self_left.right.parent = self
        # connect x.left and x
        self_left.right = self
        self.parent = self_left

    def connect(self, left=None, right=None):
        if left:
            left.parent = self
            self.left = left
        if right:
            right.parent = self
            self.right = right


class RandomizedSplayTreeIterator(object):
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


class RandomizedSplayTree(object):
    def __init__(self, seq=None, prob_threshold=0.125, prob_func=None, **kwargs):
        self._root = None
        self._size = 0
        self._prob_threshold = prob_threshold
        self._prob_func = prob_func
        if isinstance(seq, tuple):
            for (k, w) in seq:
                self[k] = w
        elif isinstance(seq, dict):
            for k in seq:
                self[k] = seq[k]
        for k in kwargs:
            self[k] = kwargs[k]

    def __len__(self):
        return self._size

    def __bool__(self):
        return self._size > 0

    def __contains__(self, key):
        return self.find(key) is not None

    def __iter__(self):
        return RandomizedSplayTreeIterator(self.keys())

    def __getitem__(self, key):
        """\
        Returns the node that has the given key if exists. Otherwise, adds one with value is None
        """
        x = self.find(key)
        if x is None:
            return self.insert(key, None).val
        else:
            self._splay(x)
            return self._root.val

    def __setitem__(self, key, value):
        self.insert(key, value)

    def __delitem__(self, key):
        self.erase(key)

    def __str__(self):
        def rec(root, indent="", p_height=0):
            if root is None:
                return
            rec.height = max(rec.height, p_height)
            rec.ans += (indent + "[%r : %r] -> %r\n" % (root.key, root.val,
                                                        (root.left.key if root.left else None,
                                                         root.right.key if root.right else None,
                                                         root.parent.key if root.parent else None)))
            rec(root.left, indent + "   .", p_height + 1)
            rec(root.right, indent + "   .", p_height + 1)
        rec.ans = ""
        rec.height = 0
        rec(self._root)
        return rec.ans + "\nTotal %s node%s, height = %s\n" % (self._size, "s" if self._size > 1 else "", rec.height)

    def __repr__(self):
        ans = ""
        for key in self.keys():
            ans += "%r: %r, " % (key, self[key])
        return "{" + ans[:-2] + "}"

    def copy(self):
        from copy import deepcopy
        return deepcopy(self)

    def keys(self):
        def rec(root):
            if root is None:
                return
            rec(root.left)
            rec.ans.append(root.key)
            rec(root.right)
        rec.ans = []
        rec(self._root)
        return rec.ans

    def values(self):
        def rec(root):
            if root is None:
                return
            rec(root.left)
            rec.ans.append(root.val)
            rec(root.right)
        rec.ans = []
        rec(self._root)
        return rec.ans

    def clear(self):
        def rec(root):
            if root is None:
                return
            rec(root.left)
            del root.left
            rec(root.right)
            del root.right
            root.left = None
            root.right = None
            root.parent = None
        rec(self._root)
        self._root = None
        self._size = 0

    def size(self):
        """\
        Returns the number of nodes in the tree. Acts exactly the same as __len__
        """
        return self._size

    def find(self, key):
        """\
        Finds node whose 'key' is key if any. Otherwise, returns None
        """
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
        """\
        Returns the node whose the greatest key is less than key
        """
        node = self._root
        ans = None
        while node is not None:
            if key < node.key:
                node = node.left
            elif key > node.key:
                if (ans is None) or (ans.key < node.key):
                    ans = node
                node = node.right
            else:
                return node
        return ans

    def upper_bound(self, key):
        """\
        Returns the node whose the smallest key is greater than key
        """
        node = self._root
        ans = None
        while node is not None:
            if key < node.key:
                if (ans is None) or (ans.key > node.key):
                    ans = node
                node = node.left
            elif key > node.key:
                node = node.right
        return ans

    def _splay(self, x):
        """\
        Brings node to root. Bottom up implementation
        """
        while x.parent is not None:
            parent = x.parent
            g_parent = parent.parent
            if g_parent is None:
                if x.is_left():
                    parent.rotate_right()
                else:
                    parent.rotate_left()
            elif x.is_left() and parent.is_left():
                parent.rotate_right()
                g_parent.rotate_right()
            elif x.is_right() and parent.is_right():
                parent.rotate_left()
                g_parent.rotate_left()
            elif x.is_right() and parent.is_left():
                parent.rotate_left()
                g_parent.rotate_right()
            elif x.is_left() and parent.is_right():
                parent.rotate_right()
                g_parent.rotate_left()
        self._root = x

    def splay_insert(self, key, val):
        """\
        Adds a new node with then given 'key' and 'val'. If 'key' exists, then this will change
        the value of node own this 'key'. Returns the added node.
        """
        if self._root is None:
            self._root = RandomizedSplayTreeNode(key, val)
        else:
            x = self.lower_bound(key)
            if x is None:
                node = self._root
                while node.left is not None:
                    node = node.left
                node.left = RandomizedSplayTreeNode(key, val)
                node.left.parent = node
                self._splay(node.left)
            elif x.key == key:
                self._splay(x)
                x.val = val
                self._size -= 1
            else:
                self._splay(x)
                self._root = RandomizedSplayTreeNode(key, val)
                self._root.left = x
                x.parent = self._root
                self._root.right = x.right
                if x.right:
                    x.right.parent = self._root
                x.right = None
        self._size += 1
        return self._root

    def normal_insert(self, key, val):
        if self._root is None:
            self._root = RandomizedSplayTreeNode(key, val)
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
                x.value = val
                return x

        if key < x.key:
            x.connect(left=RandomizedSplayTreeNode(key, val))
            y = x.left
        elif key > x.key:
            x.connect(right=RandomizedSplayTreeNode(key, val))
            y = x.right

        ans = y
        self._size += 1
        return ans

    def insert(self, key, val):
        if self._prob_func is None:
            p = random()
        else:
            p = self._prob_func(self, key)
        if p <= self._prob_threshold:
            return self.splay_insert(key, val)
        else:
            return self.normal_insert(key, val)

    def find_min(self, root=None):
        if root is None:
            root = self._root
        while root and root.left:
            root = root.left
        return root

    def find_max(self, root=None):
        if root is None:
            root = self._root
        while root and root.right:
            root = root.right
        return root

    def splay_erase(self, key):
        """\
        Removes a node from the tree if exists
        """

        x = self.find(key)
        if (x is None) or (x.key != key):
            return

        self._size -= 1
        self._splay(x)

        left_tree = x.left
        right_tree = x.right
        x.left = x.right = None

        if left_tree:
            left_tree.parent = None
        if right_tree:
            right_tree.parent = None

        y = self.find_max(left_tree)

        if y is None:
            y = self.find_min(right_tree)
            if y is None:
                self._root = None
                return
            self._splay(y)
            y.left = left_tree
            if left_tree:
                left_tree.parent = y
        else:
            self._splay(y)
            y.right = right_tree
            if right_tree:
                right_tree.parent = y
        self._root = y

    def normal_erase(self, key):
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

    def erase(self, key):
        if self._prob_func is None:
            p = random()
        else:
            p = self._prob_func(self, key)
        if p <= self._prob_threshold:
            self.splay_erase(key)
        else:
            self.normal_erase(key)


if __name__ == '__main__':
    exit(0)

