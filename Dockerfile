#FROM ubuntu:20.04
FROM nginx:latest

#RUN adduser laurent

#WORKDIR /home/laurent


#RUN apt-get update
#RUN apt-get install -y python3
#RUN apt-get install -y virtualenv
#RUN apt-get install -y postgresql-client

#COPY requirements.txt requirements.txt
#COPY src/srp/requirements.txt requirements-web.txt

#RUN virtualenv venv --python=`which python`
#RUN venv/bin/pip install -r requirements.txt
#RUN venv/bin/pip install -r requirements-web.txt
#RUN venv/bin/pip install gunicorn



# COPY app app
#COPY . .

#ENV FLASK_APP websong.py

#RUN chown -R laurent:laurent .
#USER laurent

#EXPOSE 80


COPY html-build /usr/share/nginx/html
COPY source/welcome.html /usr/share/nginx/html/index.html

#ENTRYPOINT ["bash", "export.sh"]


