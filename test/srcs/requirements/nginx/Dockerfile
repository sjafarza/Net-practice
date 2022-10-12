# debian because I don't understand alpine issues ._.
FROM debian:buster
LABEL maintainer="saray@student.42.fr"

# same cache, so must be run in the same RUN
RUN apt-get -yq update && \
	apt-get -yq upgrade && \
	apt-get install -yq nginx openssl

#set nginx config
ARG DOMAIN_NAME
ARG LOGIN
COPY ./conf/ssl.conf /etc/nginx/conf.d/ssl.conf
COPY ./tools/replace.sh /replace.sh
COPY ./tools/start.sh /start.sh
#set ARGS using env
RUN bash /replace.sh "DOMAIN_NAME" ${DOMAIN_NAME} /etc/nginx/conf.d/ssl.conf && \
	bash /replace.sh "LOGIN" ${LOGIN} /etc/nginx/conf.d/ssl.conf

# SSL configuration
RUN openssl req -new -newkey rsa:2048 -nodes \
     -out /etc/ssl/certs/$LOGIN.csr \
     -keyout /etc/ssl/private/$LOGIN.key \
     -subj "/C=DE/ST=0/L=0/O=0/CN=$LOGIN"
RUN openssl x509 -req -in /etc/ssl/certs/$LOGIN.csr -signkey /etc/ssl/private/$LOGIN.key -out /etc/ssl/certs/$LOGIN.crt

# # Start initialization script
# # [,] exec form for perfs
# # ENTRYPOINT because CMD can be overrided, and we don't want it. Well, entrypoint can too, but less easily
ENTRYPOINT ["bash", "/start.sh"]