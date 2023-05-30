from rdflib import Graph
from rdflib.namespace import FOAF

g = Graph()
# Se obtiene el grafo de la url
g.parse("http://danbri.livejournal.com/data/foaf")

# Para cada foaf:member_name se agrega un foaf:name y se elimina el foaf:member_name
for s, p, o in g.triples((None, FOAF['member_name'], None)):
    g.add((s, FOAF['name'], o))
    g.remove((s, FOAF['member_name'], o))

