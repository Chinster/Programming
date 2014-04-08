# Exercise 44: Inheritance vs Composition

# method Inheritance
class Parent( object ):
    def method( self ):
        print( "PARENT method()" )

class Child( Parent ):
    pass

dad = Parent()
son = Child()
dad.method()
son.method()

# Override Explicitly
class Child2( Parent ):
    def method( self ):
        print( "CHILD override() method()" )

son2 = Child2()
son2.method()

# Alter Before or After
class Child3( Parent ):
    def method( self ):
        print( "CHILD, BEFORE PARENT altered() " )
        super( Child3, self ).method()
        print( "CHILD, AFTER PARENT altered() " )

son3 = Child3()
son3.method()

#Composition - Class possesses an instance of another class
class Other( object):
    def override( self ):
        print( "OTHER override()" )
    def implicit( self ):
        print( "OTHER implicit()" )
    def altered( self ):
        print( "OTHER altered()" )

class Another (object):
    def __init__ (self):
        self.other = Other()
    def implicit (self):
        self.other.implicit()
    def override (self):
        print( "CHILD override()" )
    def altered (self):
        print( "CHILD, BEFORE OTHER altered()" )
        self.other.altered()
        print( "CHILD, AFTER OTHER altered()" )

comp = Another()
comp.implicit()
comp.override()
comp.altered()
