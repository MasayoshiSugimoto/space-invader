#!/bin/bash

cat /tmp/space-invaders.log \
| grep -E '\[INFO\]\[src/color_test.c:157\] .*' \
| sed -E 's|\[INFO\]\[src/color_test.c:157\] ||' \
> /tmp/space_invader.debug_data

gnuplot plot_graph
