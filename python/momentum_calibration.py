#!/usr/bin/env python3
import os
import subprocess
from optparse import OptionParser
import findFiles

#parameters
ntuple_dir = "/eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/ntuples/13TeV/ALCARERECO/103X_dataRun2_v6_ULBaseForICs_newRegV1/"#parent folder containing all the ntuples of interest
tag_list = ["2016"]
ignored_ntuples_label_list = ["obsolete"]
required_label = "zskim" #only ntuples with this label anywhere in the path (case insensitive) are used, "" to disable

#parse arguments
parser = OptionParser()
parser.add_option("-c", "--cfg",    action="store", type="str", dest="configFile",                                    help="template cfg with SELECTED_INPUTFILE and EXTRACALIBTREE_INPUTFILE")
parser.add_option("-o", "--outcfg", action="store", type="str", dest="outcfg",     default="CalibrationMomentum.cfg", help="filled cfg to write")
parser.add_option("-e", "--exedir", action="store", type="str", dest="exedir",     default="./bin/",                  help="executable directory")
parser.add_option("--run",          action="store_true",        dest="run",        default=False,                     help="run CalibrationMomentum after writing the cfg")
(options, args) = parser.parse_args()

if not options.configFile:
    parser.error("template cfg not given (-c)")

#get ntuples, the extraCalibTree filename is generated from the ntuple one --> keep only complete pairs
selected_filelist,extracalibtree_filelist = findFiles.findFiles(ntuple_dir,"unmerged",tag_list,ignored_ntuples_label_list)
labelled = [(s, e) for s, e in zip(selected_filelist, extracalibtree_filelist) if required_label.lower() in s.lower()]
print(str(len(labelled))+" of "+str(len(selected_filelist))+" ntuples match the label '"+required_label+"'")
pairs = [(s, e) for s, e in labelled if os.path.exists(e)]
print(str(len(pairs))+" ntuple/extraCalibTree pairs found ("+str(len(labelled)-len(pairs))+" ntuples without extraCalibTree skipped)")
if len(pairs)==0:
    print("NOT any file found --> EXIT")
    raise SystemExit(1)

#fill the template
with open(options.configFile) as fi:
    contents = fi.read()
contents = contents.replace("SELECTED_INPUTFILE",       " \\\n".join(s for s, e in pairs))
contents = contents.replace("EXTRACALIBTREE_INPUTFILE", " \\\n".join(e for s, e in pairs))
with open(options.outcfg, "w") as fo:
    fo.write(contents)
print("> written "+options.outcfg)

if options.run:
    subprocess.run([os.path.join(options.exedir, "CalibrationMomentum.exe"), "--cfg", options.outcfg], check=True)
