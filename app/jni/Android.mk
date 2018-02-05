# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# $Id: Android.mk 216 2015-05-18 15:28:41Z oparviai $

LOCAL_PATH := $(call my-dir)

include $(clear_VARS)

# *** Remember: Change -O0 into -O2 in add-applications.mk ***
LOCAL_MODULE    := liblame

LOCAL_MODULE_FILENAME := liblame

LOCAL_SRC_FILES := lame-jni.cpp \
../lame/bitstream.c \
../lame/encoder.c \
../lame/fft.c \
../lame/gain_analysis.c \
../lame/id3tag.c \
../lame/lame.c \
../lame/mpglib_interface.c \
../lame/newmdct.c \
../lame/presets.c \
../lame/psymodel.c \
../lame/quantize.c \
../lame/quantize_pvt.c \
../lame/reservoir.c \
../lame/set_get.c \
../lame/tables.c \
../lame/takehiro.c \
../lame/util.c \
../lame/vbrquantize.c \
../lame/VbrTag.c \
../lame/version.c


# for native audio
# LOCAL_SHARED_LIBRARIES += -lgcc 
# --whole-archive -lgcc 
# for logging
LOCAL_LDLIBS    += -llog
# for native asset manager
#LOCAL_LDLIBS    += -landroid

# Custom Flags: 
# -fvisibility=hidden : don't export all symbols
# LOCAL_CFLAGS += -fvisibility=hidden -I ../../../include -fdata-sections -ffunction-sections


LOCAL_CPPFLAGS += -fexceptions


# OpenMP mode : enable these flags to enable using OpenMP for parallel computation 
#LOCAL_CFLAGS += -fopenmp
#LOCAL_LDFLAGS += -fopenmp


# Use ARM instruction set instead of Thumb for improved calculation performance in ARM CPUs	
LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)
