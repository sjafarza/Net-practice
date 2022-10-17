FROM alpine:3.13.2

RUN apk update && apk add --no-cache nginx openssl

WORKDIR /home/nginx

RUN openssl req -new -newkey rsa:4096 -days 365 -nodes -x509 \
    -subj "/C=FR/ST=France/L=Paris/O=Dis/CN=user42.42.fr" \
    -keyout /etc/ssl/private/user42.42.fr.key  -out  /etc/ssl/certs/user42.42.fr.crt

RUN adduser -D -g 'www' www && mkdir /www && chown -R www:www /var/lib/nginx && chown -R www:www /www && \
	mkdir -p /run/nginx

COPY ./default.conf /etc/nginx/nginx.conf

EXPOSE 443
CMD ["nginx", "-g", "daemon off;"]

EXPOSE 443
