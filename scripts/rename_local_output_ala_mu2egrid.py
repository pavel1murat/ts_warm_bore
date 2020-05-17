#!/usr/bin/env python
#
# call: grid_submit.py --project=ts_warm_bore --dsid=760_3000 --stage=ts1_sim  -step=gen_fcl 
#-------------------------------------------------------------------------------------------------

import configparser, subprocess, shutil
import sys, string, getopt, glob, os, time, re, array


#------------------------------------------------------------------------------
class RenameLocalFilesAlaMu2eGrid:

    def __init__(self):
        self.fProject       = None
        self.fProjectDir    = None
        self.fDsid          = xxx_xxxx # just to make up 
        self.fDoit          = 1
        self.fJob           = None
        self.fStage         = None
        self.fIStage        = None;
        self.fIStream       = None;
        self.fUser          = 'murat'
        self.fGridJobID     = None;

        self.fOutputPath    = {}
        self.fOutputStreams = None

        self.fVerbose   = 1

# ---------------------------------------------------------------------
    def Print(self,Name,level,Message):
        if(level>self.fVerbose): return 0;
        now = time.strftime('%Y/%m/%d %H:%M:%S',time.localtime(time.time()))
        message = now+' [ RenameLocalFilesAlaMu2eGrid::'+Name+' ] '+Message
        print(message)
        
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
                     ['project=', 'verbose=', 'job=', 'doit=', 'dsid=', 'stage=' ] )
 
        except getopt.GetoptError:
            self.Print(name,0,'%s' % sys.argv)
            self.Print(name,0,'Errors arguments did not parse')
            return 110

        for key, val in optlist:

            # print('key,val = ',key,val)

            if key == '--project':
                self.fProject = val
            elif key == '--doit':
                self.fDoit = int(val)
            elif key == '--job':
                self.fJob = val
            elif key == '--dsid':
                self.fDsid = val
            elif key == '--stage':
                self.fStage = val
            elif key == '--verbose':
                self.fVerbose = int(val)

        self.fProjectDir = self.fProject+'/'+self.fDsid;

        self.Print(name,1,'Job        = %s' % self.fJob    )
        self.Print(name,1,'Project    = %s' % self.fProject)
        self.Print(name,1,'Verbose    = %s' % self.fVerbose)
        self.Print(name,1,'Doit       = %s' % self.fDoit)
        self.Print(name,1,'Dsid       = %s' % self.fDsid)
        self.Print(name,1,'ProjectDir = %s' % self.fProjectDir)

        if (self.fProject == None) :
            self.Print(name,0,'Error: Project not defined - exiting!')
            sys.exit(1)


        self.Print(name,1,'Done')
        return 0

#------------------------------------------------------------------------------
    def InitProject(self):
        name = 'InitProject'

        #------------------------------------------------------------------------------
        # read project config file
        #------------------------------------------------------------------------------
        config_dir = self.fProjectDir+'/config'
        name_stub  = self.fProject+'.'+self.fDsid+'.'+self.fStage;

        fn = config_dir+'/'+name_stub+'.cfg';

        self.fConfig = configparser.ConfigParser()
        self.fConfig.read(fn)

        self.Print(name,1,'self.fProject=%s, fn=%s' % (self.fProject,fn))

        # step 1: need to generate fcl files 
        projectName         = self.fConfig['project']['name']
        dsid                = self.fConfig['project']['dsid']
        
        self.fIStage        = self.fConfig['input']['stage' ]
        self.fIStream       = self.fConfig['input']['stream']
        self.fInputDs       = self.fConfig['input']['dataset']
        self.fOutputStreams = self.fConfig['output']['streams'].split(',');

        for s in self.fOutputStreams:
            self.fOutputPath[s] = self.fConfig['path'][s];
            self.Print(name,1,'self.fOutputPath[%s] = %s' % (s,self.fOutputPath[s]));

        self.Print(name,1,'projectName   = %s' % projectName)
        self.Print(name,1,'dsid          = %s' % projectName)
        self.Print(name,1,'self.fIStage  = %s' % self.fIStage)
        self.Print(name,1,'self.fIStream = %s' % self.fIStream)

        #  read grid config, if it exists

        fn1 = config_dir+'/'+name_stub+'.jobid';

        if os.path.exists(fn1) :
            line  = open(fn1).readline()
            self.fGridJobID = line.strip()
            self.Print(name,1,'self.fGridJobID = %s' % self.fGridJobID)
       
