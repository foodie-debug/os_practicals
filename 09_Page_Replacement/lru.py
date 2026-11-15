# LRU (Least Recently Used) Page Replacement

pages = [2, 2, 3, 4, 3, 5, 1, 4, 3, 1, 4, 5, 1, 2, 3, 1]
capacity = 3


def lru(pages, capacity):
    frames = []
    recent = []     # front = least recently used, back = most recently used
    faults = hits = 0
    for page in pages:
        if page in frames:
            hits += 1
            recent.remove(page)
        else:
            faults += 1
            if len(frames) == capacity:
                old = recent.pop(0)         # least recently used page
                frames.remove(old)
            frames.append(page)
        recent.append(page)
    return faults, hits


faults, hits = lru(pages, capacity)
print("LRU Page Replacement")
print("Reference String:", pages)
print("Frames:", capacity)
print("Page Faults:", faults)
print("Page Hits:", hits)
