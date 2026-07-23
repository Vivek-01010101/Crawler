# Build Log

---

## Session 1

**Date:** July 22, 2026

**Duration:** 2.5 hours

**Goal:** To implement web crawling on user entered site.

**Problem Encountered:**

- In earlier main.cpp, i manually wrote url in the code and then my program crawl on that site.
- User cant enter url of there choice.

**What I Tried:**

- Tried getline to take input from user and check if the entered url in correct format, if it in correct format then crawl it otherwise reject it and ask user to re enter url.

**Outcome:**

- now user can enter url of there choice, a url format will be given to them which they can follow.

---

## Session 2

**Date:** July 22, 2026

**Duration:** 2.5 hours

**Goal:** To modify url normalizer and link extractor code.

**Problem Encountered:**

-  First i implemented link extractor and url normalizer for only the url i manually entered in main.cpp, so when any other site is passed in the crawler, it didn't successfully perfrom normalisation on relative url.

**What I Tried:**

- Earlier i was doing, inside .find() function i was already set the base index in case of relative url as i manually entered url in main.cpp but now if user will enter there own url then it will give wrong url for relative url.

**Outcome:**

- Now my code successfully store relative url.

---
