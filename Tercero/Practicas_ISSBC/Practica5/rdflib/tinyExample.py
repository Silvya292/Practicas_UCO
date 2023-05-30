from rdflib import Graph

# Se crea un gráfico
g = Graph()

# PSe analiza en un archivo RDF alojado en la Internet
g.parse("http://www.w3.org/People/Berners-Lee/card")

# Se recorre cada triple del gráfico
for subj, pred, obj in g:
    # Se comprueba si hay al menos un triple
    if (subj, pred, obj) not in g:
       raise Exception("It better be!")

# Se imprime el número de triples
print(f"Graph g has {len(g)} statements.")
# Se imprime que el gráfico tiene 86 triples

# Se imprime el gráfico en formato turtle
print(g.serialize(format="turtle"))

