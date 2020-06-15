
# This file is a part of MRNIU/FreeRTOS-PortentaH7 (https://github.com/MRNIU/FreeRTOS-PortentaH7).
#
# Makefile for MRNIU/FreeRTOS-PortentaH7.

CURR_DIR := $(shell pwd)
ROOT_DIR := $(CURR_DIR)/..
include $(ROOT_DIR)/Makefile.env

exclude_dirs :=
subdirs := $(shell find . -maxdepth 1 -type d)
subdirs := $(basename $(patsubst ./%, %, $(subdirs)))
subdirs := $(filter-out $(exclude_dirs), $(subdirs))
SUB_DIR := $(subdirs)

.PHONY: default
default:
	@echo Entry $(CURR_DIR)
	@$(MAKE) all
	@echo Leave $(CURR_DIR)

.PHONY: all
all: $(SUB_DIR)
	@echo Entry $(CURR_DIR)
	@for subdir in $(SUB_DIR); \
    	do $(MAKE) -C $$subdir all || exit 1; \
    done
	@# $(MAKE) info
	@$(MAKE) $(patsubst %.ino, %.o, $(wildcard *.ino))
	@echo Leave $(CURR_DIR)

%.o: %.ino
	@echo Compiling C++ Files $< ...
	@$(CXX) $(CXXFLAGS_INO_$(MCU)) $< -o $@
	@echo Compile Complete

.PHONY: clean
clean:
	@echo Entry $(CURR_DIR)
	@echo Deleting... $<
	@echo Deleting Completed
	@echo Leave $(CURR_DIR)

.PHONY: info
info:
	@echo Current dir: $(CURR_DIR)
	@echo ARCH: $(ARCH)
	@echo CC: $(CC)
	@echo CFLAGS: $(CFLAGS)
	@echo CXX: $(CXX)
	@echo CXXFLAGS: $(CXXFLAGS)
	@echo LD: $(LD)
	@echo LDFLAGS: $(LDFLAGS)
	@echo AS: $(AS)
	@echo ASFLAGS: $(ASFLAGS)
	@echo exclude_dirs: $(exclude_dirs)
	@echo SUBDIRS: $(SUB_DIR)