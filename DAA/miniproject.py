import threading
import random
# Complexity Summary:
# 
# | Algorithm             | Time Complexity | Space Complexity |
# |-----------------------|------------------|------------------|
# | Non-Threaded Merge Sort | O(n log n)       | O(n)             |
# | Threaded Merge Sort    | O(n log n)       | O(n)             |
# 
# Notes:
# - Time complexity for both versions is O(n log n).
# - Space complexity for both versions is O(n) due to the additional space required for merging.
# - Threaded version may benefit from multi-core processors but introduces thread management overhead.
# - Non-threaded version is simpler and may perform better for smaller datasets or single-core systems.

# Function to merge two halves
def merge(left, right):
    merged = []
    left_index, right_index = 0, 0
    while left_index < len(left) and right_index < len(right):
        if left[left_index] <= right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1
    merged.extend(left[left_index:])
    merged.extend(right[right_index:])
    return merged

# Non-threaded merge sort function
def merge_sort(data):
    if len(data) <= 1:
        return data

    middle = len(data) // 2

    left_half = data[:middle]
    right_half = data[middle:]

    left_sorted = merge_sort(left_half)
    right_sorted = merge_sort(right_half)

    return merge(left_sorted, right_sorted)

# Function to implement merge sort with threading
def merge_sort_threaded(data, depth=0):
    if len(data) <= 1:
        return data

    middle = len(data) // 2

    left_half = data[:middle]
    right_half = data[middle:]

    left_sorted = []
    right_sorted = []

    def sort_left():
        nonlocal left_sorted
        print(f"{'  ' * depth}[Thread {threading.current_thread().name}] Sorting left: {left_half}")
        left_sorted = merge_sort_threaded(left_half, depth + 1)
        print(f"{'  ' * depth}[Thread {threading.current_thread().name}] Left sorted: {left_sorted}")

    def sort_right():
        nonlocal right_sorted
        print(f"{'  ' * depth}[Thread {threading.current_thread().name}] Sorting right: {right_half}")
        right_sorted = merge_sort_threaded(right_half, depth + 1)
        print(f"{'  ' * depth}[Thread {threading.current_thread().name}] Right sorted: {right_sorted}")

    left_thread = threading.Thread(target=sort_left, name=f"LeftThread-{depth}")
    right_thread = threading.Thread(target=sort_right, name=f"RightThread-{depth}")

    print(f"{'  ' * depth}[Thread {threading.current_thread().name}] Starting threads for: {data}")
    left_thread.start()
    right_thread.start()

    left_thread.join()
    right_thread.join()

    sorted_data = merge(left_sorted, right_sorted)
    print(f"{'  ' * depth}[Thread {threading.current_thread().name}] Merged: {sorted_data}")
    return sorted_data

# Example usage
if __name__ == "__main__":
    data = [random.randint(0, 100) for _ in range(16)]  # Smaller size for demonstration
    print(f"Original data: {data}")

    # Non-threaded merge sort
    non_threaded_sorted_data = merge_sort(data)
    print(f"Non-threaded sorted data: {non_threaded_sorted_data}")

    # Threaded merge sort
    threaded_sorted_data = merge_sort_threaded(data)
    print(f"Threaded sorted data: {threaded_sorted_data}")