#------------------------------------------------------------------------------
# check log files. asume they are copied into the output area
#------------------------------------------------------------------------------
    def CheckOutput(self):
        name = 'CheckOutput'

        input_stub = self.fIStage+'_'+self.fIStream;
        grid_dsid = self.fProject+'.'+self.fDsid+'.'+input_stub+'.'+self.fStage;
        topdir    = '/pnfs/mu2e/scratch/users/'+self.fUser+'/workflow/'+grid_dsid+'/outstage/';

        if (self.fGridJobID): topdir = topdir+self.fGridJobID+'/00/'
        # print('topdir=',topdir)

        dir = '/mu2e/data/users/murat/datasets/'+self.fProject+'/'+self.fDsid+'/'+self.fStage

        dir = '/mu2e/data/users/murat/datasets/'+self.fProject+'/'+self.fDsid+'/'+'ts1/log'

        ntot = 0;
        nev  = {}

        for stream in self.fOutputStreams: 
            nev[stream] = array.array('i',[0,0])   # nfiles, nev
            # print ("stream, nev : ",stream,nev[stream][0],nev[stream][1])


        bad_files = []
        for fn in glob.glob(dir+'/*.log'):
            f = open(fn)
            #            print('-- fn: ',fn)
            lines = f.readlines();

            segment_ok = 1
            for line in lines:
                if ('Art has completed and will exit with status' in line):
                    words = line.strip().split()
                    rc = words[8].strip('.');
                    if (rc != "0"):
                        segment_ok = 0
                        # print ("rc = %s, words:"%rc,words)
                        bad_files.append((fn,rc));
                        break;

            if (segment_ok == 1):
                for line in lines:
                    words = line.strip().split()
                    if (len(words) == 0) : continue

                    # print('words:',words, 'nw=',len(words))

                    if ('TrigReport Events total' in line):
                        ntot = ntot+int(words[4]);

                    for stream in self.fOutputStreams:
                        if (words[0] == 'TrigReport') :
                            if (words[2] == 'Event') or (words[2] == 'Path'): 
                                continue
                            if (len(words) == 8) and (words[7] == self.fOutputPath[stream]):
                                nev[stream][0] = nev[stream][0]+1
                                nev[stream][1] = nev[stream][1]+int(words[4])
            # else:
            #     print("failed processing %s" % fn);

        print("total input: %10i" % ntot);
        for stream in self.fOutputStreams:
            print("stream ",stream,' : processed ',stream,nev[stream][1],' events ', nev[stream][0],' files');

        for bf in bad_files:
            print("ERROR: file ", bf[0]," RC = ",bf[1])
        
#------------------------------------------------------------------------------
# check log files. asume they are copied into the output area
#------------------------------------------------------------------------------
    def BuildTarball(self):
        name = 'BuildTarball'

        cmd_pars = ['gridexport' ,'-E '+os.getenv('PWD')+'/grid_export', '-A ts_warm_bore/AAA_GRIDEXPORT_EXCLUDE.txt'];

        print(">>> [BuildTarball] executing :"," ".join(cmd_pars));

        process = subprocess.run(cmd_pars,capture_output=True,universal_newlines=True)

        print(">>> [BuildTarball] done executing");

        if (process.returncode == 0):
            lines       = process.stdout.split('\n')

            for line in lines: print(line)

            word        = lines[2].split();
            tarball     = word[4]
            tmp_dir     = os.path.dirname(tarball)
            new_tarball = self.fProject+'/tmp_code/'+self.fProject+'.code.'+self.fDsid+'.tbz'

            if os.path.exists(new_tarball): os.remove(new_tarball);
            
            shutil.copy(tarball,new_tarball);
            os.remove(tarball);

            # remove old directory
            os.rmdir(tmp_dir);

            # copy tarball to /pnfs
            grid_tarball = '/pnfs/mu2e/resilient/users/murat/'+self.fProject+'.code.tbz'
            if os.path.exists(grid_tarball):
                os.remove(grid_tarball)
            shutil.copy(new_tarball,grid_tarball);
            
#------------------------------------------------------------------------------
# check log files. asume they are copied into the output area
#------------------------------------------------------------------------------
    def SubmitGridJob(self):
        name = 'BuildTarball'

        input_ds = self.fConfig['input']['stage']+':'+self.fConfig['input']['stream']
        stage    = self.fConfig['job'  ]['stage']+':'+self.fConfig['job']  ['type'  ]

        parms    = ['ts_warm_bore/scripts/submit_grid_job',
                    self.fProject,
                    self.fDsid,
                    input_ds, 
                    stage, 
                    self.fConfig['job']['time_request'],
                    self.fConfig['job']['ifdh']
                    ,'.']  # doit

        print(parms);

        process = subprocess.run(parms, capture_output=True, universal_newlines=True)
        # 
        if (process.returncode == 0):
            lines       = process.stdout.split('\n')
            print(lines)
            # extract the grid job ID and save the output 
            jobid = None;
            for line in lines:
                print(line)
                if line != '':
                    w = line.split()
                    if (w[0] == 'JobsubJobId') : 
                        jobid = w[4].split('.')[0]
                        break
    
            print('jobid:',jobid)

            # ok, now we have jobid, write it into a file
            dir = self.fProject+'/'+self.fDsid+'/config'
            bn  = self.fProject+'.'+self.fDsid+'.'+self.fConfig['job']['stage']+'_'+self.fConfig['job']['type']+'.jobid'
            fn  = dir+'/'+bn+'.jobid';
            f = open(fn,'w')
            f.write(jobid)
            f.close()

            # also want to save a grid submission loginto a separate file
            dir = self.fProject+'/'+self.fDsid+'/log'
            fn = dir+'/'+bn+'.'+jobid
            f = open(fn,'w')
            for line in lines:
                f.write(line)

            f.close();
            
            # finally, add one line to a grid submittion summary
            fn = dir+'/AAA_grid_submission_summary.org'
            
           
#------------------------------------------------------------------------------
# main program, just make a RenameLocalFilesAlaMu2eGrid instance and call its methods
#------------------------------------------------------------------------------
if (__name__ == '__main__'):

    x = RenameLocalFilesAlaMu2eGrid()
    x.ParseParameters()

    x.InitProject()

#    if (x.fJob == 'check_output'   ) : x.CheckOutput()
#    if (x.fJob == 'build_tarball'  ) : x.BuildTarball()
#    if (x.fJob == 'submit_grid_job') : x.SubmitGridJob()
# 
#    gs.PrintConfFile(1)
#    gs.CheckForNewFiles()
#    gs.UpdateJobStatus()
#    gs.SubmitNewJobs()
#    gs.PrintConfFile(1)
#    gs.CatExit(0)
    sys.exit(0);
