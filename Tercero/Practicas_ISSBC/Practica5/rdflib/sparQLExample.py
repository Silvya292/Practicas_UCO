from rdflib import Graph

# Se crea un gráfico
g = Graph().parse("http://www.w3.org/People/Berners-Lee/card")

# Para todas las personas en el grafo, se itera sobre todos los objetos de la propiedad FOAF.mbox
# Esta query devuelve el nombre de todas las personas en el gráfico
q = """
    PREFIX foaf: <http://xmlns.com/foaf/0.1/>

    SELECT ?name
    WHERE {
        ?p rdf:type foaf:Person .

        ?p foaf:name ?name .
    }
"""

# Se aplica la query al gráfico y se imprimen los resultados
for r in g.query(q):
    print(r["name"])

# Se imprimirá: Tim Berners-Lee


