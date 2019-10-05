#!/usr/bin/ruby
#------------------------------------------------------------------------------
#  example: 
#  --------
# ts_warm_bore/scripts/parse_grid_logs.rb -p ts_warm_bore -d 711_1010 -s s1 \
#       > ts_warm_bore/timing_data/ts_warm_bore.711_1010.s1_sim.txt# parse_grid_logs 
#------------------------------------------------------------------------------
# puts "starting---"

require 'find'
require 'fileutils'
require 'getoptlong'

# puts " emoe"
#-----------------------------------------------------------------------
def usage
  puts "usage: parse_grid_logs -d dsid [-v] "
  exit(-1)
end
#------------------------------------------------------------------------------
# specify defaults for the global variables and parse command line options
#------------------------------------------------------------------------------

opts = GetoptLong.new(
  [ "--dsid"          , "-d",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--istream"       , "-i",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--ostream"       , "-o",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--project"       , "-p",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--stage"         , "-s",     GetoptLong::REQUIRED_ARGUMENT ],
  [ "--verbose"       , "-v",     GetoptLong::NO_ARGUMENT       ]
)
#----------------------------- defaults
$project = nil
$dsid    = nil
$istream = nil
$ostream = nil
$verbose = 0
$tmp_dir = nil

opts.each do |opt, arg|
  if    (opt == "--dsid"          ) ; $dsid     = arg
  elsif (opt == "--istream"       ) ; $istream  = arg
  elsif (opt == "--ostream"       ) ; $ostream  = arg
  elsif (opt == "--project"       ) ; $project  = arg
  elsif (opt == "--stage"         ) ; $stage    = arg
  elsif (opt == "--verbose"       ) ; $verbose  = 1
  end

  if ($verbose != 0) ; puts "Option: #{opt}, arg #{arg.inspect}" ; end
end


$stage=$ostream.split(':')[0];

#------------------------------------------------------------------------------
def run(dsid)

  #   puts "[run] dsid = #{dsid}"
  
  istage   = $istream.split(':')[0];
  istreaam = $istream.split(':')[0];

  istub    = $istream.gsub(':','_');
  ostub    = $ostream.gsub(':','_');

  fcl_top = Dir.pwd()+'/'+$project+"/tmp_fcl";
  fcl_dir = fcl_top+'/'+dsid+'.'+istub+'.'+ostub ;

  #   puts "fcl_dir = #{fcl_dir}"

  odir =  "/mu2e/data/users/murat/datasets/"+$project+"/"+dsid+'/'+$stage+'/log';
  #   puts "odir = #{odir}"
#------------------------------------------------------------------------------
# loop over all .fcl files, find thise, for which there is no output files
#------------------------------------------------------------------------------
  nfailed=0;
  for fn in Dir.glob("#{fcl_dir}/*.fcl") do
    #    puts "-----------------"+fn

    fn_stub = File.basename(fn).split('.')[4];

    logfiles=Dir.glob(odir+'/'+'*.'+fn_stub+'.log');  # expect either 1 file or nothing

    if (logfiles.length == 1) then
#------------------------------------------------------------------------------
# do not analyse the log file, just assume that the job succeeded
#------------------------------------------------------------------------------
    else
#------------------------------------------------------------------------------
# copy fcl into a separate subdirectory, which one?
#------------------------------------------------------------------------------
      fout = $tmp_dir+'/'+File.basename(fn);
      #      puts "fn, fout = #{fn}  #{fout}"
      FileUtils.copy(fn,fout);
      nfailed += 1;
    end
  end

  puts "nfailed = #{nfailed}"

  if (nfailed > 0) then
    #    puts "$project = #{$project} $dsid=#{$dsid} istub=#{istub} ostub=#{ostub}"
    tarball = $project+'.'+$dsid.to_s+'.'+istub+'.'+ostub+'.fcl.tbz';
    cmd="cd #{$tmp_dir}; tar -cjf #{tarball} *.fcl ; cp #{tarball} #{fcl_top}/."
    #    puts "cmd=#{cmd}"
    `#{cmd}`
  end

  return 0;
end

#------------------------------------------------------------------------------
pid     = Process.pid;
$tmp_dir = "/tmp/"+pid.to_s;
puts "tpm_dir = #{$tmp_dir}"
Dir.mkdir($tmp_dir);

rc = run($dsid);

if (rc == 0) then Dir.rmdir($tmp_dir); end

exit(0)
