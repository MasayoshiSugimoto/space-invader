#!/bin/bash

cat /tmp/space-invaders.log \
| grep -E '\[INFO\]\[src/color_test.c:.*\] COLOR_TEST_INTERPOLATION_COS_F:.*' \
| sed -E 's|\[INFO\]\[src/color_test.c:.*\] COLOR_TEST_INTERPOLATION_COS_F:||' \
> /tmp/space_invader.debug_data

gnuplot plot_graph
