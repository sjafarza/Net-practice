FROM debian:buster 
#LABEL maintainer="saray@student.42.fr"

#ARG PHP_VERSION

RUN apt-get -y update && \
	apt-get -y upgrade && \
	apt-get install -y \
		php7.3 \
		php7.3-mysql \
		php7.3-fpm \
		php7.3-gd \
		php7.3-mbstring \
		php7.3-zip \
		mariadb-client \
		wget


#user:group in debian is www-data
RUN mkdir -p /var/www/html
RUN chown -R www-data:www-data /var/www/html 
# https://medium.com/swlh/wordpress-deployment-with-nginx-php-fpm-and-mariadb-using-docker-compose-55f59e5c1a

RUN useradd  nginx
# RUN userdel -f www-data && useradd -u 82 www-data

COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/ 
COPY ./conf/php-fpm.conf /etc/php/7.3/fpm/

# ! Install wp-cli, using it to build, configure wordpress
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
	chmod +x wp-cli.phar && \
	mv wp-cli.phar /usr/local/bin/wp

WORKDIR /var/www/html/wordpress
COPY ./tools/start.sh /start.sh
# # Start initialization script
# # [,] exec form for perfs
# # ENTRYPOINT because CMD can be overrided, and we don't want it. Well, entrypoint can too, but less easily
ENTRYPOINT ["sh", "/start.sh"]