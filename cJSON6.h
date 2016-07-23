#define cJSON_Number 1
#define cJSON_String 2
#define cJSON_Object 3
int depth=0;

typedef struct cJSON {
	struct cJSON *next;
	struct cJSON *child;		
	int type;				
	char *valuestring;		
	int valueint;				
	double valuedouble;		
	char *string;				
} cJSON;

extern cJSON * cJSON_CreateObject();

extern void cJSON_AddStringToObject(cJSON *root,char *string,char *valuestring);

extern void cJSON_AddNumberToObject(cJSON *root,char *string,double num);

extern void cJSON_AddObjectToObject(cJSON *root,cJSON child);

extern void print_object(cJSON *root);

extern void print_number(cJSON *p);

extern void print_string(cJSON *p);

extern void cJSON_Print(cJSON *c);

extern cJSON * cJSON_GetObjectItem(cJSON *root,char *string);

extern void Delete(cJSON *root);

extern void Deletechild(cJSON *c);

