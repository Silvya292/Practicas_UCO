from rdflib import Graph, URIRef, Literal
from rdflib.namespace import FOAF

g = Graph()
bob = URIRef("http://example.org/people/Bob")

g.add((bob, FOAF.age, Literal(42)))
print(f"Bob tiene {g.value(bob, FOAF.age)} años")
# Se imrpime: Bob tiene 42 años

g.set((bob, FOAF.age, Literal(43)))  # Reemplaza el valor anterior
print(f"Bob tiene ahora {g.value(bob, FOAF.age)} años")
# Se imprime: Bob tiene ahora 43 años

