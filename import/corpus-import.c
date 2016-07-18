
/* 
 * File:   corpus-import.c
 * Author: peter
 *
 * Created on 17 July 2016, 21:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <networkrail/corpus.h>
#include <json-c/json.h>
#include <area51/charbuffer.h>
#include <log.h>

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc!=3) {
        fprintf(stderr,"Usage:\n\tcorpus-import input output\n");
        exit(1);
    }

    loginfo("Reading %s",argv[1]);
    FILE *in = fopen(argv[1],"r");
    struct charbuffer buf;
    charbuffer_init(&buf);
    charbuffer_read(&buf,in);
    fclose(in);
    
    loginfo("Read %d characters",buf.pos);
    
    loginfo("Decoding json");
    struct json_object *obj = json_tokener_parse(buf.buffer);

    loginfo("Writing %s",argv[2]);
    FILE *out = fopen(argv[2],"w");
    
    //int res = corpus_import(in,out);
    
    
    
    fclose(out);
    return (EXIT_SUCCESS);
}

