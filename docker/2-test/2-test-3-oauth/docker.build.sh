#!/bin/bash
# This file is a part of quicksave project.
# Copyright 2017 Aleksander Gajewski <adiog@quicksave.io>.

cp ../2-test-0-storage/storage_id_rsa* .

cat Dockerfile.in | envsubst > Dockerfile
sudo docker build --no-cache -t quicksave/test-oauth .

rm Dockerfile
rm storage_id_rsa*

