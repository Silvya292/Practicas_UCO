from rdflib import Graph, URIRef, Literal, BNode
from rdflib.namespace import FOAF, RDF

g = Graph()
g.bind("foaf", FOAF)

# Se añaden los datos
bob = URIRef("http://example.org/people/Bob")
g.add((bob, RDF.type, FOAF.Person))
g.add((bob, FOAF.name, Literal("Bob")))
g.add((bob, FOAF.age, Literal(38)))

# Para obtener un valor, se usa 'value'
print(g.value(bob, FOAF.age))

# Para cambiar un valor, se usa 'set'
g.set((bob, FOAF.age, Literal(39)))
print(g.value(bob, FOAF.age))
