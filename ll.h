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

#define ll_split_after(node)                                                   \
  do {                                                                         \
    (node)->next->prev = NULL;                                                 \
    (node)->next       = NULL;                                                 \
  } while (0)

#define ll_split_before(node)                                                  \
  do {                                                                         \
    (node)->prev->next = NULL;                                                 \
    (node)->prev       = NULL;                                                 \
  } while (0)

#define ll_iter(item) (item) = (item)->next
#define ll_iter_back(item) (item) = (item)->prev

#define ll_foreach(type, it, head)                                             \
  for (type * (it) = (head); (it) != NULL; ll_iter(it))

#define ll_foreach_back(type, it, tail)                                        \
  for (type * (it) = (tail); (it) != NULL; ll_iter_back(it))

#define ll_count(type, head)                                                   \
  ({                                                                           \
    size_t count = 0;                                                          \
    ll_foreach(type, it, head) { ++count; }                                    \
    count;                                                                     \
  })

#define ll_count_back(type, tail)                                              \
  ({                                                                           \
    size_t count = 0;                                                          \
    ll_foreach_back(type, it, tail) { ++count; }                               \
    count;                                                                     \
  })

#define ll_free(head)                                                          \
  do {                                                                         \
    if ((head) != NULL) {                                                      \
      if ((head)->prev != NULL)                                                \
        (head)->prev->next = NULL;                                             \
      while ((head)->next != NULL) {                                           \
        ll_iter(head);                                                         \
        (head)->prev->next = NULL;                                             \
        free((head)->prev);                                                    \
      }                                                                        \
      free((head));                                                            \
      (head) = NULL;                                                           \
    }                                                                          \
  } while (0)

#define ll_set_head(item)                                                      \
  do {                                                                         \
    while ((node)->prev != NULL)                                               \
      ll_iter_back(node);                                                      \
  } while (0)

#define ll_set_tail(item)                                                      \
  do {                                                                         \
    while ((node)->next != NULL)                                               \
      ll_iter(node);                                                           \
  } while (0)

#define ll_get_head(type, node)                                                \
  ({                                                                           \
    type *it = (node);                                                         \
    ll_set_head(it);                                                           \
    it;                                                                        \
  })

#define ll_get_tail(type, node)                                                \
  ({                                                                           \
    type *it = (node);                                                         \
    ll_set_tail(it);                                                           \
    it;                                                                        \
  })

#define ll_make_cll(type, node)                                                \
  do {                                                                         \
    type *head = node;                                                         \
    ll_set_head(head);                                                         \
    type *tail = node;                                                         \
    ll_set_tail(tail);                                                         \
    head->prev = tail;                                                         \
    tail->next = head;                                                         \
  } while (0)

/*

===========================

---   ---   CLL   ---   ---

===========================

 */

#define cll_insert_after(node, item) ll_insert_after(node, item)
#define cll_inster_before(node, item) ll_insert_before(node, item)
#define cll_remove(item) ll_remove(item)
#define cll_remove_and_free_next(node) ll_remove_and_free_next(node)
#define cll_remove_and_free_prev(node) ll_remove_and_free_prev(node)
#define cll_split_after(node) ll_split_after(node)
#define cll_split_before(node) ll_split_before(node)
#define cll_iter(item) ll_iter(item)
#define cll_iter_back(item) ll_iter_back(item)

#define cll_foreach(type, it, node)                                            \
  for (type *it = (node); it != NULL;                                          \
       it       = ((it->next == (node)) ? NULL : it->next))

#define cll_foreach_back(type, it, node)                                       \
  for (type *it = (node); it != NULL;                                          \
       it       = ((it->prev == (node)) ? NULL : it->prev))

#define cll_count(type, node)                                                  \
  ({                                                                           \
    size_t count = 0;                                                          \
    cll_foreach(type, it, head) { ++count; }                                   \
    count;                                                                     \
  })

#define cll_count_back(type, tail)                                             \
  ({                                                                           \
    size_t count = 0;                                                          \
    cll_foreach_back(type, it, tail) { ++count; }                              \
    count;                                                                     \
  })

#define cll_free(cll) ll_free(cll)

#endif // LL_H_
