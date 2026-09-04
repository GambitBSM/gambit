#!/usr/bin/env python3
"""
Draw a full HepMC3 event - hard process *and* parton shower - as a
hierarchical graph, instead of trying to force it into a Feynman-diagram
layout.

Why: tools like feynml/pyfeyn2 lay diagrams out the way a person would
draw one by hand - fine for a handful of legs and propagators, but it
falls over (overlapping, unreadable) once an event has the hundreds of
particles a real generator produces. Graphviz's "dot" algorithm is built
for exactly the opposite case: large layered directed graphs. Since a
HepMC event *is* a directed graph (vertices -> particles -> vertices),
handing it to that algorithm instead scales far better - no filtering
required, though you can still combine this with the filtering helpers
in hepmc_to_feynman.py if you want.

Trade-off: this draws plain labelled arrows, not proper Feynman-diagram
line conventions (wavy=boson, curly=gluon, etc.) - it favours legibility
of a big event over diagram "correctness". Final-state particles (status
1 - what a detector would actually see) are drawn in a different color
to help them stand out from internal shower structure, and photons are
highlighted in gold if their pT is above HIGH_PT_PHOTON_THRESHOLD (15 GeV
by default) or if they're one of the two highest-pT photons in the event
(so at least two photons are always highlighted, even in a very soft
event where none clear the threshold).

Requires: pyhepmc, networkx, pydot, particle, matplotlib, and the
Graphviz `dot` binary on your PATH (e.g. `apt install graphviz` /
`brew install graphviz`).
"""

import matplotlib
matplotlib.use("Agg")

import matplotlib.pyplot as plt
import networkx as nx
import pyhepmc
from particle import Particle

# Photons with pT above this are highlighted in a distinct color.
PHOTON_PDGID = 22
HIGH_PT_PHOTON_THRESHOLD = 15.0

# Custom short labels for particles the `particle` package either doesn't
# know (BSM IDs) or names less conveniently than a physicist would.
LABEL_OVERRIDES = {
    1000022: "N1",  # lightest neutralino
    1000023: "N2",  # second neutralino
    1000024: "C1",  # lightest chargino
}


def read_event(filepath, event_index=0):
    """Read the event at `event_index` (0 = first) from a HepMC3 file."""
    with pyhepmc.open(filepath) as f:
        for i, event in enumerate(f):
            if i == event_index:
                return event
    raise IndexError(f"File only contains {i + 1} event(s); index {event_index} not found.")


def particle_label(pid):
    """Human-readable particle name for a PDG ID, falling back to the raw
    numeric ID for particles not in the standard `particle` database
    (e.g. some BSM/SUSY IDs). The photon is shortened to its Greek-letter
    symbol since "gamma" was wide enough to hide the arrow underneath it.
    A few particles have hand-picked short labels in LABEL_OVERRIDES."""
    if pid in LABEL_OVERRIDES:
        return LABEL_OVERRIDES[pid]
    if pid == PHOTON_PDGID:
        return "\u03b3"  # gamma
    try:
        return Particle.from_pdgid(pid).name
    except Exception:
        return str(pid)


def build_graph(event, keep=None):
    """
    Turn a GenEvent into a networkx DiGraph: one node per HepMC vertex
    (plus synthetic nodes for particles with no production/end vertex,
    i.e. true incoming/outgoing legs), one edge per particle.

    keep: optional predicate `keep(particle) -> bool` to drop particles
    before building the graph (see hepmc_to_feynman.py's keep_by_* /
    keep_family helpers for ready-made ones).
    """
    G = nx.DiGraph()
    for p in event.particles:
        if keep is not None and not keep(p):
            continue
        src = ("v", p.production_vertex.id) if p.production_vertex else ("in", p.id)
        dst = ("v", p.end_vertex.id) if p.end_vertex else ("out", p.id)
        px, py = p.momentum.px, p.momentum.py
        pt = (px**2 + py**2) ** 0.5
        G.add_edge(src, dst, pid=p.pid, status=p.status, particle_id=p.id, pt=pt)
    return G


def draw_shower_tree(event, output_path, keep=None, figsize=(16, 12), font_size=6, dpi=150):
    """Render the event graph with a Graphviz hierarchical layout."""
    G = build_graph(event, keep=keep)
    if G.number_of_edges() == 0:
        raise ValueError("Nothing to draw - the filter matched no particles.")

    pos = nx.nx_pydot.graphviz_layout(G, prog="dot")

    # Gold highlight = photons above the pT threshold, plus the two
    # highest-pT photons in the event overall (even if neither happens to
    # clear the threshold).
    photon_edges = [(u, v, d) for u, v, d in G.edges(data=True) if d["pid"] == PHOTON_PDGID]
    top_photon_ids = {
        d["particle_id"]
        for _, _, d in sorted(photon_edges, key=lambda e: e[2]["pt"], reverse=True)[:2]
    }

    def is_gold_photon(d):
        return d["pid"] == PHOTON_PDGID and (
            d["pt"] > HIGH_PT_PHOTON_THRESHOLD or d["particle_id"] in top_photon_ids
        )

    high_pt_photon_edges = [(u, v) for u, v, d in G.edges(data=True) if is_gold_photon(d)]
    final_state_edges = [(u, v) for u, v, d in G.edges(data=True)
                          if d["status"] == 1 and not is_gold_photon(d)]
    other_edges = [(u, v) for u, v, d in G.edges(data=True)
                   if d["status"] != 1 and not is_gold_photon(d)]

    fig, ax = plt.subplots(figsize=figsize)
    nx.draw_networkx_nodes(G, pos, ax=ax, node_size=10, node_color="black")
    nx.draw_networkx_edges(G, pos, ax=ax, edgelist=other_edges, arrows=True,
                            arrowsize=8, width=0.7, edge_color="0.4")
    nx.draw_networkx_edges(G, pos, ax=ax, edgelist=final_state_edges, arrows=True,
                            arrowsize=10, width=1.4, edge_color="crimson")
    nx.draw_networkx_edges(G, pos, ax=ax, edgelist=high_pt_photon_edges, arrows=True,
                            arrowsize=10, width=1.8, edge_color="gold")
    edge_labels = {(u, v): particle_label(d["pid"]) for u, v, d in G.edges(data=True)}
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, ax=ax, font_size=font_size)

    ax.axis("off")
    plt.tight_layout()
    plt.savefig(output_path, dpi=dpi)
    plt.close(fig)


def main(hepmc_path, output_path="shower_tree.png", event_index=0, keep=None):
    event = read_event(hepmc_path, event_index=event_index)
    draw_shower_tree(event, output_path, keep=keep)
    print(f"Wrote shower tree for event {event_index} to {output_path}")


if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python hepmc_shower_tree.py <hepmc3_file> [output.png] [event_index]")
        sys.exit(1)

    hepmc_path = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) > 2 else "shower_tree.png"
    event_index = int(sys.argv[3]) if len(sys.argv) > 3 else 0

    main(hepmc_path, output_path, event_index)
