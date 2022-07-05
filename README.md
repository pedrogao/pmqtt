# pmqtt

> simple mqtt in memory implement by C.

## setup

### prequirements

```sh
sudo yum install libuuid libuuid-devel
```

### steps

```sh
$ git clone https://github.com/pedrogao/pmqtt
$ cd pmqtt && mkdir build && cd build
$ cmake .. -DDEBUG=off
$ make -j $(nproc)
$ ./app/pmqtt
```

## references

- [An MQTT broker from scratch](https://codepr.github.io/posts/sol-mqtt-broker/)
- [pedantic](https://stackoverflow.com/questions/2855121/what-is-the-purpose-of-using-pedantic-in-the-gcc-g-compiler)
- [minunit](https://github.com/siu/minunit)
- [uuid](https://stackoverflow.com/questions/51053568/generating-a-random-uuid-in-c)
