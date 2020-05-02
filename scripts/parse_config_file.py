#!/usr/bin/env python
#
# call: parse_config_file.py --project=ts_warm_bore --dsid=760_3000 --stage=ts1_sim  -step=gen_fcl 
#-------------------------------------------------------------------------------------------------

import configparser
import sys, string, getopt, glob, os, time, commands, re


#------------------------------------------------------------------------------
class GridSubmit:

    def __init__(self):
        self.fProject = None
        self.fDsid    = None
        self.fDoit    = 1
        self.fStage   = None
        self.fVerbose = 1

# ---------------------------------------------------------------------
    def Print(self,Name,level,Message):
        if(level>self.fVerbose): return 0;
        now = time.strftime('%Y/%m/%d %H:%M:%S',time.localtime(time.time()))
        message = now+' [ GridSubmit::'+Name+' ] '+Message
        print message
        
#----------------------------------------------------------------------
# Parse the command-line parameters.
# the only required one is --project=$Project which defines the tiki page
# where the rest of the parameters can be found.  Set --doit=0 to
# only compute what would be done, and not actually do it.
# --verbose=0 only print necessary error messages etc.
# --verbose=1 (default) print some summary of what was done
# --verbose=2 print detailed summary of what was done
# --verbose=10 dump everything
#------------------------------------------------------------------------------
    def ParseParameters(self):
        name = 'ParseParameters'
        
        self.Print(name,2,'Starting')
        self.Print(name,2, '%s' % sys.argv)

        try:
            optlist, args = getopt.getopt(sys.argv[1:], '',
                     ['project=', 'verbose=', 'doit=', 'dsid=', 'stage' ] )
        except getopt.GetoptError, e:
            self.Print(name,0,'%s' % sys.argv)
            self.Print(name,0,'Errors arguments did not parse')
            return 110

        for key, val in optlist:
            if key == '--project':
                self.fProject = val
            elif key == '--doit':
                self.fDoit = int(val)
            elif key == '--dsid':
                self.fDsid = val
            elif key == '--stage':
                self.fStage = val
            elif key == '--verbose':
                self.fVerbose = int(val)

        self.Print(name,1,'Project=%s' % self.fProject)
        self.Print(name,1,'Verbose=%s' % self.fVerbose)
        self.Print(name,1,'Doit   =%s' % self.fDoit)
        self.Print(name,1,'Dsid   =%s' % self.fDsid)

        if(! self.fProject):
            self.Print(name,0,'Error: Project not defined - exiting!')
            sys.exit(1)

        self.Print(name,1,'Done')
        return 0

#------------------------------------------------------------------------------
    def InitProject(self):
        name = 'InitProject'

        self.fConfig = configparser.ConfigParser()

        fn = self.fProject+'/'+self.fDsid+'/'+self.fProject+'.'+self.fDsid+'.'+self.fStage+'.cfg';

        self.fConfig.read('ts_warm_bore/760_3000/ts_warm_bore.760_3000.ts1_sim.cfg')

        # step 1: need to generate fcl files 
        self.fProjectName = self.fConfig['project']['name']
        self.fDsid        = self.fConfig['project']['dsid']
        
        self.fIstage      = self.fConfig['input']['stage' ]
        self.fIstream     = self.fConfig['input']['stream']
        
        self.fInputDs    = self.fConfig['input']['dataset']


#------------------------------------------------------------------------------
# main program, just make a GridSubmit instance and call its methods
#------------------------------------------------------------------------------
if (__name__ == '__main__'):

    gs = GridSubmit()
    gs.ParseParameters()

    gs.InitProject()


#    gs.PrintConfFile(1)
#    gs.CheckForNewFiles()
#    gs.UpdateJobStatus()
#    gs.SubmitNewJobs()
#    gs.PrintConfFile(1)
#    gs.CatExit(0)
    sys.exit(0);
