import logging
import sys
from pathlib import Path

import rdflib

EXAMPLES_DIR = Path(__file__).parent

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG, stream=sys.stderr)

    g = rdflib.Graph()
    g.parse(f"{EXAMPLES_DIR / 'foaf.n3'}", format="n3")

    # The QueryProcessor knows the FOAF prefix from the graph
    # which in turn knows it from reading the N3 RDF file
    for row in g.query("SELECT ?s WHERE { [] foaf:knows ?s .}"):
        # For select queries, the Result object is an iterable of ResultRow
        # objects.
        assert isinstance(row, rdflib.query.ResultRow)
        print(row.s)
        # or row["s"]
        # or row[rdflib.Variable("s")]

