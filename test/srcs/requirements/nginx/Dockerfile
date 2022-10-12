FROM	alpine:3.14


RUN		apk update
RUN		apk upgrade

#==== NGINX ===================================================================#
RUN		apk add nginx

RUN		mkdir -p /var/www/html/wordpress

COPY     ./conf/default.conf /etc/nginx/http.d/default.conf  

#==== OPENSSL =================================================================#
# https://www.digicert.com/kb/ssl-support/openssl-quick-reference-guide.htm #

RUN		apk add openssl
RUN		mkdir -p /etc/nginx/ssl

RUN		openssl req \
		-newkey rsa:4096 \
		-nodes \
          -out /etc/ssl/certs/user42.crt \ 
          -keyout /etc/ssl/private/user42.key \
          -subj "/C=DE/ST=0/L=0/O=0/CN=user42" \
          -x509 \
		-sha256 \
		-days 365 
		
#==== OPENRC ==================================================================#
RUN		apk add openrc
RUN		rc-update add nginx default

#==============================================================================#
#EXPOSE	443
CMD		["nginx", "-g", "daemon off;"]