/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)queue.h	8.5 (Berkeley) 8/20/94
 */

/*
 * Keep this as _SYS_QUEUE_H_ so it doesn't conflict with any system headers.
 */
#ifndef _SYS_QUEUE_H_
#define _SYS_QUEUE_H_

/*
 * NULL defined here for freestanding use.
 */
#if !defined(NULL)
#if defined(__cplusplus)
#if __cplusplus >= 201103L
#define NULL nullptr
#else
#if defined(__GNUG__) && defined(__GNUC__) && __GNUC__ >= 4
#define NULL __null
#else
#if defined(__LP64__)
#define NULL 0L
#else
#define NULL 0
#endif
#endif
#endif
#else
#define NULL ((void *) 0)
#endif
#endif

#define LIST_HEAD(name, type) \
	struct name { \
		struct type *lh_first; \
	}

#define LIST_ENTRY(type) \
	struct name { \
		struct type *le_next; \
		struct type **le_prev; \
	}

#define LIST_FIRST(head) ((head)->lh_first)
#define LIST_NEXT(node, field) ((node)->field.le_next)
#define LIST_END(head) (NULL)
#define LIST_EMPTY(head) ((head)->lh_first == NULL)

#define LIST_HEAD_INITIALIZER(head) { NULL }
#define LIST_INIT(head) do { \
	(head)->lh_first = NULL; \
} while (0)

#define LIST_INSERT_HEAD(head, node, field) do { \
	if (((node)->field.le_next = (head)->lh_first) != NULL) \
	(head)->lh_first->field.le_prev = &(node)->field.le_next; \
	(head)->lh_first = (node); \
	(node)->field.le_prev = &(head)->lh_first; \
} while (0)

#define LIST_INSERT_AFTER(listnode, node, field) do { \
	if (((node)->field.le_next = (listnode)->field.le_next) != NULL) \
	(listnode)->field.le_next->field.le_prev = &(node)->field.le_next; \
	(listnode)->field.le_next = (node); \
	(node)->field.le_prev = &(listnode)->field.le_next; \
} while (0)

#define LIST_INSERT_BEFORE(listnode, node, field) do { \
	(node)->field.le_prev = (listnode)->field.le_prev; \
	(node)->field.le_next = (listnode); \
	*(listnode)->field.le_prev = (node); \
	(listnode)->field.le_prev = &(node)->field.le_next; \
} while (0)

#define LIST_FOREACH(lvar, head, field) \
	for ((lvar) = (head)->lh_first; \
			(lvar) != NULL; \
			(lvar) = (lvar)->field.le_next)

#define TAILQ_HEAD(name, type) \
	struct name { \
		struct type *tqh_first; \
		struct type **tqh_last; \
	}

#define TAILQ_ENTRY(type) \
	struct { \
		struct type *tqe_next; \
		struct type **tqe_prev; \
	}

#define TAILQ_FIRST(head) ((head)->tqh_first)
#define TAILQ_NEXT(node, field) ((node)->field.tqe_next)
#define TAILQ_END(head) (NULL)
#define TAILQ_EMPTY(head) ((head)->tqh_first == NULL)

#define TAILQ_HEAD_INITIALIZER(head) { NULL, &(head).tqh_first }

#define TAILQ_INIT(head) do { \
	(head)->tqh_first = NULL; \
	(head)->tqh_last = &(head)->tqh_first; \
} while (0)

#define TAILQ_INSERT_HEAD(head, node, field) do { \
	if (((node)->field.tqe_next = (head)->tqh_first) != NULL) \
	(head)->tqh_first->field.tqe_prev = &(node)->field.tqe_next; \
	else \
	(head)->tqh_last = &(node)->field.tqe_next; \
	(head)->tqh_first = (node); \
	(node)->field.tqe_prev = &(head)->tqh_first; \
} while (0)

#define TAILQ_INSERT_TAIL(head, node, field) do { \
	(node)->field.tqe_next = NULL; \
	(node)->field.tqe_prev = (head)->tqh_last; \
	*(head)->tqh_last = (node); \
	(head)->tqh_last = &(node)->field.tqe_next; \
} while (0)

#define TAILQ_INSERT_AFTER(head, listnode, node, field) do { \
	if (((node)->field.tqe_next = (listnode)->field.tqe_next) != NULL) \
	(listnode)->field.tqe_next->field.tqe_prev = &(node)->field.tqe_next; \
	else \
	(head)->tqh_last = &(node)->field.tqe_next; \
	(listnode)->field.tqe_next = (node); \
	(node)->field.tqe_prev = &(listnode)->field.tqe_next; \
} while (0)

#define TAILQ_INSERT_BEFORE(listnode, node, field) do { \
	(node)->field.tqe_prev = (listnode)->field.tqe_prev; \
	(node)->field.tqe_next = (listnode); \
	*(listnode)->field.tqe_prev = (node); \
	(listnode)->field.tqe_prev = &(node)->field.tqe_next; \
} while (0)

#define TAILQ_FOREACH(lvar, head, field) \
	for ((lvar) = (head)->tqh_first; \
			(lvar) != NULL; \
			(lvar) = (lvar)->field.tqe_next)

#define SLIST_HEAD(name, type) \
	struct name { \
		struct type *slh_first; \
	}

#define SLIST_ENTRY(type) \
	struct name { \
		struct type *sle_next; \
	}

#define SLIST_FIRST(head) ((head)->slh_first)
#define SLIST_NEXT(node, field) ((node)->field.sle_next)
#define SLIST_END(head) (NULL)
#define SLIST_EMPTY(head) ((head)->slh_first == NULL)

#define SLIST_HEAD_INITIALIZER(head) { NULL }
#define SLIST_INIT(head) do { \
	(head)->slh_first = NULL; \
} while (0)

