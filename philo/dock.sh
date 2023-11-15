#!/bin/bash

docker build ../docker/build -t testing
docker run -it --rm -v=$PWD:/code testing