#ifndef CORE_H
#define CORE_H

#include "trie.h"
#include "list.h"
#include "network.h"
#include "hashtable.h"

struct topic
{
    const char *name;
    List *subscribers;
};

/*
 * Main structure, a global instance will be instantiated at start, tracking
 * topics, connected clients and registered closures.
 */
struct sol
{
    HashTable *clients;
    HashTable *closures;
    Trie topics;
};

struct session
{
    List *subscriptions;
    // TODO add pending confirmed messages
};

/*
 * Wrapper structure around a connected client, each client can be a publisher
 * or a subscriber, it can be used to track sessions too.
 */
struct p_client
{
    char *client_id;
    int fd;
    struct session session;
    struct buffer buf;
};

struct subscriber
{
    unsigned qos;
    struct p_client *client;
};

struct topic *topic_create(const char *);

void topic_init(struct topic *, const char *);

void topic_add_subscriber(struct topic *, struct p_client *, unsigned, bool);

void topic_del_subscriber(struct topic *, struct p_client *, bool);

void p_topic_put(struct sol *, struct topic *);

void p_topic_del(struct sol *, const char *);

/* Find a topic by name and return it */
struct topic *p_topic_get(struct sol *, const char *);

#endif
