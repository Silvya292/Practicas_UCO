from rdflib import Graph, URIRef, Literal
from rdflib.namespace import FOAF

# URIRef
person = URIRef("http://xmlns.com/foaf/0.1/Person")
print(person.n3())

# Se simplifica el output con un prefijo de namespace
g = Graph()
g.bind("foaf", FOAF)

print(person.n3(g.namespace_manager))

# Literal
l = Literal(2)
print(l.n3())

# Se simplifica el output con un prefijo de namespace
l.n3(g.namespace_manager)

