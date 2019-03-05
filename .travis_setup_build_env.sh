#!/bin/sh

set -ex

mkdir -p ${TOOLCHAIN_DIR}
cd ${TOOLCHAIN_DIR}

wget --no-verbose -O xtensa-esp32-elf.tar.gz "${ESP32_TOOLCHAIN_URL}"
tar zxf xtensa-esp32-elf.tar.gz
rm xtensa-esp32-elf.tar.gz

mkdir -p ${SDKS_DIR}
cd ${SDKS_DIR}


wget --no-verbose -O esp32_idf.zip "${ESP32_IDF_URL}"
unzip -q esp32_idf.zip
mv esp-idf-* "esp-idf"
rm esp32_idf.zip
