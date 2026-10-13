
SDK_VERSION := 1.0

include ../../../build/platform.make

ifeq (,$(USE_ECLIPSE))
all: \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/$(TARGET_NAME).rom \
#  image_summary
else
all: \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/$(TARGET_NAME).rom \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/startup$(PART1).txt \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/startup$(PART2).txt \
#  image_summary
endif
