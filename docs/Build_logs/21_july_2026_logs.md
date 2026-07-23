# Build Log

---

## Session 1

**Date:** July 21, 2026

**Duration:** 2 hours

**Goal:** To implement Link extractor for static sites in Crawler.

**Problem Encountered:**

- i have to choose in between regex, string functions like .find() and .substr() or string matching algorithms.
- First i implemented only using .find() function which search for "href" but if developer write this in capital my code fails.

**What I Tried:**

- Saw the Time Complexity and working of all approaches.
- Tried making the html lowercase or uppercase and then do the searching in the html.

**Outcome:**

- I got to know that .find() and .substr() works good for small length patterns. Decided to use string inbuilt functions to use in link extractor.
- I lowercase the HTML and then i searcher for the pattern in the html.

---

## Session 2

**Date:** July 21, 2026

**Duration:** 2.5 hours

**Goal:** To implement URL normalizer for crawler.

**Problem Encountered:**

-  First i implemented link normalizer and for root relative url i fixed 8 positions (https://) but in case of http it got failed becasue in my code it was written 8 not 7.

**What I Tried:**

- Changed the block of code and changed it to find (//) in the baseURL to search for start of site baseURL to sesarch for (/) in the site baseURL

**Outcome:**

- Now my code run successfully for http and https and normalize link for both.

---

## Session 3

**Date:** July 21, 2026

**Duration:** 3.5 hours

**Goal:** To implement Seen Store and Page Storage for Crawler

**Problem Encountered:**

-  I have to store downladed pages somewhere which i can access after program ends.
- Also i have to store the already visited pages so that i dont stuck in a loop of revisiting pages.

**What I Tried:**

- I have 3 approach to store pages in PageStorage, i can use simple .txt file, database or a single file which store all data
- For SeenStore i have to choose a data structure which can give me random access in very optimised time complexity.

**Outcome:**

- Currenlty I used .txt file to store each page in separate .txt file. In future i can change it to database or any other technique but for now i choosed .txt file.
- For SeenStore, I choose Hashmap data strcture where i store (url,true or false) pair, to check the url is already visited or not.

---


