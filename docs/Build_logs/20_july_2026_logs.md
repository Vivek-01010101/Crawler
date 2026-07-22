# Build Log

---

## Session 1

**Date:** July 20, 2026

**Duration:** 2 hours

**Goal:** To implement Fetcher for static sites in Crawler.

**Problem Encountered:**

- After lots of data fetched up using curl, it blocked the fetching access.

**What I Tried:**

- Search for the solution of the problem on gpt and google.

**Outcome:**

-  Used sleep of 1 second after each fetch to dont get blocked by the libcurl.

---

## Entry 2

**Date:** July 20, 2026

**Duration:** 3 hours

**Goal:** To implement Frontier for crawler.

**Problem Encountered:**

-  For frontier i have to use queue data structure, I have two options, 1st to implement queue using dynamic array or 2nd to implememt it using linked list.

**What I Tried:**

- First i tried to implemented it using dynamic array but there was issue of space optimisation, if i have to optimised space then i have to use compaction and shrinking but it will become complex and i also have to change by ds libaray dynamic array code
- Second, i tried it using Linked list, i don't have to change any code in this data structure, but it will use extra pointer to store address but i think its much better than changing my exisiting code.

**Outcome:**

- I selected linked list to implement queue data strcture and then i used my implemented queue in frontier.

---
