#!/bin/bash
ACAI_PATH="datasets/custom-small-fruits/preprocess-ppm/acai/"

for file in "${ACAI_PATH}"/*.ppm; do
    echo "$(basename "$file")"
done
