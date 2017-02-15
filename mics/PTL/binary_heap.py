from __future__ import print_function


__all__ = ["EmptyHeapError", "BinaryHeap"]


class EmptyHeapError(Exception):
    pass


class BinaryHeap(object):
    def __init__(self, seq=None, compare=None):
        self._pool = [None]
        self._comp = compare if compare else BinaryHeap.greater
        self._size = 0
        if seq:
            for entry in seq:
                self.push(entry)

    def __bool__(self):
        return self._size > 0

    def __nonzero__(self):
        return self.__bool__()

    def __len__(self):
        return self._size

    def __iter__(self):
        return self._pool.__iter__()

    @staticmethod
    def greater(entry_a, entry_b):
        return entry_a > entry_b

    @staticmethod
    def less(entry_a, entry_b):
        return entry_a < entry_b

    def clear(self):
        self._pool = [None]
        self._size = 0

    def peak(self):
        if self._size > 0:
            return self._pool[1]
        else:
            raise EmptyHeapError

    def push(self, entry):
        self._pool.append(entry)
        self._size += 1
        self._bubble_up(self._size)

    def pop(self):
        if self._size == 1:
            ans = self._pool[1]
            self._pool.pop()
            self._size -= 1
        elif self._size > 1:
            ans = self._pool[1]
            self._pool[1] = self._pool[-1]
            self._pool.pop()
            self._size -= 1
            self._bubble_down(1)
        else:
            raise EmptyHeapError
        return ans

    def _bubble_up(self, index):
        higher = self._comp
        child = index
        while child > 1:
            parent = child / 2
            if higher(self._pool[child], self._pool[parent]):
                temp = self._pool[parent]
                self._pool[parent] = self._pool[child]
                self._pool[child] = temp
            else:
                break
            child = parent

    def _bubble_down(self, index):
        higher = self._comp
        parent = index
        while parent * 2 <= self._size:
            child = parent * 2
            if (child + 1 <= self._size) and higher(self._pool[child + 1], self._pool[child]):
                child += 1
            if higher(self._pool[child], self._pool[parent]):
                temp = self._pool[parent]
                self._pool[parent] = self._pool[child]
                self._pool[child] = temp
            else:
                break
            parent = child

if __name__ == '__main__':
    exit(0)
