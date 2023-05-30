from pathlib import Path

from rdflib import RDF, Graph
from rdflib.namespace import FOAF

EXAMPLES_DIR = Path(__file__).parent


if __name__ == "__main__":
    graph = Graph()
    graph.parse(f"{EXAMPLES_DIR / 'foaf.n3'}", format="n3")

    for person in graph[: RDF.type : FOAF.Person]:  # type: ignore[misc]
        friends = list(graph[person : FOAF.knows * "+" / FOAF.name])  # type: ignore[operator]
        if friends:
            print(f"{graph.value(person, FOAF.name)}'s circle of friends:")
            for name in friends:
                print(name)

