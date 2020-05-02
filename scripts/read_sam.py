#

import subprocess, json


# samweb get-metadata --json sim.mu2e.antiprotons_cs1VD91.170829.001000_00000751.art

process = subprocess.run(['samweb' ,'get-metadata', '--json', 'sim.mu2e.antiprotons_cs1VD91.170829.001000_00000751.art'], 
                         capture_output=True,
                         universal_newlines=True)
process




