#!/bin/bash

current_env="$1"
if [ "$current_env" == "" ];then
  current_env="dev_usb"
fi
use_usb=$(echo "$current_env"|grep "_usb")

. .env

CURRENT_ENV=$(echo "$current_env"|sed 's/_usb//g;')
CURRENT_HOST=$(echo "$DEVICE_NAME"|sed 's/_/-/g;')
CURRENT_IP=$(echo "$ESP_IP"|sed 's/_/-/g;')

PLATFORMIO_SRC_DIR=$(pwd)/src

PLATFORMIO_BUILD_FLAGS=""
for envvar in $(cat .env);do
  PLATFORMIO_BUILD_FLAGS="$PLATFORMIO_BUILD_FLAGS -D $envvar"
done

#echo "PLATFORMIO_SRC_DIR=$PLATFORMIO_SRC_DIR"
#echo "PLATFORMIO_BUILD_FLAGS=$PLATFORMIO_BUILD_FLAGS"
echo "CURRENT_ENV=$CURRENT_ENV"
echo "CURRENT_HOST=$CURRENT_HOST"
echo "CURRENT_IP=$CURRENT_IP"

echo "flags $PLATFORMIO_BUILD_FLAGS"

if [ "$use_usb" == "" ];then
  PLATFORMIO_BUILD_FLAGS="$PLATFORMIO_BUILD_FLAGS" \
    PLATFORMIO_UPLOAD_FLAGS="--auth=$OTA_PASSWORD" \
    PLATFORMIO_SRC_DIR="$PLATFORMIO_SRC_DIR" \
    PLATFORMIO_UPLOAD_PORT="$CURRENT_IP" \
    pio run   -e "$current_env" -t upload
else
  PLATFORMIO_BUILD_FLAGS="$PLATFORMIO_BUILD_FLAGS" \
  PLATFORMIO_SRC_DIR="$PLATFORMIO_SRC_DIR" \
  PLATFORMIO_UPLOAD_PORT="/dev/cu.usbserial-*" \
    pio run   -e "$current_env" -t upload
fi
