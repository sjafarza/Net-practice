include ./srcs/.env
export #to load .env fully for docker

NAME = inception
SRCS	:= ./srcs/docker-compose.yml
# FLAGS	:=  -d
FLAGS	:= 

all: fclean init re
$(NAME): all

#https://stackoverflow.com/questions/2214575/passing-arguments-to-make-run
ifeq (cmd_in_doc,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

# id command from wordpress docker to figure out what's the id of www-machintruc
init:
	@ ( [ $$(cat /etc/hosts | grep $(DOMAIN_NAME) | wc -l) = 0 ] && \
		echo "Adding $(DOMAIN_NAME) to hosts" && \
		sudo echo "127.0.0.1 $(DOMAIN_NAME)" >> /etc/hosts ) || \
		true 
	@ ( [ ! -d  $(DATA_FOLDER) ] && \
		echo "Adding $(DATA_FOLDER) folders and childrens" && \
		sudo mkdir -p $(DATA_FOLDER)/$(WP_FOLDER) && \
		sudo mkdir -p $(DATA_FOLDER)/$(DB_FOLDER) ) || \ 
		true
	sudo service nginx stop

cmd_in_doc:
	sudo docker exec -it $(RUN_ARGS)
	
down:
	docker-compose -f $(SRCS) down $(FLAGS)

up:
	docker-compose -f $(SRCS) up $(FLAGS)


define tester_sep
	@printf "\n____.--.--.____.--.--.____.--.--.____.--.--.__** $(1) **__.--.--.____.--.--.____.--.--.____.--.--.____\n" ;\
	$(1)
endef
define tester_sep_no_stop_if_failure
	@printf "\n____.--.--.____.--.--.____.--.--.____.--.--.__** $(1) **__.--.--.____.--.--.____.--.--.____.--.--.____\n" ;\
	$(1) $(2) 2>/dev/null || true
endef

info: 
	$(call tester_sep,docker ps -a)
	$(call tester_sep,docker images -a)
	$(call tester_sep,docker volume ls)
	$(call tester_sep,docker volume inspect srcs_db)
	$(call tester_sep,docker volume inspect srcs_wp)
	$(call tester_sep,docker network ls)
	$(call tester_sep,docker-compose -f $(SRCS) config)

clean:
	$(call tester_sep_no_stop_if_failure,sudo docker stop, $$(sudo docker ps -qa))
	$(call tester_sep_no_stop_if_failure,docker rm, $$(docker ps -qa))
	$(call tester_sep_no_stop_if_failure,docker rmi -f, $$(docker images -qa))
	$(call tester_sep_no_stop_if_failure,docker volume rm, $$(docker volume ls -q))
	$(call tester_sep_no_stop_if_failure,docker network rm, $$(docker network ls -q))

clean_data: 
	sudo rm -rf $(DATA_FOLDER)
	
fclean: clean clean_data
	docker system prune -fa

re: 
	docker-compose -f $(SRCS) up $(FLAGS) --build

.PHONY: stop clean init cmd_in_doc re all info fclean clean_data
