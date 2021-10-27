# print -> print()
# changed filter(),map() to list(filter()), list(map())
# iteritems -> items


import collections # OrderedDict
import array # array
from dataclasses import dataclass

# data structure: dictionary (essentially unordered map)

phonebook = { "bob":7654 , "alice":4321 }
squares = { x: x*x for x in range(6) }
element = phonebook["bob"]

# data structure: ordered dictionary (essentially map, remembers insertion order)

phonebook = collections.OrderedDict([("bob",7654) , ("alice",4321)])

# data structure: list  (mutable dynamic array)

arr = ["one","two","three"]
element1 = arr[0]

# data structure: tuple  (immutable array)

arr = ("one", "two", "three")

# data structure: array (space-efficient fixed type dynamic array)

arr = array.array("f", (1.0, 1.5, 2.0, 2.5))

# data structure: string (immutable string)

strr = "abcd"

# data structure: string as a list (mutable string)

strr = list("abcd")

#  classes

class Car:
    def __init__(self):
        self.var1 = "name"

# data class

@dataclass
class Car:
    color: str
    mileage: float



