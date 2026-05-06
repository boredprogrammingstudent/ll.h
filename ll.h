/*
 * MIT License
 *
 * Copyright (c) 2026 boredprogrammingstudent
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef LL_H_
#define LL_H_

#include <stdlib.h>

#define ll_insert_after(node, item)                                            \
  do {                                                                         \
    (item)->next = (node)->next;                                               \
    (item)->prev = (node);                                                     \
    if ((node)->next)                                                          \
      (node)->next->prev = (item);                                             \
    (node)->next = (item);                                                     \
  } while (0)

#define ll_insert_before(node, item)                                           \
  do {                                                                         \
    (item)->prev = (node)->prev;                                               \
    (item)->next = (node);                                                     \
    if ((node)->prev)                                                          \
      (node)->prev->next = (item);                                             \
    (node)->prev = (item);                                                     \
  } while (0)

#define ll_remove(item)                                                        \
  do {                                                                         \
    if ((item)->prev)                                                          \
      (item)->prev->next = (item)->next;                                       \
    if ((item)->next)                                                          \
      (item)->next->prev = (item)->prev;                                       \
    (item)->next = NULL;                                                       \
    (item)->prev = NULL;                                                       \
  } while (0)

#define ll_remove_and_free_next(node)                                          \
  do {                                                                         \
    if ((node)->next->next != NULL) {                                          \
      (node)->next = (node)->next->next;                                       \
      free((node)->next->prev);                                                \
      (node)->next->prev = (node);                                             \
    } else {                                                                   \
      free((node)->next);                                                      \
      (node)->next = NULL;                                                     \
    }                                                                          \
  } while (0)

#define ll_remove_and_free_prev(node)                                          \
  do {                                                                         \
    if ((node)->prev->prev != NULL) {                                          \
      (node)->prev = (node)->prev->prev;                                       \
      free((node)->prev->next);                                                \
      (node)->prev->next = (node);                                             \
    } else {                                                                   \
      free((node)->prev);                                                      \
      (node)->prev = NULL;                                                     \
    }                                                                          \
  } while (0)

#define ll_count(type, head)                                                   \
  ({                                                                           \
    size_t count    = 0;                                                       \
    type *it_##type = (head);                                                  \
    while (it_##type) {                                                        \
      it_##type = it_##type->next;                                             \
      ++count;                                                                 \
    }                                                                          \
    count;                                                                     \
  })

#define ll_count_back(type, tail)                                              \
  ({                                                                           \
    size_t count    = 0;                                                       \
    type *it_##type = (tail);                                                  \
    while (it_##type) {                                                        \
      it_##type = it_##type->prev;                                             \
      ++count;                                                                 \
    }                                                                          \
    count;                                                                     \
  })

#define ll_foreach(type, item, head)                                           \
  for (type * (item) = (head); (item) != NULL; (item) = (item)->next)

#define ll_foreach_back(type, item, tail)                                      \
  for (type * (item) = (tail); (item) != NULL; (item) = (item)->prev)

#define ll_free(head)                                                          \
  do {                                                                         \
    if ((head) != NULL) {                                                      \
      while ((head)->next != NULL) {                                           \
        (head) = (head)->next;                                                 \
        free((head)->prev);                                                    \
      }                                                                        \
      free((head));                                                            \
      (head) = NULL;                                                           \
    }                                                                          \
  } while (0)

#define ll_get_head(node)                                                      \
  do {                                                                         \
    while ((node)->prev != NULL)                                               \
      (node) = (node)->prev;                                                   \
  } while (0)

#define ll_get_tail(node)                                                      \
  do {                                                                         \
    while ((node)->next != NULL)                                               \
      (node) = (node)->next;                                                   \
  } while (0)

#endif // LL_H_
