
## Commands from scratch:
    cmsrel CMSSW_14_0_13_patch2  #Create CMSSW working area
    cd CMSSW_14_0_13_patch2/src/
    cmsenv
    git clone -b run3_version https://github.com/PraveshSharma1729/Eop_framework.git
    cd Eop_framework/
    mkdir build lib bin    
    chmod +x scripts/*.sh
### modify the working directory in temporary_setup.sh & proceed
    source scripts/setup.sh && source scripts/temporary_setup.sh
    cmake_reset #ignore the possible errors due to the fact that the build/ directory is empty 
    cmake_build
    
modify python/calibration.py and add current directory and ECALElF directory with taglists as well.

### Now make cfg file and run it using this command to generate the jobs submission file(e.g.):
    python3 python/calibration_2016.py -o /eos/user/p/pravesh/outputs/output_2016 -l ulrereco2016_EB -e /afs/cern.ch/user/p/pravesh/private/EoP/CMSSW_14_0_13_patch2/src/Eop_framework/bin/ -c /afs/cern.ch/user/p/pravesh/private/EoP/CMSSW_14_0_13_patch2/src/Eop_framework/cfg/template_2016.cfg -N 15


### You will get condor job submit command in terminal after running above command.
### Once condor jobs are completed, Generate even and odd files of last iteration to use for statistical precision estimation (use last iteration merging  (merge_IC_loop_14.sh) to merge odd and even files)

### Now do post processing of the ICs and final plots by running cfg file( having path of odd, even and last itereration ) and using the command:
    bin/CalibrationPlots.exe cfg/calibrationplots_2016.cfg

### these are final plots

