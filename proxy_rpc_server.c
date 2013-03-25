/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "proxy_rpc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#define SIZE 1024

struct page_info{
    int len;
    int size;
    char* data;
};


static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
    struct page_info* p_info = userp;
    while(p_info->len+(size*nmemb)>=p_info->size){
        p_info->data = realloc(p_info->data, p_info->size*2);
        if(p_info->data == NULL){
            fprintf(stderr,"Reallocate memeory failed.\n");
        }
        p_info->size*=2;
    }
    printf("in write data, data size %d*%d\n",size,nmemb);
    memcpy(p_info->data + p_info->len, buffer, size * nmemb);
    p_info->len+=size * nmemb;
    return size * nmemb;
}

void grab_webpage(char* url, proxy_rpc_out* result)
{
    static struct page_info p_info;
    CURL* curl;
    CURLcode res;
    printf("url:\n%s\n",url);
    memset(&p_info, 0, sizeof(p_info));
    p_info.size = SIZE;
    //get a curl handler
    curl = curl_easy_init();
    if(curl == NULL){
        fprintf(stderr, "Error: could not get CURL handle.\n");
        exit(1);
    }
    p_info.data = (char*)malloc(SIZE*sizeof(char));
    //set the url for the operation
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //set the callback function
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    //userp parameter passed to write_data
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &p_info);
    //perform query
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    }
    //clean up
    curl_easy_cleanup(curl);

    result->len = p_info.len;
    result->res = p_info.data;
    printf("%s\n",result->res);
    printf("%d\n",result->len);
}
proxy_rpc_out *
proxy_rpc_proc_1_svc(proxy_rpc_in *argp, struct svc_req *rqstp)
{
	static proxy_rpc_out  result;
    char* url;
    url = argp->arg;
    grab_webpage(url,&result);
	return &result;
}


