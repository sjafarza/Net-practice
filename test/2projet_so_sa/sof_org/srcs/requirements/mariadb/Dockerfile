#must contain mariadb only
FROM alpine:3.15
LABEL maintainer="user42@student.42.fr"

# Update package list and upgrade out-dated packages
RUN apk update && apk upgrade && \
    apk add --no-cache mariadb mariadb-client
RUN mkdir -p /run/mysqld && \
	chown -R mysql:mysql /run/mysqld

# Copy scripts
COPY ./tools/start.sh /

# Start initialization script
# [,] exec form for perfs
# ENTRYPOINT because CMD can be overrided, and we don't want it. Well, entrypoint can too, but less easily
ENTRYPOINT ["sh", "/start.sh"]