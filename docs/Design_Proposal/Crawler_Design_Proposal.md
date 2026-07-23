# Design Proposal for Web Crawler

## Web Crawler

A web crawler is a program that automatically browses the web by following links. It starts from a seed URL, downloads pages using HTTP GET requests, extracts all links from those pages, and adds them to a queue for future processing. The crawler continues until it has visited all reachable pages or hits a defined limit (max depth or max pages).

The crawler uses the **work queue pattern**:
- A **Frontier** stores URL-depth pairs waiting to be crawled.
- A **SeenStore** tracks already visited URLs to prevent duplicates and infinite loops.
- **PageStorage** persists the crawled pages for future consumption.

---

# Section 1 – Public API

## URLDepth

The `URLDepth` structure stores a URL along with its discovery depth, which must travel together through the Frontier.

```cpp
struct URLDepth {
    string url;
    int depth;
};
```

---

## i) Frontier

**Purpose:** Stores URL-depth pairs waiting to be crawled in FIFO order.

```cpp
class Frontier {
public:
    Frontier();                    // Constructor
    void push(const URLDepth& item);      // Adds URL-depth pair to end
    URLDepth pop();                // Removes and returns from front
    bool empty() const;            // Checks if queue is empty
    int size() const;              // Returns number of pending items
};
```

**Error Handling**

- `pop()` on an empty Frontier returns an empty `URLDepth` with `depth = -1`.

---

## ii) Seen Store

**Purpose:** Tracks URLs already visited to prevent duplicates and infinite loops.

```cpp
class SeenStore {
public:
    SeenStore();                   // Constructor
    bool contains(string url);     // Checks if URL was visited
    void insert(string url);       // Marks URL as visited
    int count();                   // Returns number of visited URLs
};
```

---

## iii) Page Storage

**Purpose:** Stores crawled pages for **Project 03 Indexer** to consume.

```cpp
class PageStorage {
public:
    PageStorage(string storageDir);              // Constructor with directory path
    void storePage(string url, string html, int depth);  // Saves page
    string getPage(string url);                  // Retrieves HTML by URL
    bool hasPage(string url);                    // Checks if page exists
    int pageCount();                             // Returns total pages stored
    string getURLByID(int id);                   // Retrieves URL by numeric ID
};
```

---

## iv) Crawler

**Purpose:** Execute all components and runs the main crawl loop.

```cpp
class Crawler {
public:
    Crawler();
    void crawl(const std::string& seedURL);

private:
    Frontier frontier;
    Fetcher fetcher;
    LinkExtractor extractor;
    SeenStore seen;
    PageStorage storage;
};
```

---

# Section 2 – Internal Representation

## Working Flow of Crawler

<img width="1536" height="1024" alt="image" src="https://github.com/Vivek-01010101/Crawler/blob/main/docs/Design_Proposal/Memory_Diagrams/Crawler_wrorkflow.png?raw=true" />

---

## Frontier – Linked List Based Queue


The linked list stores elements as separate nodes.

- The **head** pointer tracks the front for **O(1)** pop operations.
- The **tail** pointer tracks the back for **O(1)** push operations.

---

## SeenStore – HashMap Based


Uses **Project 01's HashMap implementation**.

- The URL string serves as the key.
- A boolean value indicates visited status.
- Provides **O(1)** average-case lookup and insertion.

---

## PageStorage – File per Page

Each page is stored as a separate text file.

- A HashMap maps URLs to numeric IDs for fast lookup.
- `nextId` auto-increments for every new page.

## Fetcher - 

libcurl is used to fetch HTML pages. This crawler is for static sites, so here libcurl will work best. But for dynamic sites Selenium need to use.

---

## File Format

```text
File "1"

https://books.toscrape.com
0
<!DOCTYPE html><html>...
```

```text
File "2"

https://books.toscrape.com/catalogue/page-2.html
1
<!DOCTYPE html><html>...
```


---

## URL Normalization

URL normalization converts URLs to a consistent form before storing or looking them up.

Different URLs can point to the same page, causing duplicate crawling and wasted resources.

### Normalization Steps

- Convert scheme and host to lowercase.
  - `HTTPS://EXAMPLE.COM`
  - → `https://example.com`

- Remove trailing slash where redundant.
  - `https://example.com/page/`
  - → `https://example.com/page`

- Remove empty query strings.
  - `https://example.com/page?`
  - → `https://example.com/page`

- Remove fragments.
  - `https://example.com/page#section`
  - → `https://example.com/page`

### Why It Matters

Prevents the same page from being crawled multiple times.

Without normalization, several variations of the same URL would be treated as different pages.

<!-- ### What We Skip

- URL encoding variations (`%20` vs space)
- Default ports (`:80`, `:443`)
- `www` vs non-`www` differences -->

---

## Link Extraction

Link extraction finds all hyperlinks in HTML pages and extracts the `href` attribute values for crawling.

### What We Extract

- Absolute URLs
  - `https://example.com/page`

- Resolved relative URLs
  - `/about`
  - → `https://example.com/about`

- Valid `href` attributes

### What We Skip

- Fragment links (`#section`)
- JavaScript links (`javascript:void(0)`)
- `mailto:`
- `tel:`
- `ftp:`
- Empty `href` values

### Relative URL Resolution

```text
Base: https://example.com/about/

"/contact"      → https://example.com/contact
"team.html"     → https://example.com/about/team.html
"../index"      → https://example.com/index
```

### Extraction Method

String-based parsing without external libraries.

The parser finds `<a href="...">` tags and extracts the `href` value.

This approach is simple, fast, and works well for well-formed HTML.

---

# Section 3 – Complexity Estimates

