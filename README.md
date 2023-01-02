# Simple linear tf-lite model on Bela

This repo uses cross-compilation to build a simple linear tensorflow-lite model for Bela. The cross-compilation environment used is [xc-bela-container](https://github.com/rodrigodzf/xc-bela-container) by [@rodrigodzf](https://github.com/rodrigodzf), which runs inside a Docker container. You will need to have [Docker installed](https://docs.docker.com/get-docker/) and if you want to use VSCode, the [Remote Development Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack).

This has been tested for the Bela [v.0.5.0alpha2 experimental image](https://github.com/BelaPlatform/bela-image-builder/releases/tag/v0.5.0alpha2).

**Note**: This repo is a simplified version of [@rodrigodzf](https://github.com/rodrigodzf/)'s [DeepLearningForBela](https://github.com/rodrigodzf/DeepLearningForBela). [@rodrigodzf](https://github.com/rodrigodzf/) also wrote the `CMakeLists.txt` for this project (many thanks!). Except for the `render.cpp` file, most of the code in the `bela-tflite-linear` folder comes from [DeepLearningForBela](https://github.com/rodrigodzf/DeepLearningForBela).

## Overview

This repo has two folders: the `python` directory contains a jupyter notebook to generate a simple linear model with Tensorflow Keras and save it with the `.tflite` extension. The `bela-tf-linear` directory contains the code you will need to clone to the cross-compiler to build a program that executes the model in Bela.

## Instructions

1. Clone the cross-compilation repo to your machine (don't forget to add the `--recurse-submodules` flag):
   ```bash
   git clone --recurse-submodules https://github.com/rodrigodzf/xc-bela-container.git
   ```
2. Open the repo folder in VSCode and run the command `Remote-Containers: Reopen in Container` or click the popup when prompted. This will download the image, install a few extensions and attach the editor to the container.
3. At this stage, you can connect your Bela to your host machine. If you are using a Bela IP address different than the default one (`192.168.7.2`) you will need to modify it in the `.devcontainer/devcontainer.env` file and restart the container.
4. For the cross-compiled binaries to run in your Bela, you will need to copy the `libbelafull.so` and `armnn-dist` libraries from the Docker container into your Bela. You can do by opening an integrated terminal in VSCode (the command is `Terminal: Create New Integrated Terminal`) and typing:
   ```bash
   scp /sysroot/root/Bela/lib/libbelafull.so root@$BBB_HOSTNAME:Be
   la/lib/libbelafull.so
   scp -r /opt/armnn-dist/ root@$BBB_HOSTNAME:/opt/armnn-dist/
   ```
5. Clone this repo into the docker container:
    ```bash
    git clone https://github.com/pelinski/bela-tflite-example.git
    cd bela-tf-linear
    ```
6. You can now cross-compile the program using:
    ```bash
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain.cmake
    cd build
    cmake --build .
    ```
7. If you have the Bela connected to your host machine, the executable and the tflite model will be copied into your Bela. In your Bela, you can run the program by using:
    ```bash
    ./linear -m model.tflite
    ```


### Python instructions
If you want to modify the model in `python/model.ipynb`, you will need to first install the `ipykernel` library if you don't have it yet. You can do so by running `pip install ipykernel` in your terminal. The other 3 libraries to install (`tensorflow`, `numpy` and `matplotlib`) are pip-installed in the notebook. 


