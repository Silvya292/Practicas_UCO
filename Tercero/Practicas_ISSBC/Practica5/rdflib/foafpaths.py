from pathlib import Path

from rdflib import Graph, URIRef
from rdflib.namespace import FOAF

EXAMPLES_DIR = Path(__file__).parent

if __name__ == "__main__":
    g = Graph()
    g.parse(f"{EXAMPLES_DIR / 'foaf.n3'}")

    tim = URIRef("http://www.w3.org/People/Berners-Lee/card#i")

    print("Timbl knows:")

    for o in g.objects(tim, FOAF.knows / FOAF.name):
        print(o)

