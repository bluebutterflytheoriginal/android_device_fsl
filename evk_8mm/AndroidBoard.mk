LOCAL_PATH := $(call my-dir)

include $(FSL_PROPRIETARY_PATH)/fsl-proprietary/media-profile/media-profile.mk
include $(FSL_PROPRIETARY_PATH)/fsl-proprietary/sensor/fsl-sensor.mk
include device/fsl/evk_8mm/AndroidUboot.mk
include device/fsl/evk_8mm/AndroidTee.mk
