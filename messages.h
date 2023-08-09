/**
 * messages.h - A Single-Header Library for Message Queues
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef MESSAGES_H
#define MESSAGES_H

#include "queues.h"

#define create_message_queue(queue, message_buffer, message_limit) \
    create_queue(queue, message_buffer, message_limit)

#define destroy_message_queue(queue) \
    destroy_queue(queue)

#define set_message_queue_item_limit(queue, new_message_limit) \
    set_queue_item_limit(queue, new_message_limit)

#define send_message(queue, message) \
    push_queue_item(queue, message)

#define jam_message(queue, message) \
    jam_queue_item(queue, message)

#define receive_message(queue, message) \
    pull_queue_item(queue, message)

#endif /* MESSAGES_H */
