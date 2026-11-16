# Optimal Page Replacement

pages = [2, 2, 3, 4, 3, 5, 1, 4, 3, 1, 4, 5, 1, 2, 3, 1]
capacity = 3


def optimal(pages, capacity):
    frames = []
    faults = hits = 0
    for i, page in enumerate(pages):
        if page in frames:
            hits += 1
        else:
            faults += 1
            if len(frames) < capacity:
                frames.append(page)
            else:
                # replace the page that will be used farthest in the future
                future = pages[i + 1:]
                next_use = [
                    future.index(p) if p in future else float('inf')
                    for p in frames
                ]
                frames[next_use.index(max(next_use))] = page
    return faults, hits


faults, hits = optimal(pages, capacity)
print("Optimal Page Replacement")
print("Reference String:", pages)
print("Frames:", capacity)
print("Page Faults:", faults)
print("Page Hits:", hits)
