# 工程说明
- 此工程是演示如何使用libcurl开源库的一个测试程序。

# 编译说明
## windows平台
- 创建build目录，在build目录下执行以下命令
- ```sh
    cmake -G "Visual Studio 14 2015" ..
    cmake --build ./ --config Release
    ```
## linux平台
- 创建build目录，在build目录下执行以下命令
- ```sh
    sudo cmake ..
    sudo make
    ```