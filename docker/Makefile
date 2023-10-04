CYAN	=\033[1;36m
LILA 	=\033[0;35m
BLUE	=\033[1;34m
GREEN	=\033[2;32m
YELLOW	=\033[1;33m
END		=\033[1;37m

DOCKER_PATH = ./build/Dockerfile

OS	:=	$(shell uname -s) 

APPNAME = philo:latest
CONTAINER = p_container

all:	header up exec

define HEADER

           ▀▄▀     ▄     ▄
        ▄███████▄  ▀██▄██▀
      ▄█████▀█████▄  ▄█
      ███████▀████████▀
       ▄▄▄▄▄▄███████▀
					
endef
export HEADER

header:
	clear
	@echo "$(BLUE)$$HEADER$(END)"

ifeq  ($(OS),Darwin)
COMP_CMD = docker-compose
COMPOSE = ./docker/docker-compose.yml
else
COMP_CMD = docker-compose
COMPOSE = ./docker/docker-compose.yml
endif

list:
	@echo "${BLUE}> Compose running containers: --------------------------"
	@$(COMP_CMD) ps -a
	@echo "${LILA}> Running containers: \t--------------------------------${END}"
	@docker ps -a
	@echo "${LILA}> Existing docker images: ------------------------------${END}"
	@docker images 
	
up:
	@$(COMP_CMD)  up -d

build:
	@docker build -f $(DOCKER_PATH) -t $(APPNAME)

down:
	@${COMP_CMD} down

delete: down
	docker rm -fv $(CONTAINER)
	docker rmi -f $(DOCKER_PATH) $(APPNAME)
#Check why delete cause error 

prune:
	docker system prune

exec:
	@docker exec -it $(CONTAINER) /bin/sh -c bash

help:
	@echo ""
	@echo "${BLUE}GENERAL COMMANDS:\033[2;37m"
	@echo "\t[ list ] \tShows images and all containers with compose."
	@echo "\t[ make ] \tExecutes 'up' and 'exec'."
	@echo "\t[ up ] \t\tBuilds images and run containers."
	@echo "\t[ exec ] \tExecutes container with bash."
	@echo "\t[ delete ] \tStop and delete containers and images."
	@echo "\t[ build ] \tBuild the image."
	@echo ""
	@echo "\t[ prune ] \tRemove: \n \
\t\t\t- all stopped containers \n \
\t\t\t- all networks not used by at least one container\n \
\t\t\t- all dangling images\n \
\t\t\t- all dangling build cache\n"
	@echo ""
	@echo "\tA normal workflow would be: [ make build ] + [ make ] "
	@echo ""
	@echo "\tThen you can [ make list ] to se all existing images and containers and"
	@echo "\tto delete the images and containers related, execute [ make down ] "
