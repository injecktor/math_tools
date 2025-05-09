namespace math_tools {
    template<class T>
    void bubble_sort(T* start, T* end) {
        if (start >= end) return;
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
        if (start >= end) return;
        for (T* i = start; i < end; i++) {
            T *min = i;
            for (T* j = i + 1; j <= end; j++) {
                if (*j < *min) {
                    min = j;
                }
            }
            if (min != i) {
                math_tools::swap(i, min);
            }
        }
    }

    template<class T>
    void insertion_sort(T* start, T* end) {
        if (start >= end) return;
        for (T* i = start + 1; i <= end; i++) {
            T* last_sorted = i - 1;
            while (last_sorted >= start && *last_sorted > *(last_sorted + 1)) {
                math_tools::swap(last_sorted, last_sorted + 1);
                last_sorted--;
            }
        }
    }

    template<class T, size_t T_size = sizeof(T)>
    void fast_sort(T* start, T* end) {
        if (start >= end) return;
        auto start_num = reinterpret_cast<size_t>(start);
        auto end_num = reinterpret_cast<size_t>(end);
        auto pivot = reinterpret_cast<T*>(((start_num + end_num) >> 1) & ~(T_size - 1));
        T *left = start, *right = end;
        while (left <= right) {
            while (*left < *pivot) left++;
            while (*right > *pivot) right--;
            if (left <= right) {
                math_tools::swap(left, right);
                left++;
                right--;
            }
        }
        fast_sort(start, left - 1);
        fast_sort(left, end);
    }

    template<class T, size_t T_size = sizeof(T)>
    void lomuto_sort(T* start, T* end) {
        if (start >= end) return;
        T* left = start;
        for (T* current = left; current < end; current++) {
            if (*current < *end) {
                math_tools::swap(current, left);
                left++;
            }
        }
        math_tools::swap(left, end);
        lomuto_sort(start, left - 1);
        lomuto_sort(left, end);
    }
    
}