#! /usr/bin/env python3

## Handle command line
import argparse
ap = argparse.ArgumentParser()
ap.add_argument("ANAFILES", nargs="*", help="analysis info files to parse, defaults to using all in the pwd")
ap.add_argument("-o", dest="OUTFILE", nargs="?", default="analyses.json", help="output JSON filename [default=%(default)s]")
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
        ## Analyses without valid Inspire entries  are either missing or set to negative values
        if inspireid > 0:
            adata.append( {"inspire_id" : inspireid, "implementations" : { "name" : aname } } )

## Write JSON
import json, datetime
data = {}
data["tool"] = "GAMBIT"
data["version"] = args.GVERSION
data["date_created"] = datetime.datetime.now().isoformat()
data["implementations_description"] = "GAMBIT ColliderBit analysis"
data["url_templates"] = { "main_url": "https://github.com/GambitBSM/gambit/blob/master/ColliderBit/src/analyses/Analysis_{name}.cpp" }
data["analyses"] = adata
data["implementations_license"] = { "name" : "BSD-3", "url" : "https://opensource.org/license/bsd-3-clause" }
with open(args.OUTFILE, 'w', encoding='utf-8') as of:
    json.dump(data, of, ensure_ascii=False, indent=4)
