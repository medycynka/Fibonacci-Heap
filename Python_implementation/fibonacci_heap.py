from typing import TypeVar, Generic
from fibo_node import FiboNode


T = TypeVar('T')


class FibonacciHeap(Generic[T]):
    def __init__(self, heap: 'FiboNode[T]' = None):
        self.__heap = heap
        self.curr_max = 0
        self.size_ = 0
        self.__was_deletion = False

    # Magic methods
    def __str__(self) -> str:
        ret = "Heap (min key): {0}, all nodes:\n".format(self.__heap.key)
        for i_ in self:
            ret += str(i_)

        return ret

    def __iter__(self):
        self.curr_it = self.__heap
        self.stop = False
        return self

    def __next__(self) -> T:
        if self.curr_it is not None and not self.stop:
            ret = self.curr_it.key
            if not self.__was_deletion:
                if self.curr_it.next_ != self.__heap:
                    self.curr_it = self.curr_it.next_
                else:
                    self.curr_it = None
            else:
                self.curr_it = self.curr_it.get_next_node_for_iter()
                if self.curr_it == self.__heap:
                    self.stop = True

            return ret
        else:
            raise StopIteration

    def __eq__(self, other: 'FibonacciHeap[T]') -> bool:
        if self.size_ != other.size_ or self.__heap != other.__heap:
            return False
        else:
            it = iter(self)
            other_it = iter(other)

            while it is not None and other_it is not None:
                try:
                    i_ = it.__next__()
                    oi_ = other_it.__next__()

                    if i_ != oi_:
                        return False
                except StopIteration:
                    it = None
                    other_it = None

        return True

    def __ne__(self, other: 'FibonacciHeap[T]') -> bool:
        return not self == other

    def __lt__(self, other: 'FibonacciHeap[T]') -> bool:
        if self.size_> other.size_ or self.__heap >= other.__heap:
            return False
        else:
            it = iter(self)
            other_it = iter(other)

            while it is not None and other_it is not None:
                try:
                    i_ = it.__next__()
                    oi_ = other_it.__next__()

                    if i_ >= oi_:
                        return False
                except StopIteration:
                    it = None
                    other_it = None

        return True

    def __le__(self, other: 'FibonacciHeap[T]') -> bool:
        return not self > other

    def __gt__(self, other: 'FibonacciHeap[T]') -> bool:
        if self.size_< other.size_ or self.__heap <= other.__heap:
            return False
        else:
            it = iter(self)
            other_it = iter(other)

            while it is not None and other_it is not None:
                try:
                    i_ = it.__next__()
                    oi_ = other_it.__next__()

                    if i_ <= oi_:
                        return False
                except StopIteration:
                    it = None
                    other_it = None

        return True

    def __ge__(self, other: 'FibonacciHeap[T]') -> bool:
        return not self < other

    def __len__(self) -> int:
        return self.size_

    # Private methods
    def __empty(self):
        return None

    def __singleton(self, value: T) -> 'FiboNode[T]':
        n = FiboNode[T]()
        n.key = value
        n.prev_ = n
        n.next_ = n
        n.degree = 0
        n.marked = False
        n.parent = None
        n.child = None
        return n

    def __merge(self, a: 'FiboNode[T]', b: 'FiboNode[T]') -> 'FiboNode[T]':
        if a is None:
            return b
        if b is None:
            return a
        if a.key > b.key:
            temp = a
            a = b
            b = temp

        an = a.next_
        bp = b.prev_
        a.next_ = b
        b.prev_ = a
        an.prev_ = bp
        bp.next_ = an
        return a

    def __add_child(self, parent: 'FiboNode[T]', child: 'FiboNode[T]'):
        child.prev_ = child
        child.next_ = child
        child.parent = parent
        parent.degree += 1
        parent.child = self.__merge(parent.child, child)

    def __unmark_and_unparent_all(self, n: 'FiboNode[T]'):
        if n is None:
            return

        c = n
        while True:
            c.marked = False
            c.parent = None
            c = c.next_
            if c == n:
                break

    def __remove_minimum(self, n: 'FiboNode[T]') -> 'FiboNode[T]':
        self.__unmark_and_unparent_all(n.child)

        if n.next_ == n:
            n = n.child
        else:
            n.next_.prev_ = n.prev_
            n.prev_.next_ = n.next_
            n = self.__merge(n.next_, n.child)

        if n is None:
            return n

        trees = [None for x in range(64)]
        while True:
            if trees[n.degree] is not None:
                t = trees[n.degree]
                if t == n:
                    break

                if n.key < t.key:
                    t.prev_.next_ = t.next_
                    t.next_.prev_ = t.prev_
                    self.__add_child(n, t)
                else:
                    t.prev_.next_ = t.next_
                    t.next_.prev_ = t.prev_

                    if n.next_ == n:
                        t.next_ = t
                        t.prev_ = t
                        self.__add_child(t, n)
                        n = t
                    else:
                        n.prev_.next_ = t
                        n.next_.prev_ = t
                        t.next_ = n.next_
                        t.prev_ = n.prev_
                        self.__add_child(t, n)
                        n = t
            else:
                trees[n.degree] = n

            n = n.next_

        min = n
        stat = n
        while True:
            if n.key < min.key:
                min = n
            n = n.next_
            if n == stat:
                break

        return min

    def __cut(self, heap_: 'FiboNode[T]', n: 'FiboNode[T]') -> 'FiboNode[T]':
        if n.next_ == n:
            n.parent.child = None
        else:
            n.next_.prev_ = n.prev_
            n.prev_.next_ = n.next_
            n.parent.child = n.next_

        n.next_ = n.prev_ = n
        n.marked = False

        return self.__merge(heap_, n)

    def __decrease_key(self, heap_: 'FiboNode[T]', n: 'FiboNode[T]', value: T) -> 'FiboNode[T]':
        if n.key < value:
            return heap_

        n.key = value
        if n.parent:
            if n.key < n.parent.key:
                self.__heap = self.__cut(self.__heap, n)
                parent = n.parent
                n.parent = None

                while parent is not None and parent.marked:
                    self.__heap = self.__cut(self.__heap, parent)
                    n = parent
                    parent = n.parent
                    n.parent = None

                if parent is not None and parent.parent is not None:
                    parent.marked = True
        elif n.key < self.__heap.key:
            self.__heap = n

        return heap_

    def __find(self, heap_: 'FiboNode', value: T) -> 'FiboNode[T]' or None:
        n = heap_
        if n is None:
            return None

        while True:
            if n.key == value:
                return n
            ret = self.__find(n.child, value)
            if ret:
                return ret
            n = n.next_

            if n == heap_:
                break

        return None

    def __display_heap(self, in_: 'FiboNode[T]'):
        if in_:
            c = in_
            print("Minimum: {0}".format(self.__heap.key))
            while True:
                self.__display_childrens(c)
                c = c.next_
                if c == in_:
                    break

    def __display_childrens(self, n: 'FiboNode[T]'):
        if n:
            print("Key: {0}, marked: {1}, -> next: {2}, -> prev: {3}".format(n.key, n.marked, n.next_.key, n.prev_.key))
            if n.has_parent():
                print("Parent: {0}".format(n.parent.key))
            else:
                print("No parent")

            if n.has_children():
                c = n.child
                while True:
                    print("Parent: {0}, child: {1}".format(n.key, n.child.key))
                    self.__display_childrens(c)
                    c = c.next_
                    if c == n.child:
                        break
            else:
                print("No child")

    # Public methods
    def empty(self) -> bool:
        return self.size_ == 0 and self.__heap is None

    def insert(self, value: T) -> 'FiboNode[T]':
        ret = self.__singleton(value)
        if ret:
            self.size_ += 1
            if ret.key > self.curr_max:
                self.curr_max = ret.key

        self.__heap = self.__merge(self.__heap, ret)
        return ret

    def merge(self, other: 'FibonacciHeap[T]'):
        self.__heap = self.__merge(self.__heap, other.__heap)
        other.__heap = None

    def remove_minimum(self) -> T:
        old = self.__heap
        self.__heap = self.__remove_minimum(self.__heap)
        ret = old.key
        del old
        self.size_ -= 1
        self.__was_deletion = True
        return ret

    def display_heap(self):
        if self.empty():
            print("Heap is empty")
        else:
            self.__display_heap(self.__heap)

    def decrease_key(self, n: 'FiboNode[T]', value: T):
        self.__heap = self.__decrease_key(self.__heap, n, value)

    def find(self, value: T) -> bool:
        if self.__find(self.__heap, value):
            return True
        else:
            return False

    def get_minimum(self) -> T:
        return self.__heap.key

    def get_root(self) -> 'FiboNode[T]' or None:
        return self.__heap

    def size(self):
        return self.size_

    def get_max(self) -> T:
        return self.curr_max

    def clear(self):
        while not self.empty():
            self.remove_minimum()

        self.size_ = 0
        self.curr_max = 0
        self.__heap = None
        self.__was_deletion = False


if __name__ == '__main__':
    f = FibonacciHeap[int]()
    f.insert(0)
    f.insert(1)
    f.insert(2)
    f.insert(3)
    f.insert(4)
    f.display_heap()
    f.remove_minimum()
    for i in f:
        print(i)
