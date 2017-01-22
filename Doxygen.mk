# Doxygen parameters
DOXY_PROJECT_NAME?="Conway"
DOXY_PROJECT_BRIEF?="\"Conway\'s game of life.\""
DOXY_INPUT?=$(foreach V,h t c a,$($(V)pp_files)) README.md
DOXY_COLS_IN_ALPHA_INDEX?=5

include ../Maker/Doxygen.mk
