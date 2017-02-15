from __future__ import print_function


class NilNodeObject(object):
    hasInstance = False

    def __init__(self):
        if NilNodeObject.hasInstance:
            raise SyntaxError("NilNodeObject must have only one instance.")
        self.is_red = False
        self.left = self
        self.right = self
        self.parent = self
        NilNodeObject.hasInstance = True

    def __setitem__(self, key, value):
        raise SyntaxError("Cannot set attribute for NilNodeObject")

    def __nonzero__(self):
        return False

    def __bool__(self):
        return False


class RedBlackTreeNode(object):
    Nil = NilNodeObject()

    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.is_red = True
        self.left = RedBlackTreeNode.Nil
        self.right = RedBlackTreeNode.Nil
        self.parent = RedBlackTreeNode.Nil

    def connect(self, other, is_left):
        if not self:
            return
        if is_left:
            self.left = other
        else:
            self.right = other
        if other:
            other.parent = self

    def is_left(self):
        return self.parent and (self.parent.left is self)

    def is_right(self):
        return self.parent and (self.parent.right is self)

    def go_up(self):
        if not self.parent:
            return
        parent = self.parent
        g_parent = parent.parent
        p_is_left = parent.is_left()
        if self.is_left():
            parent.connect(self.right, True)
            self.connect(parent, False)
        else:
            parent.connect(self.left, False)
            self.connect(parent, True)
        if g_parent:
            g_parent.connect(self, p_is_left)
        else:
            self.parent = RedBlackTreeNode.Nil

    def __str__(self):
        return "[%r: %r] -> (%r, %r, %r, %s)" % (
            self.key, self.value,
            self.left.key if self.left else 'Nil',
            self.right.key if self.right else 'Nil',
            self.parent.key if self.parent else 'Nil',
            "RED" if self.is_red else "BLACK")

    def browse(self, indent=""):
        print(indent + str(self))
        if self.left:
            RedBlackTreeNode.browse(self.left, indent + "   .")
        if self.right:
            RedBlackTreeNode.browse(self.right, indent + "   .")


class RedBlackTree(object):
    def __init__(self):
        self.root = RedBlackTreeNode.Nil
        self.size = 0

    def browse(self):
        if self.root:
            self.root.browse()

    def insert(self, key, value):
        x = self.root
        y = RedBlackTreeNode.Nil
        while x:
            y = x
            if key == x.key:
                x.value = value
                return x
            elif key < x.key:
                x = x.left
            else:
                x = x.right
        x = RedBlackTreeNode(key, value)
        ans = x
        if not y:
            self.root = x
        else:
            y.connect(x, key < y.key)
            while y.is_red:
                y = x.parent
                x = y
                
        self.size += 1
        self.root.is_red = False
        return ans

if __name__ == '__main__':

    exit(0)
