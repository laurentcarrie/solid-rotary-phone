#!/bin/bash

set -e
set -x


docker build --tag songs .

#aws lightsail push-container-image --region eu-west-3 --service-name songs --label songs --image lc-songs:latest

aws lightsail push-container-image --region eu-west-3 --service-name chansons --label chansons --image songs:latest
