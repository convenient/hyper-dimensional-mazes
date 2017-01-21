#!/usr/bin/env bash
echo "" > .sidewinderfinder.log
for i in `seq 1 100000`; do ././../bin/binary_3d -l 6; done > .sidewinderfinder.log
