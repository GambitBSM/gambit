import yaml
import ScannerBit as scan 

# define likelihood, technically optional
def like(m):
    a = m["model1::x"]
    scan.print("my_param", 0.5) # can print custom parameters 
    
    return -a*a/2.0

# define prior, optional
def prior(vec, map):
    # tell ScannerBit that the hypergrid dimension is 1
    vec.ensure_size(1) # this needs to be the first line!
    
    map["model1::x"] = 5.0 - 10.0*vec[0]

# declare scan object
myscan = scan.scan()

# run scan
myscan.run(inifile="ScannerBit.yaml", lnlike={"LogLike": like}, prior=prior, restart=True)

###
### can run diagnostics
### NOTE: can specify any number of object to run diagnostics on
###       e.g. myscan.diagnostics("twalk", "multinest", "ais", "priors", "scanners", ...)
###
# myscan.diagnostics("twalk")

###
### can use with pyyaml!
### NOTE: yaml vector keys, [...], must be preceded by !!/python/tuple 
###
# with open("ScannerBit.yaml", 'r') as f:
#     try:
#         inifile = yaml.load(f)
#     except yaml.YAMLError as exc:
#         print(exc)
# 
# myscan.run(inifile=inifile, lnlike={"LogLike": like}, prior=prior, restart=True)

###
### or can also run multiple proposes
###
# lnlike = {
#     "LogLike1": like1
#     "LogLike2": like2
# }
# myscan.run(inifile="ScannerBit.yaml", lnlike=lnlike, prior=prior, restart=True)