#define SLIST_INSERT_HEAD(head, node, field) do { \
	(node)->field.sle_next = (head)->slh_first; \
	(head)->slh_first = (node); \
} while (0)

#define SLIST_INSERT_AFTER(listnode, node, field) do { \
	(node)->field.sle_next = (listnode)->field.sle_next; \
	(listnode)->field.sle_next = (node); \
} while (0)

#define SLIST_REMOVE_HEAD(head, field) do { \
	(head)->slh_first = (head)->slh_first->field.sle_next; \
} while (0)

#define SLIST_REMOVE_AFTER(listnode, field) do { \
	(listnode)->field.sle_next = (listnode)->field.sle_next->field.sle_next; \
} while (0)

#define SLIST_FOREACH(lvar, head, field) \
	for ((lvar) = (head)->slh_first; \
			(lvar) != NULL; \
			(lvar) = (lvar)->field.sle_next)

#define SIMPLEQ_HEAD(name, type) \
	struct name { \
		struct type *sqh_first; \
		struct type **sqh_last; \
	}

#define SIMPLEQ_ENTRY(type) \
	struct { \
		struct type *sqe_next; \
	}

#define SIMPLEQ_FIRST(head) ((head)->sqh_first)
#define SIMPLEQ_NEXT(node, field) ((node)->field.sqe_next)
#define SIMPLEQ_END(head) (NULL)
#define SIMPLEQ_EMPTY(head) ((head)->sqh_first == NULL)

#define SIMPLEQ_HEAD_INITIALIZER(head) { NULL, &(head).sqh_first }
#define SIMPLEQ_INIT(head) do { \
	(head)->sqh_first = NULL; \
	(head)->sqh_last = &(head)->sqh_first; \
} while (0)

#define SIMPLEQ_INSERT_HEAD(head, node, field) do { \
	if (((node)->field.sqe_next = (head)->sqh_first) == NULL) \
	(head)->sqh_last = &(node)->field.sqe_next; \
	(head)->sqh_first = (node); \
} while (0)

#define SIMPLEQ_INSERT_TAIL(head, node, field) do { \
	(node)->field.sqe_next = NULL; \
	*(head)->sqh_last = (node); \
	(head)->sqh_last = &(node)->field.sqe_next; \
} while (0)

#define SIMPLEQ_INSERT_AFTER(head, listnode, node, field) do { \
	if (((node)->field.sqe_next = (listnode)->field.sqe_next) == NULL) \
	(head)->sqh_last = &(node)->field.sqe_next; \
	(listnode)->field.sqe_next = (node); \
} while (0)

#define SIMPLEQ_REMOVE_HEAD(head, field) do { \
	if (((head)->sqh_first = (head)->sqh_first->field.sqe_next) == NULL) \
	(head)->sqh_last = &(head)->sqh_first; \
} while (0)

#define SIMPLEQ_REMOVE_AFTER(head, listnode, field) do { \
	if (((listnode)->field.sqe_next = (listnode)->field.sqe_next->field.sqe_next) == NULL) \
	(head)->sqh_last = &(listnode)->field.sqe_next; \
} while (0)

#define SIMPLEQ_FOREACH(lvar, head, field) \
	for ((lvar) = (head)->sqh_first; \
			(lvar) != NULL; \
			(lvar) = (lvar)->field.sqe_next)

#define STAILQ_HEAD(name, type) \
	struct name { \
		struct type *stqh_first; \
		struct type **stqh_last; \
	}

#define STAILQ_ENTRY(type) \
	struct { \
		struct type *stqe_next; \
	}

#define STAILQ_FIRST(head) ((head)->stqh_first)
#define STAILQ_NEXT(node, field) ((node)->field.stqe_next)
#define STAILQ_END(head) (NULL)
#define STAILQ_EMPTY(head) ((head)->stqh_first == NULL)

#define STAILQ_HEAD_INITIALIZER(head) { NULL, &(head).stqh_first }
#define STAILQ_INIT(head) do { \
	(head)->stqh_first = NULL; \
	(head)->stqh_last = &(head)->stqh_first; \
} while (0)

#define STAILQ_INSERT_HEAD(head, node, field) do { \
	if (((node)->field.stqe_next = (head)->stqh_first) == NULL) \
	(head)->stqh_last = &(node)->field.stqe_next; \
	(head)->stqh_first = (node); \
} while (0)

#define STAILQ_INSERT_TAIL(head, node, field) do { \
	(node)->field.stqe_next = NULL; \
	*(head)->stqh_last = (node); \
	(head)->stqh_last = &(node)->field.stqe_next; \
} while (0)

#define STAILQ_INSERT_AFTER(head, listnode, node, field) do { \
	if (((node)->field.stqe_next = (listnode)->field.stqe_next) == NULL) \
	(head)->stqh_last = &(node)->field.stqe_next; \
	(listnode)->field.stqe_next = (node); \
} while (0)

#define STAILQ_REMOVE_HEAD(head, field) do { \
	if (((head)->stqh_first = (head)->stqh_first->field.stqe_next) == NULL) \
	(head)->stqh_last = &(head)->stqh_first; \
} while (0)

#define STAILQ_REMOVE_AFTER(head, listnode, field) do { \
	if (((listnode)->field.stqe_next = (listnode)->field.stqe_next->field.stqe_next) == NULL) \
	(head)->stqh_last = &(listnode)->field.stqe_next; \
} while (0)

#define STAILQ_FOREACH(lvar, head, field) \
	for ((lvar) = (head)->stqh_first; \
			(lvar) != NULL; \
			(lvar) = (lvar)->field.stqe_next)

#endif /* _SYS_QUEUE_H_ */

