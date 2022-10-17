#!/bin/sh


echo "Checking if wp-config.php exist"
if [ ! -f "/var/www/wp-config.php" ]; then
	echo "wp-config.php not found"
	echo "Configuring wordpress..."
	wp config create --dbname="$DB_NAME" --dbuser="$DB_USER" --dbpass="$DB_PASS" --dbhost=mariadb --path=/var/www/ --dbprefix=wp_
	wp core install --url="user42.42.fr" --title="user42's inception" --admin_user="$WP_ADMIN" --admin_password="$WP_ADMIN_PASS" --admin_email="$WP_ADMIN@42.fr" --path=/var/www/
	wp user create $WP_USER $WP_USER@student.42.fr --role="author" --user_pass="$WP_USER_PASS" --path="/var/www"
else
	echo "wp-config.php found, skipping configuration"
fi

exec "$@"
