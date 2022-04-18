# Dockerfile
# Solomon Himelbloom
# Tyler Chase
# 2022-04-17
# 
# For CS 321 Spring 2022
# Lab 5: Docker & Anaconda

# syntax=docker/dockerfile:1
# 2. Download Ubuntu Script
FROM ubuntu:21.10

# 3. Install Anaconda
RUN apt-get update && apt-get install -y wget bzip2 
RUN wget --quiet https://repo.anaconda.com/archive/Anaconda2-5.3.0-Linux-x86_64.sh -O Anaconda3-2021.11-Linux-x86_64.sh

# 4. Script Installation Commands
RUN chmod 777 Anaconda3-2021.11-Linux-x86_64.sh
RUN chmod +x Anaconda3-2021.11-Linux-x86_64.sh
RUN ./Anaconda3-2021.11-Linux-x86_64.sh -b
# FIXME: /bin/sh: 1: conda: not found
RUN conda create -n test
RUN conda activate test
RUN conda install -c anaconda jupyter
