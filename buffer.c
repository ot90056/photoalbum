/*
 * buffer.c
 * thread safe implementation
 *
 * 11/1/2022
 * Kevin Gonzales
 */
#include "buffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

enum {
    DESIRED_CHANNELS = 4, /* RGBA 32bit */
};

typedef struct texture_node_t {
    struct texture_node_t * prev;
    struct texture_node_t * next;
    texture_t texture;
} texture_node_t;

/* ~ private .data ~ */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static texture_node_t * dll_textures = NULL; /* dll: doubly linked list. O(1) free and easy iteration for reset */
static texture_node_t * dll_tail = NULL; /* insertion O(1) */

/* ~ private .text ~ */
static texture_node_t * parse_node(const image_node * node)
{
    texture_node_t * ret_val = NULL;
    char * file_location = NULL;
    size_t length, sanity;
    int nchannels;
    
    if (!node || !node->location)
    {
        printf("::BUFFER_INTERNAL_ERROR::\nInvalid image_node * node\n\n");
        goto clean;
    }
    
    length = strlen(node->name) + strlen(node->location) + 2; /* room for '\' */
    file_location = (char*)malloc(length);
    if (!file_location)
    {
        printf("::BUFFER_INTERNAL_ERROR::\nOut of memory\n\n");
        goto clean;
    }
    
    /* get nul terminated file location */
    sanity = strlcpy(file_location, node->location, length);
    if (sanity >= length)
    {
        printf("::BUFFER_INTERNAL_ERROR::\nUnexpected strlcpy error\n\n");
        goto clean;
    }
    if (file_location[sanity-1] != '\\') /* add '\' to end of location if not already there */
    {
        file_location[sanity] = '\\';
        file_location[sanity+1] = '\0';
    }
    sanity = strlcat(file_location, node->name, length);
    if (sanity >= length)
    {
        printf("::BUFFER_INTERNAL_ERROR::\nUnexpected strlcat error\n\n");
        goto clean;
    }
    
    /* parse image */
    ret_val = (texture_node_t*)malloc(sizeof(texture_node_t));
    if (!ret_val)
    {
        printf("::BUFFER_INTERNAL_ERROR::\nOut of memory\n\n");
        goto clean;
    }
    
    ret_val->texture.data = stbi_load(file_location, &ret_val->texture.width, &ret_val->texture.height, &nchannels, DESIRED_CHANNELS);
    if (!ret_val->texture.data)
    {
        printf("::BUFFER_INTERNAL_ERROR::\nstbi failure... potentially invalid image_node\n\n");
        free((void*)ret_val);
        goto clean;
    }
    
clean:
    if (file_location)
        free((void*)file_location);
    return ret_val;
}

/* ~ public .text ~ */
const texture_t * buffer_load_image(const image_node * node)
{
    texture_node_t * new_node;
    
    if (!node)
    {
        printf("::BUFFER_ERROR::\nInvalid image_node * node\n\n");
        return NULL;
    }
    
    if (!(new_node = parse_node(node)))
        return NULL;
    
    /* insert */
    pthread_mutex_lock(&mutex);
    
    new_node->prev = NULL;
    new_node->next = NULL;
    if (!dll_tail)
    {
        dll_textures = new_node;
        dll_tail = dll_textures;
    }
    else
    {
        new_node->prev = dll_tail;
        dll_tail->next = new_node;
        dll_tail = new_node;
    }
    
    pthread_mutex_unlock(&mutex);
    
    return &new_node->texture;
}

void buffer_free_image(const texture_t * texture)
{
    if (!texture)
    {
        printf("::BUFFER_ERROR::\nAttempt to free null pointer\n\n");
        return;
    }
    
    pthread_mutex_lock(&mutex);
    
#ifndef NDEBUG
    texture_node_t * iterator = dll_textures;
    while (iterator != NULL)
    {
        if (&iterator->texture == texture)
            break;
        iterator = iterator->next;
    }
    assert(!iterator && dll_textures && "::BUFFER_DEBUG_ERROR::\n"
           "Attempt to call free on invalid address, this WILL be fatal on release!");
#endif
    /* [texture_node_t]
     *      -> pointer
     *      -> pointer
     *      -> [texture_t]
     * temp uses the difference between the sizeof [texture_node_t]
     * and [texture_t] to get the header struct's base address */
    texture_node_t * temp = (texture_node_t *)((char*)texture - (sizeof(texture_node_t) - sizeof(texture_t)));
    if (temp == dll_textures) /* delete the root node */
    {
        if ((dll_textures = dll_textures->next))
            dll_textures->prev = NULL;
        else
            dll_tail = dll_textures;
    }
    else if (temp == dll_tail) /* delete the tail node */
    {
        temp->prev->next = NULL;
        dll_tail = temp->prev;
    }
    else /* delete an internal node */
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
    }
    stbi_image_free((void*)temp->texture.data);
    free((void*)temp);
    
    pthread_mutex_unlock(&mutex);
}

void buffer_reset()
{
    pthread_mutex_lock(&mutex);
    
    while (dll_textures != NULL)
    {
        texture_node_t * next = dll_textures->next;
        stbi_image_free((void*)dll_textures->texture.data);
        free((void*)dll_textures);
        dll_textures = next;
    }
    dll_tail = dll_textures;
    
    pthread_mutex_unlock(&mutex);
}
