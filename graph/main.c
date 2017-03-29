/*
   Graph
   (C) 2017  HuiMing Sun <bamboo1886@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "hashtable.h"

#define NAMEMAX 50

static int ver_count = 0;

typedef struct _VERTEX {
    int weight;
    char name[NAMEMAX];
    struct _VERTEX * _horizonal_next;
} _vertex ;

typedef struct VERTEX {
    struct listnode _vertical_list;
    struct _VERTEX VER;
} vertex;

typedef struct Relationship {
    char person_a[NAMEMAX];
    char person_b[NAMEMAX];
    int a_to_b;
    int b_to_a;
} relation;

typedef void (*vertex_foreach_function)(_vertex * ver, void *data_1,void*data_2);

static list_declare(vertex_list);

void vertex_vertical_add(struct listnode *list,vertex * ver) {
    list_init(&ver->_vertical_list);
    list_add_tail(list,&ver->_vertical_list);
}

void vertex_horizonal_add(vertex * head,_vertex * ver) {
    ver->_horizonal_next = head->VER._horizonal_next;
    head->VER._horizonal_next = ver;
}
/*
   bool vertex_del_by_name(struct listnode *list,char * name) {
   struct listnode * node;
   struct listnode * n;
   vertex * ver;
   list_for_each_safe(node,n,list){
   ver = node_to_item(node,vertex,_vertical_list);
   if(strcmp(name,ver->VER.name)) {
   printf("vertical_list_del, name : %s\n",ver->VER.name);
   list_remove(node);
   free(ver);
   ver = NULL;
   return true;
   }
   }
   return false;
   }
   */

void horizonal_free(vertex * head) {
    _vertex * tmp;

    for(tmp = head->VER._horizonal_next; tmp ; tmp = tmp->_horizonal_next) {
        free(tmp);
    }
}

void vertex_del(struct listnode *list) {
    struct listnode * node;
    struct listnode * n;
    vertex * ver;

    list_for_each_safe(node,n,list){
        if(!ver_count){break;}
        ver = node_to_item(node,vertex,_vertical_list);
        printf("vertical_list_del, name : %s\n",ver->VER.name);
        ver_count--;
        printf("ver_count = %d\n",ver_count);
        if(ver){
            horizonal_free(ver);
            list_remove(node);
            free(ver);
            ver = NULL;
        }
    }
}

void vertex_vertical_foreach(struct listnode * list,vertex_foreach_function fun,void * data) {
    struct listnode * node;
    vertex * ver;

    list_for_each(node,list){
        ver = node_to_item(node,vertex,_vertical_list);
        fun(&ver->VER,data,data);
    }
}

void vertex_all_foreach(struct listnode * list,vertex_foreach_function fun,void * data) {
    struct listnode * node_v;
    vertex * ver;
    _vertex * _ver;
    int i = ver_count;

    list_for_each(node_v,list){
        if(!i){break;}
        ver = node_to_item(node_v,vertex,_vertical_list);
        fun(&ver->VER,data,data);
        i--;

        for(_ver = ver->VER._horizonal_next ; _ver ; _ver = _ver ->_horizonal_next){
            // printf("name:%s ,weight: %d->",_ver->name,_ver->weight);
            fun(_ver,data,data);
        }

        printf("\n----------------\n");
    }
}

void vertex_print(_vertex * _ver, void * data_1,void * data_2) {
    printf("(name:%s ,weight: %d)->",_ver->name,_ver->weight);
}

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

_vertex * copy(vertex * ver, int weight) {
    _vertex * ver_copy = NULL;
    ver_copy = calloc(1,sizeof(_vertex));
    strcpy(ver_copy->name,ver->VER.name);
    ver_copy->weight = weight;
    return ver_copy;
}

void _graph_add(struct listnode * list,struct hashtab * hashtable , char * name ,int weight){

}

