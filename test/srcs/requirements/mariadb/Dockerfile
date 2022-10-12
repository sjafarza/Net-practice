FROM alpine:3.15
#LABEL maintainer="saray@student.42.fr"


RUN apk update && apk upgrade && \
    apk add --no-cache mariadb mariadb-client
RUN mkdir -p /run/mysqld && \
	chown -R mysql:mysql /run/mysqld


COPY ./tools/start.sh /

ENTRYPOINT ["sh", "/start.sh"]