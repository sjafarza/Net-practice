FROM alpine:3.13.2

ARG DB_NAME
ARG DB_USER
ARG DB_PASS
ARG ROOT_PASS

RUN apk update

RUN apk add mariadb mariadb-client

RUN mkdir /run/mysqld && chown mysql /run/mysqld

RUN mysql_install_db --user=mysql --datadir=/var/lib/mysql --auth-root-authentication-method=normal

COPY ./mariadb-server.cnf /etc/my.cnf.d/mariadb-server.cnf

RUN mysqld -umysql &\
    sleep 5 && \ 
    echo "CREATE DATABASE $DB_NAME;" | mysql &&\
    echo "CREATE USER '$DB_USER'@'%' IDENTIFIED BY '$DB_PASS';" | mysql &&\
    echo "GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'%';" | mysql &&\
    echo "FLUSH PRIVILEGES;" | mysql &&\
    echo "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('$ROOT_PASS');" | mysql
CMD ["mysqld", "--user=mysql"]

EXPOSE 3306
