#!/usr/bin/env ruby
#------------------------------------------------------------------------------
#  example: 
#  --------
# ts_warm_bore/scripts/parse_grid_logs.rb -p ts_warm_bore -d 711_1010 -s s1 \
#       > ts_warm_bore/timing_data/ts_warm_bore.711_1010.s1_sim.txt# parse_grid_logs 
#------------------------------------------------------------------------------
require 'find'
require 'fileutils'
require 'getoptlong'
#-----------------------------------------------------------------------------------------------
# CATALOG_DIR needs to be defined, normally, points to /grid/fermiapp/mu2e/users/murat/catalogs
# defined in my ~/.bashrc
#-----------------------------------------------------------------------------------------------
        project=$1 # ts_warm_bore # $1 # ts_inner_bore
           dsid=$2 # 711_0001
    input_stage=$3 # s1 ... or gen
   input_stream=$4 # 'mubeam', or if 'gen', '250_20000' means 'njobs_neventsPerJob'
        fileset=$5 # if ".", then full dataset
       job_type=$6 # s1_sim, s2_sim, or s3_stn ...
           doit=$7

prefix='echo ' ; if [ ".$doit" != "." ] ; then prefix='' ; fi

output_stage=`echo $job_type | awk -F _ '{print $1}'`
     jobtype=`echo $job_type | awk -F _ '{print $2}'`

fss="files" ; if [ ".$fileset" != "." ] ; then fss=$fss.$fileset ; fi

def usage
  puts "usage: parse_grid_logs -d dsid [-v] "
  exit(-1)
end
#------------------------------------------------------------------------------
# specify defaults for the global variables and parse command line options
#------------------------------------------------------------------------------

