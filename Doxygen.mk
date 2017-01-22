# Doxygen parameters
DOXY_STRIP_FROM_PATH?=../
DOXY_PROJECT_NAME?="Conway"
DOXY_PROJECT_BRIEF?="\"Conway\'s game of life.\""
DOXY_QT_AUTOBRIEF?=YES
DOXY_BUILTIN_STL_SUPPORT?=YES
DOXY_EXTRACT_ALL?=YES
DOXY_EXTRACT_PRIVATE?=YES
DOXY_EXTRACT_PACKAGE?=YES
DOXY_SHOW_INCLUDE_FILES?=YES
DOXY_INPUT?=$(foreach V,h t c a,$($(V)pp_files)) README.md
DOXY_RECURSIVE?=YES
DOXY_USE_MDFILE_AS_MAINPAGE?=README.md
DOXY_COLS_IN_ALPHA_INDEX?=5
DOXY_GENERATE_MAN?=YES
DOXY_CALL_GRAPH?=YES
DOXY_DOT_TRANSPARENT?=YES

include ../Maker/Doxygen.mk