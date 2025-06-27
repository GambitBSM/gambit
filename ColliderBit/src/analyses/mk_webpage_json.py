#! /usr/bin/env python3

## Handle command line
import argparse
ap = argparse.ArgumentParser()
ap.add_argument("ANAFILES", nargs="*", help="analysis info files to parse, defaults to using all in the pwd")
ap.add_argument("-o", dest="OUTFILE", nargs="?", default="analyses_webpage.json", help="output JSON filename [default=%(default)s]")
ap.add_argument("--gversion", dest="GVERSION", nargs="?", default=None, help="specify the GAMBIT version [default=try to read from CMake]")
args = ap.parse_args()

## Identify the input files
if not args.ANAFILES:
    from glob import glob
    args.ANAFILES = glob("*.info")

## Identify the GAMBIT version
if not args.GVERSION:
    try:
        import re
        with open("../../../cmake/tarball_info.cmake", "r") as cf:
            for line in cf:
                m = re.match(r"set\(GAMBIT_VERSION_FULL ([\d\.]+)\)", line)
                if m: args.GVERSION = m.group(1)
    except:
        pass

## Parse analysis info files into dict
adata = []
import yaml, os
for afile in args.ANAFILES:
    aname = os.path.basename(afile).replace("Analysis_", "").replace(".info", "")
    with open(afile, "r") as af:
        ayaml = yaml.safe_load(af)
        inspireid = ayaml.get("InspireID", -1)
        summary = ayaml.get("Summary", "")
        lumi = ayaml.get("Lumi_ifb", 0)
        sqrts = ayaml.get("Ecm_TeV", 0)
        keywords = ayaml.get("Keywords", "")
        signatures = ayaml.get("Signatures", "")
        experiment, run = ayaml.get("ExptRun", "Unknown-Unknown").split("-")
        note = ayaml.get("Note", "")
        adata.append( {"inspire_id" : inspireid, "name" : aname, "exp" : experiment, "run" : run, "summary" : summary, "luminosity" : lumi, "ecm" : sqrts, "sign" : signatures, "keyword" : keywords, "note": note} )

## Write JSON
import json, datetime
data = {}
data["version"] = args.GVERSION
data["date_created"] = datetime.datetime.now().isoformat()
data["analyses"] = adata
with open(args.OUTFILE, 'w', encoding='utf-8') as of:
    json.dump(data, of, ensure_ascii=False, indent=4)
