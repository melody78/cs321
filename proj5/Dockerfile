# Dockerfile
# Solomon Himelbloom
# Tyler Chase
# 2022-04-17
# 
# For CS 321 Spring 2022
# Lab 5: Docker & Anaconda

# syntax=docker/dockerfile:1
FROM ubuntu:21.10

# 3. Install Anaconda
RUN apt-get update && apt-get install -y wget bzip2 curl

# RUN wget --quiet https://repo.anaconda.com/archive/Anaconda2-5.3.0-Linux-x86_64.sh -O Anaconda3-2021.11-Linux-x86_64.sh
# RUN chmod 777 Anaconda3-2021.11-Linux-x86_64.sh
# RUN chmod +x Anaconda3-2021.11-Linux-x86_64.sh
# RUN ./Anaconda3-2021.11-Linux-x86_64.sh -b -p /opt/conda

# RUN     ln -s /opt/conda/etc/profile.d/conda.sh /etc/profile.d/conda.sh && \
#     echo ". /opt/conda/etc/profile.d/conda.sh" >> ~/.bashrc && \
#     echo "conda activate base" >> ~/.bashrc

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
