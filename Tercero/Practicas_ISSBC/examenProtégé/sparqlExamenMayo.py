from rdflib import Graph
from rdflib import Namespace

# Se crea un gráfico
g = Graph()

# Se analiza en un archivo RDF
g.parse("examenMayo.owl", format="xml")

# Se crea una consulta
def queryVivienda():
    qres = g.query(
        """SELECT ?vivienda ?precio ?habitaciones ?area ?ubicacion ?comprador ?vendedor
           WHERE {
                ?vivienda rdf:type examenMayo:Vivienda .
                ?vivienda examenMayo:tienePrecio ?precio .
                ?vivienda examenMayo:tieneHabitaciones ?habitaciones . 
                ?vivienda examenMayo:tieneArea ?area .
                ?vivienda examenMayo:tieneUbicacion ?ubicacion .
                ?vivienda examenMayo:tieneComprador ?comprador .
                ?vivienda examenMayo:tieneVendedor ?vendedor .
           }""")
    # Se imprimen los resultados
    for row in qres:
        print("Nombre de la vivienda: %s \n\tPrecio: %s € \n\tHabitaciones: %s \n\tÁrea total: %s m2 \n\tUbicación: %s \n\tSu comprador es: %s \n\tSu vendedor es: %s\n" % row)

#Se crea otra consulta
def queryVendedores():
    qres = g.query(
        """SELECT ?vendedor
           WHERE {
                ?vendedor rdf:type examenMayo:Vendedor .
           }""")
    # Se imprimen los resultados
    for row in qres:
        print("Nombre del vendedor: %s" % row)


# Se ejecutan la consultas
print("Vivienda: ")
queryVivienda()
print("Vendedores existentes en el sistema: ")
queryVendedores()