| Component | Operation | Best Case | Average Case | Worst Case | Reason |
|-----------|-----------|-----------|--------------|------------|--------|
| **Frontier** | `push()` | O(1) | O(1) | O(1) | Appends to tail of linked list. No resizing needed. |
| | `pop()` | O(1) | O(1) | O(1) | Removes from head of linked list. O(1) pointer update. |
| | `empty()` | O(1) | O(1) | O(1) | Checks whether `head == nullptr`. |
| **SeenStore** | `contains()` | O(1) | O(1) | O(n) | HashMap lookup by key. Worst case is rare with a good hash function. |
| | `insert()` | O(1) | O(1) | O(n) | HashMap insertion. |
| **PageStorage** | `storePage()` | O(1) | O(1) | O(1) | File write operation plus HashMap insertion. |
| | `getPage()` | O(1) | O(1) | O(1) | HashMap lookup followed by file read. |
| | `getURLByID()` | O(1) | O(1) | O(1) | HashMap lookup. |
| **Crawler** | `crawl()` | O(P × (L + E)) | O(P × (L + E)) | O(P × (L + E)) | **P** = pages crawled, **L** = HTML length, **E** = links per page. |
<!-- | **URL Normalization** | `normalizeURL()` | O(k) | O(k) | O(k) | **k** = URL string length. String operations. |
| **Link Extraction** | `extractLinks()` | O(n) | O(n) | O(n) | **n** = HTML length. Parses the entire HTML string. | -->

---

# Section 4 – Design Decisions

## Decision 1 – Frontier Structure

### Chosen

**Linked List as Queue (FIFO)**

### Reason

- Breadth-first crawl discovers pages closer to the seed first.
- More systematic coverage of website structure.
- Linked List provides true **O(1)** push and **O(1)** pop operations.
- No resizing overhead like a DynamicArray.
- No need to compact or shift elements.
- Each node is allocated independently with no wasted capacity.
- Easier to implement and reason about.

### Rejected Alternative

**DynamicArray as Queue**

### Reason

- Periodic resizing copies all elements (**O(n)** occasionally).
- `frontIndex` approach wastes space and requires compaction.
- Memory must be reallocated and copied during growth.
- More complex implementation due to index management.
- Capacity doubling may allocate more memory than needed.

| Operation | Linked List | DynamicArray |
|-----------|-------------|--------------|
| `push()` | O(1) always | O(1) amortized, O(n) on resize |
| `pop()` | O(1) always | O(1), but leaves unused space |
| Memory | Per-node allocation | Contiguous, may overallocate |
| Cache Locality | Poor (scattered nodes) | Good (contiguous) |
| Implementation | Simpler | More complex with `frontIndex` |

---

## Decision 2 – SeenStore Structure

### Chosen

**HashMap (from Project 1 – `HashMap.h`)**

### Reason

- O(1) average-case lookup.
- Critical for crawler performance.
- At **10,000 URLs**:
  - HashMap performs about **10,000 lookups**.
  - Linked List would require roughly **100 million comparisons**.
- Prevents infinite loops on cyclic websites.

### Rejected Alternative

- Linked List
- DynamicArray

### Reason

- O(n) lookup for every URL.
- Comparison count becomes prohibitively large as the crawl grows.
- The crawler becomes unusably slow.

| Structure | Lookup Time | 10,000 URLs | 100,000 URLs |
|-----------|-------------|-------------|--------------|
| Linked List | O(n) | 100 million comparisons | 10 billion comparisons |
| HashMap | O(1) | 10,000 lookups | 100,000 lookups |

---

## Decision 3 – PageStorage Structure

### Chosen

**File-per-page with URL-to-ID HashMap**

### Reason

- Persistent storage.
- Data survives program termination.
- Compatible with the Indexer.
- Fast URL lookup using a HashMap.

### Rejected Alternative

**In-memory HashMap (URL → HTML)**

### Reason

- Data disappears when the program exits.
- Memory usage becomes enormous.
- Large crawls may consume several gigabytes of RAM.

---

## Decision 4 – Crawl Delay

### Chosen

**1 second delay between requests**

### Reason

- Respects server resources.
- Prevents IP blocking.
- Simple implementation.

### Usage

```cpp
#include <unistd.h>

sleep(1);   // 1 second delay
```

### Why Not Less?

- Too aggressive on shared servers.
- May result in IP blocking.
- Server politeness is important.

### Why Not More?

- Crawling becomes unnecessarily slow.

Example:

- 1,000 pages × 1 second
- ≈ **17 minutes**, which is acceptable.

---

## Decision 5 – Depth Tracking

### Chosen

**Store depth together with the URL in Frontier**

### Reason

- Required metadata for PageStorage.
- Enforces the maximum crawl depth.
- Useful for the Indexer as a relevance signal.

### Depth Meaning

| Depth | Meaning |
|--------|---------|
| 0 | Seed page |
| 1 | Pages linked directly from the seed |
| 2 | Pages linked from depth-1 pages |

**Default `maxDepth`:** `2`

### Why Depth = 2?

- Good for testing.
- Around **20–30 pages** on `quotes.toscrape.com`.
- Prevents unbounded crawler growth.
- Websites like Wikipedia can generate millions of URLs without a depth limit.

---

## Decision 6 – Crawl Order (Breadth-First)

### Chosen

**Breadth-First Search (FIFO)**

### Reason

- Discovers pages level by level.
- Crawls pages closer to the seed first.
- Produces a more comprehensive website snapshot.
- Makes depth tracking meaningful.

### Rejected Alternative

**Depth-First Search**

### Reason

- Goes deep before exploring sibling pages.
- May miss many important shallow pages.
- Less suitable for an Indexer that requires broad website coverage.

---
