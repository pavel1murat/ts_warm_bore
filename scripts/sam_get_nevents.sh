#!/bin/bash
# source ./sam_get_nevents.sh  /mu2e/app/users/murat/beamline_prof/ts_warm_bore/760_3000/catalog/pbar/ts_warm_bore.760_3000.pbar_vd91.art.files > /mu2e/app/users/murat/beamline_prof/ts_warm_bore/760_3000/catalog/pbar/ts_warm_bore.760_3000.pbar_vd91.art.files.nevents

filelist=$1

for f in `cat $filelist` ; do
    bn=`basename $f`
    nev=`samweb get-metadata $bn | grep "Event Count" | awk '{print $3}'`
    echo $bn " " $nev
done


# murat@mu2ebuild01:/mu2e/app/users/murat/beamline_prof>samweb get-metadata sim.mu2e.antiprotons_cs1VD91.170829.001000_00000751.art
#           File Name: sim.mu2e.antiprotons_cs1VD91.170829.001000_00000751.art
#             File Id: 74863211
#         Create Date: 2017-09-08T15:14:42+00:00
#                User: mu2epro
#           File Size: 209807153
#            Checksum: (none)
#      Content Status: good
#           File Type: mc
#         File Format: art
#           Data Tier: sim
#         Event Count: 366384
#    dh.configuration: 170829
#          dh.dataset: sim.mu2e.antiprotons_cs1VD91.170829.art
#      dh.description: antiprotons_cs1VD91
#      dh.first_event: 6
#  dh.first_run_event: 1000
# dh.first_run_subrun: 1000
#     dh.first_subrun: 751
#       dh.last_event: 500000
#   dh.last_run_event: 1000
#  dh.last_run_subrun: 1000
#      dh.last_subrun: 1999
#            dh.owner: mu2e
#        dh.sequencer: 001000_00000751
#           dh.sha256: 98e3e5dfe7426cf03b8ab4a31874620c7e017a0c5d2b3e9fca18e26b34c24d35
