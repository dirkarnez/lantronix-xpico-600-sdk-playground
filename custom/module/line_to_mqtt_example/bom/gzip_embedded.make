# ----------------------------------------------------------------------------
# DESCRIPTION:
# This file gzip embedded files for use by all projects.
# Typically these include .css, .js and .html static (not sent to browser through 
#  ajax framework) files.
# Conditional inclusion typically looks like:
#
# $(if $(filter MY_FLAG, $(FEATURE_FLAGS)), \
#     $(MY_DIR)/my.js \
# ) \
#
# ALERT:
# Files added to these variables should maintain the alphabetical order.
# ----------------------------------------------------------------------------

GZIP_EMBEDDED := \
    $(MY_DIR)/http/web/mqtt_init.js \
