# Document Search Engine

## Overview

This project is a document search engine written in C.

The goal is to efficiently search a collection of text documents without scanning every document for every query.

Instead of reading all files during each search, the program builds an inverted index backed by a hash table and performs fast lookups when the user searches for a word.

---

## Problem

A simple search engine can search documents by scanning every file:

Query
→ Open every document
→ Read every document
→ Search for matches

This approach becomes increasingly expensive as the number of documents grows.

This project solves that problem by building an index once and reusing it for future searches.

---

## Features

- Index individual text files
- Index entire folders
- Tokenize and normalize text
- Hash-table-based word lookup
- Inverted index storage
- Interactive command-line interface
- Relevance ranking using word frequency
- Automated tests

---

## Data Structures

### Hash Table

Used for quick word lookup.

A word is hashed into a bucket, reducing the amount of searching required to find an entry.

### Inverted Index

Maps:

word → documents

Example:

cat → doc1.txt, doc3.txt

dog → doc1.txt, doc2.txt

### Frequency Tracking

Each document stores the number of occurrences of a word.

Example:

cat

- doc2.txt (3 occurrences)
- doc3.txt (2 occurrences)
- doc1.txt (1 occurrence)

This allows results to be ranked by relevance.

---

## Performance

### Old Approach

Every word searched:

Search
→ Scan every document
→ Read every document

### Indexed Approach

Startup:
→ Build index once

Every query:
→ Hash lookup
→ Retrieve matching documents

Trade-off:

- Takes longer intially because of initial indexing
- Much faster searches afterwards

---

## Usage

Compile:

```bash
gcc main.c hashtable.c -o search_engine
```

Run:

```bash
./search_engine
```

Enter a folder path when prompted.

Example:

```text
Enter folder to index: sample_files

search> cat

Results for 'cat'

- doc2.txt (3 occurrences)
- doc3.txt (2 occurrences)
- doc1.txt (1 occurrence)
```

---

## Testing

The project includes tests for:

- Word insertion
- Searching
- Document indexing
- Folder indexing
- Frequency counting
- Result ranking

---

## What I Learned

Through this project I learned:

- What hashtables and inverted index are
- How hash tables improve lookup performance
- How inverted indexes allow quicker search
- How to break a large problem into smaller engineering tasks
- How to design and test hashtables and inverted index
- How to apply those concepts in a word document conext
- How to build a complete system from problem to solution