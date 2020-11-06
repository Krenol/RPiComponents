ARG IMG_VERSION=20201106

FROM krenol/cpp_raspbian:${IMG_VERSION}

ARG PROJECT_DIR=rpicomponents
ARG BUILD_TEST
ENV BUILD_TEST "$BUILD_TEST"

RUN apt-get install -y libeigen3-dev

WORKDIR /data

# copy files
COPY CMakeLists.txt .
COPY ./${PROJECT_DIR} ./${PROJECT_DIR}

#prepare build
RUN mkdir build && cd build && cmake ../

#build
RUN cmake --build ./build

COPY ./docker-entrypoint.sh /
ENTRYPOINT ["/docker-entrypoint.sh"]
CMD ["start"]
