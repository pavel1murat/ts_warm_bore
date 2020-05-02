#!/usr/bin/env python

import subprocess

process = subprocess.run(['gridexport' ,'-E $PWD/grid_export', '-A ts_warm_bore/AAA_GRIDEXPORT_EXCLUDE.txt'], 
                         capture_output=True,
                         universal_newlines=True)

# process = subprocess.run(['ls','-l'], capture_output=True, universal_newlines=True)
process
