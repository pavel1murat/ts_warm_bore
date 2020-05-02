#!/usr/bin/ruby
#------------------------------------------------------------------------------
# parse log files produced by 'mu2e -c Print/fcl/print.fcl' job
# count various numbers of events
#------------------------------------------------------------------------------

require 'getoptlong'
require 'fileutils'

$fn      = nil
$verbose = nil


#------------------------------------------------------------------------------
def parse_command_line() 

  opts = GetoptLong.new(
                        [ "--file"          , "-f",        GetoptLong::REQUIRED_ARGUMENT ],
                        [ "--verbose"       , "-v",        GetoptLong::NO_ARGUMENT       ]
                        )

  opts.each do |opt, arg|
    if    (opt == "--file"    )
      $fn  = arg
      if $verbose ; puts "Option: #{opt}, arg #{arg.inspect}" ; end
    elsif (opt == "--verbose"   )
      $verbose = 1
    end
  end
end


#------------------------------------------------------------------------------
# count number of pbars reaching the end of TS1 simulation stage
#------------------------------------------------------------------------------
def count_pbars(fn)

  blin = 0;
  nev  = 0;

  for l in File.readlines(fn)
    w  = l.split(' ')
    nw = w.length

    if (blin == 0) then 
      if (w[0] == 'ProductPrint') and (w[1].index('mu2e::StepPointMCs_muonBeamFilter_Coll31OutRecord') != nil) then
        blin = 1
      end
    else
      if (nw == 11) and (w[10] == 'Transportation') then
        if (w[1] == '100001') then nev += 1 end
        blin = 0
      end
    end
  end

  puts "nev = #{nev}"
end


if __FILE__ == $0 then
  x = ENV["RUBYLIB"];

  parse_command_line();
  count_pbars($fn)

end