void graph_add(struct listnode * list,struct hashtab * hashtable , relation * re) {
    vertex * ver_a = NULL;
    vertex * ver_b = NULL;
    _vertex * ver_a_copy = NULL;
    _vertex * ver_b_copy = NULL;

    if(!strcmp(re->person_a,re->person_b)) {
        return;
    }

    ver_a= hashtab_search(hashtable,re->person_a);
    ver_b= hashtab_search(hashtable,re->person_b);
    if(!ver_a && !ver_b){
        ver_a = calloc(1,sizeof(vertex));
        ver_b = calloc(1,sizeof(vertex));
        ver_count = ver_count + 2;
        hashtab_insert(hashtable,strdup(re->person_a),ver_a);
        hashtab_insert(hashtable,strdup(re->person_b),ver_b);
        strcpy(ver_a->VER.name,re->person_a);
        strcpy(ver_b->VER.name,re->person_b);
        ver_a_copy = copy(ver_a,re->a_to_b);
        ver_b_copy = copy(ver_b,re->b_to_a);
        vertex_vertical_add(&vertex_list,ver_a);
        vertex_vertical_add(&vertex_list,ver_b);
        vertex_horizonal_add(ver_a,ver_b_copy);
        vertex_horizonal_add(ver_b,ver_a_copy);
        return ;
    } if(!ver_a && ver_b){
        ver_a = calloc(1,sizeof(vertex));
        ver_count++;
        hashtab_insert(hashtable,strdup(re->person_a),ver_a);
        strcpy(ver_a->VER.name,re->person_a);
        ver_a_copy = copy(ver_a,re->a_to_b);
        ver_b_copy = copy(ver_b,re->b_to_a);
        vertex_vertical_add(&vertex_list,ver_a);
        vertex_horizonal_add(ver_a,ver_b_copy);
        vertex_horizonal_add(ver_b,ver_a_copy);
        return ;
    }
    if(ver_a && !ver_b){
        ver_b = calloc(1,sizeof(vertex));
        ver_count++;
        hashtab_insert(hashtable,strdup(re->person_b),ver_b);
        strcpy(ver_b->VER.name,re->person_b);
        ver_a_copy = copy(ver_a,re->a_to_b);
        ver_b_copy = copy(ver_b,re->b_to_a);
        vertex_vertical_add(&vertex_list,ver_b);
        vertex_horizonal_add(ver_a,ver_b_copy);
        vertex_horizonal_add(ver_b,ver_a_copy);
        return ;
    }
    if(ver_a && ver_b){
        ver_a_copy = copy(ver_a,re->a_to_b);
        ver_b_copy = copy(ver_b,re->b_to_a);
        vertex_horizonal_add(ver_a,ver_b_copy);
        vertex_horizonal_add(ver_b,ver_a_copy);
        return ;
    }
}

void _read_from_stream(struct hashtab * hashtable, struct listnode * list , FILE * stream) {
    relation re;

    while(!feof(stream)){
        memset(&re,0,sizeof(re));

        if(fscanf(stream,"%s %s %d %d",re.person_a,re.person_b,&(re.a_to_b),&(re.b_to_a))){
            graph_add(list,hashtable,&re);
        } else { 
            perror("ERROR IN READ\n"); 
            fflush(stream);
            clearerr(stream);
            printf("Please enter again\n");
            continue;
        }
    }
}

void read_from_stdin_or_file(struct hashtab * hashtable, struct listnode * list,char * filename) {

    if(filename){
        printf("You are in Per_Read Module\n");
        FILE * stream = fopen(filename,"r");
        if(!stream){
             perror("OPEN FILE ERROR\n");
             return; 
        }
        _read_from_stream(hashtable,list,stream);
        fclose(stream);
    } else {
        printf("You are in Add_Data Module\n");
        _read_from_stream(hashtable,list,stdin);
    }

}

int main(int argc ,char** argv) {

    if(argc != 1 && argc != 2) {
        perror("Please Usage : ./a.out <file> or ./a.out \n");
        return -1;
    }

    struct hashtab * name_to_vertex_table = NULL;
    name_to_vertex_table = hashtab_create(NULL,NULL,1000);

    if(!name_to_vertex_table){
        perror("No enough memory !\n");
        return -ENOMEM;
    }

    if(argc == 1) {
        read_from_stdin_or_file(name_to_vertex_table, &vertex_list ,NULL); 
    } else {
        read_from_stdin_or_file(name_to_vertex_table, &vertex_list ,argv[1]);
    }

    //     vertex_vertical_foreach(&vertex_list,vertex_print,(void *)0);
    vertex_all_foreach(&vertex_list,vertex_print,(void *)0);
    printf("**********\n");
    graphviz_print(&vertex_list);
    //    hashtab_print_all_keys(name_to_vertex_table);
    vertex_del(&vertex_list);
    hashtab_destroy(name_to_vertex_table);
    printf("\n");
    return 0;
}
