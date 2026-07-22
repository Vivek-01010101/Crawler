## Specific Issue

Today's goal was to implement the Fetcher for static sites and the Frontier for the Crawler.
I faced issues with cURL blocking requests and choosing the right data structure for the Frontier queue

---

## Failed Attempt

I first tried implementing the queue using a dynamic array, but space optimization made it too complex.

---

## Code Reference

- Implemented the Fetcher for static websites.
- Added a 1-second delay between requests to avoid cURL blocking.
- Evaluated queue implementation using a dynamic array and a linked list.
- Selected a linked list and implemented the Frontier queue.

---

## Learning Reflection

- Learned how to avoid request blocking while crawling.
- Understood the trade-offs between dynamic arrays and linked lists.