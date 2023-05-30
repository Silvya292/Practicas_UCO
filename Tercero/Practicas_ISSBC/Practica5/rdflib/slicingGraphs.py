#for i in range(20)[2:9:3]:
#    print(i)

from rdflib import Graph, URIRef, Literal, BNode
from rdflib.namespace import FOAF, RDF

g = Graph()
g.bind("foaf", FOAF)

# Se añaaden los datos
bob = URIRef("http://example.org/people/Bob")
bill = URIRef("http://example.org/people/Bill")
g.add((bob, RDF.type, FOAF.Person))
g.add((bob, FOAF.name, Literal("Bob")))
g.add((bob, FOAF.age, Literal(38)))
g.add((bob, FOAF.knows, bill))

print(g[:])
print(iter(g))

print(g[bob])
print(g.predicate_objects(bob))

print(g[bob: FOAF.knows])
print(g.objects(bob, FOAF.knows))

print(g[bob: FOAF.knows: bill])
print((bob, FOAF.knows, bill) in g)

print(g[:FOAF.knows])
print(g.subject_objects(FOAF.knows))

