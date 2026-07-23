## Specific Issue

Today's goal was to implement the Link Extractor, URL Normalizer, Seen Store, and Page Storage for the Crawler.
I faced issues with case-insensitive link extraction, URL normalization, and selecting suitable storage methods.

---

## Failed Attempt

Initially, the link extractor failed for uppercase HREF, and the URL normalizer only worked for https because of a fixed index.

---

## Code Reference

- Implemented the Link Extractor using string functions.
- Made HTML lowercase for case-insensitive searching.
- Fixed the URL Normalizer to support both http and https.
- Implemented Page Storage using separate .txt files.
- Implemented Seen Store using a HashMap.

---

## Learning Reflection

- Learned when to use string functions instead of complex algorithms.
- Improved URL normalization logic.
- Understood the benefits of HashMap for fast lookups.
- Learned different approaches for storing crawled pages.