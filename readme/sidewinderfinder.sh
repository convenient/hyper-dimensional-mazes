#!/usr/bin/env bash
echo "" > .sidewinderfinder.log
for i in `seq 1 100000`; do ././../bin/sidewinder_3d -l 7; done > sidewinderfinder.log
