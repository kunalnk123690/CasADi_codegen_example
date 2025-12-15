# Use a base image suitable for C development. Ubuntu is a good choice.
FROM ubuntu:22.04

ARG USERNAME=codegen
ARG USER_UID=1000
ARG USER_GID=$USER_UID

SHELL ["/bin/bash", "-c"]

# Delete user if it exists in container (e.g Ubuntu Noble: ubuntu)
RUN if id -u $USER_UID ; then userdel `id -un $USER_UID` ; fi

# Create the user
# [Optional] Add sudo support. Omit if you don't need to install software after connecting.
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y build-essential gcc git ninja-build wget pkg-config ca-certificates
RUN apt-get install -y lsb-release gnupg curl
RUN apt-get install -y bash bash-completion
RUN apt-get install -y python3-pip libeigen3-dev
RUN pip completion --bash >> /home/$USERNAME/.bashrc
RUN pip install --upgrade pip
RUN pip install casadi
RUN pip install cmake



# ENV SHELL /bin/bash
RUN echo "export PATH=$PATH:/usr/local/bin:$HOME/.local/bin" >> /home/$USERNAME/.bashrc
RUN echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib" >> /home/$USERNAME/.bashrc

# ********************************************************
# * Anything else you want to do like clean up goes here *
# ********************************************************

# [Optional] Set the default user. Omit if you want to keep the default as root.
USER $USERNAME
CMD ["/bin/bash"]