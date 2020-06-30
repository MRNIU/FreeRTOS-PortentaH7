
# This file is a part of MRNIU/FreeRTOS-PortentaH7 (https://github.com/MRNIU/FreeRTOS-PortentaH7).
#
# Makefile for MRNIU/FreeRTOS-PortentaH7.

CURR_DIR := $(shell pwd)
ROOT_DIR := $(CURR_DIR)/../..
include $(ROOT_DIR)/Makefile.env

exclude_dirs := include
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
	@$(MAKE) $(patsubst %.c, %.o, $(wildcard *.c))
	@$(MAKE) $(patsubst %.s, %.o, $(wildcard *.s))
	@echo Leave $(CURR_DIR)

%.o: %.c
	@echo Compiling C file $< ...
	@$(CC) $(CFLAGS_FREERTOS_$(MCU)) $< -o $@
	@echo Compiling Done

%.o: %.s
	@echo Compiling .s file $< ...
	@$(CC) $(CFLAGS_FREERTOS_$(MCU)) $< -o $@
	@echo Compiling Done

.PHONY: clean
clean:
	@echo Entry $(CURR_DIR)
	@echo Deleting... $<
	@for subdir in $(SUB_DIR); \
		do $(MAKE) -C $$subdir clean || exit 1; \
	done
	@echo Deleting Completed
	@echo Leave $(CURR_DIR)

.PHONY: info
info:
	@echo Current dir: $(CURR_DIR)
	@echo MCU: $(MCU)
	@echo CC: $(CC)
	@echo CFLAGS_@MCU: $(CFLAGS_$(MCU))
	@echo CFLAGS_ARDUINOCORE_@MCU: $(CFLAGS_ARDUINOCORE_$(MCU))
	@echo CFLAGS_FREERTOS_@MCU: $(CFLAGS_FREERTOS_$(MCU))
	@echo CXX: $(CXX)
	@echo CXXFLAGS_@MCU: $(CXXFLAGS_$(MCU))
	@echo CXXFLAGS_ARDUINOCORE_@MCU: $(CXXFLAGS_ARDUINOCORE_$(MCU))
	@echo CXXFLAGS_INO_@MCU: $(CXXFLAGS_INO_$(MCU))
	@echo LDFLAGS_ALL_@MCU: $(LDFLAGS_ALL_$(MCU))
	@echo LINKERSCRIPT_@MCU: $(LINKERSCRIPT_$(MCU))
	@echo AS: $(AS)
	@echo ASFLAGS: $(ASFLAGS)
	@echo exclude_dirs: $(exclude_dirs)
	@echo SUBDIRS: $(SUB_DIR)
	@echo CORE_C@MCU_DIR: $(CORE_C$(MCU)_DIR)
	@echo CORE_C@MCU_INCLUDE_DIR: $(CORE_C$(MCU)_INCLUDE_DIR)
	@echo VARIANTS_DIR: $(VARIANTS_DIR)
	@echo MCU_@MCU: $(MCU_$(MCU))
	@echo DEFINES_@MCU: $(DEFINES_$(MCU))
	@echo INCLUDES_@MCU: $(INCLUDES_$(MCU))
	@echo FREERTOSH7_DIR: $(FREERTOSH7_DIR)
	@echo ARDUINOAPI_DIR: $(ARDUINOAPI_DIR)
	@echo DEPRECATED_DIR: $(DEPRECATED_DIR)
	@echo FREERTOS_DIR: $(FREERTOS_DIR)
	@echo FREERTOS_INCLUDE_DIR: $(FREERTOS_INCLUDE_DIR)
	@echo FREERTOS_IAR_DIR: $(FREERTOS_IAR_DIR)
	@echo STM32H7XXHAL_INCLUDE_DIR: $(STM32H7XXHAL_INCLUDE_DIR)
	@echo CMSIS_INCLUDE_DIR: $(CMSIS_INCLUDE_DIR)
	@echo OBJ: $(OBJ)