opts = GetoptLong.new(
  [ "--dsid"          , "-d",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--project"       , "-p",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--istage"        , "-i",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--verbose"       , "-v",     GetoptLong::NO_ARGUMENT       ]
)
#----------------------------- defaults
$project = nil
$dsid    = nil
$stage   = nil
$verbose = 0

opts.each do |opt, arg|
  if    (opt == "--dsid"          ) ; $dsid     = arg
  elsif (opt == "--project"       ) ; $project  = arg
  elsif (opt == "--stage"         ) ; $stage    = arg
  elsif (opt == "--verbose"       ) ; $verbose  = 1
  end

  if ($verbose != 0) ; puts "Option: #{opt}, arg #{arg.inspect}" ; end
end

setup mu2etools
setup mu2efiletools
setup mu2egrid

dsconf=${dsid}_${input_stage}_${input_stream}_${job_type}
inputs=""
njobs=xxxx
nevents_per_job=xxxxx

if [ -d 000 ] ; then 
    tmp_stub=`cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 1`
    echo directory 000 already exists, move it to 000.$tmp_stub
    mv 000 000.$tmp_stub
fi

template_fcl="undefined"
       merge=0

if [ $input_stage == "s3" ] ; then

    inputs=$project/catalogs/$dsid/$input_stage/$project.${dsid}.${input_stage}_$input_stream.art.$fss

    if [ $jobtype == "stn" ] ; then
	merge=1000
	if   [ $input_stream == "tgtstops"  ] ; then template_fcl=Stntuple/test/g4s3_tgtstops_stn.fcl
	elif [ $input_stream == "ootstops"  ] ; then template_fcl=Stntuple/test/g4s3_ootstops_stn.fcl
	elif [ $input_stream == "beam"      ] ; then template_fcl=Stntuple/test/g4s3_mothers_stn.fcl
	elif [ $input_stream == "crv"       ] ; then template_fcl=Stntuple/test/g4s3_crv_stn.fcl
	elif [ $input_stream == "truncated" ] ; then template_fcl=Stntuple/test/g4s3_truncated_stn.fcl
	else                                         echo WRONG INPUT STREAM: s3 $input_stream
	fi
    else
	echo ERROR: UNKNOWN job type: $jobtype for s3 $input_stream
    fi
elif [ $input_stage == "s2" ] ; then

    inputs=$project/catalogs/$dsid/$input_stage/$project.${dsid}.${input_stage}_${input_stream}.art.$fss
    echo S2: inputs:$inputs

    if [ $jobtype == "sim" ] ; then
	merge=2
	if [ $input_stream == "mubeam" ] ; then template_fcl=ts_warm_bore/$dsid/DS_$dsid.fcl
	else                                    echo UNKNOWN INPUT STREAM: s2 $input_stream
	fi
    elif [ $jobtype == "stn" ] ; then
	merge=1000
	if [ $input_stream == "mubeam" ] ; then template_fcl=Stntuple/test/g4s2_mubeam_stn.fcl
	else                                    echo WRONG INPUT STREAM: s3 $input_stream
	fi
    else
	echo ERROR: UNKNOWN job type: $jobtype for input_stage=$input_stage and input_stream=$input_stream
    fi
elif [ $input_stage == "s1" ] ; then # stntupling s1 stage or s2

    inputs=$project/catalogs/$dsid/$input_stage/$project.${dsid}.${input_stage}_${input_stream}.art.$fss
    
    if [ $jobtype == "stn" ] ; then
	template_fcl=Stntuple/test/g4s1_${input_stream}_stn.fcl
	merge=1000
    elif [ $jobtype == "sim" ] ; then
	template_fcl=${project}/$dsid/TS_$dsid.fcl
	merge=25
    else
	echo ERROR: UNKNOWN job type: $jobtype for input_stage=$input_stage
    fi
elif [ $input_stage == "ts1" ] ; then # 

    inputs=$project/catalogs/$dsid/$input_stage/$project.${dsid}.${input_stage}_${input_stream}.art.$fss
    
    if [ $jobtype == "stn" ] ; then
	template_fcl=Stntuple/test/g4_ts1_${input_stream}_stn.fcl
	merge=1000
    elif [ $jobtype == "sim" ] ; then                        # pbars, VD91 --> Coll31out
	template_fcl=${project}/$dsid/TS2_$dsid.fcl
	merge=50
    else
	echo ERROR: UNKNOWN job type: $jobtype for input_stage=$input_stage
    fi
elif [ $input_stage == "ts2" ] ; then # stntupling s1 stage or s2

    inputs=$project/catalogs/$dsid/$input_stage/$project.${dsid}.${input_stage}_${input_stream}.art.$fss
    
    if [ $jobtype == "stn" ] ; then
	template_fcl=Stntuple/test/g4_ts2_${input_stream}_stn.fcl
	merge=1000
    elif [ $jobtype == "sim" ] ; then                        # pbars, Coll32In --> TS5
	template_fcl=${project}/$dsid/TS3_$dsid.fcl
	merge=50
    else
	echo ERROR: UNKNOWN job type: $jobtype for input_stage=$input_stage
    fi
elif [ $input_stage == "ts3" ] ; then # stntupling ts3 - use the same FCL as for s2

    inputs=$project/catalogs/$dsid/$input_stage/$project.${dsid}.${input_stage}_${input_stream}.art.$fss
    
    if [ $jobtype == "stn" ] ; then
	template_fcl=Stntuple/test/g4s2_${input_stream}_stn.fcl
	merge=1000
    elif [ $jobtype == "sim" ] ; then                        # pbars, TS5 --> DS
	template_fcl=${project}/$dsid/DS_$dsid.fcl
	merge=50
    else
	echo ERROR: UNKNOWN job type: $jobtype for input_stage=$input_stage
    fi
else
    if [ $input_stage == "gen" ] ; then # s1 stage
	if [ $jobtype == "sim" ] ; then
	       template_fcl=ts_warm_bore/$dsid/PS_$dsid.fcl
	              njobs=`echo $input_stream | awk -F _ '{print $1}'`
	    nevents_per_job=`echo $input_stream | awk -F _ '{print $2}'`
	elif [ $jobtype == "stn" ] ; then
		template_fcl=Stntuple/test/g4s1_${input_stream}_stn.fcl
	else
	    echo ERROR: UNKNOWN job type: $jobtype for input_stage=$input_stage
	fi
    else
	echo input_stage = $input_stage, DONT KNOW WHAT DO TO
    fi
fi

if [ $template_fcl == "undefined" ] ; then exit -1 ; fi
#------------------------------------------------------------------------------
# now generate fcl, creates '000' subdirectory
#------------------------------------------------------------------------------
cmd="generate_fcl --description=$project --dsconf=$dsconf --embed $template_fcl"

if [ ".$inputs" != "." ] ; then cmd=$cmd" --merge=$merge  --inputs=$inputs"
else                            cmd=$cmd" --events=$nevents_per_job --njobs=$njobs  --run=1"
fi

echo cmd=$cmd

$prefix$cmd

${prefix}mv seeds.$USER.$project.${dsconf}.*.txt 000/.
#------------------------------------------------------------------------------
# make sure we're not overwriting the existing directory
#------------------------------------------------------------------------------
istub=${input_stage}_${input_stream}
if [ ".$fileset" != "" ] ; then istub=${istub}_$fileset ; fi

dir=$PWD/$project/tmp_fcl/$dsid.$istub.$job_type

if [ -d $dir ] ; then 
    echo ERROR: directory $dir already exists !
else
    echo mv 000 $dir
    ${prefix}mv 000 $dir
    cd $dir
#------------------------------------------------------------------------------
# need to replace: 'MU2EGRIDDSOWNER' --> "$USER"
#                  'MU2EGRIDDSCONF'  --> ${dsid}_${input_stage}_${input_stream}_${jobtype}
#------------------------------------------------------------------------------
    dsconf=${dsid}_${input_stage}_${input_stream}_${jobtype}
    for f in `ls *.fcl` ; do 
	f1=$f.tmp
	cat $f | sed "s/xxx_xxxx/$project/" | sed "s/MU2EGRIDDSOWNER/$USER/" | sed "s/MU2EGRIDDSCONF/$dsconf/">| $f1
	mv $f1 $f
    done

    tarfile=${project}.$dsid.$istub.$job_type.fcl.tbz
    tdir=..
    tar -cjf $tdir/$tarfile *.fcl
#------------------------------------------------------------------------------
# move fcl files for the simulation jobs to PNFS
#------------------------------------------------------------------------------
    if [ $jobtype == "sim" ] ; then
	echo CMD: cp $tarfile /pnfs/mu2e/resilient/users/murat/$tarfile
	cp $tdir/$tarfile /pnfs/mu2e/resilient/users/murat/$tarfile
    fi
fi
