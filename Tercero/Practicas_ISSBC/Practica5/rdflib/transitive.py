if __name__ == "__main__":
    from rdflib import ConjunctiveGraph, URIRef

    person = URIRef("ex:person")
    dad = URIRef("ex:d")
    mom = URIRef("ex:m")
    momOfDad = URIRef("ex:gm0")
    momOfMom = URIRef("ex:gm1")
    dadOfDad = URIRef("ex:gf0")
    dadOfMom = URIRef("ex:gf1")

    parent = URIRef("ex:parent")

    g = ConjunctiveGraph()
    g.add((person, parent, dad))
    g.add((person, parent, mom))
    g.add((dad, parent, momOfDad))
    g.add((dad, parent, dadOfDad))
    g.add((mom, parent, momOfMom))
    g.add((mom, parent, dadOfMom))

    print("Parents, forward from `ex:person`:")
    for i in g.transitive_objects(person, parent):
        print(i)

    print("Parents, *backward* from `ex:gm1`:")
    for i in g.transitive_subjects(parent, momOfMom):
        print(i)

