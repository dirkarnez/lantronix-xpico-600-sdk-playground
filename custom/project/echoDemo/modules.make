# -----------------------------------------------------------------------------------
# DESCRIPTION:
# This file defines MODULE_NAMES used by this project.
# -----------------------------------------------------------------------------------

MODULE_NAMES := \
    discovery \
    main \
    ntp \
    line_echo \
    $(if $(filter xPico200,$(PROJECT_NAME)),usb_host) \
