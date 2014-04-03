correctness = False
try:
    assert correctness
    print( "I'm right." )
except AssertionError:
    assert True
    print( "Still correct." )
