#!/bin/bash

source venv/bin/activate
cd src/srp
exec gunicorn -b :5000 --access-logfile - --error-logfile - websong:app
