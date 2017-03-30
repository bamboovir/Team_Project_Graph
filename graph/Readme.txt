1.工作任务：Build a mini social network to find the shortest chain of people who can connect two strangers.
    1.完成一个寻找社交平台两人之间最短路径的C语言命令行程序：程序名称：sc（shortest chain）{
        要求 规模：{
            The amount of coding is expected to have at least twice of an average programming project.
            估计2000行左右；
        }

        要求 input：{
        在linux平台下：sc <ENTER>(无预录入模式 )
            Please Enter 'a' to Add data To the database or Enter 's' to enter search module Enter 'q' to Quit: a <ENTER>
            You are in AddData Module if you want to stop AddData into database you can enter 'Q'       
            Tom Jerry Friend-Friend
            Jerry python ImportantFriend-Friend
            C++ C Son-Parents
            python Sanmy Friend-Friend
            Q
            Please Enter 'a' to Add data To the database or Enter 's' to enter search module Enter 'q' to Quit: s <ENTER>
            Tom Sanny <ENTER>
            No Person Named 'Sanny' in the database do you mean 'Sanmy'?
            Tom <ENTER>
            Please enter the second people name :Sanmy <ENTER>
            The Shortest Chain between Tom and Sanmy is ：
            Tom->Jerry->python->Sanmy Min:7 
            Tom Jerry Friend-Friend
            Jerry python ImportantFriend-Friend
            python Sanmy Friend-Friend
            Please Enter 'a' to Add data To the database or Enter 's' to enter search module Enter 'q' to Quit: s <ENTER>
            Tom Jerry <ENTER>
            Tom and Jerry is not strangers !
            Tom Jerry Friend-Friend
            Please Enter 'a' to Add data To the database or Enter 's' to enter search module Enter 'q' to Quit: s <ENTER>
            Tom Tom <ENTER>
            Everyone is his own friend
            Please Enter 'a' to Add data To the database or Enter 's' to enter search module Enter 'q' to Quit: q <ENTER>
            Bye~ ^_^


           (First Person)[First Name / Second Name]  (Second Person)[First Name / Second Name] (Relationship)[A to B / B to A]
           关系的重要程度设计成量值表示，例如：Friend->3 ; ImportantFriend->4;
        当然 实验性数据出来之后要求：{
                sc input <ENTER>
            Please Enter 'a' to Add data To the database or Enter 's' to enter search module Enter 'q' to Quit: q <ENTER>
            Bye~ ^_^
            }
        }
        要求 output：{
            一张图（包括所有的人节点，以及所有的关系，最短关系特殊标注）【如果不能打完，则打印部分图】
        文字版的output：写出最短关系并且写出最短的量值(最短关系即两节点之间通过量值最小)
        }
    }
    2.伪代码
    3.撰写说明文档，说明程序可以做什么，输入格式，样本输入以及如何运行它。
    4.makefile

2.任务分配：{
    1.需要的数据结构与算法有：{链表，优先队列，hashtable，Dijkstra’s algorithm}
    2.makefile：（要求写一个非常cool，功能非常炸的）
    3：图结构的定义与维护：（邻近表式）（维护包括图的创造，删除，插入，etc）
    4：Dijkstra’s algorithm主体算法的编写
    5：优先队列的编写
    6：hash table的编写
    7：撰写说明文档，说明程序可以做什么，输入格式，样本输入以及如何运行它，伪代码（即编写man文档，当用户安装了我们的程序时，sc -man即可显示结果）
    8：接入 graphviz工具（用来绘图）
    9：手工推导出实验性数据，提供input的人，而且要推导出正确答案以验证程序正确性（要求数据不能出错）：丁好
    10：main()部分以及数据导入部分；
}

3.注意事项{
    1.错误检查！！！对于不正确的信息录入彻底不接受{数据录入模块编写人注意！包括当读入一个不符合规则的字符的时候清空缓存区，让用户从新输入}
    2.是否要使用多线程技术？

}
