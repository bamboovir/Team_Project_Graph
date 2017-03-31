
<!-- TOC -->

- [How to use me ?](#how-to-use-me-)
- [工作任务](#工作任务)
- [任务分离](#任务分离)
- [任务分配](#任务分配)
    - [HuiMing's Part](#huimings-part)
        - [Two-way list](#two-way-list)
        - [hashtable](#hashtable)
        - [graph](#graph)

<!-- /TOC -->

## How to use me ?

Warning : Only work in linux system.

```
git clone https://github.com/bamboovir/Team_Project_Graph/
cd graph
make

```
----

## 工作任务
> Build a mini social network to find the shortest chain of people who can connect two strangers.


-  完成一个寻找社交平台两人之间最短路径的C语言命令行程序：程序名称：**sc**（*shortest chain*）
-  伪代码
-  撰写说明文档，说明程序可以做什么，输入格式，样本输入以及如何运行它。
-  makefile

## 任务分离

> - 需要的数据结构与算法有：{链表，优先队列，hashtable，Dijkstra’s algorithm}
> - makefile：（要求写一个非常cool，功能非常炸的）
> - 图结构的定义与维护：（邻近表式）（维护包括图的创造，删除，插入，etc）
> - Dijkstra’s algorithm主体算法的编写
> - 撰写说明文档，说明程序可以做什么，输入格式，样本输入以及如何运行它，伪代码（即编写man文档，当用户安装了我们的程序时，sc -man即可显示结果）
> - 接入 graphviz工具（用来绘图）
> - 手工推导出实验性数据，提供input的人，而且要推导出正确答案以验证程序正确性（要求数据不能出错）
> - main()部分以及数据导入部分

## 任务分配

|图数据结构 |hashtable | 优先队列 | Dijkstra_algorithm | graphviz | 说明文档 | 实验数据&main() |
-----------|----------|----------|--------------------|----------|---------|----------------|
|HuiMIng   | HuiMing | NULL | Joe Wong and zichuan | HuiMing | HuiMing and Joe Wong | Ding Hao|


---------------------------------------------------------------

### HuiMing's Part

> **Part1** :*graph data structure*

- [x] Two-way list
- [x] hashtable

------------

#### Two-way list

- This is the two macros, widely used in the linux kernel . Used to determine the struct's head pointer

```c
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER) 

#define node_to_item(node, container, member) \  
    (container *) (((char*) (node)) - offsetof(container, member))   

```

- list struct

```c
struct listnode  
{  
    struct listnode *next;  
    struct listnode *prev;  
};  

#define list_declare(name) \  
    struct listnode name = { \  
        .next = &name, \  
        .prev = &name, \  
    }  


```

#### hashtable

- hashtable struct

```c
struct hashtab_node {
	void *key;
	void *datum;
	struct hashtab_node *next;
};

struct hashtab {
	struct hashtab_node **htable;					 /* hash table */
	unsigned int size;                               /* number of slots in hash table */
	unsigned int nel;                                /* number of elements in hash table */
	unsigned int(*hash_value)(int hashtablesize, void *key);            /* hash function */
	int(*keycmp)(void *key1, void *key2);			 /* key comparison function */
};

```

#### graph

- graph struct

```c
typedef struct _VERTEX {
    int weight;
    char name[NAMEMAX];
    struct _VERTEX * _horizonal_next;
} _vertex ;

typedef struct VERTEX {
    struct listnode _vertical_list;
    struct _VERTEX VER;
} vertex;
```

> **Part2** : *graphviz工具（用来绘图）*

- Join the graphviz module to show the abstract graph in graphical form

```c
void graphviz_print( struct listnode * list) {
    struct listnode * node_v;
    vertex * ver;
    _vertex * _ver;
    int i = ver_count;
    FILE * stream = fopen("graph.dot","w");
    fprintf(stream,"digraph G {\n");
    fprintf(stream,"node [peripheries=2 style=filled color=\"#eecc80\"]");
    fprintf(stream,"edge [color=\"sienna\" fontcolor=\"green\"]");
    list_for_each(node_v,list){
        if(!i){break;}
        ver = node_to_item(node_v,vertex,_vertical_list);
        i--;
        for(_ver = ver->VER._horizonal_next ; _ver ; _ver = _ver ->_horizonal_next){
            fprintf(stream,"%s->%s[label=%d];\n",ver->VER.name,_ver->name,_ver->weight);
        }
    }
    fprintf(stream,"}");
    fclose(stream);
    system("dot -Tgif graph.dot -o graph.gif");
}
```
