#!/usr/bin/env bash
echo "" > sidewinderfinder.log
for i in `seq 1 100000`; do ././../bin/sidewinder_nd -l 3; done > sidewinderfinder.log
