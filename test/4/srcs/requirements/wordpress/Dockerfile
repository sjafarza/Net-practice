FROM alpine:3.13.2

WORKDIR /home

COPY ./entry.sh .

RUN apk update

RUN apk add php php7-fpm php7-mysqli php7-json php7-phar php7-iconv php7-mbstring mariadb-client

COPY ./www.conf /etc/php7/php-fpm.d/www.conf

RUN mkdir -p /var/www

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -O /usr/local/bin/wp \
 && chmod +x /usr/local/bin/wp && wp core download --path=/var/www

ENTRYPOINT ["sh", "/home/entry.sh"]

CMD ["php-fpm7", "-F"]

EXPOSE 9000
