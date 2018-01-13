s2go-php-ext
======

使用libs2go库 计算cellid和getcoving

依赖
------

* libs2go: https://github.com/fieldhood/libs2go

安装
------

```
cd s2go-php-ext
phpiize
./configure --with-php-config=php-config --with-s2go=/usr/local
make
sudo make install
```

加载配置
------
```
Edit php.ini, add extension=s2go.so
```

测试
------
```
php s2go.php
```

函数
------
```
int s2_cellid(float lat, float lng)
string s2_getcoving(float lat, float lng, float radius, int maxcell)  返回一个json字符串
```
