pages = [2, 2, 3, 4, 3, 5, 1, 4, 3, 1, 4, 5, 1, 2, 3, 1]
capacity = 3
def fifo(pages, capacity):
    frames = []
    pointer = faults = hits = 0
    for page in pages:
        if page in frames:
            hits += 1
        else:
            faults += 1
            if len(frames) < capacity:
                frames.append(page)
            else:
                frames[pointer] = page
                pointer = (pointer + 1) % capacity
    return faults, hits
faults, hits = fifo(pages, capacity)
print("FIFO Page Replacement")
print("Reference String:", pages)
print("Frames:", capacity)
print("Page Faults:", faults)
print("Page Hits:", hits)
