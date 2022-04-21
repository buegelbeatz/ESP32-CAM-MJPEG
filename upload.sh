#!/bin/bash

current_env="$1"
if [ "$current_env" == "" ];then
  current_env="dev"
fi
use_usb=$(echo "$current_env"|grep "_usb")

. .env

PLATFORMIO_BUILD_FLAGS=""
for envvar in $(cat .env);do
  PLATFORMIO_BUILD_FLAGS="$PLATFORMIO_BUILD_FLAGS -D $envvar"
done

mkdir ./data 2>/dev/null
cp -f $(find . | grep /lib/ | grep json | grep /data/) ./data/ 2>/dev/null

if [ "$use_usb" == "" ];then
  PLATFORMIO_BUILD_FLAGS="$PLATFORMIO_BUILD_FLAGS" \
    PLATFORMIO_UPLOAD_FLAGS="--auth=$OTA_PASSWORD" \
    pio run  -e "$current_env" -t uploadfs
else
  PLATFORMIO_BUILD_FLAGS="$PLATFORMIO_BUILD_FLAGS" \
    pio run  -e "$current_env" -t uploadfs
fi
