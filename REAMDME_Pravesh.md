
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
