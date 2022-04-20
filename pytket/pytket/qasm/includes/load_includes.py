"""Helper file to convert gate definitions of any .inc files in this directory
in to python files containing dictionaries of pytket CustomGateDefs. To be used
with qasm parsing."""

from pathlib import Path
from typing import Dict, cast
from lark import Lark
from pytket.qasm.qasm import grammar, CircuitTransformer

files = Path(__file__).parent.glob("*.inc")

for fi in files:
    with open(fi) as inc_file:

        parser = Lark(
            grammar,
            start="prog",
            debug=False,
            parser="lalr",
            cache=True,
            transformer=CircuitTransformer(return_gate_dict=True),
        )
        gdict = cast(Dict[str, Dict], parser.parse(inc_file.read()))

    with open(Path(__file__).parent / f"_{fi.stem}_defs.py", "w") as f_out:
        f_out.write("_INCLUDE_DEFS=")
        f_out.write(repr(gdict))

    with open(Path(__file__).parent / f"_{fi.stem}_decls.py", "w") as f_out:
        for gate in gdict:
            del gdict[gate]["definition"]
        f_out.write("_INCLUDE_DECLS=")
        f_out.write(repr(gdict))
