#!/usr/bin/env bash
DIR_BASE="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )"

function run () {
    runningSolutionDistanceCount=0;
    for i in {1..20}; do
        solutionDistance=$($DIR_BASE/bin/$maze -d $dimensions -l $length | grep "distance" | cut -d ' ' -f10)
        runningSolutionDistanceCount="$((runningSolutionDistanceCount + $solutionDistance))"
    done;

    printf "$maze -d $dimensions -l $length\t$(($runningSolutionDistanceCount/20))\n"
}

length=6; dimensions=2; maze='binary_nd'; run;
length=6; dimensions=3; maze='binary_nd'; run;
length=6; dimensions=4; maze='binary_nd'; run;

length=6; dimensions=2; maze='aldous_broder_nd'; run;
length=6; dimensions=3; maze='aldous_broder_nd'; run;
length=6; dimensions=4; maze='aldous_broder_nd'; run;

length=6; dimensions=2; maze='wilsons_nd'; run;
length=6; dimensions=3; maze='wilsons_nd'; run;
length=6; dimensions=4; maze='wilsons_nd'; run;

length=6; dimensions=2; maze='recursive_backtracker_nd'; run;
length=6; dimensions=3; maze='recursive_backtracker_nd'; run;
length=6; dimensions=4; maze='recursive_backtracker_nd'; run;