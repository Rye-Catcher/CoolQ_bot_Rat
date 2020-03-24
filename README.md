# CoolQ Bot Rat



本仓库是在 [CoolQ C++ SDK 项目模板](https://github.com/cqmoe/cqcppsdk-template) 的基础上编写的一个 [CoolQ](https://cqp.cc/) 应用 （所以根本就不是一个 bot, 逃)

很多灵感来自于 [BOIT](https://github.com/kernelbin/BOIT) （什么时候我的开发功底能有那么强 QAQ）



## 功能

- \#文章生成 something: 生成一篇主题为 something 的文章链接 (基于[BullshitGenerator](https://github.com/menzi11/BullshitGenerator) )

- \#runcode_c：运行C语言代码并输出结果 (支持私聊)

- \#runcode_cpp：运行C++语言代码并输出结果 (支持私聊)

- \#二次元：随机输出一条二刺螈语录来增加你的二次元浓度

- \#一言: 获取一句来自 https://hitokoto.cn/ 的话（支持私聊）

- \#音乐 名字：获取音乐的播放与下载链接,音乐名建议小写，部分特殊字符暂不支持，可加入作者或是专辑等相关信息增加辨识度, 感谢 [api 来源](https://zhuanlan.zhihu.com/p/30246788)（支持私聊）

- \#问好：收获一句来自祖安的温馨问候

- \#体温:  NUS体温申报网站 (dead people no need for admission -- Prof Tay)

- \#电竞 游戏名：获得相关游戏的赛事资讯网址

- \#新冠病毒：获得新冠病毒相关资讯，支持后接地名

- \#deadline：获取接下来的deadline （仅限Group 4 lah）



## demo

![run_c](https://ykxahq.ch.files.1drv.com/y4mhfxlJClumRa6g1wZzDrayQ7mk1WHGTLUX6K1-wTY9AU4eGxp3lcWtFUixYA2fvwvK5yf4eOeaEZoByBmEq9P0IyhiLT10JaEk4UvCvjwb14pY-uARJ1zKba94lsjR6GiUfYUK-98jh1kbI5tdEP38RXBEuC6iRtqx_OeiRf573e2zWvoVpPgpglNbLDWowt30oD4XkfcC90LfWdJ8aHbNw?width=742&height=372&cropmode=none)

![run_cpp](https://0uwdvq.ch.files.1drv.com/y4mdx76L2etWmfF8Pf9jY77onKRGFHGd1yjhlFTbEre4t_wL-8N1jJl2ZaZkOTeejP7If1M9po4wSUhyZ4CWJspBYs9MBAd6-JIWbLhmYhIAurMI2ICXz6G-8GZceJhEBsH8_2ZKjU2RYZCIzCzrrs4e9-Rehpy3PQRn9sHSgmCoxp2oSzkHmuBZ4zeUNhVGPkulX0CmVYs3kT-5q4R8GTQPA?width=776&height=355&cropmode=none)

![acg](https://1exahq.ch.files.1drv.com/y4mL0TvkWf6LO8qoZKAG1MkqUkTHfu_k2d2040BPKPOGXW0mkbrHz0e5WWSD-sBAIxPGd_O_6JuJCfT9jCBkuf9oLK2gP2cBaWQOkpx8tUFjaLmXfUTfodhAGfw2qMlD4hhYLqnsgvjBV8PSH4o-35hq2Ntuwwg1-YJOVPAiOvHFa_4nSMOQqvT7NzePYIhsvEfOGrc_Ku4eYS215Zt8R49Xg?width=742&height=396&cropmode=none)

![e-sports](https://yuxahq.ch.files.1drv.com/y4moqQJI9ppIym2z2uahZEe0IHJdV5ERIFvPy4WrUySyH2f5w-EcgIGQZFkneVj0GQIMJHXiWJz1zNr7hroro3ek0tGa2McW2q9dRNGz0yXdS1WRwx9zA-IC-4bqM013dNTdZKG_J-OwcTfNavMXigtqzaBTy4zrgsR9tFujpsGTuUd9vzOsScgrB_kS2Ieb4zPxhuyH6ErSvCQZhtTVxsFiA?width=742&height=148&cropmode=none)



## 如何运行?



开头已经说过，这个其实是CoolQ的一个应用

所以请先下载 CoolQ, 建议下载 [CoolQ Air版](https://cqp.cc/t/23253)，它已经可以实现本应用所有功能，建议使用小号作为机器人账号



关于应用使用，本仓库是以 [CoolQ C++ SDK 项目模板](https://github.com/cqmoe/cqcppsdk-template)为模板编写的，所以使用操作请 refer to [CoolQ C++ SDK 文档](https://cqcppsdk.cqp.moe/)

与文档唯一的区别在于在 **下载/克隆项目模板** 步骤中，不是下载项目模板而是下载本仓库文件; 但是同样需要下载`cqcppsdk-master`  ，并将 `cqcppsdk-master` 中的所有内容拷贝到 `CoolQ_bot_Rat\extern\cqcppsdk` 内

同样的，只能在开发模式下进行


## 注意

- 第一次运行前，你需要在 `src\main.cpp` 中修改 `code_src_path` 以及 `src_path`，分别代表你想保存运行代码的绝对路径和 `main.cpp` 的绝对路径

- 运行 .c/.cpp 是使用 `_popen` 来运行 powershell 指令及获取输出的，不知道是否对其他操作系统适用

- 若你想修改`\src`中的代码，请注意注释，C++ 坑是真的多



## To-do list & some bugs

- [ ] c/cpp 代码中出现" [ "或" ] "字符（导致无法使用数组）就会编译错误的问题 （其实是文本编码的问题）

- [ ] 显示编译错误信息， 并控制运行时间

- [x] 搞一个 http client，利用 GET 获取随机 [一言]

- [ ]  部署在服务器上

- [ ]  支持标准输入