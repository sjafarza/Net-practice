include ./srcs/.env
export #to load .env fully for docker


NAME = inception

all: $(NAME)

$(NAME):
	docker-compose --project-directory srcs -f srcs/docker-compose.yml up --build

clean:
	docker-compose --project-directory srcs -f srcs/docker-compose.yml down
	docker volume rm srcs_database
	docker volume rm srcs_website
	sudo rm -rf /home/user42/data/

re:	clean all

fclean:	clean


setup:
	sudo chmod 777 /var/run/docker.sock
	echo "127.0.0.1	user42.42.fr" | sudo tee -a /etc/hosts

