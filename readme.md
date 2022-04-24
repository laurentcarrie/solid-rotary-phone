
- pour copier l'image sur lightsail

    aws lightsail push-container-image --region eu-west-3 --service-name songs --label songs --image lc-songs:latest

- docker create volume toto

- lancer nginx

   docker run -d --rm -p 8080:80 --volume toto:/etc/nginx --name web nginx

- lancer songs

  docker run --rm --volume toto:/home/laurent/html-build --name songs songs:latest

