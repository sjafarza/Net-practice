#!/bin/sh

chown -R nginx:nginx .
while ! $(test $(sh -c "mariadb -h$DB_SERVER -u$DB_USER_NAME -p$DB_USER_PWD 2>&1 | wc -l") -eq 0); do
	echo "waiting for $DB_SERVER ..."
	sleep 2
done
echo "$DB_SERVER is now available"
if [ ! -f "/var/www/html/wordpress/index.php" ]; then
	su nginx -c sh -c ' \
	wp core download && \
	wp config create --dbname=$DB_NAME --dbuser=$DB_USER_NAME --dbpass=$DB_USER_PWD --dbhost=$DB_SERVER --dbcharset="utf8" && \
	wp core install --url=$DOMAIN_NAME --title=$WP_TITLE --admin_user=$WP_ADMIN_NAME --admin_password=$WP_ADMIN_PWD --admin_email=$WP_ADMIN_EMAIL --skip-email && \
	wp user create $WP_USER $WP_USER_EMAIL --role=author --user_pass=$WP_USER_PASSWORD'
fi 
exec php-fpm7.3 -F