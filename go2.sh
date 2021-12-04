#!/bin/bash

# set -e
set -x


docker rm --force web
docker rm --force songs

docker volume rm toto
#docker volume create toto



#docker run -d -it --rm --volume toto:/home/laurent/html-build --name songs songs:latest bash
#docker run -d --rm -p 8080:80 --volume toto:/usr/share/nginx/html:ro --name web nginx

docker run -d --rm -p 8080:80 --name songs songs
#docker run -d --rm --name songs songs

#docker run -d -it --rm --name songs songs:latest bash




#Record type:CNAME

#Name:
#_aa78c29a5e43c33854261cf384ba9d11
#.laurent-carrie.net.

#Value:
#_96f20d396af05a8b0e7f3735671f5559.lggsghvbmf.acm-validations.aws.
