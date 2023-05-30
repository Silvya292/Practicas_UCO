from rdflib import XSD, Graph, Literal, Namespace, term

if __name__ == "__main__":
    #term.bind(XSD.complexNumber, complex)

    # Create a complex number RDFlib Literal
    EG = Namespace("http://example.com/")
    c = complex(2, 3)
    l = Literal(c)

    # Add it to a graph
    g = Graph()
    g.add((EG.mysubject, EG.myprop, l))
    print(list(g)[0])

    # Round-trip through n3 serialize/parse
    g2 = Graph().parse(data=g.serialize())

    l2 = list(g2)[0]
    print(l2)

    # Compare with the original python complex object (should be True)
    # l2[2] is the object of the triple
    assert isinstance(l2[2], Literal)
    print(l2[2].value == c)

