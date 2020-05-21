class OneLine(object):

    def __init__(self, color, doors, tires, vtype):
        self.color = color
        self.doors = doors
        self.tires = tires
        self.vtype = vtype

    def reconstructor(self, color, doors, tires, vtype):
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
