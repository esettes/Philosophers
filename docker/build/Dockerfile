FROM debian:bullseye-slim

WORKDIR /home/

RUN apt-get update -y && \
	apt-get install -y gcc clang build-essential make valgrind 

RUN apt-get clean && \
	rm -rf /var/lib/apt/lists/*
	
CMD ["bash"]