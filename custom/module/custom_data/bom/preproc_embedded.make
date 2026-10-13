# -----------------------------------------------------------------------------------
# DESCRIPTION:
# This file names preprocessed embedded files for use by all projects.
# Typically these include .js and .html files.
# Conditional inclusion typically looks like:
#
# $(if $(filter MY_FLAG, $(FEATURE_FLAGS)), \
#     $(MY_DIR)/my.js \
# ) \
#
# ALERT:
# Files added to these variables should maintain the alphabetical order.
# -----------------------------------------------------------------------------------

PREPROC_EMBEDDED := \
  $(MY_DIR)/http/help/config.Custom.html \
  $(MY_DIR)/http/web/user_data_specification.js \
