namespace math_tools {
    template<class T>
    void swap(T* left, T* right) {
        T tmp = *left;
        *left = *right;
        *right = tmp;
    }

    template<class T>
    void bubble_sort(T* start, T* end) {
        T* max_ptr = end;
        while (max_ptr != start) {
            T* max_ptr_itr = start;
            for (T* i = start + 1; i <= max_ptr; i++) {
                T* prev = i - 1;
                if (*prev > *i) {
                    math_tools::swap(prev, i);
                    max_ptr_itr = i;
                }
            }
            max_ptr = max_ptr_itr;
        }
    }

    template<class T>
    void selection_sort(T* start, T* end) {
        for (T* i = start; i < end; i++) {
            T *min = i;
            for (T* j = i + 1; j <= end; j++) {
                if (*j < *min) {
                    min = j;
                }
            }
            if (min != i) {
                math_tools::swap(i , min);
            }
        }
    }

    template<class T>
    void insertion_sort(T* start, T* end) {
        for (T* i = start + 1; i <= end; i++) {
            T* last_sorted = i - 1;
            while (last_sorted >= start && *last_sorted > *(last_sorted + 1)) {
                math_tools::swap(last_sorted, last_sorted + 1);
                last_sorted--;
            }
        }
    }

    template<class T, uint64_t T_size = sizeof(T)>
    void fast_sort(T* start, T* end) {
        printf("start: 0x%p, end: 0x%p\n", start, end);
        printf("%d, %d\n", *start, *end);
        auto start_addr = reinterpret_cast<uint64_t>(start);
        auto end_addr = reinterpret_cast<uint64_t>(end);
        if (start_addr == end_addr) return;
        if (end_addr - start_addr == T_size) {
            if (*end < *start) {
                math_tools::swap(start, end);
            }
            return;
        }
        auto pivot = reinterpret_cast<T*>(((start_addr + end_addr) >> 1) & ~(T_size - 1));
        T *left = start, *right = end;
        while (*left < *pivot) {
            left++;
        }
        while (*right > *pivot) {
            right--;
        }
        printf("%d, %d\n", *left, *right);
        math_tools::swap(left, right);
        printf("%d, %d\n", *left, *right);
        fast_sort(start, pivot);
        fast_sort(pivot, end);
    }
}