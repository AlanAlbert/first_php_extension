# 第一个PHP扩展

该扩展实现一个hello_msg函数，接受一个字符串作为参数

## 安装

1. 下载源码进入根目录
2. `phpize`
3. `./configure --with-php-config=/usr/bin/php-config`
4. `make && sudo make install`

## 修改PHP配置文件php.ini

在php.ini中添加以下代码：

```ini
[hello]
extension=hello.so
```

## 调用

```php
echo hello_msg('Alan');
```

输出内容为：Hello, Alan

