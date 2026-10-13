# -----------------------------------------------------------------------------------
# DESCRIPTION:
# This file defines CFILES used by all projects.
# Typically these include .c files.
# Conditional inclusion typically looks like:
#
# $(if $(filter MY_FLAG, $(FEATURE_FLAGS)), \
#     $(MY_DIR)/my.c \
# ) \
# -----------------------------------------------------------------------------------

CFILES := \
  $(MY_DIR)/power_down.c \
