from typing import TypeVar, Generic


T = TypeVar('T')


class FiboNode(Generic[T]):
    def __init__(self, key: T = None, prev_: 'FiboNode[T]' = None, next_: 'FiboNode[T]' = None,
                 child: 'FiboNode[T]' = None, parent: 'FiboNode[T]' = None, degree: int = 0, marked: bool = False):
        if key is None:
            self.key = -1
        else:
            self.key = key
        self.prev_ = prev_
        self.next_ = next_
        self.child = child
        self.parent = parent
        self.degree = degree
        self.marked = marked
        self.__iter_marked = False

    # Magic Methods:
    def __eq__(self, other: 'FiboNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key == other.key
            else:
                return False
        else:
            return False

    def __ne__(self, other: 'FiboNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key != other.key
            else:
                return False
        else:
            return False

    def __lt__(self, other: 'FiboNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key < other.key
            else:
                return False
        else:
            return False

    def __le__(self, other: 'FiboNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key <= other.key
            else:
                return False
        else:
            return False

    def __gt__(self, other: 'FiboNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key > other.key
            else:
                return False
        else:
            return False

    def __ge__(self, other: 'FiboNode[T]') -> bool:
        if self is not None and other is not None:
            if type(self.key) == type(other.key):
                return self.key >= other.key
            else:
                return False
        else:
            return False

    def __bool__(self):
        if self is not None:
            return self.key is not None
        else:
            return False

    def __str__(self) -> str:
        ret = "Key: {0}, degree: {1}".format(self.key, self.degree)
        if self.parent:
            ret += "Parent key: {}".format(self.parent.key)
        else:
            ret += "No parent"
        if self.child:
            ret += "Child key: {}".format(self.child.key)
        else:
            ret += "No child"
        if self.prev_:
            ret += "Previous key: {}".format(self.prev_.key)
        else:
            ret += "No prev"
        if self.next_:
            ret += "Next key: {}".format(self.next_.key)
        else:
            ret += "No next"
        return ret

    def __repr__(self) -> str:
        return "NODE-> Key={0}, degree={1} : [Parent: {2}, child: {3}, prev: {4}, next: {5}]".format(self.key,
                                                                                                     self.degree,
                                                                                                     self.parent.key,
                                                                                                     self.child.key,
                                                                                                     self.prev_.key,
                                                                                                     self.next_.key)

    def __getitem__(self, item: int) -> T:
        if item < 0 or item > 4:
            raise IndexError
        else:
            if item == 0:
                return self.key
            elif item == 1:
                return self.parent.key
            elif item == 2:
                return self.child.key
            elif item == 3:
                return self.prev_.key
            elif item == 4:
                return self.next_.key

    def has_children(self) -> bool:
        return self.child is not None

    def has_parent(self) -> bool:
        return self.parent is not None

    def get_next_node_for_iter(self) -> 'FiboNode[T]' or None:
        if self is not None:
            if self.has_children() and not self.child.__iter_marked:
                self.child.__iter_marked = True
                return self.child
            elif not self.prev_.__iter_marked:
                self.prev_.__iter_marked = True
                return self.prev_
            elif not self.next_.__iter_marked:
                self.next_.__iter_marked = True
                return self.next_

            bfs = self

            while True:
                bfs = bfs.parent
                if bfs is None or not bfs.has_parent() or not bfs.parent.__iter_marked:
                    break

            if bfs is not None and not bfs.prev_.__iter_marked:
                bfs.prev_.__iter_marked = True
                return bfs.prev_
            elif bfs is not None and not bfs.next_.__iter_marked:
                bfs.next_.__iter_marked = True
                return bfs.next_
            else:
                return None

        return None
