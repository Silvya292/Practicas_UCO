from rdflib import Graph

# Se crea un gráfico
g = Graph()

# Se analiza en un archivo RDF
g.parse("examenMayo.owl", format="xml")

# Se imprime el número de triples
print(f"El grafo tiene {len(g)} statements.")

# Se imprime el gráfico en formato n3
print(g.serialize(format="n3"))