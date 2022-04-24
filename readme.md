# memcheck

通过重载new/delete运算符实现检查内存泄漏

## compile

```shell
make
```



## run exmaple

```shell
(base) timo@wangyukang memcheck % ./run                                                           
===============MemCheck constructor======================
MALLOC 0x556b58d972c0 size= 1
MALLOC 0x556b58d973a0 size= 1
MALLOC 0x556b58d97410 size= 400
MALLOC 0x556b58d97600 size= 512
FREE 0x556b58d972c0
FREE 0x556b58d972e0
FREE 0x556b58d97410
FREE 0x556b58d975b0
===================MEMCHECK DESTRUCTOR====================
----------------leak memory info --------------
Leak Memory Address [0x556b58d973a0]
File [main.cpp] Line [9] Size [1]
Leak Memory Address [0x556b58d97600]
File [main.cpp] Line [11] Size [512]
----------------leak memory info --------------
```

