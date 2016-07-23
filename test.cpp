#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "cJSON6.h"

cJSON * cJSON_CreateObject(){
	cJSON * p = (cJSON*)malloc(sizeof(cJSON));
	if (p) memset(p,0,sizeof(cJSON));
	p->type = cJSON_Object;
	return p;
}

void cJSON_AddStringToObject(cJSON *root,char *string,char *valuestring){
	cJSON *child = cJSON_CreateObject();
	cJSON *c = cJSON_CreateObject();
	child->type = cJSON_String;
	child->string = string;
	child->valuestring = valuestring;
	c = root->child;
	if(!c){
		root->child = child;
	}
	else{
		while(c && c->next){
			c = c->next;
		}
		c->next = child;
	}
}

void cJSON_AddNumberToObject(cJSON *root,char *string,double num){
	cJSON *child = cJSON_CreateObject();
	cJSON *c = cJSON_CreateObject();
	child->type = cJSON_Number;
	child->string = string;
	child->valueint = (int)num;
	child->valuedouble = num;
	c = root->child;
	if(!c){
		root->child = child;
	}
	else{
		while(c && c->next){
			c = c->next;
		}
		c->next = child;
	}
}

void cJSON_AddObjectToObject(cJSON *root,cJSON *child,char *string){
	child->string = string;
	cJSON *c = root->child;
	if(!c){
		root->child = child;
	}
	else{
		while(c && c->next){
			c = c->next;
		}
		c->next = child;
	}
}

void print_object(cJSON *root){
	depth++;
	for(int i=1;i<depth;i++){
		printf("\t");
	}
	printf("{\n");
	cJSON *c = root->child;
	while(c){
		cJSON_Print(c);
		c = c->next;
	}
	for(int i=1;i<depth;i++){
		printf("\t");
	}
	printf("}\n");
	depth--;
}

void print_number(cJSON *p){
	for(int i=0;i<depth;i++){
		printf("\t");
	}
	printf("\"%s\":",p->string);
	if(p->valueint == p->valuedouble){
			printf("%d\n",p->valueint);
	}
	if(p->valueint <p->valuedouble){
		printf("%lf\n",p->valuedouble);
	}
}

void print_string(cJSON *p){
	for(int i=0;i<depth;i++){
		printf("\t");
	}
	printf("\"%s\":",p->string);
	printf("\"%s\"\n",p->valuestring);
}

void cJSON_Print(cJSON *c){
	switch(c->type){
		case cJSON_Number:	print_number(c);break;
		case cJSON_String:	print_string(c);break;
		case cJSON_Object:	print_object(c);break;
	}
}

cJSON * makeJSON(){
	cJSON *root = NULL;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root,"name","小明");
	cJSON_AddNumberToObject(root,"age",21);
	cJSON_AddNumberToObject(root,"money",12345.67);
	cJSON *child = cJSON_CreateObject();
    cJSON_AddObjectToObject(root,child,"child");
	cJSON_AddStringToObject(child,"name2","老王");
	cJSON_AddNumberToObject(child,"age2",38);
	cJSON_AddNumberToObject(child,"money2",54321.89);
	cJSON_Print(root);
	return root;
}

cJSON * cJSON_GetObjectItem(cJSON *root,char *string){
	cJSON *c;
	if(root->child){
			c = root->child;
	}
	while(c && strcmp(c->string,string)){
			c = c->next;
		}
	return c;
}

void getJson(cJSON *root){
	cJSON *p = cJSON_GetObjectItem(root,"name");
	if(p){
		printf("name:%s\n",p->valuestring);
	}
	p = cJSON_GetObjectItem(root,"age");
	if(p){
		printf("age:%d\n",p->valueint);
	}
	p = cJSON_GetObjectItem(root,"money");
	if(p){
		printf("money:%lf\n",p->valuedouble);
	}
	if(p = cJSON_GetObjectItem(root,"child")){
		getJson(p);
	}
}

void Delete(cJSON *root){
	cJSON *c = root->child;
	Deletechild(c);
	free(root);
}

void Deletechild(cJSON *c){
	if(c->next){
		Deletechild(c->next);
	}
	free(c);
}

int main(){
	cJSON *root = makeJSON();
	getJson(root);
	Delete(root);
	return 0;
}