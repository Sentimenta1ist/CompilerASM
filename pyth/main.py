import os
from globala import kek


class Vehicle(object):
    """docstring"""

    def __init__(self, color, doors, tires, vtype):
        """Constructor"""
        self.color = color
        self.doors = doors
        self.tires = tires
        self.vtype = vtype

    def reconstructor(self, color, doors, tires, vtype):
        """Constructor"""
        self.color = color
        self.doors = doors
        self.tires = tires
        self.vtype = vtype

    def brake(self):
        """
        Stop the car
        """
        return "%s braking" % self.vtype

    def drive(self):
        """
        Drive the car
        """
        return "I'm driving a %s %s!" % (self.color, self.vtype)

    def printThis(self):
        return "%s %d %s %d" % (self.color, self.doors, self.vtype, self.tires)


GlobaLList = []
GlobaLList.append(Vehicle("blue", 5, 4, "car"))
GlobaLList.append(Vehicle("red", 5, 4, "car"))

# print(GlobaLList[0].printThis() + '\n' + GlobaLList[1].printThis())

for obj in GlobaLList:
    print(obj.printThis())

# for i in GlobaLList:
#     print(GlobaLList[1].printThis())


file = open("file.txt", 'r')

for line in file:
    print(line)
