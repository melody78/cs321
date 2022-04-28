# Dockerfile
# Solomon Himelbloom
# Tyler Chase
# 2022-04-17
# 
# For CS 321 Spring 2022
# Lab 5: Docker & Anaconda

# syntax=docker/dockerfile:1
FROM ubuntu:21.10

# 3. Update Packages
RUN apt-get update && apt-get install -y bzip2 curl

# 4. Installation Commands
RUN curl -L -o ~/miniconda.sh -O  https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh  && \
    chmod +x ~/miniconda.sh && \
    ~/miniconda.sh -b -p /opt/conda && \     
    rm ~/miniconda.sh && \
    /opt/conda/bin/conda clean -ya 

ENV PATH /opt/conda/bin:$PATH
RUN conda init zsh
RUN conda create -n cs321
RUN conda update -n base -c defaults conda
RUN conda install -c anaconda jupyter
