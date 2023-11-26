#!/usr/bin/env bash
#
# The variable CODE_SIGN_IDENTITY should be set in your shell environment.
#

TARGET_PATH=$1

# Code sign
codesign --deep --force --verify --verbose --options runtime --sign "${CODE_SIGN_IDENTITY}" ${TARGET_PATH}

# Verify
codesign -dv --verbose=4 ${TARGET_PATH}

