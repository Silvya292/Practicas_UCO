from pathlib import Path

from rdflib import Graph, Namespace
from rdflib.namespace import FOAF

STABLE = Namespace("http://example.com/person/mbox_sha1sum/")

EXAMPLES_DIR = Path(__file__).parent

if __name__ == "__main__":
    g = Graph()
    g.parse(f"{EXAMPLES_DIR / 'smushingdemo.n3'}", format="n3")

    newURI = {}  # old subject : stable uri
    for s, p, o in g.triples((None, FOAF["mbox_sha1sum"], None)):
        # For this graph, all objects are Identifiers, which is a subclass of
        # string. `n3` does allow for objects which are not Identifiers, like
        # subgraphs.
        assert isinstance(o, str)
        newURI[s] = STABLE[o]

    out = Graph()
    out.bind("foaf", FOAF)

    for s, p, o in g:
        s = newURI.get(s, s)
        o = newURI.get(o, o)  # might be linked to another person
        out.add((s, p, o))

    print(out.serialize())

