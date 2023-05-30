from rdflib import Graph, Literal, RDF, URIRef
from rdflib.namespace import FOAF , XSD

# Se crea el gráfico
g = Graph()

# Se crea una RDF URIRef para la persona
donna = URIRef("http://example.org/donna")

# Se añaden triples al grafo con el método add()
g.add((donna, RDF.type, FOAF.Person))
g.add((donna, FOAF.nick, Literal("donna", lang="en")))
g.add((donna, FOAF.name, Literal("Donna Fales")))
g.add((donna, FOAF.mbox, URIRef("mailto:donna@example.org")))

# Se añade otra persona
ed = URIRef("http://example.org/edward")

# Se añaden triples al grafo con el método add()
g.add((ed, RDF.type, FOAF.Person))
g.add((ed, FOAF.nick, Literal("ed", datatype=XSD.string)))
g.add((ed, FOAF.name, Literal("Edward Scissorhands")))
g.add((ed, FOAF.mbox, Literal("e.scissorhands@example.org", datatype=XSD.anyURI)))

# Se itera sobre todos los triples en el grafo y se imprimen
print("--- printing raw triples ---")
for s, p, o in g:
    print((s, p, o))

# Para cada persona en el grafo, se itera sobre todos los objetos de la propiedad FOAF.mbox
print("--- printing mboxes ---")
for person in g.subjects(RDF.type, FOAF.Person):
    for mbox in g.objects(person, FOAF.mbox):
        print(mbox)

# Se añade un prefijo para la URI de FOAF
g.bind("foaf", FOAF)

# Se imprimen todos los datos del grafo en notación N3
print("--- printing mboxes ---")
print(g.serialize(format='n3'))

